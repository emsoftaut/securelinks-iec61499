/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibSToB
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "SlibSToB.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibSToB_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibSToB, g_nStringIdSlibSToB)

const CStringDictionary::TStringId FORTE_SlibSToB::scm_anDataInputNames[] = {g_nStringIdin};

const CStringDictionary::TStringId FORTE_SlibSToB::scm_anDataInputTypeIds[] = {g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_SlibSToB::scm_anDataOutputNames[] = {g_nStringIdout};

const CStringDictionary::TStringId FORTE_SlibSToB::scm_anDataOutputTypeIds[] = {g_nStringIdARRAY, 128, g_nStringIdBYTE};

const TForteInt16 FORTE_SlibSToB::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_SlibSToB::scm_anEIWith[] = {0, 255};
const CStringDictionary::TStringId FORTE_SlibSToB::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_SlibSToB::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_SlibSToB::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_SlibSToB::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibSToB::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  1,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_SlibSToB::setInitialValues(){
  out_Array().fromString("0");
}


void FORTE_SlibSToB::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventREQID:
    	char str[128] = {0};

    	in().toString(str, 128);

    	for(int i = 0; i < 128; i++)
    		out()[i] = str[i];

		sendOutputEvent(scm_nEventCNFID);
		break;
  }
}



