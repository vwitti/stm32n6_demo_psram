/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: CONST_LAS_PARAM_TC_OK
 *** Description: Simple FB with one algorithm
 *** Version:
 ***     1.0: 2026-02-25/volker -  -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  class FORTE_CONST_LAS_PARAM_TC_OK final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_CONST_LAS_PARAM_TC_OK)

    private:
      static const TEventID scmEventCNFID = 0;
      static const TEventID scmEventREQID = 0;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_REQ(void);

      void enterStateREQ(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_CONST_LAS_PARAM_TC_OK(StringId paInstanceNameId, CFBContainer &paContainer);

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_PARAM;

      CEventConnection conn_CNF;

      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER> conn_PARAM;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_REQ(COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER> paPARAM) {
        COutputGuard guard_PARAM(paPARAM);
        executeEvent(scmEventREQID, nullptr);
        *paPARAM = var_PARAM;
      }

      void operator()(COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER> paPARAM) {
        evt_REQ(std::forward<COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER>>(paPARAM));
      }
  };
}

