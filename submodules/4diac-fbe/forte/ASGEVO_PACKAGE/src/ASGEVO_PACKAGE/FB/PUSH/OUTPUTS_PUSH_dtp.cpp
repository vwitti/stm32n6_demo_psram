/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: OUTPUTS_PUSH
 *** Description: A Template for a Data Type
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#include "forte/ASGEVO_PACKAGE/FB/PUSH/OUTPUTS_PUSH_dtp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::ASGEVO_PACKAGE::FB::PUSH {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:zMH5vexOPb-DcGC0OtFiRQt0MKhMUBydaMNrnq1ta12-t9jcJSXLkt7YBa19IUlspC-3fLuXCwZCqUoD8xP9nA=="sv;
  }

  DEFINE_FIRMWARE_DATATYPE(OUTPUTS_PUSH, "ASGEVO_PACKAGE::FB::PUSH::OUTPUTS_PUSH"_STRID, TypeHash);

  const StringId CIEC_OUTPUTS_PUSH::scmElementNames[] = {"PUSH"_STRID};

  CIEC_OUTPUTS_PUSH::CIEC_OUTPUTS_PUSH() :
      CIEC_STRUCT(),
      var_PUSH(0_BOOL) {
  }

  CIEC_OUTPUTS_PUSH::CIEC_OUTPUTS_PUSH(const CIEC_BOOL &paPUSH) :
      CIEC_STRUCT(),
      var_PUSH(paPUSH) {
  }

  StringId CIEC_OUTPUTS_PUSH::getStructTypeNameID() const {
    return "ASGEVO_PACKAGE::FB::PUSH::OUTPUTS_PUSH"_STRID;
  }

  void CIEC_OUTPUTS_PUSH::setValue(const CIEC_ANY &paValue) {
    if (paValue.getDataTypeID() == e_STRUCT) {
      auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
      if ("ASGEVO_PACKAGE::FB::PUSH::OUTPUTS_PUSH"_STRID == otherStruct.getStructTypeNameID()) {
        operator=(static_cast<const CIEC_OUTPUTS_PUSH &>(paValue));
      }
    }
  }

  CIEC_ANY *CIEC_OUTPUTS_PUSH::getMember(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_PUSH;
    }
    return nullptr;
  }

  const CIEC_ANY *CIEC_OUTPUTS_PUSH::getMember(const size_t paIndex) const {
    switch(paIndex) {
      case 0: return &var_PUSH;
    }
    return nullptr;
  }

}