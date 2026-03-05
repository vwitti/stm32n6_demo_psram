/*******************************************************************************
 * Copyright (c) 2006, 2024 ACIN, Profactor GmbH, AIT, fortiss GmbH,
 *                          Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Alois Zoitl, Gerhard Ebenhofer, Thomas Strasser, Rene Smodic,
 *  Martin Melik Merkumians, Ingo Hegny, Filip Andren - initial API and implementation and/or initial documentation
 *  Tarik Terzimehic - make OPC UA server port setable from the command line
 *******************************************************************************/

#include <stdio.h>
#include <signal.h>
#include "forte/forteinstance.h"
#include "forte/arch/forte_architecture.h"
#include "forte/util/mainparam_utils.h"


#include "forte/ASGEVO_PACKAGE/asgevo_package_config.h"
#include "forte/ASGEVO_PACKAGE/iosubsystem.h"
#include "forte/ASGEVO_PACKAGE/events.h"
#include "forte/ASGEVO_PACKAGE/sensors.h"
#include "forte/ASGEVO_PACKAGE/valves.h"

#if USER_4DIAC_X86_FORTE_TOUCHGFX == 1
#include "forte/ASGEVO_PACKAGE/4diac/kv11_client.h"
#endif

namespace {
  forte::C4diacFORTEInstance g4diacForteInstance;

  void endForte(int) {
    g4diacForteInstance.triggerDeviceShutdown();
  }

  void callOnExit() {
    forte::arch::CForteArchitecture::deinitialize();
  }

  void hookSignals() {
    signal(SIGINT, endForte);
    signal(SIGTERM, endForte);
#ifndef WIN32
    signal(SIGHUP, endForte);
#endif
  }
} // namespace

int main(int argc, char *arg[]) {

  printf("------------------------------------------------------------------\n");
  printf("                      ASG-EVO 4diac Simulator                     \n");
  printf("------------------------------------------------------------------\n");
  if (auto result = forte::arch::CForteArchitecture::initialize(argc, arg); result != 0) {
    return result;
  }

#if USER_4DIAC_X86_FORTE_TOUCHGFX == 1
  	printf("USER_4DIAC_X86_FORTE_TOUCHGFX_IP=%s\n", USER_4DIAC_X86_FORTE_TOUCHGFX_IP);
  	printf("USER_4DIAC_X86_FORTE_TOUCHGFX_IP=%d\n", USER_4DIAC_X86_FORTE_TOUCHGFX_PORT);
  	printf("USER_4DIAC_X86_FORTE_TOUCHGFX_UPDATE=%d\n", USER_4DIAC_X86_FORTE_TOUCHGFX_UPDATE);
    if (kv11_client_start(USER_4DIAC_X86_FORTE_TOUCHGFX_IP, USER_4DIAC_X86_FORTE_TOUCHGFX_PORT, USER_4DIAC_X86_FORTE_TOUCHGFX_UPDATE) != 0) {
        printf("kv11_client_start failed\n");
        return 1;
    }
    printf("kv11_client running...\n");
#endif

  // StartpThread for Sensor Simulation Timer
  // ----------------------------------------
  sim_thread_t sim = {0};

  IoSubSystemValves_Init();
  IoSubSystemSensor_Init();
  IoSubSystemEvents_Init();
  IoSubSystem_Simulation_Init();

  int err = SensorSim_pthread_start(&sim, /*use_realtime=*/0, /*prio=*/20);
  if (err) {
    printf("start failed: %d\n", err);
    return 1;
  }

  printf("SensorSim simulation timer running...\n");
  // ---------------------------------------

  std::atexit(callOnExit);

  hookSignals();

  const std::string ipPort = forte::util::CommandLineParser::parseCommandLineArguments(argc, arg);
  if (ipPort.empty() || ipPort.find(':') == std::string::npos) {
    //! Lists the help for FORTE
    forte::util::CommandLineParser::listHelp();
    return -1;
  }

  if (!g4diacForteInstance.startupNewDevice(ipPort)) {
    DEVLOG_INFO("Could not start a new device\n");
    return -1;
  }

  DEVLOG_INFO("FORTE is up and running\n");
  g4diacForteInstance.awaitDeviceShutdown();

#if USER_4DIAC_X86_FORTE_TOUCHGFX == 1
  kv11_client_stop();
  printf("kv11_client_start stopped\n");
#endif

  // Stop simulation on exit
  // ----------------------------------------
  SensorSim_pthread_stop(&sim);
  printf("SensorSim simulation timer stopped...\n");
  // ----------------------------------------

  DEVLOG_INFO("FORTE finished\n");

  return 0;
}
