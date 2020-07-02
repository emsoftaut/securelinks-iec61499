/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibsSplit
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "SlibsSplit.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibsSplit_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibsSplit, g_nStringIdSlibsSplit)

const CStringDictionary::TStringId FORTE_SlibsSplit::scm_anDataInputNames[] = {g_nStringIdArrayOriginal};

const CStringDictionary::TStringId FORTE_SlibsSplit::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 64, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_SlibsSplit::scm_anDataOutputNames[] = {g_nStringIdArray1, g_nStringIdArray2};

const CStringDictionary::TStringId FORTE_SlibsSplit::scm_anDataOutputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const TForteInt16 FORTE_SlibsSplit::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_SlibsSplit::scm_anEIWith[] = {0, 255};
const CStringDictionary::TStringId FORTE_SlibsSplit::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_SlibsSplit::scm_anEOWith[] = {0, 1, 255};
const TForteInt16 FORTE_SlibsSplit::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_SlibsSplit::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibsSplit::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  1,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_SlibsSplit::setInitialValues(){
  ArrayOriginal_Array().fromString("0");
  Array1_Array().fromString("0");
  Array2_Array().fromString("0");
}


#define ORIGINAL_ARRAY_SIZE 64
void FORTE_SlibsSplit::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventREQID:
    	for(int i = 0; i < ORIGINAL_ARRAY_SIZE; i++) {
    		if(i < 32)
    			Array1()[i] = ArrayOriginal()[i];
    		else
    			Array2()[i - 32] = ArrayOriginal()[i];
    	}

    	sendOutputEvent(scm_nEventCNFID);
    	break;
  }
}





