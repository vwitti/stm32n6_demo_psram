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

#include "forte/ASGEVO_PACKAGE/MUX/LAS_MUX_PARA_fbt.h"

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::MUX {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:H2vK_EY9ZduZa7BQZF_aErwcmaIeHPyk8yVzxiWolHvcaY0aSG7q8UujKljudAqePgCPI2lk4CbYuJdPtO0qrA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"eP_AA_T_Vorwarnung"_STRID, "eP_AA_B_Sensorgesteuert"_STRID, "eP_AA_T_StartLAS"_STRID, "eP_AA_T_RaubenTC"_STRID, "eP_AA_N_Nachrauben"_STRID, "eP_AA_T_StartNachrauben"_STRID, "eP_AA_T_Nachrauben"_STRID, "eP_AA_T_TimeoutLoweringSensor"_STRID, "eP_AA_P_EndeRauben"_STRID, "eP_AA_T_AdditionalLowering"_STRID, "eP_AA_T_StartSchreiten"_STRID, "eP_AA_T_Schreiten"_STRID, "eP_AA_V_MinSchreiten"_STRID, "eP_AA_P_StartNachraubenSensor"_STRID, "eP_AA_T_RaubNachStartSchreit"_STRID, "eP_AA_P_StartSchreiten"_STRID, "eP_AA_Proz_EndeSchreiten"_STRID, "eP_AA_T_Setzen"_STRID, "eP_BL_T_AA_StartAusf"_STRID, "eP_BL_T_AA_Einf"_STRID, "eP_BL_T_AA_Ausf"_STRID, "eP_ECK_T_AA_PreStartEinf"_STRID, "eP_ECK_T_AA_PreEinf"_STRID, "eP_ECK_T_AA_StartAusf"_STRID, "eP_ECK_T_AA_Ausf"_STRID, "eP_ECK_T_AA_Einf"_STRID};
    const auto cDataOutputNames = std::array{"PARAM"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = cEventInputTypeIds,
        .mEONames = cEventOutputNames,
        .mEOTypeNames = cEventOutputTypeIds,
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_LAS_MUX_PARA, "ASGEVO_PACKAGE::MUX::LAS_MUX_PARA"_STRID, TypeHash)

  FORTE_LAS_MUX_PARA::FORTE_LAS_MUX_PARA(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
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
      var_eP_ECK_T_AA_Einf(0_TIME),
      var_PARAM(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER()),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_eP_AA_T_Vorwarnung(nullptr),
      conn_eP_AA_B_Sensorgesteuert(nullptr),
      conn_eP_AA_T_StartLAS(nullptr),
      conn_eP_AA_T_RaubenTC(nullptr),
      conn_eP_AA_N_Nachrauben(nullptr),
      conn_eP_AA_T_StartNachrauben(nullptr),
      conn_eP_AA_T_Nachrauben(nullptr),
      conn_eP_AA_T_TimeoutLoweringSensor(nullptr),
      conn_eP_AA_P_EndeRauben(nullptr),
      conn_eP_AA_T_AdditionalLowering(nullptr),
      conn_eP_AA_T_StartSchreiten(nullptr),
      conn_eP_AA_T_Schreiten(nullptr),
      conn_eP_AA_V_MinSchreiten(nullptr),
      conn_eP_AA_P_StartNachraubenSensor(nullptr),
      conn_eP_AA_T_RaubNachStartSchreit(nullptr),
      conn_eP_AA_P_StartSchreiten(nullptr),
      conn_eP_AA_Proz_EndeSchreiten(nullptr),
      conn_eP_AA_T_Setzen(nullptr),
      conn_eP_BL_T_AA_StartAusf(nullptr),
      conn_eP_BL_T_AA_Einf(nullptr),
      conn_eP_BL_T_AA_Ausf(nullptr),
      conn_eP_ECK_T_AA_PreStartEinf(nullptr),
      conn_eP_ECK_T_AA_PreEinf(nullptr),
      conn_eP_ECK_T_AA_StartAusf(nullptr),
      conn_eP_ECK_T_AA_Ausf(nullptr),
      conn_eP_ECK_T_AA_Einf(nullptr),
      conn_PARAM(*this, 0, var_PARAM) {
  }

  void FORTE_LAS_MUX_PARA::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_eP_AA_T_Vorwarnung = 0_TIME;
    var_eP_AA_B_Sensorgesteuert = 0_BOOL;
    var_eP_AA_T_StartLAS = 0_TIME;
    var_eP_AA_T_RaubenTC = 0_TIME;
    var_eP_AA_N_Nachrauben = 0_UINT;
    var_eP_AA_T_StartNachrauben = 0_TIME;
    var_eP_AA_T_Nachrauben = 0_TIME;
    var_eP_AA_T_TimeoutLoweringSensor = 0_TIME;
    var_eP_AA_P_EndeRauben = 0_UINT;
    var_eP_AA_T_AdditionalLowering = 0_TIME;
    var_eP_AA_T_StartSchreiten = 0_TIME;
    var_eP_AA_T_Schreiten = 0_TIME;
    var_eP_AA_V_MinSchreiten = 0_UINT;
    var_eP_AA_P_StartNachraubenSensor = 0_UINT;
    var_eP_AA_T_RaubNachStartSchreit = 0_TIME;
    var_eP_AA_P_StartSchreiten = 0_UINT;
    var_eP_AA_Proz_EndeSchreiten = 0_UINT;
    var_eP_AA_T_Setzen = 0_TIME;
    var_eP_BL_T_AA_StartAusf = 0_TIME;
    var_eP_BL_T_AA_Einf = 0_TIME;
    var_eP_BL_T_AA_Ausf = 0_TIME;
    var_eP_ECK_T_AA_PreStartEinf = 0_TIME;
    var_eP_ECK_T_AA_PreEinf = 0_TIME;
    var_eP_ECK_T_AA_StartAusf = 0_TIME;
    var_eP_ECK_T_AA_Ausf = 0_TIME;
    var_eP_ECK_T_AA_Einf = 0_TIME;
    var_PARAM = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER();
  }

  void FORTE_LAS_MUX_PARA::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventINITID:
        enterStateINIT(paECET);
        break;
      case scmEventREQID:
        enterStateREQ(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_LAS_MUX_PARA::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_LAS_MUX_PARA::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_LAS_MUX_PARA::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_eP_AA_T_Vorwarnung, conn_eP_AA_T_Vorwarnung);
        readData(1, var_eP_AA_B_Sensorgesteuert, conn_eP_AA_B_Sensorgesteuert);
        readData(2, var_eP_AA_T_StartLAS, conn_eP_AA_T_StartLAS);
        readData(3, var_eP_AA_T_RaubenTC, conn_eP_AA_T_RaubenTC);
        readData(4, var_eP_AA_N_Nachrauben, conn_eP_AA_N_Nachrauben);
        readData(5, var_eP_AA_T_StartNachrauben, conn_eP_AA_T_StartNachrauben);
        readData(6, var_eP_AA_T_Nachrauben, conn_eP_AA_T_Nachrauben);
        readData(7, var_eP_AA_T_TimeoutLoweringSensor, conn_eP_AA_T_TimeoutLoweringSensor);
        readData(8, var_eP_AA_P_EndeRauben, conn_eP_AA_P_EndeRauben);
        readData(9, var_eP_AA_T_AdditionalLowering, conn_eP_AA_T_AdditionalLowering);
        readData(10, var_eP_AA_T_StartSchreiten, conn_eP_AA_T_StartSchreiten);
        readData(11, var_eP_AA_T_Schreiten, conn_eP_AA_T_Schreiten);
        readData(12, var_eP_AA_V_MinSchreiten, conn_eP_AA_V_MinSchreiten);
        readData(13, var_eP_AA_P_StartNachraubenSensor, conn_eP_AA_P_StartNachraubenSensor);
        readData(14, var_eP_AA_T_RaubNachStartSchreit, conn_eP_AA_T_RaubNachStartSchreit);
        readData(15, var_eP_AA_P_StartSchreiten, conn_eP_AA_P_StartSchreiten);
        readData(16, var_eP_AA_Proz_EndeSchreiten, conn_eP_AA_Proz_EndeSchreiten);
        readData(17, var_eP_AA_T_Setzen, conn_eP_AA_T_Setzen);
        readData(18, var_eP_BL_T_AA_StartAusf, conn_eP_BL_T_AA_StartAusf);
        readData(19, var_eP_BL_T_AA_Einf, conn_eP_BL_T_AA_Einf);
        readData(20, var_eP_BL_T_AA_Ausf, conn_eP_BL_T_AA_Ausf);
        readData(21, var_eP_ECK_T_AA_PreStartEinf, conn_eP_ECK_T_AA_PreStartEinf);
        readData(22, var_eP_ECK_T_AA_PreEinf, conn_eP_ECK_T_AA_PreEinf);
        readData(23, var_eP_ECK_T_AA_StartAusf, conn_eP_ECK_T_AA_StartAusf);
        readData(24, var_eP_ECK_T_AA_Ausf, conn_eP_ECK_T_AA_Ausf);
        readData(25, var_eP_ECK_T_AA_Einf, conn_eP_ECK_T_AA_Einf);
        break;
      }
      case scmEventREQID: {
        readData(0, var_eP_AA_T_Vorwarnung, conn_eP_AA_T_Vorwarnung);
        readData(1, var_eP_AA_B_Sensorgesteuert, conn_eP_AA_B_Sensorgesteuert);
        readData(2, var_eP_AA_T_StartLAS, conn_eP_AA_T_StartLAS);
        readData(3, var_eP_AA_T_RaubenTC, conn_eP_AA_T_RaubenTC);
        readData(4, var_eP_AA_N_Nachrauben, conn_eP_AA_N_Nachrauben);
        readData(5, var_eP_AA_T_StartNachrauben, conn_eP_AA_T_StartNachrauben);
        readData(6, var_eP_AA_T_Nachrauben, conn_eP_AA_T_Nachrauben);
        readData(7, var_eP_AA_T_TimeoutLoweringSensor, conn_eP_AA_T_TimeoutLoweringSensor);
        readData(8, var_eP_AA_P_EndeRauben, conn_eP_AA_P_EndeRauben);
        readData(9, var_eP_AA_T_AdditionalLowering, conn_eP_AA_T_AdditionalLowering);
        readData(10, var_eP_AA_T_StartSchreiten, conn_eP_AA_T_StartSchreiten);
        readData(11, var_eP_AA_T_Schreiten, conn_eP_AA_T_Schreiten);
        readData(12, var_eP_AA_V_MinSchreiten, conn_eP_AA_V_MinSchreiten);
        readData(13, var_eP_AA_P_StartNachraubenSensor, conn_eP_AA_P_StartNachraubenSensor);
        readData(14, var_eP_AA_T_RaubNachStartSchreit, conn_eP_AA_T_RaubNachStartSchreit);
        readData(15, var_eP_AA_P_StartSchreiten, conn_eP_AA_P_StartSchreiten);
        readData(16, var_eP_AA_Proz_EndeSchreiten, conn_eP_AA_Proz_EndeSchreiten);
        readData(17, var_eP_AA_T_Setzen, conn_eP_AA_T_Setzen);
        readData(18, var_eP_BL_T_AA_StartAusf, conn_eP_BL_T_AA_StartAusf);
        readData(19, var_eP_BL_T_AA_Einf, conn_eP_BL_T_AA_Einf);
        readData(20, var_eP_BL_T_AA_Ausf, conn_eP_BL_T_AA_Ausf);
        readData(21, var_eP_ECK_T_AA_PreStartEinf, conn_eP_ECK_T_AA_PreStartEinf);
        readData(22, var_eP_ECK_T_AA_PreEinf, conn_eP_ECK_T_AA_PreEinf);
        readData(23, var_eP_ECK_T_AA_StartAusf, conn_eP_ECK_T_AA_StartAusf);
        readData(24, var_eP_ECK_T_AA_Ausf, conn_eP_ECK_T_AA_Ausf);
        readData(25, var_eP_ECK_T_AA_Einf, conn_eP_ECK_T_AA_Einf);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_LAS_MUX_PARA::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_LAS_MUX_PARA::getDI(const size_t paIndex) {
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

  CIEC_ANY *FORTE_LAS_MUX_PARA::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_PARAM;
    }
    return nullptr;
  }

  CEventConnection *FORTE_LAS_MUX_PARA::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_LAS_MUX_PARA::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_eP_AA_T_Vorwarnung;
      case 1: return &conn_eP_AA_B_Sensorgesteuert;
      case 2: return &conn_eP_AA_T_StartLAS;
      case 3: return &conn_eP_AA_T_RaubenTC;
      case 4: return &conn_eP_AA_N_Nachrauben;
      case 5: return &conn_eP_AA_T_StartNachrauben;
      case 6: return &conn_eP_AA_T_Nachrauben;
      case 7: return &conn_eP_AA_T_TimeoutLoweringSensor;
      case 8: return &conn_eP_AA_P_EndeRauben;
      case 9: return &conn_eP_AA_T_AdditionalLowering;
      case 10: return &conn_eP_AA_T_StartSchreiten;
      case 11: return &conn_eP_AA_T_Schreiten;
      case 12: return &conn_eP_AA_V_MinSchreiten;
      case 13: return &conn_eP_AA_P_StartNachraubenSensor;
      case 14: return &conn_eP_AA_T_RaubNachStartSchreit;
      case 15: return &conn_eP_AA_P_StartSchreiten;
      case 16: return &conn_eP_AA_Proz_EndeSchreiten;
      case 17: return &conn_eP_AA_T_Setzen;
      case 18: return &conn_eP_BL_T_AA_StartAusf;
      case 19: return &conn_eP_BL_T_AA_Einf;
      case 20: return &conn_eP_BL_T_AA_Ausf;
      case 21: return &conn_eP_ECK_T_AA_PreStartEinf;
      case 22: return &conn_eP_ECK_T_AA_PreEinf;
      case 23: return &conn_eP_ECK_T_AA_StartAusf;
      case 24: return &conn_eP_ECK_T_AA_Ausf;
      case 25: return &conn_eP_ECK_T_AA_Einf;
    }
    return nullptr;
  }

  CDataConnection *FORTE_LAS_MUX_PARA::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_PARAM;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_MUX_PARA::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_LAS_MUX_PARA::alg_INIT(void) {

    #line 2 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_Vorwarnung = var_eP_AA_T_Vorwarnung;
    #line 3 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_B_Sensorgesteuert = var_eP_AA_B_Sensorgesteuert;
    #line 4 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_StartLAS = var_eP_AA_T_StartLAS;
    #line 5 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_RaubenTC = var_eP_AA_T_RaubenTC;
    #line 6 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_N_Nachrauben = var_eP_AA_N_Nachrauben;
    #line 7 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_StartNachrauben = var_eP_AA_T_StartNachrauben;
    #line 8 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_Nachrauben = var_eP_AA_T_Nachrauben;
    #line 9 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_TimeoutLoweringSensor = var_eP_AA_T_TimeoutLoweringSensor;
    #line 10 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_P_EndeRauben = var_eP_AA_P_EndeRauben;
    #line 11 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_AdditionalLowering = var_eP_AA_T_AdditionalLowering;
    #line 12 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_StartSchreiten = var_eP_AA_T_StartSchreiten;
    #line 13 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_Schreiten = var_eP_AA_T_Schreiten;
    #line 14 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_V_MinSchreiten = var_eP_AA_V_MinSchreiten;
    #line 15 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_P_StartNachraubenSensor = var_eP_AA_P_StartNachraubenSensor;
    #line 16 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_RaubNachStartSchreit = var_eP_AA_T_RaubNachStartSchreit;
    #line 17 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_P_StartSchreiten = var_eP_AA_P_StartSchreiten;
    #line 18 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_Proz_EndeSchreiten = var_eP_AA_Proz_EndeSchreiten;
    #line 19 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_Setzen = var_eP_AA_T_Setzen;
    #line 20 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_BL_T_AA_StartAusf = var_eP_BL_T_AA_StartAusf;
    #line 21 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_BL_T_AA_Einf = var_eP_BL_T_AA_Einf;
    #line 22 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_BL_T_AA_Ausf = var_eP_BL_T_AA_Ausf;
    #line 23 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_PreStartEinf = var_eP_ECK_T_AA_PreStartEinf;
    #line 24 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_PreEinf = var_eP_ECK_T_AA_PreEinf;
    #line 25 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_StartAusf = var_eP_ECK_T_AA_StartAusf;
    #line 26 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_Ausf = var_eP_ECK_T_AA_Ausf;
    #line 27 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_Einf = var_eP_ECK_T_AA_Einf;
  }

  void FORTE_LAS_MUX_PARA::alg_REQ(void) {

    #line 31 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_Vorwarnung = var_eP_AA_T_Vorwarnung;
    #line 32 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_B_Sensorgesteuert = var_eP_AA_B_Sensorgesteuert;
    #line 33 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_StartLAS = var_eP_AA_T_StartLAS;
    #line 34 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_RaubenTC = var_eP_AA_T_RaubenTC;
    #line 35 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_N_Nachrauben = var_eP_AA_N_Nachrauben;
    #line 36 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_StartNachrauben = var_eP_AA_T_StartNachrauben;
    #line 37 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_Nachrauben = var_eP_AA_T_Nachrauben;
    #line 38 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_TimeoutLoweringSensor = var_eP_AA_T_TimeoutLoweringSensor;
    #line 39 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_P_EndeRauben = var_eP_AA_P_EndeRauben;
    #line 40 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_AdditionalLowering = var_eP_AA_T_AdditionalLowering;
    #line 41 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_StartSchreiten = var_eP_AA_T_StartSchreiten;
    #line 42 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_Schreiten = var_eP_AA_T_Schreiten;
    #line 43 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_V_MinSchreiten = var_eP_AA_V_MinSchreiten;
    #line 44 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_P_StartNachraubenSensor = var_eP_AA_P_StartNachraubenSensor;
    #line 45 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_RaubNachStartSchreit = var_eP_AA_T_RaubNachStartSchreit;
    #line 46 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_P_StartSchreiten = var_eP_AA_P_StartSchreiten;
    #line 47 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_Proz_EndeSchreiten = var_eP_AA_Proz_EndeSchreiten;
    #line 48 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_AA_T_Setzen = var_eP_AA_T_Setzen;
    #line 49 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_BL_T_AA_StartAusf = var_eP_BL_T_AA_StartAusf;
    #line 50 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_BL_T_AA_Einf = var_eP_BL_T_AA_Einf;
    #line 51 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_BL_T_AA_Ausf = var_eP_BL_T_AA_Ausf;
    #line 52 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_PreStartEinf = var_eP_ECK_T_AA_PreStartEinf;
    #line 53 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_PreEinf = var_eP_ECK_T_AA_PreEinf;
    #line 54 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_StartAusf = var_eP_ECK_T_AA_StartAusf;
    #line 55 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_Ausf = var_eP_ECK_T_AA_Ausf;
    #line 56 "LAS_MUX_PARA.fbt"
    var_PARAM.var_eP_ECK_T_AA_Einf = var_eP_ECK_T_AA_Einf;
  }

}