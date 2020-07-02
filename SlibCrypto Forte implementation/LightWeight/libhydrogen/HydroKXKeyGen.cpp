/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroKXKeyGen
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/
#include "HydroKXKeyGen.h"
#include "hydrogen.h"
#include "../../SlibTimeCalcs.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroKXKeyGen_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroKXKeyGen, g_nStringIdHydroKXKeyGen)

const CStringDictionary::TStringId FORTE_HydroKXKeyGen::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdpubkey, g_nStringIdprikey};

const CStringDictionary::TStringId FORTE_HydroKXKeyGen::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const TForteInt16 FORTE_HydroKXKeyGen::scm_anEIWithIndexes[] = {-1, -1};
const CStringDictionary::TStringId FORTE_HydroKXKeyGen::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroKXKeyGen::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 3, 255};
const TForteInt16 FORTE_HydroKXKeyGen::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroKXKeyGen::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroKXKeyGen::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  0,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  0,  0, 0, 
  4,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroKXKeyGen::setInitialValues(){
  pubkey_Array().fromString("0");
  prikey_Array().fromString("0");
}

void FORTE_HydroKXKeyGen::executeEvent(int pa_nEIID){
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
    	if(QO() == 1) {
    		SlibTimeCalcs tObj;
    		tObj.registerTime("LightWeightKeyExchangeStartTimes.txt");

			hydro_kx_keypair server_kp;
			hydro_kx_keygen(&server_kp);
			for(int i = 0; i < hydro_kx_PUBLICKEYBYTES; i++) {
				pubkey()[i] = server_kp.pk[i];
				prikey()[i] = server_kp.sk[i];
			}
			STATUS() = "public key generated";
			sendOutputEvent(scm_nEventCNFID);
		}
		else
			STATUS() = "Initialization error!!!";
      break;
  }
}



