/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_INPUTS
 *** Description: A Template for a Data Type
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_INPUTS_dtp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:uwArzaJkUH5XUnL1_q5kGzolqCZG3nbWPBiBC6stpjWXcLyQCsCJkGsmNWMLGJTM8aVrF7IyLe0Dnv0q7_w-xw=="sv;
  }

  DEFINE_FIRMWARE_DATATYPE(LAS_INPUTS, "ASGEVO_PACKAGE::FB::LAS::LAS_INPUTS"_STRID, TypeHash);

  const StringId CIEC_LAS_INPUTS::scmElementNames[] = {"PRESSURE_LEG_LEFT"_STRID, "PRESSURE_LEG_RIGHT"_STRID, "RAM_STROKE"_STRID};

  CIEC_LAS_INPUTS::CIEC_LAS_INPUTS() :
      CIEC_STRUCT(),
      var_PRESSURE_LEG_LEFT(0_UINT),
      var_PRESSURE_LEG_RIGHT(0_UINT),
      var_RAM_STROKE(0_UINT) {
  }

  CIEC_LAS_INPUTS::CIEC_LAS_INPUTS(const CIEC_UINT &paPRESSURE_LEG_LEFT, const CIEC_UINT &paPRESSURE_LEG_RIGHT, const CIEC_UINT &paRAM_STROKE) :
      CIEC_STRUCT(),
      var_PRESSURE_LEG_LEFT(paPRESSURE_LEG_LEFT),
      var_PRESSURE_LEG_RIGHT(paPRESSURE_LEG_RIGHT),
      var_RAM_STROKE(paRAM_STROKE) {
  }

  StringId CIEC_LAS_INPUTS::getStructTypeNameID() const {
    return "ASGEVO_PACKAGE::FB::LAS::LAS_INPUTS"_STRID;
  }

  void CIEC_LAS_INPUTS::setValue(const CIEC_ANY &paValue) {
    if (paValue.getDataTypeID() == e_STRUCT) {
      auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
      if ("ASGEVO_PACKAGE::FB::LAS::LAS_INPUTS"_STRID == otherStruct.getStructTypeNameID()) {
        operator=(static_cast<const CIEC_LAS_INPUTS &>(paValue));
      }
    }
  }

  CIEC_ANY *CIEC_LAS_INPUTS::getMember(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_PRESSURE_LEG_LEFT;
      case 1: return &var_PRESSURE_LEG_RIGHT;
      case 2: return &var_RAM_STROKE;
    }
    return nullptr;
  }

  const CIEC_ANY *CIEC_LAS_INPUTS::getMember(const size_t paIndex) const {
    switch(paIndex) {
      case 0: return &var_PRESSURE_LEG_LEFT;
      case 1: return &var_PRESSURE_LEG_RIGHT;
      case 2: return &var_RAM_STROKE;
    }
    return nullptr;
  }

}