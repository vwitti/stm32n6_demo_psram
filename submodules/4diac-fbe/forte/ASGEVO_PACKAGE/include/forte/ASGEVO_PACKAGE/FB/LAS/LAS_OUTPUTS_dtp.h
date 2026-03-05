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

#pragma once

#include "forte/datatypes/forte_struct.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"


namespace forte::ASGEVO_PACKAGE::FB::LAS {
  class CIEC_LAS_OUTPUTS final : public CIEC_STRUCT {
    DECLARE_FIRMWARE_DATATYPE(LAS_OUTPUTS)

    public:
      CIEC_LAS_OUTPUTS();

      CIEC_LAS_OUTPUTS(const CIEC_BOOL &paPREWARN, const CIEC_BOOL &paLOWER, const CIEC_BOOL &paSET, const CIEC_BOOL &paPULL, const CIEC_BOOL &paPUSH, const CIEC_BOOL &paBL_EXT, const CIEC_BOOL &paBL_RET, const CIEC_BOOL &paSTAB_EXT, const CIEC_BOOL &paSTAB_RET, const CIEC_BOOL &paCA);

      CIEC_BOOL var_PREWARN;
      CIEC_BOOL var_LOWER;
      CIEC_BOOL var_SET;
      CIEC_BOOL var_PULL;
      CIEC_BOOL var_PUSH;
      CIEC_BOOL var_BL_EXT;
      CIEC_BOOL var_BL_RET;
      CIEC_BOOL var_STAB_EXT;
      CIEC_BOOL var_STAB_RET;
      CIEC_BOOL var_CA;

      size_t getStructSize() const override {
        return 10;
      }

      const StringId* elementNames() const override {
        return scmElementNames;
      }

      StringId getStructTypeNameID() const override;

      void setValue(const CIEC_ANY &paValue) override;

      CIEC_ANY *getMember(size_t) override;
      const CIEC_ANY *getMember(size_t) const override;

    private:
      static const StringId scmElementNames[];

  };
}

