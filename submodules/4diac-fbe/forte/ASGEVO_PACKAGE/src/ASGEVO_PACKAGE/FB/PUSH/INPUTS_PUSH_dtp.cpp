/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: INPUTS_PUSH
 *** Description: A Template for a Data Type
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/PUSH/INPUTS_PUSH_dtp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::PUSH {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:4rvr0WWs9k5lzp-LapQgtVPmYz3rFR1sv5vjnOeqFMr-M3uBDUWiiP23XrCEhFJADe9K921ViAbsW0f6WoorvQ=="sv;
  }

  DEFINE_FIRMWARE_DATATYPE(INPUTS_PUSH, "ASGEVO_PACKAGE::FB::PUSH::INPUTS_PUSH"_STRID, TypeHash);

  const StringId CIEC_INPUTS_PUSH::scmElementNames[] = {"VAR1"_STRID};

  CIEC_INPUTS_PUSH::CIEC_INPUTS_PUSH() :
      CIEC_STRUCT(),
      var_VAR1(0_UINT) {
  }

  CIEC_INPUTS_PUSH::CIEC_INPUTS_PUSH(const CIEC_UINT &paVAR1) :
      CIEC_STRUCT(),
      var_VAR1(paVAR1) {
  }

  StringId CIEC_INPUTS_PUSH::getStructTypeNameID() const {
    return "ASGEVO_PACKAGE::FB::PUSH::INPUTS_PUSH"_STRID;
  }

  void CIEC_INPUTS_PUSH::setValue(const CIEC_ANY &paValue) {
    if (paValue.getDataTypeID() == e_STRUCT) {
      auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
      if ("ASGEVO_PACKAGE::FB::PUSH::INPUTS_PUSH"_STRID == otherStruct.getStructTypeNameID()) {
        operator=(static_cast<const CIEC_INPUTS_PUSH &>(paValue));
      }
    }
  }

  CIEC_ANY *CIEC_INPUTS_PUSH::getMember(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_VAR1;
    }
    return nullptr;
  }

  const CIEC_ANY *CIEC_INPUTS_PUSH::getMember(const size_t paIndex) const {
    switch(paIndex) {
      case 0: return &var_VAR1;
    }
    return nullptr;
  }

}