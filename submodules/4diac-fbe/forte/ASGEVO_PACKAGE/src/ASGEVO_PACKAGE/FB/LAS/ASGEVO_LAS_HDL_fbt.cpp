/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_LAS_HDL
 *** Description: Simple FB with one algorithm
 *** Version:
 ***     1.0: 2026-02-26/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/LAS/ASGEVO_LAS_HDL_fbt.h"

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_INPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_TIMING_dtp.h"
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

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:s9DWmCeEEg_wFfaqTz94a16nmI-FvSGQbG507WgaHKmDKNqmqpFOljVNT70QMRgYHTU_cQIqc6ItJAxAli5unA=="sv;

    const auto cEventInputNames = std::array{"REQ"_STRID};
    const auto cEventOutputNames = std::array{"CNF"_STRID};
    const auto cDataInputNames = std::array{"STATE"_STRID, "INPUT"_STRID, "PARAM"_STRID, "TARGET"_STRID};
    const auto cDataOutputNames = std::array{"DONE"_STRID, "OUTPUT"_STRID, "TIMING"_STRID, "ERRCODE"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_ASGEVO_LAS_HDL, "ASGEVO_PACKAGE::FB::LAS::ASGEVO_LAS_HDL"_STRID, TypeHash)
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL::var_const_FB_HANDLER_STATE_RESET = 0_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL::var_const_FB_HANDLER_STATE_INIT = 1_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL::var_const_FB_HANDLER_STATE_INPUTS = 2_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL::var_const_FB_HANDLER_STATE_OPERATE = 3_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL::var_const_FB_HANDLER_STATE_OUTPUTS = 4_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL::var_const_FB_HANDLER_STATE_ABORT = 5_UINT;


  FORTE_ASGEVO_LAS_HDL::FORTE_ASGEVO_LAS_HDL(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      fb_HCONSOLE("HCONSOLE"_STRID, *this),
      fb_FB_LAS_HDL_OP("FB_LAS_HDL_OP"_STRID, *this),
      var_FB_CONSOLE_DBG(false_BOOL),
      var_STATE_OLD(0_UINT),
      var_STATE(0_UINT),
      var_INPUT(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS()),
      var_PARAM(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER()),
      var_TARGET(0_UINT),
      var_DONE(0_BOOL),
      var_OUTPUT(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS()),
      var_TIMING(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING()),
      var_ERRCODE(0_UINT),
      conn_CNF(*this, 0),
      conn_STATE(nullptr),
      conn_INPUT(nullptr),
      conn_PARAM(nullptr),
      conn_TARGET(nullptr),
      conn_DONE(*this, 0, var_DONE),
      conn_OUTPUT(*this, 1, var_OUTPUT),
      conn_TIMING(*this, 2, var_TIMING),
      conn_ERRCODE(*this, 3, var_ERRCODE) {
  }

  void FORTE_ASGEVO_LAS_HDL::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_FB_CONSOLE_DBG = false_BOOL;
    var_STATE_OLD = 0_UINT;
    var_STATE = 0_UINT;
    var_INPUT = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS();
    var_PARAM = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER();
    var_TARGET = 0_UINT;
    var_DONE = 0_BOOL;
    var_OUTPUT = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS();
    var_TIMING = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING();
    var_ERRCODE = 0_UINT;
  }

  void FORTE_ASGEVO_LAS_HDL::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventREQID:
        enterStateREQ(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_ASGEVO_LAS_HDL::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_ASGEVO_LAS_HDL::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventREQID: {
        readData(0, var_STATE, conn_STATE);
        readData(1, var_INPUT, conn_INPUT);
        readData(3, var_TARGET, conn_TARGET);
        readData(2, var_PARAM, conn_PARAM);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_ASGEVO_LAS_HDL::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        writeData(4, var_DONE, conn_DONE);
        writeData(5, var_OUTPUT, conn_OUTPUT);
        writeData(7, var_ERRCODE, conn_ERRCODE);
        writeData(6, var_TIMING, conn_TIMING);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_ASGEVO_LAS_HDL::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_STATE;
      case 1: return &var_INPUT;
      case 2: return &var_PARAM;
      case 3: return &var_TARGET;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_LAS_HDL::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_DONE;
      case 1: return &var_OUTPUT;
      case 2: return &var_TIMING;
      case 3: return &var_ERRCODE;
    }
    return nullptr;
  }

  CEventConnection *FORTE_ASGEVO_LAS_HDL::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_ASGEVO_LAS_HDL::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_STATE;
      case 1: return &conn_INPUT;
      case 2: return &conn_PARAM;
      case 3: return &conn_TARGET;
    }
    return nullptr;
  }

  CDataConnection *FORTE_ASGEVO_LAS_HDL::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_DONE;
      case 1: return &conn_OUTPUT;
      case 2: return &conn_TIMING;
      case 3: return &conn_ERRCODE;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_LAS_HDL::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_FB_CONSOLE_DBG;
      case 1: return &var_STATE_OLD;
    }
    return nullptr;
  }

  void FORTE_ASGEVO_LAS_HDL::alg_REQ(void) {

    #line 6 "ASGEVO_LAS_HDL.fbt"
    if (func_AND<CIEC_BOOL>(func_NE(var_STATE, var_const_FB_HANDLER_STATE_RESET), func_EQ(var_STATE_OLD, var_const_FB_HANDLER_STATE_RESET))) {
      #line 7 "ASGEVO_LAS_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_INIT"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 8 "ASGEVO_LAS_HDL.fbt"
      fb_FB_LAS_HDL_OP(false_BOOL, fb_FB_LAS_HDL_OP->var_INPUT, fb_FB_LAS_HDL_OP->var_PARAM, fb_FB_LAS_HDL_OP->var_TARGET, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING>(), COutputParameter<CIEC_UINT>());
      #line 9 "ASGEVO_LAS_HDL.fbt"
      fb_FB_LAS_HDL_OP(true_BOOL, var_INPUT, var_PARAM, var_TARGET, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING>(), COutputParameter<CIEC_UINT>());
      #line 10 "ASGEVO_LAS_HDL.fbt"
      var_DONE = fb_FB_LAS_HDL_OP->var_DONE;
    }
    #line 12 "ASGEVO_LAS_HDL.fbt"
    var_STATE_OLD = var_STATE;
    #line 14 "ASGEVO_LAS_HDL.fbt"
    if (auto st_lv_synthetic_0 = var_STATE; false) {
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_INIT)) {
      #line 18 "ASGEVO_LAS_HDL.fbt"
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_INPUTS)) {
      #line 21 "ASGEVO_LAS_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_INPUTS"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 22 "ASGEVO_LAS_HDL.fbt"
      fb_FB_LAS_HDL_OP(true_BOOL, var_INPUT, var_PARAM, var_TARGET, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING>(), COutputParameter<CIEC_UINT>());
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_OPERATE)) {
      #line 25 "ASGEVO_LAS_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_OPERATE"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 26 "ASGEVO_LAS_HDL.fbt"
      fb_FB_LAS_HDL_OP(true_BOOL, var_INPUT, var_PARAM, var_TARGET, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING>(), COutputParameter<CIEC_UINT>());
      #line 28 "ASGEVO_LAS_HDL.fbt"
      var_DONE = fb_FB_LAS_HDL_OP->var_DONE;
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_OUTPUTS)) {
      #line 31 "ASGEVO_LAS_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_OUTPUTS"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 33 "ASGEVO_LAS_HDL.fbt"
      var_DONE = fb_FB_LAS_HDL_OP->var_DONE;
    } else if (func_EQ(st_lv_synthetic_0, var_const_FB_HANDLER_STATE_ABORT)) {
      #line 36 "ASGEVO_LAS_HDL.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_HDL_ABORT"_STRING, var_STATE, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 37 "ASGEVO_LAS_HDL.fbt"
      fb_FB_LAS_HDL_OP(false_BOOL, fb_FB_LAS_HDL_OP->var_INPUT, fb_FB_LAS_HDL_OP->var_PARAM, fb_FB_LAS_HDL_OP->var_TARGET, CAnyBitOutputParameter<CIEC_BOOL>(), CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING>(), COutputParameter<CIEC_UINT>());
      #line 38 "ASGEVO_LAS_HDL.fbt"
      var_DONE = true_BOOL;
    } else {
      #line 42 "ASGEVO_LAS_HDL.fbt"
    }
    #line 46 "ASGEVO_LAS_HDL.fbt"
    var_OUTPUT = fb_FB_LAS_HDL_OP->var_OUTPUT;
    #line 47 "ASGEVO_LAS_HDL.fbt"
    var_TIMING = fb_FB_LAS_HDL_OP->var_TIMING;
    #line 48 "ASGEVO_LAS_HDL.fbt"
    var_ERRCODE = fb_FB_LAS_HDL_OP->var_ERRCODE;
  }

}