/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_MUX_INPUTS
 *** Description: Simple FB with init event and one algorithm
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_INPUTS_dtp.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

namespace forte::ASGEVO_PACKAGE::MUX {
  class FORTE_LAS_MUX_INPUTS final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_LAS_MUX_INPUTS)

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
      FORTE_LAS_MUX_INPUTS(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_UINT var_LEG_LEFT;
      CIEC_UINT var_LEG_RIGHT;
      CIEC_UINT var_RAM_STROKE;

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS var_INPUTS;

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_LEG_LEFT;
      CDataConnection *conn_LEG_RIGHT;
      CDataConnection *conn_RAM_STROKE;

      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS> conn_INPUTS;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_UINT &paLEG_LEFT, const CIEC_UINT &paLEG_RIGHT, const CIEC_UINT &paRAM_STROKE, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS> paINPUTS) {
        COutputGuard guard_INPUTS(paINPUTS);
        var_LEG_LEFT = paLEG_LEFT;
        var_LEG_RIGHT = paLEG_RIGHT;
        var_RAM_STROKE = paRAM_STROKE;
        executeEvent(scmEventINITID, nullptr);
        *paINPUTS = var_INPUTS;
      }

      void evt_REQ(const CIEC_UINT &paLEG_LEFT, const CIEC_UINT &paLEG_RIGHT, const CIEC_UINT &paRAM_STROKE, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS> paINPUTS) {
        COutputGuard guard_INPUTS(paINPUTS);
        var_LEG_LEFT = paLEG_LEFT;
        var_LEG_RIGHT = paLEG_RIGHT;
        var_RAM_STROKE = paRAM_STROKE;
        executeEvent(scmEventREQID, nullptr);
        *paINPUTS = var_INPUTS;
      }
  };
}

