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

#include "forte/ASGEVO_PACKAGE/MUX/LAS_MUX_OUTPUTS_fbt.h"

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::MUX {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:T_LTBvFke8ybSZDGKAGqofkVDALodVBkBJQV2C7iX81q0Gpc4cxeCwKvbjUG0LsorEWfsaSllnn410rsJwoB3w=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"LOWER"_STRID, "SET"_STRID, "PULL"_STRID, "PUSH"_STRID, "BL_EXT"_STRID, "BL_RET"_STRID, "STAB_EXT"_STRID, "STAB_RET"_STRID, "CA"_STRID};
    const auto cDataOutputNames = std::array{"OUTPUTS"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_LAS_MUX_OUTPUTS, "ASGEVO_PACKAGE::MUX::LAS_MUX_OUTPUTS"_STRID, TypeHash)

  FORTE_LAS_MUX_OUTPUTS::FORTE_LAS_MUX_OUTPUTS(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_LOWER(0_BOOL),
      var_SET(0_BOOL),
      var_PULL(0_BOOL),
      var_PUSH(0_BOOL),
      var_BL_EXT(0_BOOL),
      var_BL_RET(0_BOOL),
      var_STAB_EXT(0_BOOL),
      var_STAB_RET(0_BOOL),
      var_CA(0_BOOL),
      var_OUTPUTS(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS()),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_LOWER(nullptr),
      conn_SET(nullptr),
      conn_PULL(nullptr),
      conn_PUSH(nullptr),
      conn_BL_EXT(nullptr),
      conn_BL_RET(nullptr),
      conn_STAB_EXT(nullptr),
      conn_STAB_RET(nullptr),
      conn_CA(nullptr),
      conn_OUTPUTS(*this, 0, var_OUTPUTS) {
  }

  void FORTE_LAS_MUX_OUTPUTS::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_LOWER = 0_BOOL;
    var_SET = 0_BOOL;
    var_PULL = 0_BOOL;
    var_PUSH = 0_BOOL;
    var_BL_EXT = 0_BOOL;
    var_BL_RET = 0_BOOL;
    var_STAB_EXT = 0_BOOL;
    var_STAB_RET = 0_BOOL;
    var_CA = 0_BOOL;
    var_OUTPUTS = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS();
  }

  void FORTE_LAS_MUX_OUTPUTS::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_LAS_MUX_OUTPUTS::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_LAS_MUX_OUTPUTS::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_LAS_MUX_OUTPUTS::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_LOWER, conn_LOWER);
        readData(1, var_SET, conn_SET);
        readData(2, var_PULL, conn_PULL);
        readData(3, var_PUSH, conn_PUSH);
        readData(4, var_BL_EXT, conn_BL_EXT);
        readData(5, var_BL_RET, conn_BL_RET);
        readData(6, var_STAB_EXT, conn_STAB_EXT);
        readData(7, var_STAB_RET, conn_STAB_RET);
        readData(8, var_CA, conn_CA);
        break;
      }
      case scmEventREQID: {
        readData(0, var_LOWER, conn_LOWER);
        readData(1, var_SET, conn_SET);
        readData(2, var_PULL, conn_PULL);
        readData(3, var_PUSH, conn_PUSH);
        readData(4, var_BL_EXT, conn_BL_EXT);
        readData(5, var_BL_RET, conn_BL_RET);
        readData(6, var_STAB_EXT, conn_STAB_EXT);
        readData(7, var_STAB_RET, conn_STAB_RET);
        readData(8, var_CA, conn_CA);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_LAS_MUX_OUTPUTS::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(9, var_OUTPUTS, conn_OUTPUTS);
        break;
      }
      case scmEventCNFID: {
        writeData(9, var_OUTPUTS, conn_OUTPUTS);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_LAS_MUX_OUTPUTS::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_LOWER;
      case 1: return &var_SET;
      case 2: return &var_PULL;
      case 3: return &var_PUSH;
      case 4: return &var_BL_EXT;
      case 5: return &var_BL_RET;
      case 6: return &var_STAB_EXT;
      case 7: return &var_STAB_RET;
      case 8: return &var_CA;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_MUX_OUTPUTS::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_OUTPUTS;
    }
    return nullptr;
  }

  CEventConnection *FORTE_LAS_MUX_OUTPUTS::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_LAS_MUX_OUTPUTS::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_LOWER;
      case 1: return &conn_SET;
      case 2: return &conn_PULL;
      case 3: return &conn_PUSH;
      case 4: return &conn_BL_EXT;
      case 5: return &conn_BL_RET;
      case 6: return &conn_STAB_EXT;
      case 7: return &conn_STAB_RET;
      case 8: return &conn_CA;
    }
    return nullptr;
  }

  CDataConnection *FORTE_LAS_MUX_OUTPUTS::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_OUTPUTS;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_MUX_OUTPUTS::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_LAS_MUX_OUTPUTS::alg_INIT(void) {

    #line 2 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_LOWER = var_LOWER;
    #line 3 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_SET = var_SET;
    #line 4 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_PULL = var_PULL;
    #line 5 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_PUSH = var_PUSH;
    #line 6 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_BL_EXT = var_BL_EXT;
    #line 7 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_BL_RET = var_BL_RET;
    #line 8 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_STAB_EXT = var_STAB_EXT;
    #line 9 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_STAB_RET = var_STAB_RET;
    #line 10 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_CA = var_CA;
  }

  void FORTE_LAS_MUX_OUTPUTS::alg_REQ(void) {

    #line 14 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_LOWER = var_LOWER;
    #line 15 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_SET = var_SET;
    #line 16 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_PULL = var_PULL;
    #line 17 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_PUSH = var_PUSH;
    #line 18 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_BL_EXT = var_BL_EXT;
    #line 19 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_BL_RET = var_BL_RET;
    #line 20 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_STAB_EXT = var_STAB_EXT;
    #line 21 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_STAB_RET = var_STAB_RET;
    #line 22 "LAS_MUX_OUTPUTS.fbt"
    var_OUTPUTS.var_CA = var_CA;
  }

}