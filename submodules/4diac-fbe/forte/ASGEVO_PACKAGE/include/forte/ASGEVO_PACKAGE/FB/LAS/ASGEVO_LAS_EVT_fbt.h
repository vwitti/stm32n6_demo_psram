/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_LAS_EVT
 *** Description: Composite FB wrapping other FBs
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#pragma once

#include "forte/cfb.h"
#include "forte/typelib.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_INPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_OUTPUTS_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_PARAMETER_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/LAS_TIMING_dtp.h"
#include "forte/datatypes/forte_any_variant.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"
#include "forte/ASGEVO_PACKAGE/FB/LAS/ASGEVO_LAS_CYC_fbt.h"
#include "forte/ASGEVO_PACKAGE/MUX/LAS_MUX_INPUTS_fbt.h"
#include "forte/ASGEVO_PACKAGE/SFB_ASGEVO_GET_LEG_PRESSURE_fbt.h"
#include "forte/ASGEVO_PACKAGE/SFB_ASGEVO_GET_RAM_STROKE_fbt.h"
#include "forte/iec61499/events/E_CYCLE_fbt.h"
#include "forte/iec61499/events/GEN_E_MERGE_fbt.h"

namespace forte::ASGEVO_PACKAGE::FB::LAS {
  class FORTE_ASGEVO_LAS_EVT final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_ASGEVO_LAS_EVT)

    private:
      static const TEventID scmEventCNFID = 0;
      static const TEventID scmEventBUSYID = 1;
      static const TEventID scmEventDONEID = 2;
      static const TEventID scmEventREQID = 0;
      static const TEventID scmEventABORTID = 1;
      static const TEventID scmEventIDLEID = 2;
      static const TEventID scmEventFREEZEID = 3;

      CInternalFB<forte::iec61499::events::FORTE_E_CYCLE> fb_E_CYCLE;
      CInternalFB<forte::ASGEVO_PACKAGE::FB::LAS::FORTE_ASGEVO_LAS_CYC> fb_ASGEVO_LAS_CYC;
      CInternalFB<forte::ASGEVO_PACKAGE::FORTE_SFB_ASGEVO_GET_LEG_PRESSURE> fb_SFB_ASGEVO_GET_LEG_PRESSURE;
      CInternalFB<forte::ASGEVO_PACKAGE::FORTE_SFB_ASGEVO_GET_RAM_STROKE> fb_SFB_ASGEVO_GET_RAM_STROKE;
      CInternalFB<forte::iec61499::events::GEN_E_MERGE> fb_E_MERGE_2;
      CInternalFB<forte::ASGEVO_PACKAGE::MUX::FORTE_LAS_MUX_INPUTS> fb_LAS_MUX_INPUTS;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;
      void setFBNetworkInitialValues() override;

    public:
      FORTE_ASGEVO_LAS_EVT(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_CNF;
      CEventConnection conn_BUSY;
      CEventConnection conn_DONE;

      CDataConnection *conn_INPUT;
      CDataConnection *conn_PARAM;
      CDataConnection *conn_TARGET;
      CDataConnection *conn_CYCLE;

      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_OUTPUTS> conn_OUTPUT;
      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_TIMING> conn_TIMING;
      COutDataConnection<CIEC_UINT> conn_ERRCODE;

      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_INPUTS> conn_if2in_INPUT;
      COutDataConnection<forte::ASGEVO_PACKAGE::FB::LAS::CIEC_LAS_PARAMETER> conn_if2in_PARAM;
      COutDataConnection<CIEC_UINT> conn_if2in_TARGET;
      COutDataConnection<CIEC_TIME> conn_if2in_CYCLE;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

