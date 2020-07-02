/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: OpensslRand
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "OpensslRand.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "OpensslRand_gen.cpp"
#endif

#include <openssl/rand.h>

DEFINE_FIRMWARE_FB(FORTE_OpensslRand, g_nStringIdOpensslRand)

const CStringDictionary::TStringId FORTE_OpensslRand::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdSeed};

const CStringDictionary::TStringId FORTE_OpensslRand::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdINT};

const CStringDictionary::TStringId FORTE_OpensslRand::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdRand};

const CStringDictionary::TStringId FORTE_OpensslRand::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdUDINT};

const TForteInt16 FORTE_OpensslRand::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_OpensslRand::scm_anEIWith[] = {0, 1, 255, 0, 255};
const CStringDictionary::TStringId FORTE_OpensslRand::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_OpensslRand::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_OpensslRand::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_OpensslRand::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_OpensslRand::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_OpensslRand::executeEvent(int pa_nEIID){
  static int initialized = 0;
  switch(pa_nEIID){
    case scm_nEventINITID:

    	if(RAND_poll() == 1 && RAND_status() == 1) {

    		STATUS() = "Initialized";
    		initialized = 1;
    		sendOutputEvent(scm_nEventINITOID);
    	}
    	else
    		STATUS() = "Initialization Error";
      break;
    case scm_nEventREQID:
    	if(initialized == 1) {
    		uint8_t buf[4] = {0};
    		if(RAND_bytes(buf, 4) == 1) {
    			Rand() = *((uint32_t*)buf);
    			QO() = 1;
    			STATUS() = "Ok";
    			sendOutputEvent(scm_nEventCNFID);
    		}
    		else
    			STATUS() = "Generation error!!!";
    	}
    	else
    		STATUS() = "Initialization Error";
      break;
  }
}



