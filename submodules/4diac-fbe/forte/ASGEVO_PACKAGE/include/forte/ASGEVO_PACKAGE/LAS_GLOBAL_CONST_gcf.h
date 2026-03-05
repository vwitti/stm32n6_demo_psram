/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: LAS_GLOBAL_CONST
 *** Description: Global constants
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#pragma once

#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"


namespace forte::ASGEVO_PACKAGE {
  class FORTE_LAS_GLOBAL_CONST final {
      DECLARE_FIRMWARE_GLOBAL_CONST()
    public:
      static const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_gLAS_TC_OK;
      static const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_gLAS_TC_NOGAP_OK;
      static const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_gLAS_TO_SHORT_ERR;
      static const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_gLAS_SC_OK;
      static const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_gLAS_RESI_LOW_TIME_OK;
      static const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_gLAS_RESI_2_RETRIES_OK;
      static const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_gLAS_SC_DA_RAM_DEFEKT_OK;
      static const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_gLAS_LAS_L2D_TC_OK;
      static const forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER var_gLAS_SC_L2D_SC_OK;

      FORTE_LAS_GLOBAL_CONST() = delete;
  };
}

