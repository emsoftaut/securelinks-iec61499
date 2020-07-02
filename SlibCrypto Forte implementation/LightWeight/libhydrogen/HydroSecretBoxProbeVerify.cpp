/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroSecretBoxProbeVerify
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "HydroSecretBoxProbeVerify.h"
#include "hydrogen.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroSecretBoxProbeVerify_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroSecretBoxProbeVerify, g_nStringIdHydroSecretBoxProbeVerify)

const CStringDictionary::TStringId FORTE_HydroSecretBoxProbeVerify::scm_anDataInputNames[] = {g_nStringIdkey, g_nStringIdprobe, g_nStringIdcipher, g_nStringIdcipherlen, g_nStringIdcontext};

const CStringDictionary::TStringId FORTE_HydroSecretBoxProbeVerify::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 16, g_nStringIdBYTE, g_nStringIdARRAY, 1024, g_nStringIdBYTE, g_nStringIdUINT, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_HydroSecretBoxProbeVerify::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdverified};

const CStringDictionary::TStringId FORTE_HydroSecretBoxProbeVerify::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdBOOL};

const TForteInt16 FORTE_HydroSecretBoxProbeVerify::scm_anEIWithIndexes[] = {-1, 0};
const TDataIOID FORTE_HydroSecretBoxProbeVerify::scm_anEIWith[] = {1, 3, 2, 4, 0, 255};
const CStringDictionary::TStringId FORTE_HydroSecretBoxProbeVerify::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroSecretBoxProbeVerify::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_HydroSecretBoxProbeVerify::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroSecretBoxProbeVerify::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroSecretBoxProbeVerify::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  5,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroSecretBoxProbeVerify::setInitialValues(){
  key_Array().fromString("0");
  probe_Array().fromString("0");
  cipher_Array().fromString("0");
}


void FORTE_HydroSecretBoxProbeVerify::executeEvent(int pa_nEIID){
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
    	int i = 0;
		int clen = cipherlen() + hydro_secretbox_HEADERBYTES;
		uint8_t pb[hydro_secretbox_PROBEBYTES] = {0};
		uint8_t k[hydro_secretbox_KEYBYTES] = {0};
		uint8_t c[hydro_secretbox_HEADERBYTES] = {0};
		char ctx[hydro_secretbox_CONTEXTBYTES] = {0};

		for(i = 0; i < hydro_secretbox_HEADERBYTES; i++) {
			c[i] = cipher()[i];
			if(i < hydro_secretbox_KEYBYTES)
				k[i] = key()[i];
			if(i < hydro_secretbox_PROBEBYTES)
				pb[i] = probe()[i];
		}

		context().toString(ctx, hydro_secretbox_CONTEXTBYTES);

		if(hydro_secretbox_probe_verify(pb, c, clen, ctx, k) != -1) {
			STATUS() = "probe verified.";
			QO() = 1;
			verified() = 1;
			sendOutputEvent(scm_nEventCNFID);
		}
    	else {
    		QO() = 0;
    		STATUS() = "Unverified probe!!!";
    	}
		break;
  }
}



