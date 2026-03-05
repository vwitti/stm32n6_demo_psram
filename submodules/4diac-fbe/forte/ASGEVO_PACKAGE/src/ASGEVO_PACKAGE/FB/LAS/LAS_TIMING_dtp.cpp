/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_TIMING
 *** Description: A Template for a Data Type
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_TIMING_dtp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:wx6g1_G5WPSBoure1L-ph_K02fXyOWVRl9lmiBaNAT2xvwrVupsZQUhz0NWc09UCPihMbVyy5pF3S5xjUVF64Q=="sv;
  }

  DEFINE_FIRMWARE_DATATYPE(LAS_TIMING, "ASGEVO_PACKAGE::FB::LAS::LAS_TIMING"_STRID, TypeHash);

  const StringId CIEC_LAS_TIMING::scmElementNames[] = {"T_LOWER"_STRID, "T_ADVANCE"_STRID, "T_SET"_STRID, "T_TOTAL"_STRID};

  CIEC_LAS_TIMING::CIEC_LAS_TIMING() :
      CIEC_STRUCT(),
      var_T_LOWER(0_TIME),
      var_T_ADVANCE(0_TIME),
      var_T_SET(0_TIME),
      var_T_TOTAL(0_TIME) {
  }

  CIEC_LAS_TIMING::CIEC_LAS_TIMING(const CIEC_TIME &paT_LOWER, const CIEC_TIME &paT_ADVANCE, const CIEC_TIME &paT_SET, const CIEC_TIME &paT_TOTAL) :
      CIEC_STRUCT(),
      var_T_LOWER(paT_LOWER),
      var_T_ADVANCE(paT_ADVANCE),
      var_T_SET(paT_SET),
      var_T_TOTAL(paT_TOTAL) {
  }

  StringId CIEC_LAS_TIMING::getStructTypeNameID() const {
    return "ASGEVO_PACKAGE::FB::LAS::LAS_TIMING"_STRID;
  }

  void CIEC_LAS_TIMING::setValue(const CIEC_ANY &paValue) {
    if (paValue.getDataTypeID() == e_STRUCT) {
      auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
      if ("ASGEVO_PACKAGE::FB::LAS::LAS_TIMING"_STRID == otherStruct.getStructTypeNameID()) {
        operator=(static_cast<const CIEC_LAS_TIMING &>(paValue));
      }
    }
  }

  CIEC_ANY *CIEC_LAS_TIMING::getMember(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_T_LOWER;
      case 1: return &var_T_ADVANCE;
      case 2: return &var_T_SET;
      case 3: return &var_T_TOTAL;
    }
    return nullptr;
  }

  const CIEC_ANY *CIEC_LAS_TIMING::getMember(const size_t paIndex) const {
    switch(paIndex) {
      case 0: return &var_T_LOWER;
      case 1: return &var_T_ADVANCE;
      case 2: return &var_T_SET;
      case 3: return &var_T_TOTAL;
    }
    return nullptr;
  }

}