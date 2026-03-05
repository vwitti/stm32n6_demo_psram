/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_MUX_PARA
 *** Description: Simple FB with init event and one algorithm
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

namespace forte::ASGEVO_PACKAGE::MUX {
  class FORTE_LAS_MUX_PARA final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_LAS_MUX_PARA)

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
      FORTE_LAS_MUX_PARA(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_TIME var_eP_AA_T_Vorwarnung;
      CIEC_BOOL var_eP_AA_B_Sensorgesteuert;
      CIEC_TIME var_eP_AA_T_StartLAS;
      CIEC_TIME var_eP_AA_T_RaubenTC;
      CIEC_UINT var_eP_AA_N_Nachrauben;
      CIEC_TIME var_eP_AA_T_StartNachrauben;
      CIEC_TIME var_eP_AA_T_Nachrauben;
      CIEC_TIME var_eP_AA_T_TimeoutLoweringSensor;
      CIEC_UINT var_eP_AA_P_EndeRauben;
      CIEC_TIME var_eP_AA_T_AdditionalLowering;
      CIEC_TIME var_eP_AA_T_StartSchreiten;
      CIEC_TIME var_eP_AA_T_Schreiten;
      CIEC_UINT var_eP_AA_V_MinSchreiten;
      CIEC_UINT var_eP_AA_P_StartNachraubenSensor;
      CIEC_TIME var_eP_AA_T_RaubNachStartSchreit;
      CIEC_UINT var_eP_AA_P_StartSchreiten;
      CIEC_UINT var_eP_AA_Proz_EndeSchreiten;
      CIEC_TIME var_eP_AA_T_Setzen;
      CIEC_TIME var_eP_BL_T_AA_StartAusf;
      CIEC_TIME var_eP_BL_T_AA_Einf;
      CIEC_TIME var_eP_BL_T_AA_Ausf;
      CIEC_TIME var_eP_ECK_T_AA_PreStartEinf;
      CIEC_TIME var_eP_ECK_T_AA_PreEinf;
      CIEC_TIME var_eP_ECK_T_AA_StartAusf;
      CIEC_TIME var_eP_ECK_T_AA_Ausf;
      CIEC_TIME var_eP_ECK_T_AA_Einf;

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_PARAM;

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_eP_AA_T_Vorwarnung;
      CDataConnection *conn_eP_AA_B_Sensorgesteuert;
      CDataConnection *conn_eP_AA_T_StartLAS;
      CDataConnection *conn_eP_AA_T_RaubenTC;
      CDataConnection *conn_eP_AA_N_Nachrauben;
      CDataConnection *conn_eP_AA_T_StartNachrauben;
      CDataConnection *conn_eP_AA_T_Nachrauben;
      CDataConnection *conn_eP_AA_T_TimeoutLoweringSensor;
      CDataConnection *conn_eP_AA_P_EndeRauben;
      CDataConnection *conn_eP_AA_T_AdditionalLowering;
      CDataConnection *conn_eP_AA_T_StartSchreiten;
      CDataConnection *conn_eP_AA_T_Schreiten;
      CDataConnection *conn_eP_AA_V_MinSchreiten;
      CDataConnection *conn_eP_AA_P_StartNachraubenSensor;
      CDataConnection *conn_eP_AA_T_RaubNachStartSchreit;
      CDataConnection *conn_eP_AA_P_StartSchreiten;
      CDataConnection *conn_eP_AA_Proz_EndeSchreiten;
      CDataConnection *conn_eP_AA_T_Setzen;
      CDataConnection *conn_eP_BL_T_AA_StartAusf;
      CDataConnection *conn_eP_BL_T_AA_Einf;
      CDataConnection *conn_eP_BL_T_AA_Ausf;
      CDataConnection *conn_eP_ECK_T_AA_PreStartEinf;
      CDataConnection *conn_eP_ECK_T_AA_PreEinf;
      CDataConnection *conn_eP_ECK_T_AA_StartAusf;
      CDataConnection *conn_eP_ECK_T_AA_Ausf;
      CDataConnection *conn_eP_ECK_T_AA_Einf;

      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER> conn_PARAM;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_TIME &paeP_AA_T_Vorwarnung, const CIEC_BOOL &paeP_AA_B_Sensorgesteuert, const CIEC_TIME &paeP_AA_T_StartLAS, const CIEC_TIME &paeP_AA_T_RaubenTC, const CIEC_UINT &paeP_AA_N_Nachrauben, const CIEC_TIME &paeP_AA_T_StartNachrauben, const CIEC_TIME &paeP_AA_T_Nachrauben, const CIEC_TIME &paeP_AA_T_TimeoutLoweringSensor, const CIEC_UINT &paeP_AA_P_EndeRauben, const CIEC_TIME &paeP_AA_T_AdditionalLowering, const CIEC_TIME &paeP_AA_T_StartSchreiten, const CIEC_TIME &paeP_AA_T_Schreiten, const CIEC_UINT &paeP_AA_V_MinSchreiten, const CIEC_UINT &paeP_AA_P_StartNachraubenSensor, const CIEC_TIME &paeP_AA_T_RaubNachStartSchreit, const CIEC_UINT &paeP_AA_P_StartSchreiten, const CIEC_UINT &paeP_AA_Proz_EndeSchreiten, const CIEC_TIME &paeP_AA_T_Setzen, const CIEC_TIME &paeP_BL_T_AA_StartAusf, const CIEC_TIME &paeP_BL_T_AA_Einf, const CIEC_TIME &paeP_BL_T_AA_Ausf, const CIEC_TIME &paeP_ECK_T_AA_PreStartEinf, const CIEC_TIME &paeP_ECK_T_AA_PreEinf, const CIEC_TIME &paeP_ECK_T_AA_StartAusf, const CIEC_TIME &paeP_ECK_T_AA_Ausf, const CIEC_TIME &paeP_ECK_T_AA_Einf, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER> paPARAM) {
        COutputGuard guard_PARAM(paPARAM);
        var_eP_AA_T_Vorwarnung = paeP_AA_T_Vorwarnung;
        var_eP_AA_B_Sensorgesteuert = paeP_AA_B_Sensorgesteuert;
        var_eP_AA_T_StartLAS = paeP_AA_T_StartLAS;
        var_eP_AA_T_RaubenTC = paeP_AA_T_RaubenTC;
        var_eP_AA_N_Nachrauben = paeP_AA_N_Nachrauben;
        var_eP_AA_T_StartNachrauben = paeP_AA_T_StartNachrauben;
        var_eP_AA_T_Nachrauben = paeP_AA_T_Nachrauben;
        var_eP_AA_T_TimeoutLoweringSensor = paeP_AA_T_TimeoutLoweringSensor;
        var_eP_AA_P_EndeRauben = paeP_AA_P_EndeRauben;
        var_eP_AA_T_AdditionalLowering = paeP_AA_T_AdditionalLowering;
        var_eP_AA_T_StartSchreiten = paeP_AA_T_StartSchreiten;
        var_eP_AA_T_Schreiten = paeP_AA_T_Schreiten;
        var_eP_AA_V_MinSchreiten = paeP_AA_V_MinSchreiten;
        var_eP_AA_P_StartNachraubenSensor = paeP_AA_P_StartNachraubenSensor;
        var_eP_AA_T_RaubNachStartSchreit = paeP_AA_T_RaubNachStartSchreit;
        var_eP_AA_P_StartSchreiten = paeP_AA_P_StartSchreiten;
        var_eP_AA_Proz_EndeSchreiten = paeP_AA_Proz_EndeSchreiten;
        var_eP_AA_T_Setzen = paeP_AA_T_Setzen;
        var_eP_BL_T_AA_StartAusf = paeP_BL_T_AA_StartAusf;
        var_eP_BL_T_AA_Einf = paeP_BL_T_AA_Einf;
        var_eP_BL_T_AA_Ausf = paeP_BL_T_AA_Ausf;
        var_eP_ECK_T_AA_PreStartEinf = paeP_ECK_T_AA_PreStartEinf;
        var_eP_ECK_T_AA_PreEinf = paeP_ECK_T_AA_PreEinf;
        var_eP_ECK_T_AA_StartAusf = paeP_ECK_T_AA_StartAusf;
        var_eP_ECK_T_AA_Ausf = paeP_ECK_T_AA_Ausf;
        var_eP_ECK_T_AA_Einf = paeP_ECK_T_AA_Einf;
        executeEvent(scmEventINITID, nullptr);
        *paPARAM = var_PARAM;
      }

      void evt_REQ(const CIEC_TIME &paeP_AA_T_Vorwarnung, const CIEC_BOOL &paeP_AA_B_Sensorgesteuert, const CIEC_TIME &paeP_AA_T_StartLAS, const CIEC_TIME &paeP_AA_T_RaubenTC, const CIEC_UINT &paeP_AA_N_Nachrauben, const CIEC_TIME &paeP_AA_T_StartNachrauben, const CIEC_TIME &paeP_AA_T_Nachrauben, const CIEC_TIME &paeP_AA_T_TimeoutLoweringSensor, const CIEC_UINT &paeP_AA_P_EndeRauben, const CIEC_TIME &paeP_AA_T_AdditionalLowering, const CIEC_TIME &paeP_AA_T_StartSchreiten, const CIEC_TIME &paeP_AA_T_Schreiten, const CIEC_UINT &paeP_AA_V_MinSchreiten, const CIEC_UINT &paeP_AA_P_StartNachraubenSensor, const CIEC_TIME &paeP_AA_T_RaubNachStartSchreit, const CIEC_UINT &paeP_AA_P_StartSchreiten, const CIEC_UINT &paeP_AA_Proz_EndeSchreiten, const CIEC_TIME &paeP_AA_T_Setzen, const CIEC_TIME &paeP_BL_T_AA_StartAusf, const CIEC_TIME &paeP_BL_T_AA_Einf, const CIEC_TIME &paeP_BL_T_AA_Ausf, const CIEC_TIME &paeP_ECK_T_AA_PreStartEinf, const CIEC_TIME &paeP_ECK_T_AA_PreEinf, const CIEC_TIME &paeP_ECK_T_AA_StartAusf, const CIEC_TIME &paeP_ECK_T_AA_Ausf, const CIEC_TIME &paeP_ECK_T_AA_Einf, COutputParameter<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER> paPARAM) {
        COutputGuard guard_PARAM(paPARAM);
        var_eP_AA_T_Vorwarnung = paeP_AA_T_Vorwarnung;
        var_eP_AA_B_Sensorgesteuert = paeP_AA_B_Sensorgesteuert;
        var_eP_AA_T_StartLAS = paeP_AA_T_StartLAS;
        var_eP_AA_T_RaubenTC = paeP_AA_T_RaubenTC;
        var_eP_AA_N_Nachrauben = paeP_AA_N_Nachrauben;
        var_eP_AA_T_StartNachrauben = paeP_AA_T_StartNachrauben;
        var_eP_AA_T_Nachrauben = paeP_AA_T_Nachrauben;
        var_eP_AA_T_TimeoutLoweringSensor = paeP_AA_T_TimeoutLoweringSensor;
        var_eP_AA_P_EndeRauben = paeP_AA_P_EndeRauben;
        var_eP_AA_T_AdditionalLowering = paeP_AA_T_AdditionalLowering;
        var_eP_AA_T_StartSchreiten = paeP_AA_T_StartSchreiten;
        var_eP_AA_T_Schreiten = paeP_AA_T_Schreiten;
        var_eP_AA_V_MinSchreiten = paeP_AA_V_MinSchreiten;
        var_eP_AA_P_StartNachraubenSensor = paeP_AA_P_StartNachraubenSensor;
        var_eP_AA_T_RaubNachStartSchreit = paeP_AA_T_RaubNachStartSchreit;
        var_eP_AA_P_StartSchreiten = paeP_AA_P_StartSchreiten;
        var_eP_AA_Proz_EndeSchreiten = paeP_AA_Proz_EndeSchreiten;
        var_eP_AA_T_Setzen = paeP_AA_T_Setzen;
        var_eP_BL_T_AA_StartAusf = paeP_BL_T_AA_StartAusf;
        var_eP_BL_T_AA_Einf = paeP_BL_T_AA_Einf;
        var_eP_BL_T_AA_Ausf = paeP_BL_T_AA_Ausf;
        var_eP_ECK_T_AA_PreStartEinf = paeP_ECK_T_AA_PreStartEinf;
        var_eP_ECK_T_AA_PreEinf = paeP_ECK_T_AA_PreEinf;
        var_eP_ECK_T_AA_StartAusf = paeP_ECK_T_AA_StartAusf;
        var_eP_ECK_T_AA_Ausf = paeP_ECK_T_AA_Ausf;
        var_eP_ECK_T_AA_Einf = paeP_ECK_T_AA_Einf;
        executeEvent(scmEventREQID, nullptr);
        *paPARAM = var_PARAM;
      }
  };
}

