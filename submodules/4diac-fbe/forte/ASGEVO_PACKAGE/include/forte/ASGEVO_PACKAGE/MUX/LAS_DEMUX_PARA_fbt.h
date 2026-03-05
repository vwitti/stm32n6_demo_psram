/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_DEMUX_PARA
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
  class FORTE_LAS_DEMUX_PARA final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_LAS_DEMUX_PARA)

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
      FORTE_LAS_DEMUX_PARA(StringId paInstanceNameId, CFBContainer &paContainer);

      forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_PARAM;

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

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_PARAM;

      COutDataConnection<CIEC_TIME> conn_eP_AA_T_Vorwarnung;
      COutDataConnection<CIEC_BOOL> conn_eP_AA_B_Sensorgesteuert;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_StartLAS;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_RaubenTC;
      COutDataConnection<CIEC_UINT> conn_eP_AA_N_Nachrauben;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_StartNachrauben;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_Nachrauben;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_TimeoutLoweringSensor;
      COutDataConnection<CIEC_UINT> conn_eP_AA_P_EndeRauben;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_AdditionalLowering;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_StartSchreiten;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_Schreiten;
      COutDataConnection<CIEC_UINT> conn_eP_AA_V_MinSchreiten;
      COutDataConnection<CIEC_UINT> conn_eP_AA_P_StartNachraubenSensor;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_RaubNachStartSchreit;
      COutDataConnection<CIEC_UINT> conn_eP_AA_P_StartSchreiten;
      COutDataConnection<CIEC_UINT> conn_eP_AA_Proz_EndeSchreiten;
      COutDataConnection<CIEC_TIME> conn_eP_AA_T_Setzen;
      COutDataConnection<CIEC_TIME> conn_eP_BL_T_AA_StartAusf;
      COutDataConnection<CIEC_TIME> conn_eP_BL_T_AA_Einf;
      COutDataConnection<CIEC_TIME> conn_eP_BL_T_AA_Ausf;
      COutDataConnection<CIEC_TIME> conn_eP_ECK_T_AA_PreStartEinf;
      COutDataConnection<CIEC_TIME> conn_eP_ECK_T_AA_PreEinf;
      COutDataConnection<CIEC_TIME> conn_eP_ECK_T_AA_StartAusf;
      COutDataConnection<CIEC_TIME> conn_eP_ECK_T_AA_Ausf;
      COutDataConnection<CIEC_TIME> conn_eP_ECK_T_AA_Einf;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER &paPARAM, COutputParameter<CIEC_TIME> paeP_AA_T_Vorwarnung, CAnyBitOutputParameter<CIEC_BOOL> paeP_AA_B_Sensorgesteuert, COutputParameter<CIEC_TIME> paeP_AA_T_StartLAS, COutputParameter<CIEC_TIME> paeP_AA_T_RaubenTC, COutputParameter<CIEC_UINT> paeP_AA_N_Nachrauben, COutputParameter<CIEC_TIME> paeP_AA_T_StartNachrauben, COutputParameter<CIEC_TIME> paeP_AA_T_Nachrauben, COutputParameter<CIEC_TIME> paeP_AA_T_TimeoutLoweringSensor, COutputParameter<CIEC_UINT> paeP_AA_P_EndeRauben, COutputParameter<CIEC_TIME> paeP_AA_T_AdditionalLowering, COutputParameter<CIEC_TIME> paeP_AA_T_StartSchreiten, COutputParameter<CIEC_TIME> paeP_AA_T_Schreiten, COutputParameter<CIEC_UINT> paeP_AA_V_MinSchreiten, COutputParameter<CIEC_UINT> paeP_AA_P_StartNachraubenSensor, COutputParameter<CIEC_TIME> paeP_AA_T_RaubNachStartSchreit, COutputParameter<CIEC_UINT> paeP_AA_P_StartSchreiten, COutputParameter<CIEC_UINT> paeP_AA_Proz_EndeSchreiten, COutputParameter<CIEC_TIME> paeP_AA_T_Setzen, COutputParameter<CIEC_TIME> paeP_BL_T_AA_StartAusf, COutputParameter<CIEC_TIME> paeP_BL_T_AA_Einf, COutputParameter<CIEC_TIME> paeP_BL_T_AA_Ausf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_PreStartEinf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_PreEinf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_StartAusf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_Ausf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_Einf) {
        COutputGuard guard_eP_AA_T_Vorwarnung(paeP_AA_T_Vorwarnung);
        COutputGuard guard_eP_AA_B_Sensorgesteuert(paeP_AA_B_Sensorgesteuert);
        COutputGuard guard_eP_AA_T_StartLAS(paeP_AA_T_StartLAS);
        COutputGuard guard_eP_AA_T_RaubenTC(paeP_AA_T_RaubenTC);
        COutputGuard guard_eP_AA_N_Nachrauben(paeP_AA_N_Nachrauben);
        COutputGuard guard_eP_AA_T_StartNachrauben(paeP_AA_T_StartNachrauben);
        COutputGuard guard_eP_AA_T_Nachrauben(paeP_AA_T_Nachrauben);
        COutputGuard guard_eP_AA_T_TimeoutLoweringSensor(paeP_AA_T_TimeoutLoweringSensor);
        COutputGuard guard_eP_AA_P_EndeRauben(paeP_AA_P_EndeRauben);
        COutputGuard guard_eP_AA_T_AdditionalLowering(paeP_AA_T_AdditionalLowering);
        COutputGuard guard_eP_AA_T_StartSchreiten(paeP_AA_T_StartSchreiten);
        COutputGuard guard_eP_AA_T_Schreiten(paeP_AA_T_Schreiten);
        COutputGuard guard_eP_AA_V_MinSchreiten(paeP_AA_V_MinSchreiten);
        COutputGuard guard_eP_AA_P_StartNachraubenSensor(paeP_AA_P_StartNachraubenSensor);
        COutputGuard guard_eP_AA_T_RaubNachStartSchreit(paeP_AA_T_RaubNachStartSchreit);
        COutputGuard guard_eP_AA_P_StartSchreiten(paeP_AA_P_StartSchreiten);
        COutputGuard guard_eP_AA_Proz_EndeSchreiten(paeP_AA_Proz_EndeSchreiten);
        COutputGuard guard_eP_AA_T_Setzen(paeP_AA_T_Setzen);
        COutputGuard guard_eP_BL_T_AA_StartAusf(paeP_BL_T_AA_StartAusf);
        COutputGuard guard_eP_BL_T_AA_Einf(paeP_BL_T_AA_Einf);
        COutputGuard guard_eP_BL_T_AA_Ausf(paeP_BL_T_AA_Ausf);
        COutputGuard guard_eP_ECK_T_AA_PreStartEinf(paeP_ECK_T_AA_PreStartEinf);
        COutputGuard guard_eP_ECK_T_AA_PreEinf(paeP_ECK_T_AA_PreEinf);
        COutputGuard guard_eP_ECK_T_AA_StartAusf(paeP_ECK_T_AA_StartAusf);
        COutputGuard guard_eP_ECK_T_AA_Ausf(paeP_ECK_T_AA_Ausf);
        COutputGuard guard_eP_ECK_T_AA_Einf(paeP_ECK_T_AA_Einf);
        var_PARAM = paPARAM;
        executeEvent(scmEventINITID, nullptr);
        *paeP_AA_T_Vorwarnung = var_eP_AA_T_Vorwarnung;
        *paeP_AA_B_Sensorgesteuert = var_eP_AA_B_Sensorgesteuert;
        *paeP_AA_T_StartLAS = var_eP_AA_T_StartLAS;
        *paeP_AA_T_RaubenTC = var_eP_AA_T_RaubenTC;
        *paeP_AA_N_Nachrauben = var_eP_AA_N_Nachrauben;
        *paeP_AA_T_StartNachrauben = var_eP_AA_T_StartNachrauben;
        *paeP_AA_T_Nachrauben = var_eP_AA_T_Nachrauben;
        *paeP_AA_T_TimeoutLoweringSensor = var_eP_AA_T_TimeoutLoweringSensor;
        *paeP_AA_P_EndeRauben = var_eP_AA_P_EndeRauben;
        *paeP_AA_T_AdditionalLowering = var_eP_AA_T_AdditionalLowering;
        *paeP_AA_T_StartSchreiten = var_eP_AA_T_StartSchreiten;
        *paeP_AA_T_Schreiten = var_eP_AA_T_Schreiten;
        *paeP_AA_V_MinSchreiten = var_eP_AA_V_MinSchreiten;
        *paeP_AA_P_StartNachraubenSensor = var_eP_AA_P_StartNachraubenSensor;
        *paeP_AA_T_RaubNachStartSchreit = var_eP_AA_T_RaubNachStartSchreit;
        *paeP_AA_P_StartSchreiten = var_eP_AA_P_StartSchreiten;
        *paeP_AA_Proz_EndeSchreiten = var_eP_AA_Proz_EndeSchreiten;
        *paeP_AA_T_Setzen = var_eP_AA_T_Setzen;
        *paeP_BL_T_AA_StartAusf = var_eP_BL_T_AA_StartAusf;
        *paeP_BL_T_AA_Einf = var_eP_BL_T_AA_Einf;
        *paeP_BL_T_AA_Ausf = var_eP_BL_T_AA_Ausf;
        *paeP_ECK_T_AA_PreStartEinf = var_eP_ECK_T_AA_PreStartEinf;
        *paeP_ECK_T_AA_PreEinf = var_eP_ECK_T_AA_PreEinf;
        *paeP_ECK_T_AA_StartAusf = var_eP_ECK_T_AA_StartAusf;
        *paeP_ECK_T_AA_Ausf = var_eP_ECK_T_AA_Ausf;
        *paeP_ECK_T_AA_Einf = var_eP_ECK_T_AA_Einf;
      }

      void evt_REQ(const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER &paPARAM, COutputParameter<CIEC_TIME> paeP_AA_T_Vorwarnung, CAnyBitOutputParameter<CIEC_BOOL> paeP_AA_B_Sensorgesteuert, COutputParameter<CIEC_TIME> paeP_AA_T_StartLAS, COutputParameter<CIEC_TIME> paeP_AA_T_RaubenTC, COutputParameter<CIEC_UINT> paeP_AA_N_Nachrauben, COutputParameter<CIEC_TIME> paeP_AA_T_StartNachrauben, COutputParameter<CIEC_TIME> paeP_AA_T_Nachrauben, COutputParameter<CIEC_TIME> paeP_AA_T_TimeoutLoweringSensor, COutputParameter<CIEC_UINT> paeP_AA_P_EndeRauben, COutputParameter<CIEC_TIME> paeP_AA_T_AdditionalLowering, COutputParameter<CIEC_TIME> paeP_AA_T_StartSchreiten, COutputParameter<CIEC_TIME> paeP_AA_T_Schreiten, COutputParameter<CIEC_UINT> paeP_AA_V_MinSchreiten, COutputParameter<CIEC_UINT> paeP_AA_P_StartNachraubenSensor, COutputParameter<CIEC_TIME> paeP_AA_T_RaubNachStartSchreit, COutputParameter<CIEC_UINT> paeP_AA_P_StartSchreiten, COutputParameter<CIEC_UINT> paeP_AA_Proz_EndeSchreiten, COutputParameter<CIEC_TIME> paeP_AA_T_Setzen, COutputParameter<CIEC_TIME> paeP_BL_T_AA_StartAusf, COutputParameter<CIEC_TIME> paeP_BL_T_AA_Einf, COutputParameter<CIEC_TIME> paeP_BL_T_AA_Ausf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_PreStartEinf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_PreEinf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_StartAusf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_Ausf, COutputParameter<CIEC_TIME> paeP_ECK_T_AA_Einf) {
        COutputGuard guard_eP_AA_T_Vorwarnung(paeP_AA_T_Vorwarnung);
        COutputGuard guard_eP_AA_B_Sensorgesteuert(paeP_AA_B_Sensorgesteuert);
        COutputGuard guard_eP_AA_T_StartLAS(paeP_AA_T_StartLAS);
        COutputGuard guard_eP_AA_T_RaubenTC(paeP_AA_T_RaubenTC);
        COutputGuard guard_eP_AA_N_Nachrauben(paeP_AA_N_Nachrauben);
        COutputGuard guard_eP_AA_T_StartNachrauben(paeP_AA_T_StartNachrauben);
        COutputGuard guard_eP_AA_T_Nachrauben(paeP_AA_T_Nachrauben);
        COutputGuard guard_eP_AA_T_TimeoutLoweringSensor(paeP_AA_T_TimeoutLoweringSensor);
        COutputGuard guard_eP_AA_P_EndeRauben(paeP_AA_P_EndeRauben);
        COutputGuard guard_eP_AA_T_AdditionalLowering(paeP_AA_T_AdditionalLowering);
        COutputGuard guard_eP_AA_T_StartSchreiten(paeP_AA_T_StartSchreiten);
        COutputGuard guard_eP_AA_T_Schreiten(paeP_AA_T_Schreiten);
        COutputGuard guard_eP_AA_V_MinSchreiten(paeP_AA_V_MinSchreiten);
        COutputGuard guard_eP_AA_P_StartNachraubenSensor(paeP_AA_P_StartNachraubenSensor);
        COutputGuard guard_eP_AA_T_RaubNachStartSchreit(paeP_AA_T_RaubNachStartSchreit);
        COutputGuard guard_eP_AA_P_StartSchreiten(paeP_AA_P_StartSchreiten);
        COutputGuard guard_eP_AA_Proz_EndeSchreiten(paeP_AA_Proz_EndeSchreiten);
        COutputGuard guard_eP_AA_T_Setzen(paeP_AA_T_Setzen);
        COutputGuard guard_eP_BL_T_AA_StartAusf(paeP_BL_T_AA_StartAusf);
        COutputGuard guard_eP_BL_T_AA_Einf(paeP_BL_T_AA_Einf);
        COutputGuard guard_eP_BL_T_AA_Ausf(paeP_BL_T_AA_Ausf);
        COutputGuard guard_eP_ECK_T_AA_PreStartEinf(paeP_ECK_T_AA_PreStartEinf);
        COutputGuard guard_eP_ECK_T_AA_PreEinf(paeP_ECK_T_AA_PreEinf);
        COutputGuard guard_eP_ECK_T_AA_StartAusf(paeP_ECK_T_AA_StartAusf);
        COutputGuard guard_eP_ECK_T_AA_Ausf(paeP_ECK_T_AA_Ausf);
        COutputGuard guard_eP_ECK_T_AA_Einf(paeP_ECK_T_AA_Einf);
        var_PARAM = paPARAM;
        executeEvent(scmEventREQID, nullptr);
        *paeP_AA_T_Vorwarnung = var_eP_AA_T_Vorwarnung;
        *paeP_AA_B_Sensorgesteuert = var_eP_AA_B_Sensorgesteuert;
        *paeP_AA_T_StartLAS = var_eP_AA_T_StartLAS;
        *paeP_AA_T_RaubenTC = var_eP_AA_T_RaubenTC;
        *paeP_AA_N_Nachrauben = var_eP_AA_N_Nachrauben;
        *paeP_AA_T_StartNachrauben = var_eP_AA_T_StartNachrauben;
        *paeP_AA_T_Nachrauben = var_eP_AA_T_Nachrauben;
        *paeP_AA_T_TimeoutLoweringSensor = var_eP_AA_T_TimeoutLoweringSensor;
        *paeP_AA_P_EndeRauben = var_eP_AA_P_EndeRauben;
        *paeP_AA_T_AdditionalLowering = var_eP_AA_T_AdditionalLowering;
        *paeP_AA_T_StartSchreiten = var_eP_AA_T_StartSchreiten;
        *paeP_AA_T_Schreiten = var_eP_AA_T_Schreiten;
        *paeP_AA_V_MinSchreiten = var_eP_AA_V_MinSchreiten;
        *paeP_AA_P_StartNachraubenSensor = var_eP_AA_P_StartNachraubenSensor;
        *paeP_AA_T_RaubNachStartSchreit = var_eP_AA_T_RaubNachStartSchreit;
        *paeP_AA_P_StartSchreiten = var_eP_AA_P_StartSchreiten;
        *paeP_AA_Proz_EndeSchreiten = var_eP_AA_Proz_EndeSchreiten;
        *paeP_AA_T_Setzen = var_eP_AA_T_Setzen;
        *paeP_BL_T_AA_StartAusf = var_eP_BL_T_AA_StartAusf;
        *paeP_BL_T_AA_Einf = var_eP_BL_T_AA_Einf;
        *paeP_BL_T_AA_Ausf = var_eP_BL_T_AA_Ausf;
        *paeP_ECK_T_AA_PreStartEinf = var_eP_ECK_T_AA_PreStartEinf;
        *paeP_ECK_T_AA_PreEinf = var_eP_ECK_T_AA_PreEinf;
        *paeP_ECK_T_AA_StartAusf = var_eP_ECK_T_AA_StartAusf;
        *paeP_ECK_T_AA_Ausf = var_eP_ECK_T_AA_Ausf;
        *paeP_ECK_T_AA_Einf = var_eP_ECK_T_AA_Einf;
      }
  };
}

