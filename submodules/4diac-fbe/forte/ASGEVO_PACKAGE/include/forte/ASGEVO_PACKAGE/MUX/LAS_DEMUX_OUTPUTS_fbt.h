/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_DEMUX_OUTPUTS
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
  class FORTE_LAS_DEMUX_OUTPUTS final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_LAS_DEMUX_OUTPUTS)

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
      FORTE_LAS_DEMUX_OUTPUTS(StringId paInstanceNameId, CFBContainer &paContainer);

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS var_OUTPUTS;

      CIEC_BOOL var_LOWER;
      CIEC_BOOL var_SET;
      CIEC_BOOL var_PULL;
      CIEC_BOOL var_PUSH;
      CIEC_BOOL var_BL_EXT;
      CIEC_BOOL var_BL_RET;
      CIEC_BOOL var_STAB_EXT;
      CIEC_BOOL var_STAB_RET;
      CIEC_BOOL var_CA;
      CIEC_BOOL var_PREWARN;

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_OUTPUTS;

      COutDataConnection<CIEC_BOOL> conn_LOWER;
      COutDataConnection<CIEC_BOOL> conn_SET;
      COutDataConnection<CIEC_BOOL> conn_PULL;
      COutDataConnection<CIEC_BOOL> conn_PUSH;
      COutDataConnection<CIEC_BOOL> conn_BL_EXT;
      COutDataConnection<CIEC_BOOL> conn_BL_RET;
      COutDataConnection<CIEC_BOOL> conn_STAB_EXT;
      COutDataConnection<CIEC_BOOL> conn_STAB_RET;
      COutDataConnection<CIEC_BOOL> conn_CA;
      COutDataConnection<CIEC_BOOL> conn_PREWARN;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS &paOUTPUTS, CAnyBitOutputParameter<CIEC_BOOL> paLOWER, CAnyBitOutputParameter<CIEC_BOOL> paSET, CAnyBitOutputParameter<CIEC_BOOL> paPULL, CAnyBitOutputParameter<CIEC_BOOL> paPUSH, CAnyBitOutputParameter<CIEC_BOOL> paBL_EXT, CAnyBitOutputParameter<CIEC_BOOL> paBL_RET, CAnyBitOutputParameter<CIEC_BOOL> paSTAB_EXT, CAnyBitOutputParameter<CIEC_BOOL> paSTAB_RET, CAnyBitOutputParameter<CIEC_BOOL> paCA, CAnyBitOutputParameter<CIEC_BOOL> paPREWARN) {
        COutputGuard guard_LOWER(paLOWER);
        COutputGuard guard_SET(paSET);
        COutputGuard guard_PULL(paPULL);
        COutputGuard guard_PUSH(paPUSH);
        COutputGuard guard_BL_EXT(paBL_EXT);
        COutputGuard guard_BL_RET(paBL_RET);
        COutputGuard guard_STAB_EXT(paSTAB_EXT);
        COutputGuard guard_STAB_RET(paSTAB_RET);
        COutputGuard guard_CA(paCA);
        COutputGuard guard_PREWARN(paPREWARN);
        var_OUTPUTS = paOUTPUTS;
        executeEvent(scmEventINITID, nullptr);
        *paLOWER = var_LOWER;
        *paSET = var_SET;
        *paPULL = var_PULL;
        *paPUSH = var_PUSH;
        *paBL_EXT = var_BL_EXT;
        *paBL_RET = var_BL_RET;
        *paSTAB_EXT = var_STAB_EXT;
        *paSTAB_RET = var_STAB_RET;
        *paCA = var_CA;
        *paPREWARN = var_PREWARN;
      }

      void evt_REQ(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS &paOUTPUTS, CAnyBitOutputParameter<CIEC_BOOL> paLOWER, CAnyBitOutputParameter<CIEC_BOOL> paSET, CAnyBitOutputParameter<CIEC_BOOL> paPULL, CAnyBitOutputParameter<CIEC_BOOL> paPUSH, CAnyBitOutputParameter<CIEC_BOOL> paBL_EXT, CAnyBitOutputParameter<CIEC_BOOL> paBL_RET, CAnyBitOutputParameter<CIEC_BOOL> paSTAB_EXT, CAnyBitOutputParameter<CIEC_BOOL> paSTAB_RET, CAnyBitOutputParameter<CIEC_BOOL> paCA, CAnyBitOutputParameter<CIEC_BOOL> paPREWARN) {
        COutputGuard guard_LOWER(paLOWER);
        COutputGuard guard_SET(paSET);
        COutputGuard guard_PULL(paPULL);
        COutputGuard guard_PUSH(paPUSH);
        COutputGuard guard_BL_EXT(paBL_EXT);
        COutputGuard guard_BL_RET(paBL_RET);
        COutputGuard guard_STAB_EXT(paSTAB_EXT);
        COutputGuard guard_STAB_RET(paSTAB_RET);
        COutputGuard guard_CA(paCA);
        COutputGuard guard_PREWARN(paPREWARN);
        var_OUTPUTS = paOUTPUTS;
        executeEvent(scmEventREQID, nullptr);
        *paLOWER = var_LOWER;
        *paSET = var_SET;
        *paPULL = var_PULL;
        *paPUSH = var_PUSH;
        *paBL_EXT = var_BL_EXT;
        *paBL_RET = var_BL_RET;
        *paSTAB_EXT = var_STAB_EXT;
        *paSTAB_RET = var_STAB_RET;
        *paCA = var_CA;
        *paPREWARN = var_PREWARN;
      }
  };
}

