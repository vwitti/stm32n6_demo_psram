/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_MUX_TIMING
 *** Description: Simple FB with init event and one algorithm
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/MUX/LAS_MUX_TIMING_fbt.h"

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_TIMING_dtp.h"
#include "forte/datatypes/forte_time.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::MUX {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:T3OjE0vCP-Xt2TKjpjht1s8ZeSvRYbU9YR47hx3-H-nxnfGKYrprmrtAWrk6lSSHv7OCqyAUqT9em2HHEVEdBQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"T_LOWER"_STRID, "T_ADVANCE"_STRID, "T_SET"_STRID, "T_TOTAL"_STRID};
    const auto cDataOutputNames = std::array{"TIMING"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_LAS_MUX_TIMING, "ASGEVO_PACKAGE::MUX::LAS_MUX_TIMING"_STRID, TypeHash)

  FORTE_LAS_MUX_TIMING::FORTE_LAS_MUX_TIMING(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_T_LOWER(0_TIME),
      var_T_ADVANCE(0_TIME),
      var_T_SET(0_TIME),
      var_T_TOTAL(0_TIME),
      var_TIMING(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING()),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_T_LOWER(nullptr),
      conn_T_ADVANCE(nullptr),
      conn_T_SET(nullptr),
      conn_T_TOTAL(nullptr),
      conn_TIMING(*this, 0, var_TIMING) {
  }

  void FORTE_LAS_MUX_TIMING::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_T_LOWER = 0_TIME;
    var_T_ADVANCE = 0_TIME;
    var_T_SET = 0_TIME;
    var_T_TOTAL = 0_TIME;
    var_TIMING = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING();
  }

  void FORTE_LAS_MUX_TIMING::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_LAS_MUX_TIMING::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_LAS_MUX_TIMING::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_LAS_MUX_TIMING::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_T_LOWER, conn_T_LOWER);
        readData(1, var_T_ADVANCE, conn_T_ADVANCE);
        readData(2, var_T_SET, conn_T_SET);
        readData(3, var_T_TOTAL, conn_T_TOTAL);
        break;
      }
      case scmEventREQID: {
        readData(0, var_T_LOWER, conn_T_LOWER);
        readData(1, var_T_ADVANCE, conn_T_ADVANCE);
        readData(2, var_T_SET, conn_T_SET);
        readData(3, var_T_TOTAL, conn_T_TOTAL);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_LAS_MUX_TIMING::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(4, var_TIMING, conn_TIMING);
        break;
      }
      case scmEventCNFID: {
        writeData(4, var_TIMING, conn_TIMING);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_LAS_MUX_TIMING::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_T_LOWER;
      case 1: return &var_T_ADVANCE;
      case 2: return &var_T_SET;
      case 3: return &var_T_TOTAL;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_MUX_TIMING::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_TIMING;
    }
    return nullptr;
  }

  CEventConnection *FORTE_LAS_MUX_TIMING::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_LAS_MUX_TIMING::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_T_LOWER;
      case 1: return &conn_T_ADVANCE;
      case 2: return &conn_T_SET;
      case 3: return &conn_T_TOTAL;
    }
    return nullptr;
  }

  CDataConnection *FORTE_LAS_MUX_TIMING::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_TIMING;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_MUX_TIMING::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_LAS_MUX_TIMING::alg_INIT(void) {

    #line 2 "LAS_MUX_TIMING.fbt"
    var_TIMING.var_T_LOWER = var_T_LOWER;
    #line 3 "LAS_MUX_TIMING.fbt"
    var_TIMING.var_T_ADVANCE = var_T_ADVANCE;
    #line 4 "LAS_MUX_TIMING.fbt"
    var_TIMING.var_T_SET = var_T_SET;
    #line 5 "LAS_MUX_TIMING.fbt"
    var_TIMING.var_T_TOTAL = var_T_TOTAL;
  }

  void FORTE_LAS_MUX_TIMING::alg_REQ(void) {

    #line 9 "LAS_MUX_TIMING.fbt"
    var_TIMING.var_T_LOWER = var_T_LOWER;
    #line 10 "LAS_MUX_TIMING.fbt"
    var_TIMING.var_T_ADVANCE = var_T_ADVANCE;
    #line 11 "LAS_MUX_TIMING.fbt"
    var_TIMING.var_T_SET = var_T_SET;
    #line 12 "LAS_MUX_TIMING.fbt"
    var_TIMING.var_T_TOTAL = var_T_TOTAL;
  }

}