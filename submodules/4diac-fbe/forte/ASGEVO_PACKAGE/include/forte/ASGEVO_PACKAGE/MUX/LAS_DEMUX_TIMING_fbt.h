/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_DEMUX_TIMING
 *** Description: Simple FB with init event and one algorithm
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_TIMING_dtp.h"
#include "forte/datatypes/forte_time.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

namespace forte::ASGEVO_PACKAGE::MUX {
  class FORTE_LAS_DEMUX_TIMING final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_LAS_DEMUX_TIMING)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventCNFID = 1;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventREQID = 1;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_INIT(void);
      void alg_REQ(void);

      void enterStateINIT(CEventChainExecutionThread *const paECET);
      void enterStateREQ(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_LAS_DEMUX_TIMING(StringId paInstanceNameId, CFBContainer &paContainer);

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING var_TIMING;

      CIEC_TIME var_T_LOWER;
      CIEC_TIME var_T_ADVANCE;
      CIEC_TIME var_T_SET;
      CIEC_TIME var_T_TOTAL;

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_TIMING;

      COutDataConnection<CIEC_TIME> conn_T_LOWER;
      COutDataConnection<CIEC_TIME> conn_T_ADVANCE;
      COutDataConnection<CIEC_TIME> conn_T_SET;
      COutDataConnection<CIEC_TIME> conn_T_TOTAL;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING &paTIMING, COutputParameter<CIEC_TIME> paT_LOWER, COutputParameter<CIEC_TIME> paT_ADVANCE, COutputParameter<CIEC_TIME> paT_SET, COutputParameter<CIEC_TIME> paT_TOTAL) {
        COutputGuard guard_T_LOWER(paT_LOWER);
        COutputGuard guard_T_ADVANCE(paT_ADVANCE);
        COutputGuard guard_T_SET(paT_SET);
        COutputGuard guard_T_TOTAL(paT_TOTAL);
        var_TIMING = paTIMING;
        executeEvent(scmEventINITID, nullptr);
        *paT_LOWER = var_T_LOWER;
        *paT_ADVANCE = var_T_ADVANCE;
        *paT_SET = var_T_SET;
        *paT_TOTAL = var_T_TOTAL;
      }

      void evt_REQ(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING &paTIMING, COutputParameter<CIEC_TIME> paT_LOWER, COutputParameter<CIEC_TIME> paT_ADVANCE, COutputParameter<CIEC_TIME> paT_SET, COutputParameter<CIEC_TIME> paT_TOTAL) {
        COutputGuard guard_T_LOWER(paT_LOWER);
        COutputGuard guard_T_ADVANCE(paT_ADVANCE);
        COutputGuard guard_T_SET(paT_SET);
        COutputGuard guard_T_TOTAL(paT_TOTAL);
        var_TIMING = paTIMING;
        executeEvent(scmEventREQID, nullptr);
        *paT_LOWER = var_T_LOWER;
        *paT_ADVANCE = var_T_ADVANCE;
        *paT_SET = var_T_SET;
        *paT_TOTAL = var_T_TOTAL;
      }
  };
}

