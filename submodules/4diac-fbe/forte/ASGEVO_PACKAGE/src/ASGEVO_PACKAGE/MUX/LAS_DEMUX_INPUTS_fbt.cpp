/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_DEMUX_INPUTS
 *** Description: Simple FB with init event and one algorithm
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/MUX/LAS_DEMUX_INPUTS_fbt.h"

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_INPUTS_dtp.h"
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
    constexpr std::string_view TypeHash ="v1:SHA3-512:EhtUq_jRQppuN91FFp7SYqSYBrjSrgq_siCiZkKvADDuGKvA9N4btt5A4eggjEGLutwvqbIrcV9PY-ZvQxKaOA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"INPUTS"_STRID};
    const auto cDataOutputNames = std::array{"LEG_LEFT"_STRID, "LEG_RIGHT"_STRID, "RAM_STROKE"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_LAS_DEMUX_INPUTS, "ASGEVO_PACKAGE::MUX::LAS_DEMUX_INPUTS"_STRID, TypeHash)

  FORTE_LAS_DEMUX_INPUTS::FORTE_LAS_DEMUX_INPUTS(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_INPUTS(forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS()),
      var_LEG_LEFT(0_UINT),
      var_LEG_RIGHT(0_UINT),
      var_RAM_STROKE(0_UINT),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_INPUTS(nullptr),
      conn_LEG_LEFT(*this, 0, var_LEG_LEFT),
      conn_LEG_RIGHT(*this, 1, var_LEG_RIGHT),
      conn_RAM_STROKE(*this, 2, var_RAM_STROKE) {
  }

  void FORTE_LAS_DEMUX_INPUTS::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_INPUTS = forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS();
    var_LEG_LEFT = 0_UINT;
    var_LEG_RIGHT = 0_UINT;
    var_RAM_STROKE = 0_UINT;
  }

  void FORTE_LAS_DEMUX_INPUTS::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_LAS_DEMUX_INPUTS::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_LAS_DEMUX_INPUTS::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_LAS_DEMUX_INPUTS::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_INPUTS, conn_INPUTS);
        break;
      }
      case scmEventREQID: {
        readData(0, var_INPUTS, conn_INPUTS);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_LAS_DEMUX_INPUTS::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(1, var_LEG_LEFT, conn_LEG_LEFT);
        writeData(2, var_LEG_RIGHT, conn_LEG_RIGHT);
        writeData(3, var_RAM_STROKE, conn_RAM_STROKE);
        break;
      }
      case scmEventCNFID: {
        writeData(1, var_LEG_LEFT, conn_LEG_LEFT);
        writeData(2, var_LEG_RIGHT, conn_LEG_RIGHT);
        writeData(3, var_RAM_STROKE, conn_RAM_STROKE);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_LAS_DEMUX_INPUTS::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_INPUTS;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_DEMUX_INPUTS::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_LEG_LEFT;
      case 1: return &var_LEG_RIGHT;
      case 2: return &var_RAM_STROKE;
    }
    return nullptr;
  }

  CEventConnection *FORTE_LAS_DEMUX_INPUTS::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_LAS_DEMUX_INPUTS::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INPUTS;
    }
    return nullptr;
  }

  CDataConnection *FORTE_LAS_DEMUX_INPUTS::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_LEG_LEFT;
      case 1: return &conn_LEG_RIGHT;
      case 2: return &conn_RAM_STROKE;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_LAS_DEMUX_INPUTS::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_LAS_DEMUX_INPUTS::alg_INIT(void) {

    #line 2 "LAS_DEMUX_INPUTS.fbt"
    var_LEG_LEFT = var_INPUTS.var_PRESSURE_LEG_LEFT;
    #line 3 "LAS_DEMUX_INPUTS.fbt"
    var_LEG_RIGHT = var_INPUTS.var_PRESSURE_LEG_RIGHT;
    #line 4 "LAS_DEMUX_INPUTS.fbt"
    var_RAM_STROKE = var_INPUTS.var_RAM_STROKE;
  }

  void FORTE_LAS_DEMUX_INPUTS::alg_REQ(void) {

    #line 8 "LAS_DEMUX_INPUTS.fbt"
    var_LEG_LEFT = var_INPUTS.var_PRESSURE_LEG_LEFT;
    #line 9 "LAS_DEMUX_INPUTS.fbt"
    var_LEG_RIGHT = var_INPUTS.var_PRESSURE_LEG_RIGHT;
    #line 10 "LAS_DEMUX_INPUTS.fbt"
    var_RAM_STROKE = var_INPUTS.var_RAM_STROKE;
  }

}