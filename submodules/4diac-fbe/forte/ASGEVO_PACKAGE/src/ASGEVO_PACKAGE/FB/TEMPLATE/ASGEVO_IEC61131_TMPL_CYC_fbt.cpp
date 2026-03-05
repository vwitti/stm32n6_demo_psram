/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_IEC61131_TMPL_CYC
 *** Description: Basic FB with empty ECC
 *** Version:
 ***     1.0: 2026-02-26/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/ASGEVO_IEC61131_TMPL_CYC_fbt.h"

#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/INPUTS_IEC61131_TMPL_dtp.h"
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
    constexpr std::string_view TypeHash ="v1:SHA3-512:VnzOdtf8wLyyiMNvWQ7raljVdZqnu5UfFFJlPSpHAgNTZeGNieLXA1SEHZV11kYKx3wNF9qLJBqv6nJ2Db3hNw=="sv;

    const auto cEventInputNames = std::array{"REQ"_STRID, "ABORT"_STRID, "IDLE"_STRID, "FREEZE"_STRID};
    const auto cEventOutputNames = std::array{"EO"_STRID, "BUSY"_STRID, "DONE"_STRID};
    const auto cDataInputNames = std::array{"INPUT"_STRID};
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

    const auto cInternalsNames = std::array{"FB_BUSY"_STRID, "FB_DONE"_STRID, "FB_INIT"_STRID, "FB_IDLE"_STRID, "FB_FREEZE"_STRID, "FB_STATE"_STRID, "FB_CONSOLE_DBG"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_ASGEVO_IEC61131_TMPL_CYC, "ASGEVO_PACKAGE::FB::TEMPLATE::ASGEVO_IEC61131_TMPL_CYC"_STRID, TypeHash)
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TMPL_CYC::var_const_FB_HANDLER_STATE_RESET = 0_UINT;
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TMPL_CYC::var_const_FB_HANDLER_STATE_INIT = 1_UINT;
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TMPL_CYC::var_const_FB_HANDLER_STATE_INPUTS = 2_UINT;
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TMPL_CYC::var_const_FB_HANDLER_STATE_OPERATE = 3_UINT;
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TMPL_CYC::var_const_FB_HANDLER_STATE_OUTPUTS = 4_UINT;
  const CIEC_UINT FORTE_ASGEVO_IEC61131_TMPL_CYC::var_const_FB_HANDLER_STATE_ABORT = 5_UINT;


  FORTE_ASGEVO_IEC61131_TMPL_CYC::FORTE_ASGEVO_IEC61131_TMPL_CYC(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      fb_HCONSOLE("HCONSOLE"_STRID, *this),
      fb_FB_HANDLER("FB_HANDLER"_STRID, *this),
      var_FB_BUSY(0_BOOL),
      var_FB_DONE(0_BOOL),
      var_FB_INIT(0_BOOL),
      var_FB_IDLE(0_BOOL),
      var_FB_FREEZE(0_BOOL),
      var_FB_STATE(0_UINT),
      var_FB_CONSOLE_DBG(false_BOOL),
      var_INPUT(forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_INPUTS_IEC61131_TMPL()),
      var_OUTPUT(forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL()),
      var_ERRCODE(0_UINT),
      conn_EO(*this, 0),
      conn_BUSY(*this, 1),
      conn_DONE(*this, 2),
      conn_INPUT(nullptr),
      conn_OUTPUT(*this, 0, var_OUTPUT),
      conn_ERRCODE(*this, 1, var_ERRCODE) {
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::setInitialValues() {
    CBasicFB::setInitialValues();
    var_FB_BUSY = 0_BOOL;
    var_FB_DONE = 0_BOOL;
    var_FB_INIT = 0_BOOL;
    var_FB_IDLE = 0_BOOL;
    var_FB_FREEZE = 0_BOOL;
    var_FB_STATE = 0_UINT;
    var_FB_CONSOLE_DBG = false_BOOL;
    var_INPUT = forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_INPUTS_IEC61131_TMPL();
    var_OUTPUT = forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL();
    var_ERRCODE = 0_UINT;
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if((scmEventABORTID == paEIID) && (true_BOOL)) enterStateST_ABORT(paECET);
          else
          if((scmEventREQID == paEIID) && (func_EQ(var_FB_INIT, false_BOOL))) enterStateST_INIT(paECET);
          else
          if((scmEventREQID == paEIID) && (func_AND<CIEC_BOOL>(func_EQ(var_FB_INIT, true_BOOL), func_EQ(var_FB_BUSY, true_BOOL)))) enterStateST_OPERATE(paECET);
          else
          if((scmEventIDLEID == paEIID) && (true_BOOL)) enterStateST_IDLE(paECET);
          else
          if((scmEventFREEZEID == paEIID) && (true_BOOL)) enterStateST_FREEZE(paECET);
          else return; //no transition cleared
          break;
        case scmStateST_INIT:
          if(func_EQ(var_FB_DONE, false_BOOL)) enterStateST_OPERATE(paECET);
          else
          if(func_EQ(var_FB_DONE, true_BOOL)) enterStateST_OUTPUTS(paECET);
          else return; //no transition cleared
          break;
        case scmStateST_OPERATE:
          if(true_BOOL) enterStateST_OUTPUTS(paECET);
          else return; //no transition cleared
          break;
        case scmStateST_OUTPUTS:
          if(func_EQ(var_FB_DONE, true_BOOL)) enterStateST_OUTPUTS_DONE(paECET);
          else
          if(func_EQ(var_FB_DONE, false_BOOL)) enterStateST_OUTPUTS_BUSY(paECET);
          else return; //no transition cleared
          break;
        case scmStateST_IDLE:
          if(true_BOOL) enterStateST_OUTPUTS_BUSY(paECET);
          else return; //no transition cleared
          break;
        case scmStateST_OUTPUTS_DONE:
          if(true_BOOL) enterStateST_END(paECET);
          else return; //no transition cleared
          break;
        case scmStateST_OUTPUTS_BUSY:
          if(true_BOOL) enterStateST_END(paECET);
          else return; //no transition cleared
          break;
        case scmStateST_ABORT:
          if(true_BOOL) enterStateST_OUTPUTS_DONE(paECET);
          else return; //no transition cleared
          break;
        case scmStateST_END:
          if(true_BOOL) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateST_FREEZE:
          if(true_BOOL) enterStateST_OUTPUTS_BUSY(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 10.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateST_INIT(CEventChainExecutionThread *const) {
    mECCState = scmStateST_INIT;
    alg_ACT_INIT();
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateST_OPERATE(CEventChainExecutionThread *const) {
    mECCState = scmStateST_OPERATE;
    alg_ACT_OPERATE();
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateST_OUTPUTS(CEventChainExecutionThread *const) {
    mECCState = scmStateST_OUTPUTS;
    alg_ACT_OUPUTS();
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateST_IDLE(CEventChainExecutionThread *const) {
    mECCState = scmStateST_IDLE;
    alg_ACT_IDLE();
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateST_OUTPUTS_DONE(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateST_OUTPUTS_DONE;
    alg_ACT_OUTPUTS_DONE();
    sendOutputEvent(scmEventDONEID, paECET);
    alg_ACT_OUTPUTS_DONE_EO();
    sendOutputEvent(scmEventEOID, paECET);
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateST_OUTPUTS_BUSY(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateST_OUTPUTS_BUSY;
    alg_ACT_OUTPUTS_BUSY();
    sendOutputEvent(scmEventBUSYID, paECET);
    alg_ACT_OUTPUTS_BUSY_EO();
    sendOutputEvent(scmEventEOID, paECET);
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateST_ABORT(CEventChainExecutionThread *const) {
    mECCState = scmStateST_ABORT;
    alg_ACT_ABORT();
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateST_END(CEventChainExecutionThread *const) {
    mECCState = scmStateST_END;
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::enterStateST_FREEZE(CEventChainExecutionThread *const) {
    mECCState = scmStateST_FREEZE;
    alg_ACT_FREEZE();
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventREQID: {
        readData(0, var_INPUT, conn_INPUT);
        break;
      }
      case scmEventABORTID: {
        readData(0, var_INPUT, conn_INPUT);
        break;
      }
      case scmEventIDLEID: {
        readData(0, var_INPUT, conn_INPUT);
        break;
      }
      case scmEventFREEZEID: {
        readData(0, var_INPUT, conn_INPUT);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventEOID: {
        writeData(2, var_ERRCODE, conn_ERRCODE);
        writeData(1, var_OUTPUT, conn_OUTPUT);
        break;
      }
      case scmEventBUSYID: {
        writeData(2, var_ERRCODE, conn_ERRCODE);
        writeData(1, var_OUTPUT, conn_OUTPUT);
        break;
      }
      case scmEventDONEID: {
        writeData(2, var_ERRCODE, conn_ERRCODE);
        writeData(1, var_OUTPUT, conn_OUTPUT);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_ASGEVO_IEC61131_TMPL_CYC::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_INPUT;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_IEC61131_TMPL_CYC::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_OUTPUT;
      case 1: return &var_ERRCODE;
    }
    return nullptr;
  }

  CEventConnection *FORTE_ASGEVO_IEC61131_TMPL_CYC::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_EO;
      case 1: return &conn_BUSY;
      case 2: return &conn_DONE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_ASGEVO_IEC61131_TMPL_CYC::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INPUT;
    }
    return nullptr;
  }

  CDataConnection *FORTE_ASGEVO_IEC61131_TMPL_CYC::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_OUTPUT;
      case 1: return &conn_ERRCODE;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_ASGEVO_IEC61131_TMPL_CYC::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_FB_BUSY;
      case 1: return &var_FB_DONE;
      case 2: return &var_FB_INIT;
      case 3: return &var_FB_IDLE;
      case 4: return &var_FB_FREEZE;
      case 5: return &var_FB_STATE;
      case 6: return &var_FB_CONSOLE_DBG;
    }
    return nullptr;
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_INIT(void) {

    #line 5 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_HCONSOLE(var_FB_CONSOLE_DBG, "CYC_ACT_INIT"_STRING, 0_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
    #line 7 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_STATE = var_const_FB_HANDLER_STATE_RESET;
    #line 8 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_FB_HANDLER(var_FB_STATE, fb_FB_HANDLER->var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL>());
    #line 9 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_STATE = var_const_FB_HANDLER_STATE_INIT;
    #line 10 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_FB_HANDLER(var_FB_STATE, var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL>());
    #line 11 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_IDLE = false_BOOL;
    #line 12 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_FREEZE = false_BOOL;
    #line 13 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    if (func_EQ(fb_FB_HANDLER->var_DONE, true_BOOL)) {
      #line 16 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_OUTPUT = fb_FB_HANDLER->var_OUTPUT;
      #line 17 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_ERRCODE = fb_FB_HANDLER->var_ERRCODE;
      #line 18 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_FB_INIT = false_BOOL;
      #line 19 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_FB_BUSY = false_BOOL;
      #line 20 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_FB_DONE = true_BOOL;
    }
    else {
      #line 23 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_FB_INIT = true_BOOL;
      #line 24 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_FB_BUSY = true_BOOL;
      #line 25 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_FB_DONE = false_BOOL;
    }
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_IDLE(void) {

    #line 32 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_HCONSOLE(var_FB_CONSOLE_DBG, "CYC_ACT_IDLE"_STRING, 0_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
    #line 33 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_IDLE = func_NOT<CIEC_BOOL>(var_FB_IDLE);
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_FREEZE(void) {

    #line 40 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_HCONSOLE(var_FB_CONSOLE_DBG, "CYC_ACT_FREEZE"_STRING, 0_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
    #line 41 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_FREEZE = func_NOT<CIEC_BOOL>(var_FB_FREEZE);
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_OPERATE(void) {

    #line 46 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_HCONSOLE(var_FB_CONSOLE_DBG, "CYC_ACT_OPERATE"_STRING, 3_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
    #line 49 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    if (func_EQ(var_FB_IDLE, false_BOOL)) {
      #line 50 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_FB_STATE = var_const_FB_HANDLER_STATE_OPERATE;
      #line 51 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      fb_FB_HANDLER(var_FB_STATE, var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL>());
      #line 52 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      if (func_EQ(fb_FB_HANDLER->var_DONE, true_BOOL)) {
        #line 55 "ASGEVO_IEC61131_TMPL_CYC.fbt"
        var_OUTPUT = fb_FB_HANDLER->var_OUTPUT;
        #line 56 "ASGEVO_IEC61131_TMPL_CYC.fbt"
        var_ERRCODE = fb_FB_HANDLER->var_ERRCODE;
        #line 57 "ASGEVO_IEC61131_TMPL_CYC.fbt"
        var_FB_BUSY = false_BOOL;
        #line 58 "ASGEVO_IEC61131_TMPL_CYC.fbt"
        var_FB_DONE = true_BOOL;
      }
      else {
        #line 61 "ASGEVO_IEC61131_TMPL_CYC.fbt"
        var_FB_BUSY = true_BOOL;
        #line 62 "ASGEVO_IEC61131_TMPL_CYC.fbt"
        var_FB_DONE = false_BOOL;
      }
    }
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_OUPUTS(void) {

    #line 69 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_HCONSOLE(var_FB_CONSOLE_DBG, "CYC_ACT_OUTPUTS"_STRING, 2_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
    #line 70 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    if (func_EQ(var_FB_FREEZE, false_BOOL)) {
      #line 71 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_FB_STATE = var_const_FB_HANDLER_STATE_OUTPUTS;
      #line 72 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      fb_FB_HANDLER(var_FB_STATE, fb_FB_HANDLER->var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL>());
      #line 74 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_OUTPUT = fb_FB_HANDLER->var_OUTPUT;
      #line 75 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_ERRCODE = fb_FB_HANDLER->var_ERRCODE;
      #line 76 "ASGEVO_IEC61131_TMPL_CYC.fbt"
      var_FB_DONE = fb_FB_HANDLER->var_DONE;
    }
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_OUTPUTS_BUSY(void) {

  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_OUTPUTS_BUSY_EO(void) {

  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_OUTPUTS_DONE(void) {

  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_OUTPUTS_DONE_EO(void) {

    #line 102 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_HCONSOLE(var_FB_CONSOLE_DBG, "CYC_ACT_OUTPUTS_DONE_EO"_STRING, 0_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
    #line 103 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_INIT = false_BOOL;
  }

  void FORTE_ASGEVO_IEC61131_TMPL_CYC::alg_ACT_ABORT(void) {

    #line 108 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_HCONSOLE(var_FB_CONSOLE_DBG, "CYC_ACT_ABORT"_STRING, 4_SINT, CAnyBitOutputParameter<CIEC_BOOL>());
    #line 110 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_STATE = var_const_FB_HANDLER_STATE_ABORT;
    #line 111 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    fb_FB_HANDLER(var_FB_STATE, fb_FB_HANDLER->var_INPUT, CAnyBitOutputParameter<CIEC_BOOL>(), COutputParameter<CIEC_UINT>(), COutputParameter<forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL>());
    #line 113 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_OUTPUT = fb_FB_HANDLER->var_OUTPUT;
    #line 114 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_ERRCODE = fb_FB_HANDLER->var_ERRCODE;
    #line 116 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_ERRCODE = 255_UINT;
    #line 117 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_INIT = false_BOOL;
    #line 118 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_IDLE = false_BOOL;
    #line 119 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_FREEZE = false_BOOL;
    #line 120 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_BUSY = false_BOOL;
    #line 121 "ASGEVO_IEC61131_TMPL_CYC.fbt"
    var_FB_DONE = true_BOOL;
  }

}