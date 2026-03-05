/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_LAS_CYC
 *** Description: Basic FB with empty ECC
 *** Version:
 ***     1.0: 2026-02-26/volker -  -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_INPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_TIMING_dtp.h"
#include "forte/datatypes/forte_any_variant.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/ASGEVO_LAS_HDL_fbt.h"
#include "forte/eclipse4diac/utils/OUT_ANY_CONSOLE_fbt.h"

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  class FORTE_ASGEVO_LAS_CYC final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_ASGEVO_LAS_CYC)

    private:
      static const TEventID scmEventEOID = 0;
      static const TEventID scmEventBUSYID = 1;
      static const TEventID scmEventDONEID = 2;
      static const TEventID scmEventREQID = 0;
      static const TEventID scmEventABORTID = 1;
      static const TEventID scmEventIDLEID = 2;
      static const TEventID scmEventFREEZEID = 3;

      CIEC_BOOL var_FB_BUSY;
      CIEC_BOOL var_FB_DONE;
      CIEC_BOOL var_FB_INIT;
      CIEC_BOOL var_FB_IDLE;
      CIEC_BOOL var_FB_FREEZE;
      CIEC_UINT var_FB_STATE;
      CIEC_BOOL var_FB_CONSOLE_DBG;

      static const CIEC_UINT var_const_FB_HANDLER_STATE_RESET;
      static const CIEC_UINT var_const_FB_HANDLER_STATE_INIT;
      static const CIEC_UINT var_const_FB_HANDLER_STATE_INPUTS;
      static const CIEC_UINT var_const_FB_HANDLER_STATE_OPERATE;
      static const CIEC_UINT var_const_FB_HANDLER_STATE_OUTPUTS;
      static const CIEC_UINT var_const_FB_HANDLER_STATE_ABORT;

      CIEC_ANY *getVarInternal(size_t) override;

      CInternalFB<forte::eclipse4diac::utils::FORTE_OUT_ANY_CONSOLE> fb_HCONSOLE;
      CInternalFB<forte::ASGEVO_PACKAGE::FB::LAS::FORTE_ASGEVO_LAS_HDL> fb_FB_HANDLER;
      void alg_ACT_INIT(void);
      void alg_ACT_IDLE(void);
      void alg_ACT_FREEZE(void);
      void alg_ACT_OPERATE(void);
      void alg_ACT_OUPUTS(void);
      void alg_ACT_OUTPUTS_BUSY(void);
      void alg_ACT_OUTPUTS_BUSY_EO(void);
      void alg_ACT_OUTPUTS_DONE(void);
      void alg_ACT_OUTPUTS_DONE_EO(void);
      void alg_ACT_ABORT(void);

      static const TForteInt16 scmStateSTART = 0;
      static const TForteInt16 scmStateST_INIT = 1;
      static const TForteInt16 scmStateST_OPERATE = 2;
      static const TForteInt16 scmStateST_OUTPUTS = 3;
      static const TForteInt16 scmStateST_IDLE = 4;
      static const TForteInt16 scmStateST_OUTPUTS_DONE = 5;
      static const TForteInt16 scmStateST_OUTPUTS_BUSY = 6;
      static const TForteInt16 scmStateST_ABORT = 7;
      static const TForteInt16 scmStateST_END = 8;
      static const TForteInt16 scmStateST_FREEZE = 9;

      void enterStateSTART(CEventChainExecutionThread *const paECET);
      void enterStateST_INIT(CEventChainExecutionThread *const paECET);
      void enterStateST_OPERATE(CEventChainExecutionThread *const paECET);
      void enterStateST_OUTPUTS(CEventChainExecutionThread *const paECET);
      void enterStateST_IDLE(CEventChainExecutionThread *const paECET);
      void enterStateST_OUTPUTS_DONE(CEventChainExecutionThread *const paECET);
      void enterStateST_OUTPUTS_BUSY(CEventChainExecutionThread *const paECET);
      void enterStateST_ABORT(CEventChainExecutionThread *const paECET);
      void enterStateST_END(CEventChainExecutionThread *const paECET);
      void enterStateST_FREEZE(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_ASGEVO_LAS_CYC(StringId paInstanceNameId, CFBContainer &paContainer);

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS var_INPUT;
      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_PARAM;
      CIEC_UINT var_TARGET;

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS var_OUTPUT;
      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING var_TIMING;
      CIEC_UINT var_ERRCODE;

      CEventConnection conn_EO;
      CEventConnection conn_BUSY;
      CEventConnection conn_DONE;

      CDataConnection *conn_INPUT;
      CDataConnection *conn_PARAM;
      CDataConnection *conn_TARGET;

      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> conn_OUTPUT;
      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING> conn_TIMING;
      COutDataConnection<CIEC_UINT> conn_ERRCODE;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_REQ(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS &paINPUT, const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER &paPARAM, const CIEC_UINT &paTARGET, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUT, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING> paTIMING, COutputParameter<CIEC_UINT> paERRCODE) {
        COutputGuard guard_OUTPUT(paOUTPUT);
        COutputGuard guard_TIMING(paTIMING);
        COutputGuard guard_ERRCODE(paERRCODE);
        var_INPUT = paINPUT;
        var_PARAM = paPARAM;
        var_TARGET = paTARGET;
        executeEvent(scmEventREQID, nullptr);
        *paOUTPUT = var_OUTPUT;
        *paTIMING = var_TIMING;
        *paERRCODE = var_ERRCODE;
      }

      void evt_ABORT(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS &paINPUT, const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER &paPARAM, const CIEC_UINT &paTARGET, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUT, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING> paTIMING, COutputParameter<CIEC_UINT> paERRCODE) {
        COutputGuard guard_OUTPUT(paOUTPUT);
        COutputGuard guard_TIMING(paTIMING);
        COutputGuard guard_ERRCODE(paERRCODE);
        var_INPUT = paINPUT;
        var_PARAM = paPARAM;
        var_TARGET = paTARGET;
        executeEvent(scmEventABORTID, nullptr);
        *paOUTPUT = var_OUTPUT;
        *paTIMING = var_TIMING;
        *paERRCODE = var_ERRCODE;
      }

      void evt_IDLE(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS &paINPUT, const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER &paPARAM, const CIEC_UINT &paTARGET, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUT, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING> paTIMING, COutputParameter<CIEC_UINT> paERRCODE) {
        COutputGuard guard_OUTPUT(paOUTPUT);
        COutputGuard guard_TIMING(paTIMING);
        COutputGuard guard_ERRCODE(paERRCODE);
        var_INPUT = paINPUT;
        var_PARAM = paPARAM;
        var_TARGET = paTARGET;
        executeEvent(scmEventIDLEID, nullptr);
        *paOUTPUT = var_OUTPUT;
        *paTIMING = var_TIMING;
        *paERRCODE = var_ERRCODE;
      }

      void evt_FREEZE(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS &paINPUT, const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER &paPARAM, const CIEC_UINT &paTARGET, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUT, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING> paTIMING, COutputParameter<CIEC_UINT> paERRCODE) {
        COutputGuard guard_OUTPUT(paOUTPUT);
        COutputGuard guard_TIMING(paTIMING);
        COutputGuard guard_ERRCODE(paERRCODE);
        var_INPUT = paINPUT;
        var_PARAM = paPARAM;
        var_TARGET = paTARGET;
        executeEvent(scmEventFREEZEID, nullptr);
        *paOUTPUT = var_OUTPUT;
        *paTIMING = var_TIMING;
        *paERRCODE = var_ERRCODE;
      }
  };
}

