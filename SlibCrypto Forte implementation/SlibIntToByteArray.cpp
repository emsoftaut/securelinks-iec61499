/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibIntToByteArray
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "SlibIntToByteArray.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibIntToByteArray_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibIntToByteArray, g_nStringIdSlibIntToByteArray)

const CStringDictionary::TStringId FORTE_SlibIntToByteArray::scm_anDataInputNames[] = {g_nStringIdin};

const CStringDictionary::TStringId FORTE_SlibIntToByteArray::scm_anDataInputTypeIds[] = {g_nStringIdINT};

const CStringDictionary::TStringId FORTE_SlibIntToByteArray::scm_anDataOutputNames[] = {g_nStringIdout};

const CStringDictionary::TStringId FORTE_SlibIntToByteArray::scm_anDataOutputTypeIds[] = {g_nStringIdARRAY, 1024, g_nStringIdBYTE};

const TForteInt16 FORTE_SlibIntToByteArray::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_SlibIntToByteArray::scm_anEIWith[] = {0, 255};
const CStringDictionary::TStringId FORTE_SlibIntToByteArray::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_SlibIntToByteArray::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_SlibIntToByteArray::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_SlibIntToByteArray::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibIntToByteArray::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  1,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_SlibIntToByteArray::setInitialValues(){
  out_Array().fromString("0");
}


void FORTE_SlibIntToByteArray::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventREQID:
    	uint16_t i = in();
    	out()[0] = ((uint8_t*)&i)[1];
    	out()[1] = ((uint8_t*)&i)[0];

      sendOutputEvent(scm_nEventCNFID);
      break;
  }
}



