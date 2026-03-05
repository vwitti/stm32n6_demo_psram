/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: SFB_ASGEVO_LAS_SIGNALS
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2026-02-21/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/SFB_ASGEVO_LAS_SIGNALS_fbt.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

#if defined(FORTE_NO_SIMULATOR)
	#include "Common/Inc/IoSubSystem/events.h"
#else
	#include "forte/ASGEVO_PACKAGE/events.h"
#endif

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:0uBht53nHuYue-pzAvp7Yd-Pwc7rPvFnDWir1iqFAWWdYW_MJor145zPIMCCWZyiyG9qaXOUxkXAe6RH175xQw=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID, "RSP"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID, "IND"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"QI"_STRID, "PARAMS"_STRID, "SD"_STRID, "PREWARN"_STRID, "ERRCODE"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_SFB_ASGEVO_LAS_SIGNALS, "ASGEVO_PACKAGE::SFB_ASGEVO_LAS_SIGNALS"_STRID, TypeHash)

  FORTE_SFB_ASGEVO_LAS_SIGNALS::FORTE_SFB_ASGEVO_LAS_SIGNALS(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CFunctionBlock(paContainer, cFBInterfaceSpec, paInstanceNameId),
      var_QI(0_BOOL),
      var_PARAMS(u""_WSTRING),
      var_SD(CIEC_ANY_VARIANT()),
      var_PREWARN(0_BOOL),
      var_ERRCODE(0_UINT),
      var_QO(0_BOOL),
      var_STATUS(u""_WSTRING),
      var_RD(CIEC_ANY_VARIANT()),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_IND(*this, 2),
      conn_QI(nullptr),
      conn_PARAMS(nullptr),
      conn_SD(nullptr),
      conn_PREWARN(nullptr),
      conn_ERRCODE(nullptr),
      conn_QO(*this, 0, var_QO),
      conn_STATUS(*this, 1, var_STATUS),
      conn_RD(*this, 2, var_RD) {
  };

  void FORTE_SFB_ASGEVO_LAS_SIGNALS::setInitialValues() {
    CFunctionBlock::setInitialValues();
    var_QI = 0_BOOL;
    var_PARAMS = u""_WSTRING;
    var_SD = CIEC_ANY_VARIANT();
    var_PREWARN = 0_BOOL;
    var_ERRCODE = 0_UINT;
    var_QO = 0_BOOL;
    var_STATUS = u""_WSTRING;
    var_RD = CIEC_ANY_VARIANT();
  }

  void FORTE_SFB_ASGEVO_LAS_SIGNALS::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventINITID:
        //#error add code for INIT event!
        /*
          do not forget to send output event, calling e.g.
            sendOutputEvent(scmEventCNFID, paECET);
        */
        break;
      case scmEventREQID:
          readData(3, var_PREWARN, conn_PREWARN);
          readData(4, var_ERRCODE, conn_ERRCODE);
          IoSubSystemEvents_Set_LAS_Prewarn((bool) var_PREWARN);
          IoSubSystemEvents_Set_LAS_Error((uint16_t) var_ERRCODE);
//#if !defined(FORTE_NO_SIMULATOR)
//          printf("PC Simulator: ##################################\r\n");
//          printf("PC Simulator: var_PREWARN=%d   var_ERRCODE=%u\r\n", (int) var_PREWARN, (uint16_t) var_ERRCODE);
//#endif
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

  void FORTE_SFB_ASGEVO_LAS_SIGNALS::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_QI, conn_QI);
        readData(1, var_PARAMS, conn_PARAMS);
        readData(3, var_PREWARN, conn_PREWARN);
        readData(4, var_ERRCODE, conn_ERRCODE);
        break;
      }
      case scmEventREQID: {
        readData(0, var_QI, conn_QI);
        readData(2, var_SD, conn_SD);
        readData(3, var_PREWARN, conn_PREWARN);
        readData(4, var_ERRCODE, conn_ERRCODE);
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

  void FORTE_SFB_ASGEVO_LAS_SIGNALS::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(5, var_QO, conn_QO);
        writeData(6, var_STATUS, conn_STATUS);
        break;
      }
      case scmEventCNFID: {
        writeData(5, var_QO, conn_QO);
        writeData(6, var_STATUS, conn_STATUS);
        writeData(7, var_RD, conn_RD);
        break;
      }
      case scmEventINDID: {
        writeData(5, var_QO, conn_QO);
        writeData(6, var_STATUS, conn_STATUS);
        writeData(7, var_RD, conn_RD);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SFB_ASGEVO_LAS_SIGNALS::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_QI;
      case 1: return &var_PARAMS;
      case 2: return &var_SD;
      case 3: return &var_PREWARN;
      case 4: return &var_ERRCODE;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SFB_ASGEVO_LAS_SIGNALS::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_QO;
      case 1: return &var_STATUS;
      case 2: return &var_RD;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SFB_ASGEVO_LAS_SIGNALS::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
      case 2: return &conn_IND;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SFB_ASGEVO_LAS_SIGNALS::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QI;
      case 1: return &conn_PARAMS;
      case 2: return &conn_SD;
      case 3: return &conn_PREWARN;
      case 4: return &conn_ERRCODE;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SFB_ASGEVO_LAS_SIGNALS::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QO;
      case 1: return &conn_STATUS;
      case 2: return &conn_RD;
    }
    return nullptr;
  }

}
