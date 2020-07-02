/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibSlipt16_1024
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "SlibSlipt16_1024.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibSlipt16_1024_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibSlipt16_1024, g_nStringIdSlibSlipt16_1024)

const CStringDictionary::TStringId FORTE_SlibSlipt16_1024::scm_anDataInputNames[] = {g_nStringIdAIn};

const CStringDictionary::TStringId FORTE_SlibSlipt16_1024::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 1040, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_SlibSlipt16_1024::scm_anDataOutputNames[] = {g_nStringIdA16, g_nStringIdA1024};

const CStringDictionary::TStringId FORTE_SlibSlipt16_1024::scm_anDataOutputTypeIds[] = {g_nStringIdARRAY, 16, g_nStringIdBYTE, g_nStringIdARRAY, 1024, g_nStringIdBYTE};

const TForteInt16 FORTE_SlibSlipt16_1024::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_SlibSlipt16_1024::scm_anEIWith[] = {0, 255};
const CStringDictionary::TStringId FORTE_SlibSlipt16_1024::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_SlibSlipt16_1024::scm_anEOWith[] = {1, 0, 255};
const TForteInt16 FORTE_SlibSlipt16_1024::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_SlibSlipt16_1024::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibSlipt16_1024::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  1,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_SlibSlipt16_1024::setInitialValues(){
  AIn_Array().fromString("0");
  A16_Array().fromString("0");
  A1024_Array().fromString("0");
}

#define FINAL_ARRAY_SIZE 1040
#define SMALL_ARRAY_SIZE 16

void FORTE_SlibSlipt16_1024::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventREQID:

    	for(int i = 0; i < FINAL_ARRAY_SIZE; i++) {
    		if(i < SMALL_ARRAY_SIZE)
    			 A16()[i] = AIn()[i];
    		else
    			 A1024()[i - SMALL_ARRAY_SIZE] = AIn()[i];
    	}
    	sendOutputEvent(scm_nEventCNFID);
    	break;
  }
}



