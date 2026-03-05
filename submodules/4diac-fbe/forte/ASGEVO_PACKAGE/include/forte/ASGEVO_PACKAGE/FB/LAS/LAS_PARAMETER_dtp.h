/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_PARAMETER
 *** Description: A Template for a Data Type
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#pragma once

#include "forte/datatypes/forte_struct.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"


namespace forte::ASGEVO_PACKAGE::FB::LAS {
  class CIEC_LAS_PARAMETER final : public CIEC_STRUCT {
    DECLARE_FIRMWARE_DATATYPE(LAS_PARAMETER)

    public:
      CIEC_LAS_PARAMETER();

      CIEC_LAS_PARAMETER(const CIEC_TIME &paeP_AA_T_Vorwarnung, const CIEC_BOOL &paeP_AA_B_Sensorgesteuert, const CIEC_TIME &paeP_AA_T_StartLAS, const CIEC_TIME &paeP_AA_T_RaubenTC, const CIEC_UINT &paeP_AA_N_Nachrauben, const CIEC_TIME &paeP_AA_T_StartNachrauben, const CIEC_TIME &paeP_AA_T_Nachrauben, const CIEC_TIME &paeP_AA_T_TimeoutLoweringSensor, const CIEC_UINT &paeP_AA_P_EndeRauben, const CIEC_TIME &paeP_AA_T_AdditionalLowering, const CIEC_TIME &paeP_AA_T_StartSchreiten, const CIEC_TIME &paeP_AA_T_Schreiten, const CIEC_UINT &paeP_AA_V_MinSchreiten, const CIEC_UINT &paeP_AA_P_StartNachraubenSensor, const CIEC_TIME &paeP_AA_T_RaubNachStartSchreit, const CIEC_UINT &paeP_AA_P_StartSchreiten, const CIEC_UINT &paeP_AA_Proz_EndeSchreiten, const CIEC_TIME &paeP_AA_T_Setzen, const CIEC_TIME &paeP_BL_T_AA_StartAusf, const CIEC_TIME &paeP_BL_T_AA_Einf, const CIEC_TIME &paeP_BL_T_AA_Ausf, const CIEC_TIME &paeP_ECK_T_AA_PreStartEinf, const CIEC_TIME &paeP_ECK_T_AA_PreEinf, const CIEC_TIME &paeP_ECK_T_AA_StartAusf, const CIEC_TIME &paeP_ECK_T_AA_Ausf, const CIEC_TIME &paeP_ECK_T_AA_Einf);

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

      size_t getStructSize() const override {
        return 26;
      }

      const StringId* elementNames() const override {
        return scmElementNames;
      }

      StringId getStructTypeNameID() const override;

      void setValue(const CIEC_ANY &paValue) override;

      CIEC_ANY *getMember(size_t) override;
      const CIEC_ANY *getMember(size_t) const override;

    private:
      static const StringId scmElementNames[];

  };
}

