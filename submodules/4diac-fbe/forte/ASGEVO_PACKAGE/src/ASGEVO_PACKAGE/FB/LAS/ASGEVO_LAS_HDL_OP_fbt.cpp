/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_LAS_HDL_OP
 *** Description: Simple FB with one algorithm
 *** Version:
 ***     1.0: 2026-02-26/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/LAS/ASGEVO_LAS_HDL_OP_fbt.h"

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_INPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_sint.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_time.h"
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
    constexpr std::string_view TypeHash ="v1:SHA3-512:bThgSGQNETIyX0JjAhuXfJggDy-V6P5YBKU8J8QOTcEeBUMSQKaqr9r7bW7v2BGYlVw8R5Avp3n3RfN4OB3a0Q=="sv;

    const auto cEventInputNames = std::array{"REQ"_STRID};
    const auto cEventOutputNames = std::array{"CNF"_STRID};
    const auto cDataInputNames = std::array{"INIT"_STRID, "INPUT"_STRID, "PARAM"_STRID, "TARGET"_STRID};
    const auto cDataOutputNames = std::array{"DONE"_STRID, "BUSY"_STRID, "OUTPUT"_STRID, "TIMING"_STRID, "ERRCODE"_STRID};
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

    const auto cInternalsNames = std::array{"LAS_STEP"_STRID, "INIT_OLD"_STRID, "FB_CONSOLE_DBG"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_ASGEVO_LAS_HDL_OP, "ASGEVO_PACKAGE::FB::LAS::ASGEVO_LAS_HDL_OP"_STRID, TypeHash)
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL_OP::var_const_LAS_STEP_OFF = 0_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL_OP::var_const_LAS_STEP_PREWARN = 1_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL_OP::var_const_LAS_STEP_TC_LOWER_DELAY = 2_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL_OP::var_const_LAS_STEP_TC_LOWER_ADVANCE = 3_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL_OP::var_const_LAS_STEP_ADVANCE = 4_UINT;
  const CIEC_UINT FORTE_ASGEVO_LAS_HDL_OP::var_const_LAS_STEP_SET = 5_UINT;


  FORTE_ASGEVO_LAS_HDL_OP::FORTE_ASGEVO_LAS_HDL_OP(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      fb_HCONSOLE("HCONSOLE"_STRID, *this),
      fb_T_PREWARN("T_PREWARN"_STRID, *this),
      fb_T_LAS_STARTDELAY("T_LAS_STARTDELAY"_STRID, *this),
      fb_T_LAS_LOWER("T_LAS_LOWER"_STRID, *this),
      fb_T_LAS_DELAY_ADVANCE("T_LAS_DELAY_ADVANCE"_STRID, *this),
      fb_T_LAS_ADVANCE("T_LAS_ADVANCE"_STRID, *this),
      fb_T_LAS_SET("T_LAS_SET"_STRID, *this),
      var_LAS_STEP(0_UINT),
      var_INIT_OLD(0_BOOL),
      var_FB_CONSOLE_DBG(false_BOOL),
      var_INIT(0_BOOL),
      var_INPUT(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS()),
      var_PARAM(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER()),
      var_TARGET(0_UINT),
      var_DONE(0_BOOL),
      var_BUSY(0_BOOL),
      var_OUTPUT(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS()),
      var_TIMING(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING()),
      var_ERRCODE(0_UINT),
      conn_CNF(*this, 0),
      conn_INIT(nullptr),
      conn_INPUT(nullptr),
      conn_PARAM(nullptr),
      conn_TARGET(nullptr),
      conn_DONE(*this, 0, var_DONE),
      conn_BUSY(*this, 1, var_BUSY),
      conn_OUTPUT(*this, 2, var_OUTPUT),
      conn_TIMING(*this, 3, var_TIMING),
      conn_ERRCODE(*this, 4, var_ERRCODE) {
  }

  void FORTE_ASGEVO_LAS_HDL_OP::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_LAS_STEP = 0_UINT;
    var_INIT_OLD = 0_BOOL;
    var_FB_CONSOLE_DBG = false_BOOL;
    var_INIT = 0_BOOL;
    var_INPUT = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS();
    var_PARAM = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER();
    var_TARGET = 0_UINT;
    var_DONE = 0_BOOL;
    var_BUSY = 0_BOOL;
    var_OUTPUT = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS();
    var_TIMING = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING();
    var_ERRCODE = 0_UINT;
  }

  void FORTE_ASGEVO_LAS_HDL_OP::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventREQID:
        enterStateREQ(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_ASGEVO_LAS_HDL_OP::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_ASGEVO_LAS_HDL_OP::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventREQID: {
        readData(0, var_INIT, conn_INIT);
        readData(1, var_INPUT, conn_INPUT);
        readData(2, var_PARAM, conn_PARAM);
        readData(3, var_TARGET, conn_TARGET);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_ASGEVO_LAS_HDL_OP::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        writeData(4, var_DONE, conn_DONE);
        writeData(5, var_BUSY, conn_BUSY);
        writeData(6, var_OUTPUT, conn_OUTPUT);
        writeData(8, var_ERRCODE, conn_ERRCODE);
        writeData(7, var_TIMING, conn_TIMING);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_ASGEVO_LAS_HDL_OP::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_INIT;
      case 1: return &var_INPUT;
      case 2: return &var_PARAM;
      case 3: return &var_TARGET;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_LAS_HDL_OP::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_DONE;
      case 1: return &var_BUSY;
      case 2: return &var_OUTPUT;
      case 3: return &var_TIMING;
      case 4: return &var_ERRCODE;
    }
    return nullptr;
  }

  CEventConnection *FORTE_ASGEVO_LAS_HDL_OP::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_ASGEVO_LAS_HDL_OP::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INIT;
      case 1: return &conn_INPUT;
      case 2: return &conn_PARAM;
      case 3: return &conn_TARGET;
    }
    return nullptr;
  }

  CDataConnection *FORTE_ASGEVO_LAS_HDL_OP::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_DONE;
      case 1: return &conn_BUSY;
      case 2: return &conn_OUTPUT;
      case 3: return &conn_TIMING;
      case 4: return &conn_ERRCODE;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_LAS_HDL_OP::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_LAS_STEP;
      case 1: return &var_INIT_OLD;
      case 2: return &var_FB_CONSOLE_DBG;
    }
    return nullptr;
  }

  void FORTE_ASGEVO_LAS_HDL_OP::alg_REQ(void) {

    #line 4 "ASGEVO_LAS_HDL_OP.fbt"
    if (func_AND<CIEC_BOOL>(func_EQ(var_INIT, true_BOOL), func_EQ(var_INIT_OLD, false_BOOL))) {
      #line 5 "ASGEVO_LAS_HDL_OP.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_HDL_OP_INIT"_STRING, 0_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 6 "ASGEVO_LAS_HDL_OP.fbt"
      var_LAS_STEP = var_const_LAS_STEP_PREWARN;
      #line 8 "ASGEVO_LAS_HDL_OP.fbt"
      fb_T_PREWARN(false_BOOL, fb_T_PREWARN->var_PT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
      #line 9 "ASGEVO_LAS_HDL_OP.fbt"
      fb_T_LAS_STARTDELAY(false_BOOL, fb_T_LAS_STARTDELAY->var_PT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
      #line 10 "ASGEVO_LAS_HDL_OP.fbt"
      fb_T_LAS_LOWER(false_BOOL, fb_T_LAS_LOWER->var_PT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
      #line 11 "ASGEVO_LAS_HDL_OP.fbt"
      fb_T_LAS_DELAY_ADVANCE(false_BOOL, fb_T_LAS_DELAY_ADVANCE->var_PT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
      #line 12 "ASGEVO_LAS_HDL_OP.fbt"
      fb_T_LAS_ADVANCE(false_BOOL, fb_T_LAS_ADVANCE->var_PT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
      #line 13 "ASGEVO_LAS_HDL_OP.fbt"
      fb_T_LAS_SET(false_BOOL, fb_T_LAS_SET->var_PT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
      #line 14 "ASGEVO_LAS_HDL_OP.fbt"
      var_DONE = false_BOOL;
      #line 15 "ASGEVO_LAS_HDL_OP.fbt"
      var_BUSY = true_BOOL;
      #line 17 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_PREWARN = false_BOOL;
      #line 18 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_LOWER = false_BOOL;
      #line 19 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_PUSH = false_BOOL;
      #line 20 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_PULL = false_BOOL;
      #line 21 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_BL_EXT = false_BOOL;
      #line 22 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_BL_RET = false_BOOL;
      #line 23 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_STAB_EXT = false_BOOL;
      #line 24 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_STAB_RET = false_BOOL;
      #line 25 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_CA = false_BOOL;
    }
    #line 27 "ASGEVO_LAS_HDL_OP.fbt"
    var_INIT_OLD = var_INIT;
    #line 29 "ASGEVO_LAS_HDL_OP.fbt"
    if (func_EQ(var_INIT, true_BOOL)) {
      #line 33 "ASGEVO_LAS_HDL_OP.fbt"
      if (auto st_lv_synthetic_0 = var_LAS_STEP; false) {
      } else if (func_EQ(st_lv_synthetic_0, var_const_LAS_STEP_PREWARN)) {
        #line 35 "ASGEVO_LAS_HDL_OP.fbt"
        fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_HDL_OP_PREWARN"_STRING, var_PARAM.var_eP_AA_T_Vorwarnung, CAnyBitOutputParameter<CIEC_BOOL>());
        #line 36 "ASGEVO_LAS_HDL_OP.fbt"
        fb_T_PREWARN(true_BOOL, var_PARAM.var_eP_AA_T_Vorwarnung, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
        #line 37 "ASGEVO_LAS_HDL_OP.fbt"
        var_OUTPUT.var_PREWARN = true_BOOL;
        #line 38 "ASGEVO_LAS_HDL_OP.fbt"
        if (func_GE(fb_T_PREWARN->var_ET, fb_T_PREWARN->var_PT)) {
          #line 40 "ASGEVO_LAS_HDL_OP.fbt"
          fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_HDL_OP_PREWARN_DONE"_STRING, var_LAS_STEP, CAnyBitOutputParameter<CIEC_BOOL>());
          #line 41 "ASGEVO_LAS_HDL_OP.fbt"
          var_OUTPUT.var_PREWARN = false_BOOL;
          #line 42 "ASGEVO_LAS_HDL_OP.fbt"
          var_LAS_STEP = var_const_LAS_STEP_TC_LOWER_DELAY;
        }
      } else if (func_EQ(st_lv_synthetic_0, var_const_LAS_STEP_TC_LOWER_DELAY)) {
        #line 46 "ASGEVO_LAS_HDL_OP.fbt"
        fb_HCONSOLE(var_FB_CONSOLE_DBG, "TC_LOWER_DELAY"_STRING, var_LAS_STEP, CAnyBitOutputParameter<CIEC_BOOL>());
        #line 47 "ASGEVO_LAS_HDL_OP.fbt"
        fb_T_LAS_STARTDELAY(true_BOOL, var_PARAM.var_eP_AA_T_StartLAS, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
        #line 48 "ASGEVO_LAS_HDL_OP.fbt"
        if (func_GE(fb_T_LAS_STARTDELAY->var_ET, fb_T_LAS_STARTDELAY->var_PT)) {
          #line 49 "ASGEVO_LAS_HDL_OP.fbt"
          fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_HDL_OP_TC_LOWER_DELAY_DONE"_STRING, var_LAS_STEP, CAnyBitOutputParameter<CIEC_BOOL>());
          #line 51 "ASGEVO_LAS_HDL_OP.fbt"
          fb_T_LAS_LOWER(true_BOOL, var_PARAM.var_eP_AA_T_RaubenTC, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
          #line 52 "ASGEVO_LAS_HDL_OP.fbt"
          fb_T_LAS_DELAY_ADVANCE(true_BOOL, var_PARAM.var_eP_AA_T_StartSchreiten, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
          #line 53 "ASGEVO_LAS_HDL_OP.fbt"
          var_OUTPUT.var_LOWER = true_BOOL;
          #line 54 "ASGEVO_LAS_HDL_OP.fbt"
          var_LAS_STEP = var_const_LAS_STEP_TC_LOWER_ADVANCE;
        }
      } else if (func_EQ(st_lv_synthetic_0, var_const_LAS_STEP_TC_LOWER_ADVANCE)) {
        #line 58 "ASGEVO_LAS_HDL_OP.fbt"
        fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_HDL_OP_TC_LOWER_ADVANCE"_STRING, var_LAS_STEP, CAnyBitOutputParameter<CIEC_BOOL>());
        #line 62 "ASGEVO_LAS_HDL_OP.fbt"
        fb_T_LAS_LOWER(true_BOOL, var_PARAM.var_eP_AA_T_RaubenTC, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
        #line 63 "ASGEVO_LAS_HDL_OP.fbt"
        fb_T_LAS_DELAY_ADVANCE(true_BOOL, var_PARAM.var_eP_AA_T_StartSchreiten, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
        #line 65 "ASGEVO_LAS_HDL_OP.fbt"
        if (func_GE(fb_T_LAS_DELAY_ADVANCE->var_ET, fb_T_LAS_DELAY_ADVANCE->var_PT)) {
          #line 67 "ASGEVO_LAS_HDL_OP.fbt"
          fb_HCONSOLE(var_FB_CONSOLE_DBG, "TC_LOWER_ADVANCE_DONE"_STRING, var_LAS_STEP, CAnyBitOutputParameter<CIEC_BOOL>());
          #line 68 "ASGEVO_LAS_HDL_OP.fbt"
          fb_T_LAS_ADVANCE(true_BOOL, var_PARAM.var_eP_AA_T_Schreiten, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
          #line 69 "ASGEVO_LAS_HDL_OP.fbt"
          var_OUTPUT.var_PULL = true_BOOL;
          #line 70 "ASGEVO_LAS_HDL_OP.fbt"
          var_LAS_STEP = var_const_LAS_STEP_ADVANCE;
        }
      } else if (func_EQ(st_lv_synthetic_0, var_const_LAS_STEP_ADVANCE)) {
        #line 74 "ASGEVO_LAS_HDL_OP.fbt"
        fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_HDL_OP_ADVANCE"_STRING, var_LAS_STEP, CAnyBitOutputParameter<CIEC_BOOL>());
        #line 77 "ASGEVO_LAS_HDL_OP.fbt"
        fb_T_LAS_ADVANCE(true_BOOL, var_PARAM.var_eP_AA_T_Schreiten, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
        #line 78 "ASGEVO_LAS_HDL_OP.fbt"
        if (func_OR<CIEC_BOOL>(func_GE(fb_T_LAS_ADVANCE->var_ET, fb_T_LAS_ADVANCE->var_PT), func_LE(var_INPUT.var_RAM_STROKE, var_TARGET))) {
          #line 79 "ASGEVO_LAS_HDL_OP.fbt"
          var_OUTPUT.var_PULL = false_BOOL;
          #line 81 "ASGEVO_LAS_HDL_OP.fbt"
          fb_T_LAS_SET(true_BOOL, var_PARAM.var_eP_AA_T_Setzen, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
          #line 82 "ASGEVO_LAS_HDL_OP.fbt"
          var_LAS_STEP = var_const_LAS_STEP_SET;
        }
      } else if (func_EQ(st_lv_synthetic_0, var_const_LAS_STEP_SET)) {
        #line 87 "ASGEVO_LAS_HDL_OP.fbt"
        fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_HDL_OP_SET"_STRING, var_PARAM.var_eP_AA_T_Setzen, CAnyBitOutputParameter<CIEC_BOOL>());
        #line 88 "ASGEVO_LAS_HDL_OP.fbt"
        fb_T_LAS_SET(true_BOOL, fb_T_LAS_SET->var_PT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
        #line 89 "ASGEVO_LAS_HDL_OP.fbt"
        var_OUTPUT.var_SET = true_BOOL;
        #line 90 "ASGEVO_LAS_HDL_OP.fbt"
        if (func_GE(fb_T_LAS_SET->var_ET, fb_T_LAS_SET->var_PT)) {
          #line 92 "ASGEVO_LAS_HDL_OP.fbt"
          var_OUTPUT.var_SET = false_BOOL;
          #line 93 "ASGEVO_LAS_HDL_OP.fbt"
          var_LAS_STEP = var_const_LAS_STEP_OFF;
        }
      } else if (func_EQ(st_lv_synthetic_0, var_const_LAS_STEP_OFF)) {
        #line 96 "ASGEVO_LAS_HDL_OP.fbt"
        var_BUSY = false_BOOL;
        #line 97 "ASGEVO_LAS_HDL_OP.fbt"
        var_DONE = true_BOOL;
        #line 98 "ASGEVO_LAS_HDL_OP.fbt"
      } else {
        #line 101 "ASGEVO_LAS_HDL_OP.fbt"
      }
      #line 106 "ASGEVO_LAS_HDL_OP.fbt"
      fb_T_LAS_LOWER(true_BOOL, var_PARAM.var_eP_AA_T_RaubenTC, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_TIME>());
      #line 107 "ASGEVO_LAS_HDL_OP.fbt"
      if (func_GE(fb_T_LAS_LOWER->var_ET, fb_T_LAS_LOWER->var_PT)) {
        #line 108 "ASGEVO_LAS_HDL_OP.fbt"
        fb_HCONSOLE(var_FB_CONSOLE_DBG, "LAS_STEP_LOWER_DONE"_STRING, var_LAS_STEP, CAnyBitOutputParameter<CIEC_BOOL>());
        #line 109 "ASGEVO_LAS_HDL_OP.fbt"
        var_OUTPUT.var_LOWER = false_BOOL;
      }
    }
    else {
      #line 113 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_PREWARN = false_BOOL;
      #line 114 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_LOWER = false_BOOL;
      #line 115 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_PUSH = false_BOOL;
      #line 116 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_PULL = false_BOOL;
      #line 117 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_BL_EXT = false_BOOL;
      #line 118 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_BL_RET = false_BOOL;
      #line 119 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_STAB_EXT = false_BOOL;
      #line 120 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_STAB_RET = false_BOOL;
      #line 121 "ASGEVO_LAS_HDL_OP.fbt"
      var_OUTPUT.var_CA = false_BOOL;
      #line 123 "ASGEVO_LAS_HDL_OP.fbt"
      var_BUSY = false_BOOL;
      #line 124 "ASGEVO_LAS_HDL_OP.fbt"
      var_DONE = true_BOOL;
    }
  }

}