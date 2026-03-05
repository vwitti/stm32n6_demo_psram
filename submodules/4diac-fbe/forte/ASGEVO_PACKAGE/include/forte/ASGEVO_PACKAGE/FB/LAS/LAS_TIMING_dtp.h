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

#pragma once

#include "forte/datatypes/forte_struct.h"

#include "forte/datatypes/forte_time.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"


namespace forte::ASGEVO_PACKAGE::FB::LAS {
  class CIEC_LAS_TIMING final : public CIEC_STRUCT {
    DECLARE_FIRMWARE_DATATYPE(LAS_TIMING)

    public:
      CIEC_LAS_TIMING();

      CIEC_LAS_TIMING(const CIEC_TIME &paT_LOWER, const CIEC_TIME &paT_ADVANCE, const CIEC_TIME &paT_SET, const CIEC_TIME &paT_TOTAL);

      CIEC_TIME var_T_LOWER;
      CIEC_TIME var_T_ADVANCE;
      CIEC_TIME var_T_SET;
      CIEC_TIME var_T_TOTAL;

      size_t getStructSize() const override {
        return 4;
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

