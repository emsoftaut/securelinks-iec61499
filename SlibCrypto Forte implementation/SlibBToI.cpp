/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibBToI
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/
#include <stdio.h>
#include "SlibBToI.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibBToI_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibBToI, g_nStringIdSlibBToI)

const CStringDictionary::TStringId FORTE_SlibBToI::scm_anDataInputNames[] = {g_nStringIdin};

const CStringDictionary::TStringId FORTE_SlibBToI::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 1024, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_SlibBToI::scm_anDataOutputNames[] = {g_nStringIdout};

const CStringDictionary::TStringId FORTE_SlibBToI::scm_anDataOutputTypeIds[] = {g_nStringIdINT};

const TForteInt16 FORTE_SlibBToI::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_SlibBToI::scm_anEIWith[] = {0, 255};
const CStringDictionary::TStringId FORTE_SlibBToI::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_SlibBToI::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_SlibBToI::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_SlibBToI::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibBToI::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  1,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_SlibBToI::setInitialValues(){
  in_Array().fromString("0");
}


void FORTE_SlibBToI::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventREQID:
      uint16_t nOut = 0;

      ((uint8_t*)&nOut)[1] = in()[0];
      ((uint8_t*)&nOut)[0] = in()[1];

      out() = nOut;

      sendOutputEvent(scm_nEventCNFID);
      break;
  }
}



