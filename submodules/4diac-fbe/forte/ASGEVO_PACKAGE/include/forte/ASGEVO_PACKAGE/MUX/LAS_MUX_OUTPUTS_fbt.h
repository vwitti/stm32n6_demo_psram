/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_MUX_OUTPUTS
 *** Description: Simple FB with init event and one algorithm
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

namespace forte::ASGEVO_PACKAGE::MUX {
  class FORTE_LAS_MUX_OUTPUTS final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_LAS_MUX_OUTPUTS)

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
      FORTE_LAS_MUX_OUTPUTS(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_LOWER;
      CIEC_BOOL var_SET;
      CIEC_BOOL var_PULL;
      CIEC_BOOL var_PUSH;
      CIEC_BOOL var_BL_EXT;
      CIEC_BOOL var_BL_RET;
      CIEC_BOOL var_STAB_EXT;
      CIEC_BOOL var_STAB_RET;
      CIEC_BOOL var_CA;

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS var_OUTPUTS;

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_LOWER;
      CDataConnection *conn_SET;
      CDataConnection *conn_PULL;
      CDataConnection *conn_PUSH;
      CDataConnection *conn_BL_EXT;
      CDataConnection *conn_BL_RET;
      CDataConnection *conn_STAB_EXT;
      CDataConnection *conn_STAB_RET;
      CDataConnection *conn_CA;

      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> conn_OUTPUTS;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_BOOL &paLOWER, const CIEC_BOOL &paSET, const CIEC_BOOL &paPULL, const CIEC_BOOL &paPUSH, const CIEC_BOOL &paBL_EXT, const CIEC_BOOL &paBL_RET, const CIEC_BOOL &paSTAB_EXT, const CIEC_BOOL &paSTAB_RET, const CIEC_BOOL &paCA, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUTS) {
        COutputGuard guard_OUTPUTS(paOUTPUTS);
        var_LOWER = paLOWER;
        var_SET = paSET;
        var_PULL = paPULL;
        var_PUSH = paPUSH;
        var_BL_EXT = paBL_EXT;
        var_BL_RET = paBL_RET;
        var_STAB_EXT = paSTAB_EXT;
        var_STAB_RET = paSTAB_RET;
        var_CA = paCA;
        executeEvent(scmEventINITID, nullptr);
        *paOUTPUTS = var_OUTPUTS;
      }

      void evt_REQ(const CIEC_BOOL &paLOWER, const CIEC_BOOL &paSET, const CIEC_BOOL &paPULL, const CIEC_BOOL &paPUSH, const CIEC_BOOL &paBL_EXT, const CIEC_BOOL &paBL_RET, const CIEC_BOOL &paSTAB_EXT, const CIEC_BOOL &paSTAB_RET, const CIEC_BOOL &paCA, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> paOUTPUTS) {
        COutputGuard guard_OUTPUTS(paOUTPUTS);
        var_LOWER = paLOWER;
        var_SET = paSET;
        var_PULL = paPULL;
        var_PUSH = paPUSH;
        var_BL_EXT = paBL_EXT;
        var_BL_RET = paBL_RET;
        var_STAB_EXT = paSTAB_EXT;
        var_STAB_RET = paSTAB_RET;
        var_CA = paCA;
        executeEvent(scmEventREQID, nullptr);
        *paOUTPUTS = var_OUTPUTS;
      }
  };
}

