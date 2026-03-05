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

#pragma once

#include "forte/datatypes/forte_struct.h"

#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"


namespace forte::ASGEVO_PACKAGE::FB::LAS {
  class CIEC_LAS_INPUTS final : public CIEC_STRUCT {
    DECLARE_FIRMWARE_DATATYPE(LAS_INPUTS)

    public:
      CIEC_LAS_INPUTS();

      CIEC_LAS_INPUTS(const CIEC_UINT &paPRESSURE_LEG_LEFT, const CIEC_UINT &paPRESSURE_LEG_RIGHT, const CIEC_UINT &paRAM_STROKE);

      CIEC_UINT var_PRESSURE_LEG_LEFT;
      CIEC_UINT var_PRESSURE_LEG_RIGHT;
      CIEC_UINT var_RAM_STROKE;

      size_t getStructSize() const override {
        return 3;
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

