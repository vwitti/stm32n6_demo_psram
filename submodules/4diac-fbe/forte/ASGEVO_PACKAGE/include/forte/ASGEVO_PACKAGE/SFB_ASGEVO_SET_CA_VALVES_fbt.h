/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: SFB_ASGEVO_SET_CA_VALVES
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2026-02-21/volker -  -
 *************************************************************************/

#pragma once

#include "forte/funcbloc.h"
#include "forte/datatypes/forte_any_variant.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

namespace forte::ASGEVO_PACKAGE {
  class FORTE_SFB_ASGEVO_SET_CA_VALVES final : public CFunctionBlock {
      DECLARE_FIRMWARE_FB(FORTE_SFB_ASGEVO_SET_CA_VALVES)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventCNFID = 1;
      static const TEventID scmEventINDID = 2;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventREQID = 1;
      static const TEventID scmEventRSPID = 2;

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SFB_ASGEVO_SET_CA_VALVES(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_QI;
      CIEC_WSTRING var_PARAMS;
      CIEC_ANY_VARIANT var_SD;
      CIEC_BOOL var_CA;

      CIEC_BOOL var_QO;
      CIEC_WSTRING var_STATUS;
      CIEC_ANY_VARIANT var_RD;

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;
      CEventConnection conn_IND;

      CDataConnection *conn_QI;
      CDataConnection *conn_PARAMS;
      CDataConnection *conn_SD;
      CDataConnection *conn_CA;

      COutDataConnection<CIEC_BOOL> conn_QO;
      COutDataConnection<CIEC_WSTRING> conn_STATUS;
      COutDataConnection<CIEC_ANY_VARIANT> conn_RD;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_BOOL &paQI, const CIEC_WSTRING &paPARAMS, const CIEC_ANY_VARIANT &paSD, const CIEC_BOOL &paCA, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS, COutputParameter<CIEC_ANY_VARIANT> paRD) {
        COutputGuard guard_QO(paQO);
        COutputGuard guard_STATUS(paSTATUS);
        COutputGuard guard_RD(paRD);
        var_QI = paQI;
        var_PARAMS = paPARAMS;
        var_SD = paSD;
        var_CA = paCA;
        executeEvent(scmEventINITID, nullptr);
        *paQO = var_QO;
        *paSTATUS = var_STATUS;
        paRD->setValue(var_RD.unwrap());
      }

      void evt_REQ(const CIEC_BOOL &paQI, const CIEC_WSTRING &paPARAMS, const CIEC_ANY_VARIANT &paSD, const CIEC_BOOL &paCA, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS, COutputParameter<CIEC_ANY_VARIANT> paRD) {
        COutputGuard guard_QO(paQO);
        COutputGuard guard_STATUS(paSTATUS);
        COutputGuard guard_RD(paRD);
        var_QI = paQI;
        var_PARAMS = paPARAMS;
        var_SD = paSD;
        var_CA = paCA;
        executeEvent(scmEventREQID, nullptr);
        *paQO = var_QO;
        *paSTATUS = var_STATUS;
        paRD->setValue(var_RD.unwrap());
      }

      void evt_RSP(const CIEC_BOOL &paQI, const CIEC_WSTRING &paPARAMS, const CIEC_ANY_VARIANT &paSD, const CIEC_BOOL &paCA, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS, COutputParameter<CIEC_ANY_VARIANT> paRD) {
        COutputGuard guard_QO(paQO);
        COutputGuard guard_STATUS(paSTATUS);
        COutputGuard guard_RD(paRD);
        var_QI = paQI;
        var_PARAMS = paPARAMS;
        var_SD = paSD;
        var_CA = paCA;
        executeEvent(scmEventRSPID, nullptr);
        *paQO = var_QO;
        *paSTATUS = var_STATUS;
        paRD->setValue(var_RD.unwrap());
      }
  };
}

