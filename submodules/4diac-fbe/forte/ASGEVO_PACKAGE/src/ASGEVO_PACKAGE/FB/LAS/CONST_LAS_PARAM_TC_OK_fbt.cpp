/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: CONST_LAS_PARAM_TC_OK
 *** Description: Simple FB with one algorithm
 *** Version:
 ***     1.0: 2026-02-25/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/LAS/CONST_LAS_PARAM_TC_OK_fbt.h"

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

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:fpZ4uLd_erWOXeI4UruQ0IKZ3Uv2ZMDvzkbT3laSwOrkW5_AU5WMdAbJkPBivN1WGaYfRl-KUReCh-W-soEalw=="sv;

    const auto cEventInputNames = std::array{"REQ"_STRID};
    const auto cEventOutputNames = std::array{"CNF"_STRID};
    const auto cDataOutputNames = std::array{"PARAM"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = {},
        .mEONames = cEventOutputNames,
        .mEOTypeNames = {},
        .mDINames = {},
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_CONST_LAS_PARAM_TC_OK, "ASGEVO_PACKAGE::FB::LAS::CONST_LAS_PARAM_TC_OK"_STRID, TypeHash)

  FORTE_CONST_LAS_PARAM_TC_OK::FORTE_CONST_LAS_PARAM_TC_OK(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_PARAM(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER()),
      conn_CNF(*this, 0),
      conn_PARAM(*this, 0, var_PARAM) {
  }

  void FORTE_CONST_LAS_PARAM_TC_OK::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_PARAM = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER();
  }

  void FORTE_CONST_LAS_PARAM_TC_OK::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventREQID:
        enterStateREQ(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_CONST_LAS_PARAM_TC_OK::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_CONST_LAS_PARAM_TC_OK::readInputData(TEventID) {
    // nothing to do
  }

  void FORTE_CONST_LAS_PARAM_TC_OK::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        writeData(0, var_PARAM, conn_PARAM);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_CONST_LAS_PARAM_TC_OK::getDI(size_t) {
    return nullptr;
  }

  CIEC_ANY *FORTE_CONST_LAS_PARAM_TC_OK::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_PARAM;
    }
    return nullptr;
  }

  CEventConnection *FORTE_CONST_LAS_PARAM_TC_OK::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_CONST_LAS_PARAM_TC_OK::getDIConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_CONST_LAS_PARAM_TC_OK::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_PARAM;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_CONST_LAS_PARAM_TC_OK::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_CONST_LAS_PARAM_TC_OK::alg_REQ(void) {

    #line 2 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_Vorwarnung = 10000000000_TIME;
    #line 3 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_B_Sensorgesteuert = false_BOOL;
    #line 4 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_StartLAS = 0_TIME;
    #line 5 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_RaubenTC = 7000000000_TIME;
    #line 6 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_N_Nachrauben = 0_UINT;
    #line 7 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_StartNachrauben = 800000000_TIME;
    #line 8 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_Nachrauben = 1200000000_TIME;
    #line 9 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_TimeoutLoweringSensor = 0_TIME;
    #line 10 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_P_EndeRauben = 0_UINT;
    #line 11 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_AdditionalLowering = 0_TIME;
    #line 12 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_StartSchreiten = 5000000000_TIME;
    #line 13 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_Schreiten = 8000000000_TIME;
    #line 14 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_V_MinSchreiten = 0_UINT;
    #line 15 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_P_StartNachraubenSensor = 0_UINT;
    #line 16 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_RaubNachStartSchreit = 0_TIME;
    #line 17 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_P_StartSchreiten = 0_UINT;
    #line 18 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_Proz_EndeSchreiten = 0_UINT;
    #line 19 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_AA_T_Setzen = 6000000000_TIME;
    #line 20 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_BL_T_AA_StartAusf = 1100000000_TIME;
    #line 21 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_BL_T_AA_Einf = 1200000000_TIME;
    #line 22 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_BL_T_AA_Ausf = 10000000000_TIME;
    #line 23 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_ECK_T_AA_PreStartEinf = 500000000_TIME;
    #line 24 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_ECK_T_AA_PreEinf = 600000000_TIME;
    #line 25 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_ECK_T_AA_StartAusf = 3000000000_TIME;
    #line 26 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_ECK_T_AA_Ausf = 1300000000_TIME;
    #line 27 "CONST_LAS_PARAM_TC_OK.fbt"
    var_PARAM.var_eP_ECK_T_AA_Einf = 1600000000_TIME;
  }

}