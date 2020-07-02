/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: ByteToByte
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "ByteToByte.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ByteToByte_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_ByteToByte, g_nStringIdByteToByte)

const CStringDictionary::TStringId FORTE_ByteToByte::scm_anDataInputNames[] = {g_nStringIdIn};

const CStringDictionary::TStringId FORTE_ByteToByte::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_ByteToByte::scm_anDataOutputNames[] = {g_nStringIdOut};

const CStringDictionary::TStringId FORTE_ByteToByte::scm_anDataOutputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE};

const TForteInt16 FORTE_ByteToByte::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_ByteToByte::scm_anEIWith[] = {0, 255};
const CStringDictionary::TStringId FORTE_ByteToByte::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_ByteToByte::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_ByteToByte::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_ByteToByte::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_ByteToByte::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  1,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_ByteToByte::setInitialValues(){
  In_Array().fromString("0");
  Out_Array().fromString("0");
}


void FORTE_ByteToByte::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventREQID:
      for(int i = 0; i < 32; i++)
    	  Out()[i] = In()[i];
      sendOutputEvent(scm_nEventCNFID);

      break;
  }
}



