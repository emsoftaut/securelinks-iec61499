/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroSignKeyGen
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "HydroSignKeyGen.h"
#include "hydrogen.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroSignKeyGen_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroSignKeyGen, g_nStringIdHydroSignKeyGen)

const CStringDictionary::TStringId FORTE_HydroSignKeyGen::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdpubkey, g_nStringIdprikey};

const CStringDictionary::TStringId FORTE_HydroSignKeyGen::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 64, g_nStringIdBYTE};

const TForteInt16 FORTE_HydroSignKeyGen::scm_anEIWithIndexes[] = {-1, -1};
const CStringDictionary::TStringId FORTE_HydroSignKeyGen::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroSignKeyGen::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 3, 255};
const TForteInt16 FORTE_HydroSignKeyGen::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroSignKeyGen::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroSignKeyGen::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  0,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  0,  0, 0, 
  4,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroSignKeyGen::setInitialValues(){
  pubkey_Array().fromString("0");
  prikey_Array().fromString("0");
}


void FORTE_HydroSignKeyGen::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
		if (hydro_init() == 0) {
			STATUS() = "libhydrogen initialized";
			QO() = 1;
			sendOutputEvent(scm_nEventINITOID);
		}
		else
			STATUS() = "libhydrogen initialization Error!!!";
		break;
    case scm_nEventREQID:
    	hydro_sign_keypair key_pair = {0};

    	hydro_sign_keygen(&key_pair);

    	for(int i = 0; i < hydro_sign_SECRETKEYBYTES; i++) {
    		if(i < hydro_sign_PUBLICKEYBYTES)
    			pubkey()[i] = key_pair.pk[i];
    		prikey()[i] = key_pair.sk[i];
    	}
    	STATUS() = "Keys generated";
    	sendOutputEvent(scm_nEventCNFID);
    	break;
  }
}



