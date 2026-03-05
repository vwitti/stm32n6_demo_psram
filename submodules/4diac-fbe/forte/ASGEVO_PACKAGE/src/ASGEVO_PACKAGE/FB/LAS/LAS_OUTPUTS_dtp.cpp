/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_OUTPUTS
 *** Description: A Template for a Data Type
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:aidArrv5PSJOC5_LIJ3NRLB5IOqyHQ27ZG3SRKt-0ku6XMt_LRN16BQlm0h1QTYruxHWofNf86gXQ7CUC6UqAA=="sv;
  }

  DEFINE_FIRMWARE_DATATYPE(LAS_OUTPUTS, "ASGEVO_PACKAGE::FB::LAS::LAS_OUTPUTS"_STRID, TypeHash);

  const StringId CIEC_LAS_OUTPUTS::scmElementNames[] = {"PREWARN"_STRID, "LOWER"_STRID, "SET"_STRID, "PULL"_STRID, "PUSH"_STRID, "BL_EXT"_STRID, "BL_RET"_STRID, "STAB_EXT"_STRID, "STAB_RET"_STRID, "CA"_STRID};

  CIEC_LAS_OUTPUTS::CIEC_LAS_OUTPUTS() :
      CIEC_STRUCT(),
      var_PREWARN(0_BOOL),
      var_LOWER(0_BOOL),
      var_SET(0_BOOL),
      var_PULL(0_BOOL),
      var_PUSH(0_BOOL),
      var_BL_EXT(0_BOOL),
      var_BL_RET(0_BOOL),
      var_STAB_EXT(0_BOOL),
      var_STAB_RET(0_BOOL),
      var_CA(0_BOOL) {
  }

  CIEC_LAS_OUTPUTS::CIEC_LAS_OUTPUTS(const CIEC_BOOL &paPREWARN, const CIEC_BOOL &paLOWER, const CIEC_BOOL &paSET, const CIEC_BOOL &paPULL, const CIEC_BOOL &paPUSH, const CIEC_BOOL &paBL_EXT, const CIEC_BOOL &paBL_RET, const CIEC_BOOL &paSTAB_EXT, const CIEC_BOOL &paSTAB_RET, const CIEC_BOOL &paCA) :
      CIEC_STRUCT(),
      var_PREWARN(paPREWARN),
      var_LOWER(paLOWER),
      var_SET(paSET),
      var_PULL(paPULL),
      var_PUSH(paPUSH),
      var_BL_EXT(paBL_EXT),
      var_BL_RET(paBL_RET),
      var_STAB_EXT(paSTAB_EXT),
      var_STAB_RET(paSTAB_RET),
      var_CA(paCA) {
  }

  StringId CIEC_LAS_OUTPUTS::getStructTypeNameID() const {
    return "ASGEVO_PACKAGE::FB::LAS::LAS_OUTPUTS"_STRID;
  }

  void CIEC_LAS_OUTPUTS::setValue(const CIEC_ANY &paValue) {
    if (paValue.getDataTypeID() == e_STRUCT) {
      auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
      if ("ASGEVO_PACKAGE::FB::LAS::LAS_OUTPUTS"_STRID == otherStruct.getStructTypeNameID()) {
        operator=(static_cast<const CIEC_LAS_OUTPUTS &>(paValue));
      }
    }
  }

  CIEC_ANY *CIEC_LAS_OUTPUTS::getMember(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_PREWARN;
      case 1: return &var_LOWER;
      case 2: return &var_SET;
      case 3: return &var_PULL;
      case 4: return &var_PUSH;
      case 5: return &var_BL_EXT;
      case 6: return &var_BL_RET;
      case 7: return &var_STAB_EXT;
      case 8: return &var_STAB_RET;
      case 9: return &var_CA;
    }
    return nullptr;
  }

  const CIEC_ANY *CIEC_LAS_OUTPUTS::getMember(const size_t paIndex) const {
    switch(paIndex) {
      case 0: return &var_PREWARN;
      case 1: return &var_LOWER;
      case 2: return &var_SET;
      case 3: return &var_PULL;
      case 4: return &var_PUSH;
      case 5: return &var_BL_EXT;
      case 6: return &var_BL_RET;
      case 7: return &var_STAB_EXT;
      case 8: return &var_STAB_RET;
      case 9: return &var_CA;
    }
    return nullptr;
  }

}