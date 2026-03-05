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

#pragma once

#include "forte/datatypes/forte_struct.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"


namespace forte::ASGEVO_PACKAGE::FB::TEMPLATE {
  class CIEC_OUTPUTS_IEC61131_TMPL final : public CIEC_STRUCT {
    DECLARE_FIRMWARE_DATATYPE(OUTPUTS_IEC61131_TMPL)

    public:
      CIEC_OUTPUTS_IEC61131_TMPL();

      CIEC_OUTPUTS_IEC61131_TMPL(const CIEC_BOOL &paOUTVAR1, const CIEC_UINT &paOUTVAR2);

      CIEC_BOOL var_OUTVAR1;
      CIEC_UINT var_OUTVAR2;

      size_t getStructSize() const override {
        return 2;
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

