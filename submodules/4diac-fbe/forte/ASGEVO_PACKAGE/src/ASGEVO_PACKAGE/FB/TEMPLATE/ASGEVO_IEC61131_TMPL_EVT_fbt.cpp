/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_IEC61131_TMPL_EVT
 *** Description: Composite FB wrapping other FBs
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/ASGEVO_IEC61131_TMPL_EVT_fbt.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::TEMPLATE {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:sFB6MUOHltrHdfIC35pl3KbMfSwNTrdijku-tyErZI-CY0qdYfbrwfBqL7ieBgotM5VYxTS65B2xn6fcAXjSRw=="sv;

    const auto cEventInputNames = std::array{"REQ"_STRID, "ABORT"_STRID, "IDLE"_STRID, "FREEZE"_STRID};
    const auto cEventOutputNames = std::array{"CNF"_STRID, "BUSY"_STRID, "DONE"_STRID};
    const auto cDataInputNames = std::array{"INPUT"_STRID, "CYCLE"_STRID};
    const auto cDataOutputNames = std::array{"OUTPUT"_STRID, "ERRCODE"_STRID};

    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = {},
        .mEONames = cEventOutputNames,
        .mEOTypeNames = {},
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };

    const auto cEventConnections = std::to_array<SCFB_FBConnectionData>({
        {{}, "REQ"_STRID, "E_CYCLE"_STRID, "START"_STRID},
        {{}, "REQ"_STRID, "ASGEVO_IEC61131_TMPL_CYC"_STRID, "REQ"_STRID},
        {{}, "ABORT"_STRID, "ASGEVO_IEC61131_TMPL_CYC"_STRID, "ABORT"_STRID},
        {{}, "IDLE"_STRID, "ASGEVO_IEC61131_TMPL_CYC"_STRID, "IDLE"_STRID},
        {"E_CYCLE"_STRID, "EO"_STRID, "ASGEVO_IEC61131_TMPL_CYC"_STRID, "REQ"_STRID},
        {"ASGEVO_IEC61131_TMPL_CYC"_STRID, "DONE"_STRID, "E_CYCLE"_STRID, "STOP"_STRID},
        {"ASGEVO_IEC61131_TMPL_CYC"_STRID, "DONE"_STRID, {}, "DONE"_STRID},
        {"ASGEVO_IEC61131_TMPL_CYC"_STRID, "BUSY"_STRID, {}, "BUSY"_STRID},
        {"ASGEVO_IEC61131_TMPL_CYC"_STRID, "EO"_STRID, {}, "CNF"_STRID},
        {{}, "FREEZE"_STRID, "ASGEVO_IEC61131_TMPL_CYC"_STRID, "FREEZE"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
        {{}, "CYCLE"_STRID, "E_CYCLE"_STRID, "DT"_STRID},
        {{}, "INPUT"_STRID, "ASGEVO_IEC61131_TMPL_CYC"_STRID, "INPUT"_STRID},
        {"ASGEVO_IEC61131_TMPL_CYC"_STRID, "ERRCODE"_STRID, {}, "ERRCODE"_STRID},
        {"ASGEVO_IEC61131_TMPL_CYC"_STRID, "OUTPUT"_STRID, {}, "OUTPUT"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_ASGEVO_IEC61131_TMPL_EVT, "ASGEVO_PACKAGE::FB::TEMPLATE::ASGEVO_IEC61131_TMPL_EVT"_STRID, TypeHash)

  FORTE_ASGEVO_IEC61131_TMPL_EVT::FORTE_ASGEVO_IEC61131_TMPL_EVT(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_E_CYCLE("E_CYCLE"_STRID, *this),
      fb_ASGEVO_IEC61131_TMPL_CYC("ASGEVO_IEC61131_TMPL_CYC"_STRID, *this),
      conn_CNF(*this, 0),
      conn_BUSY(*this, 1),
      conn_DONE(*this, 2),
      conn_INPUT(nullptr),
      conn_CYCLE(nullptr),
      conn_OUTPUT(*this, 0, forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL()),
      conn_ERRCODE(*this, 1, 0_UINT),
      conn_if2in_INPUT(*this, 0, forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_INPUTS_IEC61131_TMPL()),
      conn_if2in_CYCLE(*this, 1, 0_TIME) {
  };

  void FORTE_ASGEVO_IEC61131_TMPL_EVT::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_INPUT.getValue() = forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_INPUTS_IEC61131_TMPL();
    conn_if2in_CYCLE.getValue() = 0_TIME;
    fb_ASGEVO_IEC61131_TMPL_CYC->conn_OUTPUT.getValue() = forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL();
    fb_ASGEVO_IEC61131_TMPL_CYC->conn_ERRCODE.getValue() = 0_UINT;
  }

  void FORTE_ASGEVO_IEC61131_TMPL_EVT::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventREQID: {
        readData(1, conn_if2in_CYCLE.getValue(), conn_CYCLE);
        readData(0, conn_if2in_INPUT.getValue(), conn_INPUT);
        break;
      }
      case scmEventABORTID: {
        readData(1, conn_if2in_CYCLE.getValue(), conn_CYCLE);
        readData(0, conn_if2in_INPUT.getValue(), conn_INPUT);
        break;
      }
      case scmEventIDLEID: {
        readData(0, conn_if2in_INPUT.getValue(), conn_INPUT);
        readData(1, conn_if2in_CYCLE.getValue(), conn_CYCLE);
        break;
      }
      case scmEventFREEZEID: {
        readData(1, conn_if2in_CYCLE.getValue(), conn_CYCLE);
        readData(0, conn_if2in_INPUT.getValue(), conn_INPUT);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_ASGEVO_IEC61131_TMPL_EVT::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        writeData(3, fb_ASGEVO_IEC61131_TMPL_CYC->conn_ERRCODE.getValue(), conn_ERRCODE);
        writeData(2, fb_ASGEVO_IEC61131_TMPL_CYC->conn_OUTPUT.getValue(), conn_OUTPUT);
        break;
      }
      case scmEventBUSYID: {
        writeData(3, fb_ASGEVO_IEC61131_TMPL_CYC->conn_ERRCODE.getValue(), conn_ERRCODE);
        writeData(2, fb_ASGEVO_IEC61131_TMPL_CYC->conn_OUTPUT.getValue(), conn_OUTPUT);
        break;
      }
      case scmEventDONEID: {
        writeData(3, fb_ASGEVO_IEC61131_TMPL_CYC->conn_ERRCODE.getValue(), conn_ERRCODE);
        writeData(2, fb_ASGEVO_IEC61131_TMPL_CYC->conn_OUTPUT.getValue(), conn_OUTPUT);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_ASGEVO_IEC61131_TMPL_EVT::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_INPUT.getValue();
      case 1: return &conn_if2in_CYCLE.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_IEC61131_TMPL_EVT::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_ASGEVO_IEC61131_TMPL_CYC->conn_OUTPUT.getValue();
      case 1: return &fb_ASGEVO_IEC61131_TMPL_CYC->conn_ERRCODE.getValue();
    }
    return nullptr;
  }

  CEventConnection *FORTE_ASGEVO_IEC61131_TMPL_EVT::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CNF;
      case 1: return &conn_BUSY;
      case 2: return &conn_DONE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_ASGEVO_IEC61131_TMPL_EVT::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INPUT;
      case 1: return &conn_CYCLE;
    }
    return nullptr;
  }

  CDataConnection *FORTE_ASGEVO_IEC61131_TMPL_EVT::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_OUTPUT;
      case 1: return &conn_ERRCODE;
    }
    return nullptr;
  }

  CDataConnection *FORTE_ASGEVO_IEC61131_TMPL_EVT::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_INPUT;
      case 1: return &conn_if2in_CYCLE;
    }
    return nullptr;
  }

}