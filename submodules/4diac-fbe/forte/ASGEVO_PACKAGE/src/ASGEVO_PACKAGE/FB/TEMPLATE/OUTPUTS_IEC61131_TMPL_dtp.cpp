/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: OUTPUTS_IEC61131_TMPL
 *** Description: A Template for a Data Type
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/OUTPUTS_IEC61131_TMPL_dtp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::TEMPLATE {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:917in1sr99_OioBw1octrBM1KIXJxVAox6AxgynI9k5LWPlmn3ybFAWPt_b2LtvE0S-Bxce9tMQPyc742SM5bg=="sv;
  }

  DEFINE_FIRMWARE_DATATYPE(OUTPUTS_IEC61131_TMPL, "ASGEVO_PACKAGE::FB::TEMPLATE::OUTPUTS_IEC61131_TMPL"_STRID, TypeHash);

  const StringId CIEC_OUTPUTS_IEC61131_TMPL::scmElementNames[] = {"OUTVAR1"_STRID, "OUTVAR2"_STRID};

  CIEC_OUTPUTS_IEC61131_TMPL::CIEC_OUTPUTS_IEC61131_TMPL() :
      CIEC_STRUCT(),
      var_OUTVAR1(0_BOOL),
      var_OUTVAR2(0_UINT) {
  }

  CIEC_OUTPUTS_IEC61131_TMPL::CIEC_OUTPUTS_IEC61131_TMPL(const CIEC_BOOL &paOUTVAR1, const CIEC_UINT &paOUTVAR2) :
      CIEC_STRUCT(),
      var_OUTVAR1(paOUTVAR1),
      var_OUTVAR2(paOUTVAR2) {
  }

  StringId CIEC_OUTPUTS_IEC61131_TMPL::getStructTypeNameID() const {
    return "ASGEVO_PACKAGE::FB::TEMPLATE::OUTPUTS_IEC61131_TMPL"_STRID;
  }

  void CIEC_OUTPUTS_IEC61131_TMPL::setValue(const CIEC_ANY &paValue) {
    if (paValue.getDataTypeID() == e_STRUCT) {
      auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
      if ("ASGEVO_PACKAGE::FB::TEMPLATE::OUTPUTS_IEC61131_TMPL"_STRID == otherStruct.getStructTypeNameID()) {
        operator=(static_cast<const CIEC_OUTPUTS_IEC61131_TMPL &>(paValue));
      }
    }
  }

  CIEC_ANY *CIEC_OUTPUTS_IEC61131_TMPL::getMember(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_OUTVAR1;
      case 1: return &var_OUTVAR2;
    }
    return nullptr;
  }

  const CIEC_ANY *CIEC_OUTPUTS_IEC61131_TMPL::getMember(const size_t paIndex) const {
    switch(paIndex) {
      case 0: return &var_OUTVAR1;
      case 1: return &var_OUTVAR2;
    }
    return nullptr;
  }

}