/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_IEC61131_TEMPL_HDL_OP
 *** Description: Simple FB with one algorithm
 *** Version:
 ***     1.0: 2026-02-26/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/ASGEVO_IEC61131_TEMPL_HDL_OP_fbt.h"

#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/OUTPUTS_IEC61131_TMPL_dtp.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_sint.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::TEMPLATE {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:MS-nqKqFYfybCZzhfOe-vii7NB9D58yA2J6X6eX6VQNjdOao2ngErJZTbDUeDcnlBbab8wyRoQ-JZNGpTz9crQ=="sv;

    const auto cEventInputNames = std::array{"REQ"_STRID};
    const auto cEventOutputNames = std::array{"CNF"_STRID};
    const auto cDataInputNames = std::array{"INIT"_STRID, "INPUT"_STRID};
    const auto cDataOutputNames = std::array{"DONE"_STRID, "BUSY"_STRID, "ERRCODE"_STRID, "OUTPUT"_STRID};
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

    const auto cInternalsNames = std::array{"FB_STEP"_STRID, "INIT_OLD"_STRID, "FB_CONSOLE_DBG"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP, "ASGEVO_PACKAGE::FB::TEMPLATE::ASGEVO_IEC61131_TEMPL_HDL_OP"_STRID, TypeHash)
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::var_const_FB_STEP_OFF = 0_UINT;
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::var_const_FB_STEP_INIT = 1_UINT;
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::var_const_FB_STEP_FIRST_OP = 2_UINT;
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::var_const_FB_STEP_SECOND_OP = 3_UINT;


  FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      fb_HCONSOLE("HCONSOLE"_STRID, *this),
      fb_T_PREWARN("T_PREWARN"_STRID, *this),
      fb_T_LAS_STARTDELAY("T_LAS_STARTDELAY"_STRID, *this),
      fb_T_LAS_LOWER("T_LAS_LOWER"_STRID, *this),
      fb_T_LAS_DELAY_ADVANCE("T_LAS_DELAY_ADVANCE"_STRID, *this),
      fb_T_LAS_ADVANCE("T_LAS_ADVANCE"_STRID, *this),
      fb_T_LAS_SET("T_LAS_SET"_STRID, *this),
      var_FB_STEP(0_UINT),
      var_INIT_OLD(0_BOOL),
      var_FB_CONSOLE_DBG(true_BOOL),
      var_INIT(0_BOOL),
      var_INPUT(forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_INPUTS_IEC61131_TMPL()),
      var_DONE(0_BOOL),
      var_BUSY(0_BOOL),
      var_ERRCODE(0_UINT),
      var_OUTPUT(forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL()),
      conn_CNF(*this, 0),
      conn_INIT(nullptr),
      conn_INPUT(nullptr),
      conn_DONE(*this, 0, var_DONE),
      conn_BUSY(*this, 1, var_BUSY),
      conn_ERRCODE(*this, 2, var_ERRCODE),
      conn_OUTPUT(*this, 3, var_OUTPUT) {
  }

  void FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_FB_STEP = 0_UINT;
    var_INIT_OLD = 0_BOOL;
    var_FB_CONSOLE_DBG = true_BOOL;
    var_INIT = 0_BOOL;
    var_INPUT = forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_INPUTS_IEC61131_TMPL();
    var_DONE = 0_BOOL;
    var_BUSY = 0_BOOL;
    var_ERRCODE = 0_UINT;
    var_OUTPUT = forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL();
  }

  void FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventREQID:
        enterStateREQ(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventREQID: {
        readData(0, var_INIT, conn_INIT);
        readData(1, var_INPUT, conn_INPUT);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        writeData(2, var_DONE, conn_DONE);
        writeData(3, var_BUSY, conn_BUSY);
        writeData(4, var_ERRCODE, conn_ERRCODE);
        writeData(5, var_OUTPUT, conn_OUTPUT);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_INIT;
      case 1: return &var_INPUT;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_DONE;
      case 1: return &var_BUSY;
      case 2: return &var_ERRCODE;
      case 3: return &var_OUTPUT;
    }
    return nullptr;
  }

  CEventConnection *FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INIT;
      case 1: return &conn_INPUT;
    }
    return nullptr;
  }

  CDataConnection *FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_DONE;
      case 1: return &conn_BUSY;
      case 2: return &conn_ERRCODE;
      case 3: return &conn_OUTPUT;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_FB_STEP;
      case 1: return &var_INIT_OLD;
      case 2: return &var_FB_CONSOLE_DBG;
    }
    return nullptr;
  }

  void FORTE_ASGEVO_IEC61131_TEMPL_HDL_OP::alg_REQ(void) {

    #line 4 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
    if (func_AND<CIEC_BOOL>(func_EQ(var_INIT, true_BOOL), func_EQ(var_INIT_OLD, false_BOOL))) {
      #line 5 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_INIT"_STRING, 0_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
      #line 6 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      var_FB_STEP = var_const_FB_STEP_INIT;
      #line 9 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      var_OUTPUT.var_OUTVAR1 = false_BOOL;
      #line 10 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      var_OUTPUT.var_OUTVAR2 = 123_UINT;
      #line 12 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      var_DONE = false_BOOL;
      #line 13 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      var_BUSY = true_BOOL;
    }
    #line 15 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
    var_INIT_OLD = var_INIT;
    #line 17 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
    if (func_EQ(var_INIT, true_BOOL)) {
      #line 21 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      if (auto st_lv_synthetic_0 = var_FB_STEP; false) {
      } else if (func_EQ(st_lv_synthetic_0, var_const_FB_STEP_FIRST_OP)) {
        #line 23 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
        fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_STEP_FIRST_OP"_STRING, 0_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
        #line 25 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
        var_OUTPUT.var_OUTVAR1 = true_BOOL;
        #line 26 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
        var_FB_STEP = var_const_FB_STEP_SECOND_OP;
      } else if (func_EQ(st_lv_synthetic_0, var_const_FB_STEP_SECOND_OP)) {
        #line 29 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
        fb_HCONSOLE(var_FB_CONSOLE_DBG, "FB_STEP_SECOND_OP"_STRING, 0_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
        #line 31 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
        var_OUTPUT.var_OUTVAR2 = 456_UINT;
        #line 32 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
        var_FB_STEP = var_const_FB_STEP_OFF;
      } else if (func_EQ(st_lv_synthetic_0, var_const_FB_STEP_OFF)) {
        #line 36 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
        var_BUSY = false_BOOL;
        #line 37 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
        var_DONE = true_BOOL;
        #line 38 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      } else {
        #line 41 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      }
    }
    else {
      #line 47 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      var_OUTPUT.var_OUTVAR1 = false_BOOL;
      #line 48 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      var_OUTPUT.var_OUTVAR2 = 0_UINT;
      #line 50 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      var_BUSY = false_BOOL;
      #line 51 "ASGEVO_IEC61131_TEMPL_HDL_OP.fbt"
      var_DONE = true_BOOL;
    }
  }

}