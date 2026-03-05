/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_PUSH_HDL
 *** Description: Simple FB with one algorithm
 *** Version:
 ***     1.0: 2026-02-26/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/PUSH/ASGEVO_PUSH_HDL_fbt.h"

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/PUSH/INPUTS_PUSH_dtp.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::PUSH {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:350uOuh2wgD5vfbk3wswaia9SicoSCvAjBXBPm4qlRbzdbhWVvR3jSe2Igphm1kU5L0_bI4imrg8dREARpQqgg=="sv;

    const auto cEventInputNames = std::array{"REQ"_STRID};
    const auto cEventOutputNames = std::array{"CNF"_STRID};
    const auto cDataInputNames = std::array{"STATE"_STRID, "INPUT"_STRID};
    const auto cDataOutputNames = std::array{"DONE"_STRID, "ERRCODE"_STRID, "OUTPUT"_STRID};
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

    const auto cInternalsNames = std::array{"FB_CONSOLE_DBG"_STRID, "STATE_OLD"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_ASGEVO_PUSH_HDL, "ASGEVO_PACKAGE::FB::PUSH::ASGEVO_PUSH_HDL"_STRID, TypeHash)
  const CIEC_UINT FORTE_ASGEVO_PUSH_HDL::var_const_FB_HANDLER_STATE_RESET = 0_UINT;
  const CIEC_UINT FORTE_ASGEVO_PUSH_HDL::var_const_FB_HANDLER_STATE_INIT = 1_UINT;
  const CIEC_UINT FORTE_ASGEVO_PUSH_HDL::var_const_FB_HANDLER_STATE_INPUTS = 2_UINT;
  const CIEC_UINT FORTE_ASGEVO_PUSH_HDL::var_const_FB_HANDLER_STATE_OPERATE = 3_UINT;
  const CIEC_UINT FORTE_ASGEVO_PUSH_HDL::var_const_FB_HANDLER_STATE_OUTPUTS = 4_UINT;
  const CIEC_UINT FORTE_ASGEVO_PUSH_HDL::var_const_FB_HANDLER_STATE_ABORT = 5_UINT;


  FORTE_ASGEVO_PUSH_HDL::FORTE_ASGEVO_PUSH_HDL(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      fb_HCONSOLE("HCONSOLE"_STRID, *this),
      fb_FB_LAS_HDL_OP("FB_LAS_HDL_OP"_STRID, *this),
      var_FB_CONSOLE_DBG(false_BOOL),
      var_STATE_OLD(0_UINT),
      var_STATE(0_UINT),
      var_INPUT(forte::ASGEVO_PACKAGE::FB::PUSH::CIEC_INPUTS_PUSH()),
      var_DONE(0_BOOL),
      var_ERRCODE(0_UINT),
      var_OUTPUT(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS()),
      conn_CNF(*this, 0),
      conn_STATE(nullptr),
      conn_INPUT(nullptr),
      conn_DONE(*this, 0, var_DONE),
      conn_ERRCODE(*this, 1, var_ERRCODE),
      conn_OUTPUT(*this, 2, var_OUTPUT) {
  }

  void FORTE_ASGEVO_PUSH_HDL::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_FB_CONSOLE_DBG = false_BOOL;
    var_STATE_OLD = 0_UINT;
    var_STATE = 0_UINT;
    var_INPUT = forte::ASGEVO_PACKAGE::FB::PUSH::CIEC_INPUTS_PUSH();
    var_DONE = 0_BOOL;
    var_ERRCODE = 0_UINT;
    var_OUTPUT = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS();
  }

  void FORTE_ASGEVO_PUSH_HDL::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventREQID:
        enterStateREQ(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_ASGEVO_PUSH_HDL::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_ASGEVO_PUSH_HDL::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventREQID: {
        readData(0, var_STATE, conn_STATE);
        readData(1, var_INPUT, conn_INPUT);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_ASGEVO_PUSH_HDL::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        writeData(2, var_DONE, conn_DONE);
        writeData(3, var_ERRCODE, conn_ERRCODE);
        writeData(4, var_OUTPUT, conn_OUTPUT);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_ASGEVO_PUSH_HDL::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_STATE;
      case 1: return &var_INPUT;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_PUSH_HDL::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_DONE;
      case 1: return &var_ERRCODE;
      case 2: return &var_OUTPUT;
    }
    return nullptr;
  }

  CEventConnection *FORTE_ASGEVO_PUSH_HDL::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_ASGEVO_PUSH_HDL::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_STATE;
      case 1: return &conn_INPUT;
    }
    return nullptr;
  }

  CDataConnection *FORTE_ASGEVO_PUSH_HDL::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_DONE;
      case 1: return &conn_ERRCODE;
      case 2: return &conn_OUTPUT;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_PUSH_HDL::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_FB_CONSOLE_DBG;
      case 1: return &var_STATE_OLD;
    }
    return nullptr;
  }

  void FORTE_ASGEVO_PUSH_HDL::alg_REQ(void) {

    #line 6 "ASGEVO_PUSH_HDL.fbt"
    if (func_AND<CIEC_BOOL>(func_NE(var_STATE, var_const_FB_HANDLER_STATE_RESET), func_EQ(var_STATE_OLD, var_const_FB_HANDLER_STATE_RESET))) {
      #line 7 "ASGEVO_PUSH_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_INIT"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 8 "ASGEVO_PUSH_HDL.fbt"
      fb_FB_LAS_HDL_OP(false_BOOL, fb_FB_LAS_HDL_OP->var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>());
      #line 9 "ASGEVO_PUSH_HDL.fbt"
      fb_FB_LAS_HDL_OP(true_BOOL, var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>());
      #line 10 "ASGEVO_PUSH_HDL.fbt"
      var_DONE = fb_FB_LAS_HDL_OP->var_DONE;
    }
    #line 12 "ASGEVO_PUSH_HDL.fbt"
    var_STATE_OLD = var_STATE;
    #line 14 "ASGEVO_PUSH_HDL.fbt"
    if (auto st_lv_synthetic_0 = var_STATE; false) {
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_INIT)) {
      #line 18 "ASGEVO_PUSH_HDL.fbt"
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_INPUTS)) {
      #line 21 "ASGEVO_PUSH_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_INPUTS"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 22 "ASGEVO_PUSH_HDL.fbt"
      fb_FB_LAS_HDL_OP(true_BOOL, var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>());
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_OPERATE)) {
      #line 25 "ASGEVO_PUSH_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_OPERATE"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 26 "ASGEVO_PUSH_HDL.fbt"
      fb_FB_LAS_HDL_OP(true_BOOL, fb_FB_LAS_HDL_OP->var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>());
      #line 27 "ASGEVO_PUSH_HDL.fbt"
      var_DONE = fb_FB_LAS_HDL_OP->var_DONE;
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_OUTPUTS)) {
      #line 30 "ASGEVO_PUSH_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_OUTPUTS"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 32 "ASGEVO_PUSH_HDL.fbt"
      var_DONE = fb_FB_LAS_HDL_OP->var_DONE;
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_ABORT)) {
      #line 35 "ASGEVO_PUSH_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_ABORT"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 36 "ASGEVO_PUSH_HDL.fbt"
      fb_FB_LAS_HDL_OP(false_BOOL, fb_FB_LAS_HDL_OP->var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>());
      #line 37 "ASGEVO_PUSH_HDL.fbt"
      var_DONE = true_BOOL;
    } else {
      #line 41 "ASGEVO_PUSH_HDL.fbt"
    }
    #line 45 "ASGEVO_PUSH_HDL.fbt"
    var_OUTPUT = fb_FB_LAS_HDL_OP->var_OUTPUT;
    #line 46 "ASGEVO_PUSH_HDL.fbt"
    var_ERRCODE = fb_FB_LAS_HDL_OP->var_ERRCODE;
  }

}