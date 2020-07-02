/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibMux
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "SlibMux.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibMux_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibMux, g_nStringIdSlibMux)

const CStringDictionary::TStringId FORTE_SlibMux::scm_anDataInputNames[] = {g_nStringIdpubkeys, g_nStringIdsignatures};

const CStringDictionary::TStringId FORTE_SlibMux::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 64, g_nStringIdBYTE, g_nStringIdARRAY, 64, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_SlibMux::scm_anDataOutputNames[] = {g_nStringIdArrayOut};

const CStringDictionary::TStringId FORTE_SlibMux::scm_anDataOutputTypeIds[] = {g_nStringIdARRAY, 64, g_nStringIdBYTE};

const TForteInt16 FORTE_SlibMux::scm_anEIWithIndexes[] = {0, 2};
const TDataIOID FORTE_SlibMux::scm_anEIWith[] = {0, 255, 1, 255};
const CStringDictionary::TStringId FORTE_SlibMux::scm_anEventInputNames[] = {g_nStringIdE1, g_nStringIdE2};

const TDataIOID FORTE_SlibMux::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_SlibMux::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_SlibMux::scm_anEventOutputNames[] = {g_nStringIdEO};

const SFBInterfaceSpec FORTE_SlibMux::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_SlibMux::setInitialValues(){
  pubkeys_Array().fromString("0");
  signatures_Array().fromString("0");
  ArrayOut_Array().fromString("0");
}

#define ARRAY_SIGNATURE_SIZE 64

void FORTE_SlibMux::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventE1ID:
    	for(int i = 0; i < ARRAY_SIGNATURE_SIZE; i++)
			ArrayOut()[i] = pubkeys()[i];
    	sendOutputEvent(scm_nEventEOID);
    	break;
    case scm_nEventE2ID:
    	for(int i = 0; i < ARRAY_SIGNATURE_SIZE; i++)
			ArrayOut()[i] = signatures()[i];
    	sendOutputEvent(scm_nEventEOID);

      break;
  }
}



