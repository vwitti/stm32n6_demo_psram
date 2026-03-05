/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: SFB_ASGEVO_GET_RAM_STROKE
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2026-02-21/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/SFB_ASGEVO_GET_RAM_STROKE_fbt.h"

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
    constexpr std::string_view TypeHash ="v1:SHA3-512:WD0EBjtXDXQQfQsA930A4xUplm47sEQXPTUOC4tPOna-3by-6xeW6OJzjWuvUVPUiVV0pcjM57lIHeIT4P2jYA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID, "RSP"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID, "IND"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"QI"_STRID, "PARAMS"_STRID, "SD"_STRID};
    const auto cDataOutputNames = std::array{"QO"_STRID, "STATUS"_STRID, "RD"_STRID, "RAM_STROKE"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_SFB_ASGEVO_GET_RAM_STROKE, "ASGEVO_PACKAGE::SFB_ASGEVO_GET_RAM_STROKE"_STRID, TypeHash)

  FORTE_SFB_ASGEVO_GET_RAM_STROKE::FORTE_SFB_ASGEVO_GET_RAM_STROKE(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CFunctionBlock(paContainer, cFBInterfaceSpec, paInstanceNameId),
      var_QI(0_BOOL),
      var_PARAMS(u""_WSTRING),
      var_SD(CIEC_ANY_VARIANT()),
      var_QO(0_BOOL),
      var_STATUS(u""_WSTRING),
      var_RD(CIEC_ANY_VARIANT()),
      var_RAM_STROKE(0_UINT),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_IND(*this, 2),
      conn_QI(nullptr),
      conn_PARAMS(nullptr),
      conn_SD(nullptr),
      conn_QO(*this, 0, var_QO),
      conn_STATUS(*this, 1, var_STATUS),
      conn_RD(*this, 2, var_RD),
      conn_RAM_STROKE(*this, 3, var_RAM_STROKE) {
  };

  void FORTE_SFB_ASGEVO_GET_RAM_STROKE::setInitialValues() {
    CFunctionBlock::setInitialValues();
    var_QI = 0_BOOL;
    var_PARAMS = u""_WSTRING;
    var_SD = CIEC_ANY_VARIANT();
    var_QO = 0_BOOL;
    var_STATUS = u""_WSTRING;
    var_RD = CIEC_ANY_VARIANT();
    var_RAM_STROKE = 0_UINT;
  }

  void FORTE_SFB_ASGEVO_GET_RAM_STROKE::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_SFB_ASGEVO_GET_RAM_STROKE::readInputData(const TEventID paEIID) {
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

  void FORTE_SFB_ASGEVO_GET_RAM_STROKE::writeOutputData(const TEventID paEIID) {
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
        var_RAM_STROKE = (CIEC_UINT)IoSubSystemSensor_GetRamStroke();
//#if !defined(FORTE_NO_SIMULATOR)
//        printf("PC Simulator: ##################################\r\n");
//       printf("PC Simulator: var_RAM_STROKE=%d\n", (uint16_t) var_RAM_STROKE);
//#endif
        writeData(6, var_RAM_STROKE, conn_RAM_STROKE);
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

  CIEC_ANY *FORTE_SFB_ASGEVO_GET_RAM_STROKE::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_QI;
      case 1: return &var_PARAMS;
      case 2: return &var_SD;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SFB_ASGEVO_GET_RAM_STROKE::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_QO;
      case 1: return &var_STATUS;
      case 2: return &var_RD;
      case 3: return &var_RAM_STROKE;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SFB_ASGEVO_GET_RAM_STROKE::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
      case 2: return &conn_IND;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SFB_ASGEVO_GET_RAM_STROKE::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QI;
      case 1: return &conn_PARAMS;
      case 2: return &conn_SD;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SFB_ASGEVO_GET_RAM_STROKE::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QO;
      case 1: return &conn_STATUS;
      case 2: return &conn_RD;
      case 3: return &conn_RAM_STROKE;
    }
    return nullptr;
  }

}
