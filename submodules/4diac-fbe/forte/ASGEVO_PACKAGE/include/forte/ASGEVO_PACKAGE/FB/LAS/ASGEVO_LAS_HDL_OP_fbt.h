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

#pragma once

#include "forte/simplefb.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_INPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_TIMING_dtp.h"
#include "forte/datatypes/forte_any_variant.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"
#include "forte/eclipse4diac/utils/OUT_ANY_CONSOLE_fbt.h"
#include "forte/iec61131/timers/FB_TP_fbt.h"

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  class FORTE_ASGEVO_LAS_HDL_OP final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_ASGEVO_LAS_HDL_OP)

    private:
      static const TEventID scmEventCNFID = 0;
      static const TEventID scmEventREQID = 0;

      CIEC_UINT var_LAS_STEP;
      CIEC_BOOL var_INIT_OLD;
      CIEC_BOOL var_FB_CONSOLE_DBG;

      static const CIEC_UINT var_const_LAS_STEP_OFF;
      static const CIEC_UINT var_const_LAS_STEP_PREWARN;
      static const CIEC_UINT var_const_LAS_STEP_TC_LOWER_DELAY;
      static const CIEC_UINT var_const_LAS_STEP_TC_LOWER_ADVANCE;
      static const CIEC_UINT var_const_LAS_STEP_ADVANCE;
      static const CIEC_UINT var_const_LAS_STEP_SET;

      CIEC_ANY *getVarInternal(size_t) override;

      CInternalFB<forte::eclipse4diac::utils::FORTE_OUT_ANY_CONSOLE> fb_HCONSOLE;
      CInternalFB<forte::iec61131::timers::FORTE_FB_TP> fb_T_PREWARN;
      CInternalFB<forte::iec61131::timers::FORTE_FB_TP> fb_T_LAS_STARTDELAY;
      CInternalFB<forte::iec61131::timers::FORTE_FB_TP> fb_T_LAS_LOWER;
      CInternalFB<forte::iec61131::timers::FORTE_FB_TP> fb_T_LAS_DELAY_ADVANCE;
      CInternalFB<forte::iec61131::timers::FORTE_FB_TP> fb_T_LAS_ADVANCE;
      CInternalFB<forte::iec61131::timers::FORTE_FB_TP> fb_T_LAS_SET;
      void alg_REQ(void);

      void enterStateREQ(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_ASGEVO_LAS_HDL_OP(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_INIT;
      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS var_INPUT;
      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_PARAM;
      CIEC_UINT var_TARGET;

      CIEC_BOOL var_DONE;
      CIEC_BOOL var_BUSY;
      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS var_OUTPUT;
      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING var_TIMING;
      CIEC_UINT var_ERRCODE;

      CEventConnection conn_CNF;

      CDataConnection *conn_INIT;
      CDataConnection *conn_INPUT;
      CDataConnection *conn_PARAM;
      CDataConnection *conn_TARGET;

      COutDataConnection<CIEC_BOOL> conn_DONE;
      COutDataConnection<CIEC_BOOL> conn_BUSY;
      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> conn_OUTPUT;
      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING> conn_TIMING;
      COutDataConnection<CIEC_UINT> conn_ERRCODE;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_REQ(const CIEC_BOOL &paINIT, const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS &paINPUT, const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER &paPARAM, const CIEC_UINT &paTARGET, CAnyBitOutputParameter<CIEC_BOOL> paDONE, CAnyBitOutputParameter<CIEC_BOOL> paBUSY, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUT, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING> paTIMING, COutputParameter<CIEC_UINT> paERRCODE) {
        COutputGuard guard_DONE(paDONE);
        COutputGuard guard_BUSY(paBUSY);
        COutputGuard guard_OUTPUT(paOUTPUT);
        COutputGuard guard_TIMING(paTIMING);
        COutputGuard guard_ERRCODE(paERRCODE);
        var_INIT = paINIT;
        var_INPUT = paINPUT;
        var_PARAM = paPARAM;
        var_TARGET = paTARGET;
        executeEvent(scmEventREQID, nullptr);
        *paDONE = var_DONE;
        *paBUSY = var_BUSY;
        *paOUTPUT = var_OUTPUT;
        *paTIMING = var_TIMING;
        *paERRCODE = var_ERRCODE;
      }

      void operator()(const CIEC_BOOL &paINIT, const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS &paINPUT, const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER &paPARAM, const CIEC_UINT &paTARGET, CAnyBitOutputParameter<CIEC_BOOL> paDONE, CAnyBitOutputParameter<CIEC_BOOL> paBUSY, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUT, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING> paTIMING, COutputParameter<CIEC_UINT> paERRCODE) {
        evt_REQ(std::forward<const CIEC_BOOL &>(paINIT), std::forward<const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS &>(paINPUT), std::forward<const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER &>(paPARAM), std::forward<const CIEC_UINT &>(paTARGET), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paDONE), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paBUSY), std::forward<COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>>(paOUTPUT), std::forward<COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING>>(paTIMING), std::forward<COutputParameter<CIEC_UINT>>(paERRCODE));
      }
  };
}

