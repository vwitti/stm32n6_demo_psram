/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_DEMUX_INPUTS
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
  class FORTE_LAS_DEMUX_INPUTS final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_LAS_DEMUX_INPUTS)

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
      FORTE_LAS_DEMUX_INPUTS(StringId paInstanceNameId, CFBContainer &paContainer);

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS var_INPUTS;

      CIEC_UINT var_LEG_LEFT;
      CIEC_UINT var_LEG_RIGHT;
      CIEC_UINT var_RAM_STROKE;

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_INPUTS;

      COutDataConnection<CIEC_UINT> conn_LEG_LEFT;
      COutDataConnection<CIEC_UINT> conn_LEG_RIGHT;
      COutDataConnection<CIEC_UINT> conn_RAM_STROKE;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS &paINPUTS, COutputParameter<CIEC_UINT> paLEG_LEFT, COutputParameter<CIEC_UINT> paLEG_RIGHT, COutputParameter<CIEC_UINT> paRAM_STROKE) {
        COutputGuard guard_LEG_LEFT(paLEG_LEFT);
        COutputGuard guard_LEG_RIGHT(paLEG_RIGHT);
        COutputGuard guard_RAM_STROKE(paRAM_STROKE);
        var_INPUTS = paINPUTS;
        executeEvent(scmEventINITID, nullptr);
        *paLEG_LEFT = var_LEG_LEFT;
        *paLEG_RIGHT = var_LEG_RIGHT;
        *paRAM_STROKE = var_RAM_STROKE;
      }

      void evt_REQ(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS &paINPUTS, COutputParameter<CIEC_UINT> paLEG_LEFT, COutputParameter<CIEC_UINT> paLEG_RIGHT, COutputParameter<CIEC_UINT> paRAM_STROKE) {
        COutputGuard guard_LEG_LEFT(paLEG_LEFT);
        COutputGuard guard_LEG_RIGHT(paLEG_RIGHT);
        COutputGuard guard_RAM_STROKE(paRAM_STROKE);
        var_INPUTS = paINPUTS;
        executeEvent(scmEventREQID, nullptr);
        *paLEG_LEFT = var_LEG_LEFT;
        *paLEG_RIGHT = var_LEG_RIGHT;
        *paRAM_STROKE = var_RAM_STROKE;
      }
  };
}

