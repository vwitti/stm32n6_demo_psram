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

#include "forte/ASGEVO_PACKAGE/MUX/LAS_DEMUX_OUTPUTS_fbt.h"

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
    constexpr std::string_view TypeHash ="v1:SHA3-512:21pRMZYRtyua5mgSk7jdq9WcQk6o8jMa2RnFma1kyvgs0uo9LKZMgNcxiyFIvm9cxkagX3DgY_FWsb-e7TuJiA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"OUTPUTS"_STRID};
    const auto cDataOutputNames = std::array{"LOWER"_STRID, "SET"_STRID, "PULL"_STRID, "PUSH"_STRID, "BL_EXT"_STRID, "BL_RET"_STRID, "STAB_EXT"_STRID, "STAB_RET"_STRID, "CA"_STRID, "PREWARN"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_LAS_DEMUX_OUTPUTS, "ASGEVO_PACKAGE::MUX::LAS_DEMUX_OUTPUTS"_STRID, TypeHash)

  FORTE_LAS_DEMUX_OUTPUTS::FORTE_LAS_DEMUX_OUTPUTS(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_OUTPUTS(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS()),
      var_LOWER(0_BOOL),
      var_SET(0_BOOL),
      var_PULL(0_BOOL),
      var_PUSH(0_BOOL),
      var_BL_EXT(0_BOOL),
      var_BL_RET(0_BOOL),
      var_STAB_EXT(0_BOOL),
      var_STAB_RET(0_BOOL),
      var_CA(0_BOOL),
      var_PREWARN(0_BOOL),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_OUTPUTS(nullptr),
      conn_LOWER(*this, 0, var_LOWER),
      conn_SET(*this, 1, var_SET),
      conn_PULL(*this, 2, var_PULL),
      conn_PUSH(*this, 3, var_PUSH),
      conn_BL_EXT(*this, 4, var_BL_EXT),
      conn_BL_RET(*this, 5, var_BL_RET),
      conn_STAB_EXT(*this, 6, var_STAB_EXT),
      conn_STAB_RET(*this, 7, var_STAB_RET),
      conn_CA(*this, 8, var_CA),
      conn_PREWARN(*this, 9, var_PREWARN) {
  }

  void FORTE_LAS_DEMUX_OUTPUTS::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_OUTPUTS = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS();
    var_LOWER = 0_BOOL;
    var_SET = 0_BOOL;
    var_PULL = 0_BOOL;
    var_PUSH = 0_BOOL;
    var_BL_EXT = 0_BOOL;
    var_BL_RET = 0_BOOL;
    var_STAB_EXT = 0_BOOL;
    var_STAB_RET = 0_BOOL;
    var_CA = 0_BOOL;
    var_PREWARN = 0_BOOL;
  }

  void FORTE_LAS_DEMUX_OUTPUTS::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_LAS_DEMUX_OUTPUTS::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_LAS_DEMUX_OUTPUTS::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_LAS_DEMUX_OUTPUTS::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_OUTPUTS, conn_OUTPUTS);
        break;
      }
      case scmEventREQID: {
        readData(0, var_OUTPUTS, conn_OUTPUTS);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_LAS_DEMUX_OUTPUTS::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(1, var_LOWER, conn_LOWER);
        writeData(2, var_SET, conn_SET);
        writeData(3, var_PULL, conn_PULL);
        writeData(4, var_PUSH, conn_PUSH);
        writeData(5, var_BL_EXT, conn_BL_EXT);
        writeData(6, var_BL_RET, conn_BL_RET);
        writeData(7, var_STAB_EXT, conn_STAB_EXT);
        writeData(8, var_STAB_RET, conn_STAB_RET);
        writeData(9, var_CA, conn_CA);
        writeData(10, var_PREWARN, conn_PREWARN);
        break;
      }
      case scmEventCNFID: {
        writeData(1, var_LOWER, conn_LOWER);
        writeData(2, var_SET, conn_SET);
        writeData(3, var_PULL, conn_PULL);
        writeData(4, var_PUSH, conn_PUSH);
        writeData(5, var_BL_EXT, conn_BL_EXT);
        writeData(6, var_BL_RET, conn_BL_RET);
        writeData(7, var_STAB_EXT, conn_STAB_EXT);
        writeData(8, var_STAB_RET, conn_STAB_RET);
        writeData(9, var_CA, conn_CA);
        writeData(10, var_PREWARN, conn_PREWARN);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_LAS_DEMUX_OUTPUTS::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_OUTPUTS;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_DEMUX_OUTPUTS::getDO(const size_t paIndex) {
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
      case 9: return &var_PREWARN;
    }
    return nullptr;
  }

  CEventConnection *FORTE_LAS_DEMUX_OUTPUTS::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_LAS_DEMUX_OUTPUTS::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_OUTPUTS;
    }
    return nullptr;
  }

  CDataConnection *FORTE_LAS_DEMUX_OUTPUTS::getDOConUnchecked(const TPortId paIndex) {
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
      case 9: return &conn_PREWARN;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_DEMUX_OUTPUTS::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_LAS_DEMUX_OUTPUTS::alg_INIT(void) {

    #line 2 "LAS_DEMUX_OUTPUTS.fbt"
    var_PREWARN = var_OUTPUTS.var_PREWARN;
    #line 3 "LAS_DEMUX_OUTPUTS.fbt"
    var_LOWER = var_OUTPUTS.var_LOWER;
    #line 4 "LAS_DEMUX_OUTPUTS.fbt"
    var_SET = var_OUTPUTS.var_SET;
    #line 5 "LAS_DEMUX_OUTPUTS.fbt"
    var_PULL = var_OUTPUTS.var_PULL;
    #line 6 "LAS_DEMUX_OUTPUTS.fbt"
    var_PUSH = var_OUTPUTS.var_PUSH;
    #line 7 "LAS_DEMUX_OUTPUTS.fbt"
    var_BL_EXT = var_OUTPUTS.var_BL_EXT;
    #line 8 "LAS_DEMUX_OUTPUTS.fbt"
    var_BL_RET = var_OUTPUTS.var_BL_RET;
    #line 9 "LAS_DEMUX_OUTPUTS.fbt"
    var_STAB_EXT = var_OUTPUTS.var_STAB_EXT;
    #line 10 "LAS_DEMUX_OUTPUTS.fbt"
    var_STAB_RET = var_OUTPUTS.var_STAB_RET;
    #line 11 "LAS_DEMUX_OUTPUTS.fbt"
    var_CA = var_OUTPUTS.var_CA;
  }

  void FORTE_LAS_DEMUX_OUTPUTS::alg_REQ(void) {

    #line 15 "LAS_DEMUX_OUTPUTS.fbt"
    var_PREWARN = var_OUTPUTS.var_PREWARN;
    #line 16 "LAS_DEMUX_OUTPUTS.fbt"
    var_LOWER = var_OUTPUTS.var_LOWER;
    #line 17 "LAS_DEMUX_OUTPUTS.fbt"
    var_SET = var_OUTPUTS.var_SET;
    #line 18 "LAS_DEMUX_OUTPUTS.fbt"
    var_PULL = var_OUTPUTS.var_PULL;
    #line 19 "LAS_DEMUX_OUTPUTS.fbt"
    var_PUSH = var_OUTPUTS.var_PUSH;
    #line 20 "LAS_DEMUX_OUTPUTS.fbt"
    var_BL_EXT = var_OUTPUTS.var_BL_EXT;
    #line 21 "LAS_DEMUX_OUTPUTS.fbt"
    var_BL_RET = var_OUTPUTS.var_BL_RET;
    #line 22 "LAS_DEMUX_OUTPUTS.fbt"
    var_STAB_EXT = var_OUTPUTS.var_STAB_EXT;
    #line 23 "LAS_DEMUX_OUTPUTS.fbt"
    var_STAB_RET = var_OUTPUTS.var_STAB_RET;
    #line 24 "LAS_DEMUX_OUTPUTS.fbt"
    var_CA = var_OUTPUTS.var_CA;
  }

}