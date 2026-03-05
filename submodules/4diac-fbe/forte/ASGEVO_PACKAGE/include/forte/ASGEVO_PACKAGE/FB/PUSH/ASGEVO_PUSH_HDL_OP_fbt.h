/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_PUSH_HDL_OP
 *** Description: Simple FB with one algorithm
 *** Version:
 ***     1.0: 2026-02-26/volker -  -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/PUSH/INPUTS_PUSH_dtp.h"
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

namespace forte::ASGEVO_PACKAGE::FB::PUSH {
  class FORTE_ASGEVO_PUSH_HDL_OP final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_ASGEVO_PUSH_HDL_OP)

    private:
      static const TEventID scmEventCNFID = 0;
      static const TEventID scmEventREQID = 0;

      CIEC_UINT var_FB_STEP;
      CIEC_BOOL var_INIT_OLD;
      CIEC_BOOL var_FB_CONSOLE_DBG;

      static const CIEC_UINT var_const_FB_STEP_OFF;
      static const CIEC_UINT var_const_FB_STEP_INIT;
      static const CIEC_UINT var_const_FB_STEP_FIRST_OP;
      static const CIEC_UINT var_const_FB_STEP_SECOND_OP;

      CIEC_ANY *getVarInternal(size_t) override;

      CInternalFB<forte::eclipse4diac::utils::FORTE_OUT_ANY_CONSOLE> fb_HCONSOLE;
      CInternalFB<forte::iec61131::timers::FORTE_FB_TP> fb_T_PUSH;
      void alg_REQ(void);

      void enterStateREQ(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_ASGEVO_PUSH_HDL_OP(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_INIT;
      forte::ASGEVO_PACKAGE::FB::PUSH::CIEC_INPUTS_PUSH var_INPUT;

      CIEC_BOOL var_DONE;
      CIEC_BOOL var_BUSY;
      CIEC_UINT var_ERRCODE;
      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS var_OUTPUT;

      CEventConnection conn_CNF;

      CDataConnection *conn_INIT;
      CDataConnection *conn_INPUT;

      COutDataConnection<CIEC_BOOL> conn_DONE;
      COutDataConnection<CIEC_BOOL> conn_BUSY;
      COutDataConnection<CIEC_UINT> conn_ERRCODE;
      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> conn_OUTPUT;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_REQ(const CIEC_BOOL &paINIT, const forte::ASGEVO_PACKAGE::FB::PUSH::CIEC_INPUTS_PUSH &paINPUT, CAnyBitOutputParameter<CIEC_BOOL> paDONE, CAnyBitOutputParameter<CIEC_BOOL> paBUSY, COutputParameter<CIEC_UINT> paERRCODE, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUT) {
        COutputGuard guard_DONE(paDONE);
        COutputGuard guard_BUSY(paBUSY);
        COutputGuard guard_ERRCODE(paERRCODE);
        COutputGuard guard_OUTPUT(paOUTPUT);
        var_INIT = paINIT;
        var_INPUT = paINPUT;
        executeEvent(scmEventREQID, nullptr);
        *paDONE = var_DONE;
        *paBUSY = var_BUSY;
        *paERRCODE = var_ERRCODE;
        *paOUTPUT = var_OUTPUT;
      }

      void operator()(const CIEC_BOOL &paINIT, const forte::ASGEVO_PACKAGE::FB::PUSH::CIEC_INPUTS_PUSH &paINPUT, CAnyBitOutputParameter<CIEC_BOOL> paDONE, CAnyBitOutputParameter<CIEC_BOOL> paBUSY, COutputParameter<CIEC_UINT> paERRCODE, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUT) {
        evt_REQ(std::forward<const CIEC_BOOL &>(paINIT), std::forward<const forte::ASGEVO_PACKAGE::FB::PUSH::CIEC_INPUTS_PUSH &>(paINPUT), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paDONE), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paBUSY), std::forward<COutputParameter<CIEC_UINT>>(paERRCODE), std::forward<COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS>>(paOUTPUT));
      }
  };
}

