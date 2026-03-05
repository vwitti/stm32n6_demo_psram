/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: SFB_ASGEVO_SET_STD_VALVES
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2026-02-21/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/SFB_ASGEVO_SET_STD_VALVES_fbt.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

#if defined(FORTE_NO_SIMULATOR)
	#include "Common/Inc/IoSubSystem/valves.h"
#else
	#include "forte/ASGEVO_PACKAGE/valves.h"
	#include "forte/ASGEVO_PACKAGE/sensors.h"
	#include "forte/ASGEVO_PACKAGE/events.h"
#endif

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:nWZEaWgPwaMzrgrfacbeUSjfAvWuUNc73rdV2rhX8h0HgpEJLtg52_m-CygrtzGKg4IfbrCdv7U5y1U5mcJwxQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID, "RSP"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID, "IND"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"QI"_STRID, "PARAMS"_STRID, "SD"_STRID, "LOWER"_STRID, "SET"_STRID, "PULL"_STRID, "PUSH"_STRID, "BL_EXT"_STRID, "BL_RET"_STRID, "STAB_EXT"_STRID, "STAB_RET"_STRID};
    const auto cDataOutputNames = std::array{"QO"_STRID, "STATUS"_STRID, "RD"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = cEventInputTypeIds,
        .mEONames = cEventOutputNames,
        .mEOTypeNames = cEventOutputTypeIds,
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SFB_ASGEVO_SET_STD_VALVES, "ASGEVO_PACKAGE::SFB_ASGEVO_SET_STD_VALVES"_STRID, TypeHash)

  FORTE_SFB_ASGEVO_SET_STD_VALVES::FORTE_SFB_ASGEVO_SET_STD_VALVES(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CFunctionBlock(paContainer, cFBInterfaceSpec, paInstanceNameId),
      var_QI(0_BOOL),
      var_PARAMS(u""_WSTRING),
      var_SD(CIEC_ANY_VARIANT()),
      var_LOWER(0_BOOL),
      var_SET(0_BOOL),
      var_PULL(0_BOOL),
      var_PUSH(0_BOOL),
      var_BL_EXT(0_BOOL),
      var_BL_RET(0_BOOL),
      var_STAB_EXT(0_BOOL),
      var_STAB_RET(0_BOOL),
      var_QO(0_BOOL),
      var_STATUS(u""_WSTRING),
      var_RD(CIEC_ANY_VARIANT()),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_IND(*this, 2),
      conn_QI(nullptr),
      conn_PARAMS(nullptr),
      conn_SD(nullptr),
      conn_LOWER(nullptr),
      conn_SET(nullptr),
      conn_PULL(nullptr),
      conn_PUSH(nullptr),
      conn_BL_EXT(nullptr),
      conn_BL_RET(nullptr),
      conn_STAB_EXT(nullptr),
      conn_STAB_RET(nullptr),
      conn_QO(*this, 0, var_QO),
      conn_STATUS(*this, 1, var_STATUS),
      conn_RD(*this, 2, var_RD) {
  };

  void FORTE_SFB_ASGEVO_SET_STD_VALVES::setInitialValues() {
    CFunctionBlock::setInitialValues();
    var_QI = 0_BOOL;
    var_PARAMS = u""_WSTRING;
    var_SD = CIEC_ANY_VARIANT();
    var_LOWER = 0_BOOL;
    var_SET = 0_BOOL;
    var_PULL = 0_BOOL;
    var_PUSH = 0_BOOL;
    var_BL_EXT = 0_BOOL;
    var_BL_RET = 0_BOOL;
    var_STAB_EXT = 0_BOOL;
    var_STAB_RET = 0_BOOL;
    var_QO = 0_BOOL;
    var_STATUS = u""_WSTRING;
    var_RD = CIEC_ANY_VARIANT();
  }

  static uint32_t numEventsInit;
  static uint32_t numEventsReq;
  static uint32_t numEventsRsp;
  void FORTE_SFB_ASGEVO_SET_STD_VALVES::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventINITID:
    	  numEventsInit++;
    	  //printf("SET_STD_VALVES: Init: %ld\n", numEventsInit);
    	  //st_STATE() = !st_STATE();
    	 // sendOutputEvent(scmEventCNFID, paECET);
        //#error add code for INIT event!
        /*
          do not forget to send output event, calling e.g.
            sendOutputEvent(scmEventCNFID, paECET);
        */
        break;
      case scmEventREQID:
    	  numEventsReq++;
    	  //printf("SET_STD_VALVES: Rsp: %ld\n", numEventsReq);
          readData(3, var_LOWER, conn_LOWER);
          readData(4, var_SET, conn_SET);
          readData(5, var_PULL, conn_PULL);
          readData(6, var_PUSH, conn_PUSH);
          readData(7, var_BL_EXT, conn_BL_EXT);
          readData(8, var_BL_RET, conn_BL_RET);
          readData(9, var_STAB_EXT, conn_STAB_EXT);
          readData(9, var_STAB_RET, conn_STAB_RET);

          IoSubSystemValves_SetValve_Lowering((bool) var_LOWER);
          IoSubSystemValves_SetValve_Setting((bool) var_SET);
          IoSubSystemValves_SetValve_PullShield((bool) var_PULL);
          IoSubSystemValves_SetValve_PushShield((bool) var_PUSH);
          IoSubSystemValves_SetValve_BaseLiftExtend((bool) var_BL_EXT);
          IoSubSystemValves_SetValve_BaseLiftRetract((bool) var_BL_RET);
          IoSubSystemValves_SetValve_StabCylExtend((bool) var_STAB_EXT);
          IoSubSystemValves_SetValve_StabCylRetract((bool) var_STAB_RET);
#if !defined(FORTE_NO_SIMULATOR)
          {
          CIEC_UINT var_LEG_LEFT = (CIEC_UINT)IoSubSystemSensor_GetPressureLeft();
          CIEC_UINT var_LEG_RIGHT = (CIEC_UINT)IoSubSystemSensor_GetPressureRight();
          CIEC_UINT var_RAM_STROKE = (CIEC_UINT)IoSubSystemSensor_GetRamStroke();
          printf("PC Simulator: ##################################\r\n");
    	  printf("PC Simulator: LOWER=%d SET=%d PULL=%d PUSH=%d BL_EXT=%d BL_RET=%d STAB_EXT=%d STAB_RET=%d\r\n", (int) var_LOWER, (int) var_SET, (int) var_PULL, (int) var_PUSH, (int) var_BL_EXT, (int) var_BL_RET, (int) var_STAB_EXT, (int) var_STAB_RET);
    	  printf("PC Simulator: LEG_LEFT=%d LEG_RIGHT=%d RAM=%d\n", (uint16_t) var_LEG_LEFT, (uint16_t) var_LEG_RIGHT, (uint16_t) var_RAM_STROKE);
          bool var_CA = IoSubSystemValves_GetValve_PullCreepAdvance();
          bool var_PREWARN = IoSubSystemEvents_Get_LAS_Prewarn();
          CIEC_UINT var_ERRCODE = (CIEC_UINT)IoSubSystemEvents_Get_LAS_Error();
          printf("PC Simulator: CA=%d PREWARN=%d ERRCODE=%u\r\n", (int) var_CA, (int) var_PREWARN, (uint16_t) var_ERRCODE);
          }
#endif
    	  sendOutputEvent(scmEventCNFID, paECET);
        //#error add code for RSP event!
        /*
          do not forget to send output event, calling e.g.
            sendOutputEvent(scmEventCNFID, paECET);
        */
        break;
      case scmEventRSPID:
    	  numEventsRsp++;
    	  //printf("SET_STD_VALVES: Rsp: %ld\n", numEventsRsp);
        //#error add code for RSP event!
        /*
          do not forget to send output event, calling e.g.
            sendOutputEvent(scmEventCNFID, paECET);
        */
        break;
    }
  }

  void FORTE_SFB_ASGEVO_SET_STD_VALVES::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_QI, conn_QI);
        readData(1, var_PARAMS, conn_PARAMS);
        readData(3, var_LOWER, conn_LOWER);
        readData(4, var_SET, conn_SET);
        readData(5, var_PULL, conn_PULL);
        readData(6, var_PUSH, conn_PUSH);
        readData(7, var_BL_EXT, conn_BL_EXT);
        readData(8, var_BL_RET, conn_BL_RET);
        readData(9, var_STAB_EXT, conn_STAB_EXT);
        readData(10, var_STAB_RET, conn_STAB_RET);
        break;
      }
      case scmEventREQID: {
        readData(0, var_QI, conn_QI);
        readData(2, var_SD, conn_SD);
        readData(3, var_LOWER, conn_LOWER);
        readData(4, var_SET, conn_SET);
        readData(5, var_PULL, conn_PULL);
        readData(6, var_PUSH, conn_PUSH);
        readData(7, var_BL_EXT, conn_BL_EXT);
        readData(8, var_BL_RET, conn_BL_RET);
        readData(9, var_STAB_EXT, conn_STAB_EXT);
        readData(10, var_STAB_RET, conn_STAB_RET);
        break;
      }
      case scmEventRSPID: {
        readData(0, var_QI, conn_QI);
        readData(2, var_SD, conn_SD);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SFB_ASGEVO_SET_STD_VALVES::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(11, var_QO, conn_QO);
        writeData(12, var_STATUS, conn_STATUS);
        break;
      }
      case scmEventCNFID: {
        writeData(11, var_QO, conn_QO);
        writeData(12, var_STATUS, conn_STATUS);
        writeData(13, var_RD, conn_RD);
        break;
      }
      case scmEventINDID: {
        writeData(11, var_QO, conn_QO);
        writeData(12, var_STATUS, conn_STATUS);
        writeData(13, var_RD, conn_RD);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SFB_ASGEVO_SET_STD_VALVES::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_QI;
      case 1: return &var_PARAMS;
      case 2: return &var_SD;
      case 3: return &var_LOWER;
      case 4: return &var_SET;
      case 5: return &var_PULL;
      case 6: return &var_PUSH;
      case 7: return &var_BL_EXT;
      case 8: return &var_BL_RET;
      case 9: return &var_STAB_EXT;
      case 10: return &var_STAB_RET;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SFB_ASGEVO_SET_STD_VALVES::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_QO;
      case 1: return &var_STATUS;
      case 2: return &var_RD;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SFB_ASGEVO_SET_STD_VALVES::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
      case 2: return &conn_IND;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SFB_ASGEVO_SET_STD_VALVES::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QI;
      case 1: return &conn_PARAMS;
      case 2: return &conn_SD;
      case 3: return &conn_LOWER;
      case 4: return &conn_SET;
      case 5: return &conn_PULL;
      case 6: return &conn_PUSH;
      case 7: return &conn_BL_EXT;
      case 8: return &conn_BL_RET;
      case 9: return &conn_STAB_EXT;
      case 10: return &conn_STAB_RET;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SFB_ASGEVO_SET_STD_VALVES::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QO;
      case 1: return &conn_STATUS;
      case 2: return &conn_RD;
    }
    return nullptr;
  }

}
