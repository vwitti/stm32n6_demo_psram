/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!
 ***
 *** Name: ASGEVO_IEC61131_TMPL_EVT
 *** Description: Composite FB wrapping other FBs
 *** Version:
 ***     1.0: 2026-02-24/volker -  -
 *************************************************************************/

#pragma once

#include "forte/cfb.h"
#include "forte/typelib.h"
#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/INPUTS_IEC61131_TMPL_dtp.h"
#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/OUTPUTS_IEC61131_TMPL_dtp.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"
#include "forte/ASGEVO_PACKAGE/FB/TEMPLATE/ASGEVO_IEC61131_TMPL_CYC_fbt.h"
#include "forte/iec61499/events/E_CYCLE_fbt.h"

namespace forte::ASGEVO_PACKAGE::FB::TEMPLATE {
  class FORTE_ASGEVO_IEC61131_TMPL_EVT final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_ASGEVO_IEC61131_TMPL_EVT)

    private:
      static const TEventID scmEventCNFID = 0;
      static const TEventID scmEventBUSYID = 1;
      static const TEventID scmEventDONEID = 2;
      static const TEventID scmEventREQID = 0;
      static const TEventID scmEventABORTID = 1;
      static const TEventID scmEventIDLEID = 2;
      static const TEventID scmEventFREEZEID = 3;

      CInternalFB<forte::iec61499::events::FORTE_E_CYCLE> fb_E_CYCLE;
      CInternalFB<forte::ASGEVO_PACKAGE::FB::TEMPLATE::FORTE_ASGEVO_IEC61131_TMPL_CYC> fb_ASGEVO_IEC61131_TMPL_CYC;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_ASGEVO_IEC61131_TMPL_EVT(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_CNF;
      CEventConnection conn_BUSY;
      CEventConnection conn_DONE;

      CDataConnection *conn_INPUT;
      CDataConnection *conn_CYCLE;

      COutDataConnection<forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_OUTPUTS_IEC61131_TMPL> conn_OUTPUT;
      COutDataConnection<CIEC_UINT> conn_ERRCODE;

      COutDataConnection<forte::ASGEVO_PACKAGE::FB::TEMPLATE::CIEC_INPUTS_IEC61131_TMPL> conn_if2in_INPUT;
      COutDataConnection<CIEC_TIME> conn_if2in_CYCLE;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

