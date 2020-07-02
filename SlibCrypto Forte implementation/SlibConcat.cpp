/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibConcat
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0:
 *************************************************************************/

#include "SlibConcat.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibConcat_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibConcat, g_nStringIdSlibConcat)

const CStringDictionary::TStringId FORTE_SlibConcat::scm_anDataInputNames[] = {g_nStringIdArray1, g_nStringIdArray2};

const CStringDictionary::TStringId FORTE_SlibConcat::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_SlibConcat::scm_anDataOutputNames[] = {g_nStringIdFinalArray};

const CStringDictionary::TStringId FORTE_SlibConcat::scm_anDataOutputTypeIds[] = {g_nStringIdARRAY, 64, g_nStringIdBYTE};

const TForteInt16 FORTE_SlibConcat::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_SlibConcat::scm_anEIWith[] = {0, 1, 255};
const CStringDictionary::TStringId FORTE_SlibConcat::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_SlibConcat::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_SlibConcat::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_SlibConcat::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibConcat::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_SlibConcat::setInitialValues(){
  Array1_Array().fromString("0");
  Array2_Array().fromString("0");
  FinalArray_Array().fromString("0");
}

#define FINAL_ARRAY_SIZE 64

void FORTE_SlibConcat::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventREQID:
    	for(int i = 0; i < FINAL_ARRAY_SIZE; i++) {
    		if(i < 32)
    			FinalArray()[i] = Array1()[i];
    		else
    			FinalArray()[i] = Array2()[i - 32];
    	}
      sendOutputEvent(scm_nEventCNFID);
      break;
  }
}



