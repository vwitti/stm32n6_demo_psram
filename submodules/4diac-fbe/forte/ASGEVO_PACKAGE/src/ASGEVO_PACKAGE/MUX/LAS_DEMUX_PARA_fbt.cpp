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

#include "forte/ASGEVO_PACKAGE/MUX/LAS_DEMUX_PARA_fbt.h"

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
    constexpr std::string_view TypeHash ="v1:SHA3-512:Zkcmnv8uHJ00LkdO8m0Qi62y6tLpSDVjIKFhtYVt12_SI_DUjDKMIwI8rymybCUdP7MrjCToZcybGGRzVA2BaA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"PARAM"_STRID};
    const auto cDataOutputNames = std::array{"eP_AA_T_Vorwarnung"_STRID, "eP_AA_B_Sensorgesteuert"_STRID, "eP_AA_T_StartLAS"_STRID, "eP_AA_T_RaubenTC"_STRID, "eP_AA_N_Nachrauben"_STRID, "eP_AA_T_StartNachrauben"_STRID, "eP_AA_T_Nachrauben"_STRID, "eP_AA_T_TimeoutLoweringSensor"_STRID, "eP_AA_P_EndeRauben"_STRID, "eP_AA_T_AdditionalLowering"_STRID, "eP_AA_T_StartSchreiten"_STRID, "eP_AA_T_Schreiten"_STRID, "eP_AA_V_MinSchreiten"_STRID, "eP_AA_P_StartNachraubenSensor"_STRID, "eP_AA_T_RaubNachStartSchreit"_STRID, "eP_AA_P_StartSchreiten"_STRID, "eP_AA_Proz_EndeSchreiten"_STRID, "eP_AA_T_Setzen"_STRID, "eP_BL_T_AA_StartAusf"_STRID, "eP_BL_T_AA_Einf"_STRID, "eP_BL_T_AA_Ausf"_STRID, "eP_ECK_T_AA_PreStartEinf"_STRID, "eP_ECK_T_AA_PreEinf"_STRID, "eP_ECK_T_AA_StartAusf"_STRID, "eP_ECK_T_AA_Ausf"_STRID, "eP_ECK_T_AA_Einf"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_LAS_DEMUX_PARA, "ASGEVO_PACKAGE::MUX::LAS_DEMUX_PARA"_STRID, TypeHash)

  FORTE_LAS_DEMUX_PARA::FORTE_LAS_DEMUX_PARA(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_PARAM(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER()),
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
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_PARAM(nullptr),
      conn_eP_AA_T_Vorwarnung(*this, 0, var_eP_AA_T_Vorwarnung),
      conn_eP_AA_B_Sensorgesteuert(*this, 1, var_eP_AA_B_Sensorgesteuert),
      conn_eP_AA_T_StartLAS(*this, 2, var_eP_AA_T_StartLAS),
      conn_eP_AA_T_RaubenTC(*this, 3, var_eP_AA_T_RaubenTC),
      conn_eP_AA_N_Nachrauben(*this, 4, var_eP_AA_N_Nachrauben),
      conn_eP_AA_T_StartNachrauben(*this, 5, var_eP_AA_T_StartNachrauben),
      conn_eP_AA_T_Nachrauben(*this, 6, var_eP_AA_T_Nachrauben),
      conn_eP_AA_T_TimeoutLoweringSensor(*this, 7, var_eP_AA_T_TimeoutLoweringSensor),
      conn_eP_AA_P_EndeRauben(*this, 8, var_eP_AA_P_EndeRauben),
      conn_eP_AA_T_AdditionalLowering(*this, 9, var_eP_AA_T_AdditionalLowering),
      conn_eP_AA_T_StartSchreiten(*this, 10, var_eP_AA_T_StartSchreiten),
      conn_eP_AA_T_Schreiten(*this, 11, var_eP_AA_T_Schreiten),
      conn_eP_AA_V_MinSchreiten(*this, 12, var_eP_AA_V_MinSchreiten),
      conn_eP_AA_P_StartNachraubenSensor(*this, 13, var_eP_AA_P_StartNachraubenSensor),
      conn_eP_AA_T_RaubNachStartSchreit(*this, 14, var_eP_AA_T_RaubNachStartSchreit),
      conn_eP_AA_P_StartSchreiten(*this, 15, var_eP_AA_P_StartSchreiten),
      conn_eP_AA_Proz_EndeSchreiten(*this, 16, var_eP_AA_Proz_EndeSchreiten),
      conn_eP_AA_T_Setzen(*this, 17, var_eP_AA_T_Setzen),
      conn_eP_BL_T_AA_StartAusf(*this, 18, var_eP_BL_T_AA_StartAusf),
      conn_eP_BL_T_AA_Einf(*this, 19, var_eP_BL_T_AA_Einf),
      conn_eP_BL_T_AA_Ausf(*this, 20, var_eP_BL_T_AA_Ausf),
      conn_eP_ECK_T_AA_PreStartEinf(*this, 21, var_eP_ECK_T_AA_PreStartEinf),
      conn_eP_ECK_T_AA_PreEinf(*this, 22, var_eP_ECK_T_AA_PreEinf),
      conn_eP_ECK_T_AA_StartAusf(*this, 23, var_eP_ECK_T_AA_StartAusf),
      conn_eP_ECK_T_AA_Ausf(*this, 24, var_eP_ECK_T_AA_Ausf),
      conn_eP_ECK_T_AA_Einf(*this, 25, var_eP_ECK_T_AA_Einf) {
  }

  void FORTE_LAS_DEMUX_PARA::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_PARAM = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER();
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
  }

  void FORTE_LAS_DEMUX_PARA::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_LAS_DEMUX_PARA::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_LAS_DEMUX_PARA::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_LAS_DEMUX_PARA::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_PARAM, conn_PARAM);
        break;
      }
      case scmEventREQID: {
        readData(0, var_PARAM, conn_PARAM);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_LAS_DEMUX_PARA::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(1, var_eP_AA_T_Vorwarnung, conn_eP_AA_T_Vorwarnung);
        writeData(2, var_eP_AA_B_Sensorgesteuert, conn_eP_AA_B_Sensorgesteuert);
        writeData(3, var_eP_AA_T_StartLAS, conn_eP_AA_T_StartLAS);
        writeData(4, var_eP_AA_T_RaubenTC, conn_eP_AA_T_RaubenTC);
        writeData(5, var_eP_AA_N_Nachrauben, conn_eP_AA_N_Nachrauben);
        writeData(6, var_eP_AA_T_StartNachrauben, conn_eP_AA_T_StartNachrauben);
        writeData(7, var_eP_AA_T_Nachrauben, conn_eP_AA_T_Nachrauben);
        writeData(8, var_eP_AA_T_TimeoutLoweringSensor, conn_eP_AA_T_TimeoutLoweringSensor);
        writeData(9, var_eP_AA_P_EndeRauben, conn_eP_AA_P_EndeRauben);
        writeData(10, var_eP_AA_T_AdditionalLowering, conn_eP_AA_T_AdditionalLowering);
        writeData(11, var_eP_AA_T_StartSchreiten, conn_eP_AA_T_StartSchreiten);
        writeData(12, var_eP_AA_T_Schreiten, conn_eP_AA_T_Schreiten);
        writeData(13, var_eP_AA_V_MinSchreiten, conn_eP_AA_V_MinSchreiten);
        writeData(14, var_eP_AA_P_StartNachraubenSensor, conn_eP_AA_P_StartNachraubenSensor);
        writeData(15, var_eP_AA_T_RaubNachStartSchreit, conn_eP_AA_T_RaubNachStartSchreit);
        writeData(16, var_eP_AA_P_StartSchreiten, conn_eP_AA_P_StartSchreiten);
        writeData(17, var_eP_AA_Proz_EndeSchreiten, conn_eP_AA_Proz_EndeSchreiten);
        writeData(18, var_eP_AA_T_Setzen, conn_eP_AA_T_Setzen);
        writeData(19, var_eP_BL_T_AA_StartAusf, conn_eP_BL_T_AA_StartAusf);
        writeData(20, var_eP_BL_T_AA_Einf, conn_eP_BL_T_AA_Einf);
        writeData(21, var_eP_BL_T_AA_Ausf, conn_eP_BL_T_AA_Ausf);
        writeData(22, var_eP_ECK_T_AA_PreStartEinf, conn_eP_ECK_T_AA_PreStartEinf);
        writeData(23, var_eP_ECK_T_AA_PreEinf, conn_eP_ECK_T_AA_PreEinf);
        writeData(24, var_eP_ECK_T_AA_StartAusf, conn_eP_ECK_T_AA_StartAusf);
        writeData(25, var_eP_ECK_T_AA_Ausf, conn_eP_ECK_T_AA_Ausf);
        writeData(26, var_eP_ECK_T_AA_Einf, conn_eP_ECK_T_AA_Einf);
        break;
      }
      case scmEventCNFID: {
        writeData(1, var_eP_AA_T_Vorwarnung, conn_eP_AA_T_Vorwarnung);
        writeData(2, var_eP_AA_B_Sensorgesteuert, conn_eP_AA_B_Sensorgesteuert);
        writeData(3, var_eP_AA_T_StartLAS, conn_eP_AA_T_StartLAS);
        writeData(4, var_eP_AA_T_RaubenTC, conn_eP_AA_T_RaubenTC);
        writeData(5, var_eP_AA_N_Nachrauben, conn_eP_AA_N_Nachrauben);
        writeData(6, var_eP_AA_T_StartNachrauben, conn_eP_AA_T_StartNachrauben);
        writeData(7, var_eP_AA_T_Nachrauben, conn_eP_AA_T_Nachrauben);
        writeData(8, var_eP_AA_T_TimeoutLoweringSensor, conn_eP_AA_T_TimeoutLoweringSensor);
        writeData(9, var_eP_AA_P_EndeRauben, conn_eP_AA_P_EndeRauben);
        writeData(10, var_eP_AA_T_AdditionalLowering, conn_eP_AA_T_AdditionalLowering);
        writeData(11, var_eP_AA_T_StartSchreiten, conn_eP_AA_T_StartSchreiten);
        writeData(12, var_eP_AA_T_Schreiten, conn_eP_AA_T_Schreiten);
        writeData(13, var_eP_AA_V_MinSchreiten, conn_eP_AA_V_MinSchreiten);
        writeData(14, var_eP_AA_P_StartNachraubenSensor, conn_eP_AA_P_StartNachraubenSensor);
        writeData(15, var_eP_AA_T_RaubNachStartSchreit, conn_eP_AA_T_RaubNachStartSchreit);
        writeData(16, var_eP_AA_P_StartSchreiten, conn_eP_AA_P_StartSchreiten);
        writeData(17, var_eP_AA_Proz_EndeSchreiten, conn_eP_AA_Proz_EndeSchreiten);
        writeData(18, var_eP_AA_T_Setzen, conn_eP_AA_T_Setzen);
        writeData(19, var_eP_BL_T_AA_StartAusf, conn_eP_BL_T_AA_StartAusf);
        writeData(20, var_eP_BL_T_AA_Einf, conn_eP_BL_T_AA_Einf);
        writeData(21, var_eP_BL_T_AA_Ausf, conn_eP_BL_T_AA_Ausf);
        writeData(22, var_eP_ECK_T_AA_PreStartEinf, conn_eP_ECK_T_AA_PreStartEinf);
        writeData(23, var_eP_ECK_T_AA_PreEinf, conn_eP_ECK_T_AA_PreEinf);
        writeData(24, var_eP_ECK_T_AA_StartAusf, conn_eP_ECK_T_AA_StartAusf);
        writeData(25, var_eP_ECK_T_AA_Ausf, conn_eP_ECK_T_AA_Ausf);
        writeData(26, var_eP_ECK_T_AA_Einf, conn_eP_ECK_T_AA_Einf);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_LAS_DEMUX_PARA::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_PARAM;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_DEMUX_PARA::getDO(const size_t paIndex) {
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

  CEventConnection *FORTE_LAS_DEMUX_PARA::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_LAS_DEMUX_PARA::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_PARAM;
    }
    return nullptr;
  }

  CDataConnection *FORTE_LAS_DEMUX_PARA::getDOConUnchecked(const TPortId paIndex) {
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

  CIEC_ANY *FORTE_LAS_DEMUX_PARA::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_LAS_DEMUX_PARA::alg_INIT(void) {

    #line 2 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_Vorwarnung = var_PARAM.var_eP_AA_T_Vorwarnung;
    #line 3 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_B_Sensorgesteuert = var_PARAM.var_eP_AA_B_Sensorgesteuert;
    #line 4 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_StartLAS = var_PARAM.var_eP_AA_T_StartLAS;
    #line 5 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_RaubenTC = var_PARAM.var_eP_AA_T_RaubenTC;
    #line 6 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_N_Nachrauben = var_PARAM.var_eP_AA_N_Nachrauben;
    #line 7 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_StartNachrauben = var_PARAM.var_eP_AA_T_StartNachrauben;
    #line 8 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_Nachrauben = var_PARAM.var_eP_AA_T_Nachrauben;
    #line 9 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_TimeoutLoweringSensor = var_PARAM.var_eP_AA_T_TimeoutLoweringSensor;
    #line 10 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_P_EndeRauben = var_PARAM.var_eP_AA_P_EndeRauben;
    #line 11 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_AdditionalLowering = var_PARAM.var_eP_AA_T_AdditionalLowering;
    #line 12 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_StartSchreiten = var_PARAM.var_eP_AA_T_StartSchreiten;
    #line 13 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_Schreiten = var_PARAM.var_eP_AA_T_Schreiten;
    #line 14 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_V_MinSchreiten = var_PARAM.var_eP_AA_V_MinSchreiten;
    #line 15 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_P_StartNachraubenSensor = var_PARAM.var_eP_AA_P_StartNachraubenSensor;
    #line 16 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_RaubNachStartSchreit = var_PARAM.var_eP_AA_T_RaubNachStartSchreit;
    #line 17 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_P_StartSchreiten = var_PARAM.var_eP_AA_P_StartSchreiten;
    #line 18 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_Proz_EndeSchreiten = var_PARAM.var_eP_AA_Proz_EndeSchreiten;
    #line 19 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_Setzen = var_PARAM.var_eP_AA_T_Setzen;
    #line 20 "LAS_DEMUX_PARA.fbt"
    var_eP_BL_T_AA_StartAusf = var_PARAM.var_eP_BL_T_AA_StartAusf;
    #line 21 "LAS_DEMUX_PARA.fbt"
    var_eP_BL_T_AA_Einf = var_PARAM.var_eP_BL_T_AA_Einf;
    #line 22 "LAS_DEMUX_PARA.fbt"
    var_eP_BL_T_AA_Ausf = var_PARAM.var_eP_BL_T_AA_Ausf;
    #line 23 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_PreStartEinf = var_PARAM.var_eP_ECK_T_AA_PreStartEinf;
    #line 24 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_PreEinf = var_PARAM.var_eP_ECK_T_AA_PreEinf;
    #line 25 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_StartAusf = var_PARAM.var_eP_ECK_T_AA_StartAusf;
    #line 26 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_Ausf = var_PARAM.var_eP_ECK_T_AA_Ausf;
    #line 27 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_Einf = var_PARAM.var_eP_ECK_T_AA_Einf;
  }

  void FORTE_LAS_DEMUX_PARA::alg_REQ(void) {

    #line 31 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_Vorwarnung = var_PARAM.var_eP_AA_T_Vorwarnung;
    #line 32 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_B_Sensorgesteuert = var_PARAM.var_eP_AA_B_Sensorgesteuert;
    #line 33 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_StartLAS = var_PARAM.var_eP_AA_T_StartLAS;
    #line 34 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_RaubenTC = var_PARAM.var_eP_AA_T_RaubenTC;
    #line 35 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_N_Nachrauben = var_PARAM.var_eP_AA_N_Nachrauben;
    #line 36 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_StartNachrauben = var_PARAM.var_eP_AA_T_StartNachrauben;
    #line 37 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_Nachrauben = var_PARAM.var_eP_AA_T_Nachrauben;
    #line 38 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_TimeoutLoweringSensor = var_PARAM.var_eP_AA_T_TimeoutLoweringSensor;
    #line 39 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_P_EndeRauben = var_PARAM.var_eP_AA_P_EndeRauben;
    #line 40 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_AdditionalLowering = var_PARAM.var_eP_AA_T_AdditionalLowering;
    #line 41 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_StartSchreiten = var_PARAM.var_eP_AA_T_StartSchreiten;
    #line 42 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_Schreiten = var_PARAM.var_eP_AA_T_Schreiten;
    #line 43 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_V_MinSchreiten = var_PARAM.var_eP_AA_V_MinSchreiten;
    #line 44 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_P_StartNachraubenSensor = var_PARAM.var_eP_AA_P_StartNachraubenSensor;
    #line 45 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_RaubNachStartSchreit = var_PARAM.var_eP_AA_T_RaubNachStartSchreit;
    #line 46 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_P_StartSchreiten = var_PARAM.var_eP_AA_P_StartSchreiten;
    #line 47 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_Proz_EndeSchreiten = var_PARAM.var_eP_AA_Proz_EndeSchreiten;
    #line 48 "LAS_DEMUX_PARA.fbt"
    var_eP_AA_T_Setzen = var_PARAM.var_eP_AA_T_Setzen;
    #line 49 "LAS_DEMUX_PARA.fbt"
    var_eP_BL_T_AA_StartAusf = var_PARAM.var_eP_BL_T_AA_StartAusf;
    #line 50 "LAS_DEMUX_PARA.fbt"
    var_eP_BL_T_AA_Einf = var_PARAM.var_eP_BL_T_AA_Einf;
    #line 51 "LAS_DEMUX_PARA.fbt"
    var_eP_BL_T_AA_Ausf = var_PARAM.var_eP_BL_T_AA_Ausf;
    #line 52 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_PreStartEinf = var_PARAM.var_eP_ECK_T_AA_PreStartEinf;
    #line 53 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_PreEinf = var_PARAM.var_eP_ECK_T_AA_PreEinf;
    #line 54 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_StartAusf = var_PARAM.var_eP_ECK_T_AA_StartAusf;
    #line 55 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_Ausf = var_PARAM.var_eP_ECK_T_AA_Ausf;
    #line 56 "LAS_DEMUX_PARA.fbt"
    var_eP_ECK_T_AA_Einf = var_PARAM.var_eP_ECK_T_AA_Einf;
  }

}