/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_LAS_EVT
 *** Description: Composite FB wrapping other FBs
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/LAS/ASGEVO_LAS_EVT_fbt.h"

#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:bPktNHNsQnQZUcQ5jEPgd05Kq2gzdzocWXOSiKHUqZjrMMawAa_wkapR98WOOvld1lc8JNM2tInI8c2SCDG2dQ=="sv;

    const auto cEventInputNames = std::array{"REQ"_STRID, "ABORT"_STRID, "IDLE"_STRID, "FREEZE"_STRID};
    const auto cEventOutputNames = std::array{"CNF"_STRID, "BUSY"_STRID, "DONE"_STRID};
    const auto cDataInputNames = std::array{"INPUT"_STRID, "PARAM"_STRID, "TARGET"_STRID, "CYCLE"_STRID};
    const auto cDataOutputNames = std::array{"OUTPUT"_STRID, "TIMING"_STRID, "ERRCODE"_STRID};

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
        {{}, "ABORT"_STRID, "ASGEVO_LAS_CYC"_STRID, "ABORT"_STRID},
        {{}, "IDLE"_STRID, "ASGEVO_LAS_CYC"_STRID, "IDLE"_STRID},
        {"E_CYCLE"_STRID, "EO"_STRID, "E_MERGE_2"_STRID, "EI2"_STRID},
        {"ASGEVO_LAS_CYC"_STRID, "EO"_STRID, {}, "CNF"_STRID},
        {"ASGEVO_LAS_CYC"_STRID, "BUSY"_STRID, {}, "BUSY"_STRID},
        {"ASGEVO_LAS_CYC"_STRID, "DONE"_STRID, {}, "DONE"_STRID},
        {"ASGEVO_LAS_CYC"_STRID, "DONE"_STRID, "E_CYCLE"_STRID, "STOP"_STRID},
        {{}, "REQ"_STRID, "E_MERGE_2"_STRID, "EI1"_STRID},
        {"E_MERGE_2"_STRID, "EO"_STRID, "ASGEVO_LAS_CYC"_STRID, "REQ"_STRID},
        {"E_MERGE_2"_STRID, "EO"_STRID, "SFB_ASGEVO_GET_LEG_PRESSURE"_STRID, "REQ"_STRID},
        {"E_MERGE_2"_STRID, "EO"_STRID, "SFB_ASGEVO_GET_RAM_STROKE"_STRID, "REQ"_STRID},
        {"SFB_ASGEVO_GET_LEG_PRESSURE"_STRID, "CNF"_STRID, "LAS_MUX_INPUTS"_STRID, "REQ"_STRID},
        {"SFB_ASGEVO_GET_RAM_STROKE"_STRID, "CNF"_STRID, "LAS_MUX_INPUTS"_STRID, "REQ"_STRID},
        {{}, "FREEZE"_STRID, "ASGEVO_LAS_CYC"_STRID, "FREEZE"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
        {{}, "CYCLE"_STRID, "E_CYCLE"_STRID, "DT"_STRID},
        {{}, "PARAM"_STRID, "ASGEVO_LAS_CYC"_STRID, "PARAM"_STRID},
        {"ASGEVO_LAS_CYC"_STRID, "OUTPUT"_STRID, {}, "OUTPUT"_STRID},
        {"ASGEVO_LAS_CYC"_STRID, "TIMING"_STRID, {}, "TIMING"_STRID},
        {"ASGEVO_LAS_CYC"_STRID, "ERRCODE"_STRID, {}, "ERRCODE"_STRID},
        {"SFB_ASGEVO_GET_LEG_PRESSURE"_STRID, "LEG_LEFT"_STRID, "LAS_MUX_INPUTS"_STRID, "LEG_LEFT"_STRID},
        {"SFB_ASGEVO_GET_LEG_PRESSURE"_STRID, "LEG_RIGHT"_STRID, "LAS_MUX_INPUTS"_STRID, "LEG_RIGHT"_STRID},
        {"SFB_ASGEVO_GET_RAM_STROKE"_STRID, "RAM_STROKE"_STRID, "LAS_MUX_INPUTS"_STRID, "RAM_STROKE"_STRID},
        {"LAS_MUX_INPUTS"_STRID, "INPUTS"_STRID, "ASGEVO_LAS_CYC"_STRID, "INPUT"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_ASGEVO_LAS_EVT, "ASGEVO_PACKAGE::FB::LAS::ASGEVO_LAS_EVT"_STRID, TypeHash)

  FORTE_ASGEVO_LAS_EVT::FORTE_ASGEVO_LAS_EVT(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_E_CYCLE("E_CYCLE"_STRID, *this),
      fb_ASGEVO_LAS_CYC("ASGEVO_LAS_CYC"_STRID, *this),
      fb_SFB_ASGEVO_GET_LEG_PRESSURE("SFB_ASGEVO_GET_LEG_PRESSURE"_STRID, *this),
      fb_SFB_ASGEVO_GET_RAM_STROKE("SFB_ASGEVO_GET_RAM_STROKE"_STRID, *this),
      fb_E_MERGE_2("E_MERGE_2"_STRID, "iec61499::events::E_MERGE_2", *this),
      fb_LAS_MUX_INPUTS("LAS_MUX_INPUTS"_STRID, *this),
      conn_CNF(*this, 0),
      conn_BUSY(*this, 1),
      conn_DONE(*this, 2),
      conn_INPUT(nullptr),
      conn_PARAM(nullptr),
      conn_TARGET(nullptr),
      conn_CYCLE(nullptr),
      conn_OUTPUT(*this, 0, forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS()),
      conn_TIMING(*this, 1, forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING()),
      conn_ERRCODE(*this, 2, 0_UINT),
      conn_if2in_INPUT(*this, 0, forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS()),
      conn_if2in_PARAM(*this, 1, forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER()),
      conn_if2in_TARGET(*this, 2, 0_UINT),
      conn_if2in_CYCLE(*this, 3, 0_TIME) {
  };

  void FORTE_ASGEVO_LAS_EVT::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_INPUT.getValue() = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS();
    conn_if2in_PARAM.getValue() = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER();
    conn_if2in_TARGET.getValue() = 0_UINT;
    conn_if2in_CYCLE.getValue() = 0_TIME;
    fb_ASGEVO_LAS_CYC->conn_OUTPUT.getValue() = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS();
    fb_ASGEVO_LAS_CYC->conn_TIMING.getValue() = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING();
    fb_ASGEVO_LAS_CYC->conn_ERRCODE.getValue() = 0_UINT;
  }

  void FORTE_ASGEVO_LAS_EVT::setFBNetworkInitialValues() {
    fb_ASGEVO_LAS_CYC->var_TARGET = 30_UINT;
    fb_LAS_MUX_INPUTS->var_RAM_STROKE = 0_UINT;
  }

  void FORTE_ASGEVO_LAS_EVT::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventREQID: {
        readData(0, conn_if2in_INPUT.getValue(), conn_INPUT);
        readData(1, conn_if2in_PARAM.getValue(), conn_PARAM);
        readData(2, conn_if2in_TARGET.getValue(), conn_TARGET);
        readData(3, conn_if2in_CYCLE.getValue(), conn_CYCLE);
        break;
      }
      case scmEventABORTID: {
        readData(0, conn_if2in_INPUT.getValue(), conn_INPUT);
        readData(1, conn_if2in_PARAM.getValue(), conn_PARAM);
        readData(2, conn_if2in_TARGET.getValue(), conn_TARGET);
        readData(3, conn_if2in_CYCLE.getValue(), conn_CYCLE);
        break;
      }
      case scmEventIDLEID: {
        readData(0, conn_if2in_INPUT.getValue(), conn_INPUT);
        readData(1, conn_if2in_PARAM.getValue(), conn_PARAM);
        readData(2, conn_if2in_TARGET.getValue(), conn_TARGET);
        break;
      }
      case scmEventFREEZEID: {
        readData(3, conn_if2in_CYCLE.getValue(), conn_CYCLE);
        readData(2, conn_if2in_TARGET.getValue(), conn_TARGET);
        readData(1, conn_if2in_PARAM.getValue(), conn_PARAM);
        readData(0, conn_if2in_INPUT.getValue(), conn_INPUT);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_ASGEVO_LAS_EVT::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        writeData(4, fb_ASGEVO_LAS_CYC->conn_OUTPUT.getValue(), conn_OUTPUT);
        writeData(5, fb_ASGEVO_LAS_CYC->conn_TIMING.getValue(), conn_TIMING);
        writeData(6, fb_ASGEVO_LAS_CYC->conn_ERRCODE.getValue(), conn_ERRCODE);
        break;
      }
      case scmEventBUSYID: {
        writeData(6, fb_ASGEVO_LAS_CYC->conn_ERRCODE.getValue(), conn_ERRCODE);
        writeData(5, fb_ASGEVO_LAS_CYC->conn_TIMING.getValue(), conn_TIMING);
        writeData(4, fb_ASGEVO_LAS_CYC->conn_OUTPUT.getValue(), conn_OUTPUT);
        break;
      }
      case scmEventDONEID: {
        writeData(6, fb_ASGEVO_LAS_CYC->conn_ERRCODE.getValue(), conn_ERRCODE);
        writeData(5, fb_ASGEVO_LAS_CYC->conn_TIMING.getValue(), conn_TIMING);
        writeData(4, fb_ASGEVO_LAS_CYC->conn_OUTPUT.getValue(), conn_OUTPUT);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_ASGEVO_LAS_EVT::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_INPUT.getValue();
      case 1: return &conn_if2in_PARAM.getValue();
      case 2: return &conn_if2in_TARGET.getValue();
      case 3: return &conn_if2in_CYCLE.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_LAS_EVT::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_ASGEVO_LAS_CYC->conn_OUTPUT.getValue();
      case 1: return &fb_ASGEVO_LAS_CYC->conn_TIMING.getValue();
      case 2: return &fb_ASGEVO_LAS_CYC->conn_ERRCODE.getValue();
    }
    return nullptr;
  }

  CEventConnection *FORTE_ASGEVO_LAS_EVT::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CNF;
      case 1: return &conn_BUSY;
      case 2: return &conn_DONE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_ASGEVO_LAS_EVT::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INPUT;
      case 1: return &conn_PARAM;
      case 2: return &conn_TARGET;
      case 3: return &conn_CYCLE;
    }
    return nullptr;
  }

  CDataConnection *FORTE_ASGEVO_LAS_EVT::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_OUTPUT;
      case 1: return &conn_TIMING;
      case 2: return &conn_ERRCODE;
    }
    return nullptr;
  }

  CDataConnection *FORTE_ASGEVO_LAS_EVT::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_INPUT;
      case 1: return &conn_if2in_PARAM;
      case 2: return &conn_if2in_TARGET;
      case 3: return &conn_if2in_CYCLE;
    }
    return nullptr;
  }

}