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

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:dbC07GQts3r4q5CKL7xn5bbuvITa-PLhf9ZXuhK8fcK13e0CyIy9oDUXJzUvNgFHabs2l_qNF2_dBSLG3mxmMg=="sv;
  }

  DEFINE_FIRMWARE_DATATYPE(LAS_PARAMETER, "ASGEVO_PACKAGE::FB::LAS::LAS_PARAMETER"_STRID, TypeHash);

  const StringId CIEC_LAS_PARAMETER::scmElementNames[] = {"eP_AA_T_Vorwarnung"_STRID, "eP_AA_B_Sensorgesteuert"_STRID, "eP_AA_T_StartLAS"_STRID, "eP_AA_T_RaubenTC"_STRID, "eP_AA_N_Nachrauben"_STRID, "eP_AA_T_StartNachrauben"_STRID, "eP_AA_T_Nachrauben"_STRID, "eP_AA_T_TimeoutLoweringSensor"_STRID, "eP_AA_P_EndeRauben"_STRID, "eP_AA_T_AdditionalLowering"_STRID, "eP_AA_T_StartSchreiten"_STRID, "eP_AA_T_Schreiten"_STRID, "eP_AA_V_MinSchreiten"_STRID, "eP_AA_P_StartNachraubenSensor"_STRID, "eP_AA_T_RaubNachStartSchreit"_STRID, "eP_AA_P_StartSchreiten"_STRID, "eP_AA_Proz_EndeSchreiten"_STRID, "eP_AA_T_Setzen"_STRID, "eP_BL_T_AA_StartAusf"_STRID, "eP_BL_T_AA_Einf"_STRID, "eP_BL_T_AA_Ausf"_STRID, "eP_ECK_T_AA_PreStartEinf"_STRID, "eP_ECK_T_AA_PreEinf"_STRID, "eP_ECK_T_AA_StartAusf"_STRID, "eP_ECK_T_AA_Ausf"_STRID, "eP_ECK_T_AA_Einf"_STRID};

  CIEC_LAS_PARAMETER::CIEC_LAS_PARAMETER() :
      CIEC_STRUCT(),
      var_eP_AA_T_Vorwarnung(0_TIME),
      var_eP_AA_B_Sensorgesteuert(0_BOOL),
      var_eP_AA_T_StartLAS(0_TIME),
      var_eP_AA_T_RaubenTC(0_TIME),
      var_eP_AA_N_Nachrauben(0_UINT),
      var_eP_AA_T_StartNachrauben(0_TIME),
      var_eP_AA_T_Nachrauben(0_TIME),
      var_eP_AA_T_TimeoutLoweringSensor(0_TIME),
      var_eP_AA_P_EndeRauben(0_UINT),
      var_eP_AA_T_AdditionalLowering(0_TIME),
      var_eP_AA_T_StartSchreiten(0_TIME),
      var_eP_AA_T_Schreiten(0_TIME),
      var_eP_AA_V_MinSchreiten(0_UINT),
      var_eP_AA_P_StartNachraubenSensor(0_UINT),
      var_eP_AA_T_RaubNachStartSchreit(0_TIME),
      var_eP_AA_P_StartSchreiten(0_UINT),
      var_eP_AA_Proz_EndeSchreiten(0_UINT),
      var_eP_AA_T_Setzen(0_TIME),
      var_eP_BL_T_AA_StartAusf(0_TIME),
      var_eP_BL_T_AA_Einf(0_TIME),
      var_eP_BL_T_AA_Ausf(0_TIME),
      var_eP_ECK_T_AA_PreStartEinf(0_TIME),
      var_eP_ECK_T_AA_PreEinf(0_TIME),
      var_eP_ECK_T_AA_StartAusf(0_TIME),
      var_eP_ECK_T_AA_Ausf(0_TIME),
      var_eP_ECK_T_AA_Einf(0_TIME) {
  }

  CIEC_LAS_PARAMETER::CIEC_LAS_PARAMETER(const CIEC_TIME &paeP_AA_T_Vorwarnung, const CIEC_BOOL &paeP_AA_B_Sensorgesteuert, const CIEC_TIME &paeP_AA_T_StartLAS, const CIEC_TIME &paeP_AA_T_RaubenTC, const CIEC_UINT &paeP_AA_N_Nachrauben, const CIEC_TIME &paeP_AA_T_StartNachrauben, const CIEC_TIME &paeP_AA_T_Nachrauben, const CIEC_TIME &paeP_AA_T_TimeoutLoweringSensor, const CIEC_UINT &paeP_AA_P_EndeRauben, const CIEC_TIME &paeP_AA_T_AdditionalLowering, const CIEC_TIME &paeP_AA_T_StartSchreiten, const CIEC_TIME &paeP_AA_T_Schreiten, const CIEC_UINT &paeP_AA_V_MinSchreiten, const CIEC_UINT &paeP_AA_P_StartNachraubenSensor, const CIEC_TIME &paeP_AA_T_RaubNachStartSchreit, const CIEC_UINT &paeP_AA_P_StartSchreiten, const CIEC_UINT &paeP_AA_Proz_EndeSchreiten, const CIEC_TIME &paeP_AA_T_Setzen, const CIEC_TIME &paeP_BL_T_AA_StartAusf, const CIEC_TIME &paeP_BL_T_AA_Einf, const CIEC_TIME &paeP_BL_T_AA_Ausf, const CIEC_TIME &paeP_ECK_T_AA_PreStartEinf, const CIEC_TIME &paeP_ECK_T_AA_PreEinf, const CIEC_TIME &paeP_ECK_T_AA_StartAusf, const CIEC_TIME &paeP_ECK_T_AA_Ausf, const CIEC_TIME &paeP_ECK_T_AA_Einf) :
      CIEC_STRUCT(),
      var_eP_AA_T_Vorwarnung(paeP_AA_T_Vorwarnung),
      var_eP_AA_B_Sensorgesteuert(paeP_AA_B_Sensorgesteuert),
      var_eP_AA_T_StartLAS(paeP_AA_T_StartLAS),
      var_eP_AA_T_RaubenTC(paeP_AA_T_RaubenTC),
      var_eP_AA_N_Nachrauben(paeP_AA_N_Nachrauben),
      var_eP_AA_T_StartNachrauben(paeP_AA_T_StartNachrauben),
      var_eP_AA_T_Nachrauben(paeP_AA_T_Nachrauben),
      var_eP_AA_T_TimeoutLoweringSensor(paeP_AA_T_TimeoutLoweringSensor),
      var_eP_AA_P_EndeRauben(paeP_AA_P_EndeRauben),
      var_eP_AA_T_AdditionalLowering(paeP_AA_T_AdditionalLowering),
      var_eP_AA_T_StartSchreiten(paeP_AA_T_StartSchreiten),
      var_eP_AA_T_Schreiten(paeP_AA_T_Schreiten),
      var_eP_AA_V_MinSchreiten(paeP_AA_V_MinSchreiten),
      var_eP_AA_P_StartNachraubenSensor(paeP_AA_P_StartNachraubenSensor),
      var_eP_AA_T_RaubNachStartSchreit(paeP_AA_T_RaubNachStartSchreit),
      var_eP_AA_P_StartSchreiten(paeP_AA_P_StartSchreiten),
      var_eP_AA_Proz_EndeSchreiten(paeP_AA_Proz_EndeSchreiten),
      var_eP_AA_T_Setzen(paeP_AA_T_Setzen),
      var_eP_BL_T_AA_StartAusf(paeP_BL_T_AA_StartAusf),
      var_eP_BL_T_AA_Einf(paeP_BL_T_AA_Einf),
      var_eP_BL_T_AA_Ausf(paeP_BL_T_AA_Ausf),
      var_eP_ECK_T_AA_PreStartEinf(paeP_ECK_T_AA_PreStartEinf),
      var_eP_ECK_T_AA_PreEinf(paeP_ECK_T_AA_PreEinf),
      var_eP_ECK_T_AA_StartAusf(paeP_ECK_T_AA_StartAusf),
      var_eP_ECK_T_AA_Ausf(paeP_ECK_T_AA_Ausf),
      var_eP_ECK_T_AA_Einf(paeP_ECK_T_AA_Einf) {
  }

  StringId CIEC_LAS_PARAMETER::getStructTypeNameID() const {
    return "ASGEVO_PACKAGE::FB::LAS::LAS_PARAMETER"_STRID;
  }

  void CIEC_LAS_PARAMETER::setValue(const CIEC_ANY &paValue) {
    if (paValue.getDataTypeID() == e_STRUCT) {
      auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
      if ("ASGEVO_PACKAGE::FB::LAS::LAS_PARAMETER"_STRID == otherStruct.getStructTypeNameID()) {
        operator=(static_cast<const CIEC_LAS_PARAMETER &>(paValue));
      }
    }
  }

  CIEC_ANY *CIEC_LAS_PARAMETER::getMember(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_eP_AA_T_Vorwarnung;
      case 1: return &var_eP_AA_B_Sensorgesteuert;
      case 2: return &var_eP_AA_T_StartLAS;
      case 3: return &var_eP_AA_T_RaubenTC;
      case 4: return &var_eP_AA_N_Nachrauben;
      case 5: return &var_eP_AA_T_StartNachrauben;
      case 6: return &var_eP_AA_T_Nachrauben;
      case 7: return &var_eP_AA_T_TimeoutLoweringSensor;
      case 8: return &var_eP_AA_P_EndeRauben;
      case 9: return &var_eP_AA_T_AdditionalLowering;
      case 10: return &var_eP_AA_T_StartSchreiten;
      case 11: return &var_eP_AA_T_Schreiten;
      case 12: return &var_eP_AA_V_MinSchreiten;
      case 13: return &var_eP_AA_P_StartNachraubenSensor;
      case 14: return &var_eP_AA_T_RaubNachStartSchreit;
      case 15: return &var_eP_AA_P_StartSchreiten;
      case 16: return &var_eP_AA_Proz_EndeSchreiten;
      case 17: return &var_eP_AA_T_Setzen;
      case 18: return &var_eP_BL_T_AA_StartAusf;
      case 19: return &var_eP_BL_T_AA_Einf;
      case 20: return &var_eP_BL_T_AA_Ausf;
      case 21: return &var_eP_ECK_T_AA_PreStartEinf;
      case 22: return &var_eP_ECK_T_AA_PreEinf;
      case 23: return &var_eP_ECK_T_AA_StartAusf;
      case 24: return &var_eP_ECK_T_AA_Ausf;
      case 25: return &var_eP_ECK_T_AA_Einf;
    }
    return nullptr;
  }

  const CIEC_ANY *CIEC_LAS_PARAMETER::getMember(const size_t paIndex) const {
    switch(paIndex) {
      case 0: return &var_eP_AA_T_Vorwarnung;
      case 1: return &var_eP_AA_B_Sensorgesteuert;
      case 2: return &var_eP_AA_T_StartLAS;
      case 3: return &var_eP_AA_T_RaubenTC;
      case 4: return &var_eP_AA_N_Nachrauben;
      case 5: return &var_eP_AA_T_StartNachrauben;
      case 6: return &var_eP_AA_T_Nachrauben;
      case 7: return &var_eP_AA_T_TimeoutLoweringSensor;
      case 8: return &var_eP_AA_P_EndeRauben;
      case 9: return &var_eP_AA_T_AdditionalLowering;
      case 10: return &var_eP_AA_T_StartSchreiten;
      case 11: return &var_eP_AA_T_Schreiten;
      case 12: return &var_eP_AA_V_MinSchreiten;
      case 13: return &var_eP_AA_P_StartNachraubenSensor;
      case 14: return &var_eP_AA_T_RaubNachStartSchreit;
      case 15: return &var_eP_AA_P_StartSchreiten;
      case 16: return &var_eP_AA_Proz_EndeSchreiten;
      case 17: return &var_eP_AA_T_Setzen;
      case 18: return &var_eP_BL_T_AA_StartAusf;
      case 19: return &var_eP_BL_T_AA_Einf;
      case 20: return &var_eP_BL_T_AA_Ausf;
      case 21: return &var_eP_ECK_T_AA_PreStartEinf;
      case 22: return &var_eP_ECK_T_AA_PreEinf;
      case 23: return &var_eP_ECK_T_AA_StartAusf;
      case 24: return &var_eP_ECK_T_AA_Ausf;
      case 25: return &var_eP_ECK_T_AA_Einf;
    }
    return nullptr;
  }

}