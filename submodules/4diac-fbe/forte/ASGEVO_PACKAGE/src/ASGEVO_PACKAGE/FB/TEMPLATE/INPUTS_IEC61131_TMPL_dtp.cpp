/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: INPUTS_IEC61131_TMPL
 *** Description: A Template for a Data Type
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/INPUTS_IEC61131_TMPL_dtp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::TEMPLATE {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:OaBg_zBMgdm3MaXJ5qCvXGOEPoFLxIe6B7jFWLOelaAaCu7QM7mHh7rmT0HyPknf8iOf4r-j61IZ_MWFFKFl0g=="sv;
  }

  DEFINE_FIRMWARE_DATATYPE(INPUTS_IEC61131_TMPL, "ASGEVO_PACKAGE::FB::TEMPLATE::INPUTS_IEC61131_TMPL"_STRID, TypeHash);

  const StringId CIEC_INPUTS_IEC61131_TMPL::scmElementNames[] = {"VAR1"_STRID};

  CIEC_INPUTS_IEC61131_TMPL::CIEC_INPUTS_IEC61131_TMPL() :
      CIEC_STRUCT(),
      var_VAR1(0_UINT) {
  }

  CIEC_INPUTS_IEC61131_TMPL::CIEC_INPUTS_IEC61131_TMPL(const CIEC_UINT &paVAR1) :
      CIEC_STRUCT(),
      var_VAR1(paVAR1) {
  }

  StringId CIEC_INPUTS_IEC61131_TMPL::getStructTypeNameID() const {
    return "ASGEVO_PACKAGE::FB::TEMPLATE::INPUTS_IEC61131_TMPL"_STRID;
  }

  void CIEC_INPUTS_IEC61131_TMPL::setValue(const CIEC_ANY &paValue) {
    if (paValue.getDataTypeID() == e_STRUCT) {
      auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
      if ("ASGEVO_PACKAGE::FB::TEMPLATE::INPUTS_IEC61131_TMPL"_STRID == otherStruct.getStructTypeNameID()) {
        operator=(static_cast<const CIEC_INPUTS_IEC61131_TMPL &>(paValue));
      }
    }
  }

  CIEC_ANY *CIEC_INPUTS_IEC61131_TMPL::getMember(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_VAR1;
    }
    return nullptr;
  }

  const CIEC_ANY *CIEC_INPUTS_IEC61131_TMPL::getMember(const size_t paIndex) const {
    switch(paIndex) {
      case 0: return &var_VAR1;
    }
    return nullptr;
  }

}