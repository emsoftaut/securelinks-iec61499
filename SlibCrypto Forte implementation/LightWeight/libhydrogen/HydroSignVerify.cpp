/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroSignVerify
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "HydroSignVerify.h"
#include "hydrogen.h"
#include "../../SlibTimeCalcs.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroSignVerify_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroSignVerify, g_nStringIdHydroSignVerify)

const CStringDictionary::TStringId FORTE_HydroSignVerify::scm_anDataInputNames[] = {g_nStringIdSignatures, g_nStringIdMessage, g_nStringIdMsgSize, g_nStringIdContext, g_nStringIdpubkey};

const CStringDictionary::TStringId FORTE_HydroSignVerify::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 64, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdINT, g_nStringIdWSTRING, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_HydroSignVerify::scm_anDataOutputNames[] = {g_nStringIdVerified, g_nStringIdSTATUS};

const CStringDictionary::TStringId FORTE_HydroSignVerify::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TForteInt16 FORTE_HydroSignVerify::scm_anEIWithIndexes[] = {-1, 0};
const TDataIOID FORTE_HydroSignVerify::scm_anEIWith[] = {3, 4, 2, 1, 0, 255};
const CStringDictionary::TStringId FORTE_HydroSignVerify::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroSignVerify::scm_anEOWith[] = {1, 0, 255, 0, 1, 255};
const TForteInt16 FORTE_HydroSignVerify::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroSignVerify::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroSignVerify::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  5,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroSignVerify::setInitialValues(){
  Signatures_Array().fromString("0");
  Message_Array().fromString("0");
  pubkey_Array().fromString("0");
}



void FORTE_HydroSignVerify::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
    	if (hydro_init() == 0) {
			STATUS() = "libhydrogen initialized";
			sendOutputEvent(scm_nEventINITOID);
		}
		else
			STATUS() = "libhydrogen initialization Error!!!";
    	break;
    case scm_nEventREQID:
    	char context[hydro_sign_CONTEXTBYTES] = {0};
		uint8_t pk[hydro_sign_PUBLICKEYBYTES];
		uint8_t msg[hydro_kx_SESSIONKEYBYTES];
		uint8_t sig[hydro_sign_BYTES];

		int msize = MsgSize();
		Context().toString(context, hydro_sign_CONTEXTBYTES);

	   	for(int i = 0; i < hydro_sign_BYTES; i++) {
	   		if(i < hydro_sign_PUBLICKEYBYTES) {
	   			pk[i] = pubkey()[i];
	   			msg[i] = Message()[i];
	   		}
	   		sig[i] = Signatures()[i];
		}

		if(hydro_sign_verify(sig, msg, msize, context, pk) == 0) {
			SlibTimeCalcs tObj;
			tObj.registerTime("LightWeightKeyExchangeEndTimes.txt");
			Verified() = 1;
			STATUS() = "Signitures Verified";
			sendOutputEvent(scm_nEventCNFID);
		}
		else {
			Verified() = 0;
			STATUS() = "Invalid signitures";
		}
		break;
  }
}



