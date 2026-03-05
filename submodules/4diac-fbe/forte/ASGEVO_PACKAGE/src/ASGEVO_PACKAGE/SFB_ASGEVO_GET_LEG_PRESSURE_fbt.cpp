/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: SFB_ASGEVO_GET_LEG_PRESSURE
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2026-02-21/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/SFB_ASGEVO_GET_LEG_PRESSURE_fbt.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

#if defined(FORTE_NO_SIMULATOR)
	#include "Common/Inc/IoSubSystem/sensors.h"
#else
	#include "forte/ASGEVO_PACKAGE/sensors.h"
#endif

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:hELEYK1Be2CJcivqwitc7d6UlWD01DXI00k9xWljA9ve8F8Wk-tO5aj4GhAdNlUWmbV4sskN-efacf-9w3QS-w=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID, "RSP"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID, "IND"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"QI"_STRID, "PARAMS"_STRID, "SD"_STRID};
    const auto cDataOutputNames = std::array{"QO"_STRID, "STATUS"_STRID, "RD"_STRID, "LEG_LEFT"_STRID, "LEG_RIGHT"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_SFB_ASGEVO_GET_LEG_PRESSURE, "ASGEVO_PACKAGE::SFB_ASGEVO_GET_LEG_PRESSURE"_STRID, TypeHash)

  FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::FORTE_SFB_ASGEVO_GET_LEG_PRESSURE(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CFunctionBlock(paContainer, cFBInterfaceSpec, paInstanceNameId),
      var_QI(0_BOOL),
      var_PARAMS(u""_WSTRING),
      var_SD(CIEC_ANY_VARIANT()),
      var_QO(0_BOOL),
      var_STATUS(u""_WSTRING),
      var_RD(CIEC_ANY_VARIANT()),
      var_LEG_LEFT(0_UINT),
      var_LEG_RIGHT(0_UINT),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_IND(*this, 2),
      conn_QI(nullptr),
      conn_PARAMS(nullptr),
      conn_SD(nullptr),
      conn_QO(*this, 0, var_QO),
      conn_STATUS(*this, 1, var_STATUS),
      conn_RD(*this, 2, var_RD),
      conn_LEG_LEFT(*this, 3, var_LEG_LEFT),
      conn_LEG_RIGHT(*this, 4, var_LEG_RIGHT) {
  };

  void FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::setInitialValues() {
    CFunctionBlock::setInitialValues();
    var_QI = 0_BOOL;
    var_PARAMS = u""_WSTRING;
    var_SD = CIEC_ANY_VARIANT();
    var_QO = 0_BOOL;
    var_STATUS = u""_WSTRING;
    var_RD = CIEC_ANY_VARIANT();
    var_LEG_LEFT = 0_UINT;
    var_LEG_RIGHT = 0_UINT;
  }

  void FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventINITID:
        //#error add code for INIT event!
        /*
          do not forget to send output event, calling e.g.
            sendOutputEvent(scmEventCNFID, paECET);
        */
        break;
      case scmEventREQID:
        //#error add code for REQ event!
        /*
          do not forget to send output event, calling e.g.
            sendOutputEvent(scmEventCNFID, paECET);
        */
    	  sendOutputEvent(scmEventCNFID, paECET);
        break;
      case scmEventRSPID:
        //#error add code for RSP event!
        /*
          do not forget to send output event, calling e.g.
            sendOutputEvent(scmEventCNFID, paECET);
        */
        break;
    }
  }

  void FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_QI, conn_QI);
        readData(1, var_PARAMS, conn_PARAMS);
        break;
      }
      case scmEventREQID: {
        readData(0, var_QI, conn_QI);
        readData(2, var_SD, conn_SD);
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

  void FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(3, var_QO, conn_QO);
        writeData(4, var_STATUS, conn_STATUS);
        break;
      }
      case scmEventCNFID: {
        writeData(3, var_QO, conn_QO);
        writeData(4, var_STATUS, conn_STATUS);
        writeData(5, var_RD, conn_RD);
        var_LEG_LEFT = (CIEC_UINT)IoSubSystemSensor_GetPressureLeft();
        var_LEG_RIGHT = (CIEC_UINT)IoSubSystemSensor_GetPressureRight();
//#if !defined(FORTE_NO_SIMULATOR)
//        printf("PC Simulator: ##################################\r\n");
//        printf("PC Simulator: var_LEG_LEFT=%d var_LEG_RIGHT=%d\n", (uint16_t) var_LEG_LEFT, (uint16_t) var_LEG_RIGHT);
//#endif
        writeData(6, var_LEG_LEFT, conn_LEG_LEFT);
        writeData(7, var_LEG_RIGHT, conn_LEG_RIGHT);
        break;
      }
      case scmEventINDID: {
        writeData(3, var_QO, conn_QO);
        writeData(4, var_STATUS, conn_STATUS);
        writeData(5, var_RD, conn_RD);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_QI;
      case 1: return &var_PARAMS;
      case 2: return &var_SD;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_QO;
      case 1: return &var_STATUS;
      case 2: return &var_RD;
      case 3: return &var_LEG_LEFT;
      case 4: return &var_LEG_RIGHT;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
      case 2: return &conn_IND;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QI;
      case 1: return &conn_PARAMS;
      case 2: return &conn_SD;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SFB_ASGEVO_GET_LEG_PRESSURE::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QO;
      case 1: return &conn_STATUS;
      case 2: return &conn_RD;
      case 3: return &conn_LEG_LEFT;
      case 4: return &conn_LEG_RIGHT;
    }
    return nullptr;
  }

}
