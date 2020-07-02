/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroDecrypt
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/
#include "HydroDecrypt.h"
#include "hydrogen.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroDecrypt_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroDecrypt, g_nStringIdHydroDecrypt)

const CStringDictionary::TStringId FORTE_HydroDecrypt::scm_anDataInputNames[] = {g_nStringIdkey, g_nStringIdcipher, g_nStringIdcipherlen, g_nStringIdcontext};

const CStringDictionary::TStringId FORTE_HydroDecrypt::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 1024, g_nStringIdBYTE, g_nStringIdUINT, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_HydroDecrypt::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIddata};

const CStringDictionary::TStringId FORTE_HydroDecrypt::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdARRAY, 1024, g_nStringIdBYTE};

const TForteInt16 FORTE_HydroDecrypt::scm_anEIWithIndexes[] = {-1, 0};
const TDataIOID FORTE_HydroDecrypt::scm_anEIWith[] = {0, 3, 1, 2, 255};
const CStringDictionary::TStringId FORTE_HydroDecrypt::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroDecrypt::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_HydroDecrypt::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroDecrypt::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroDecrypt::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  4,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroDecrypt::setInitialValues(){
  key_Array().fromString("0");
  cipher_Array().fromString("0");
  data_Array().fromString("0");
}


#define MSG_MAX_BYTES 1024

void FORTE_HydroDecrypt::executeEvent(int pa_nEIID){
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
    	int msgid = 0, i = 0, max = 0;
    	int clen = cipherlen() + hydro_secretbox_HEADERBYTES;
    	uint8_t msg[MSG_MAX_BYTES] = {0};
    	uint8_t k[hydro_secretbox_KEYBYTES] = {0};
      	uint8_t c[1024] = {0}; //might not work for compilers other than GCC
    	char ctx[hydro_secretbox_CONTEXTBYTES] = {0};

    	(clen > hydro_secretbox_KEYBYTES) ? max = clen : max = hydro_secretbox_KEYBYTES;

    	while(1) { //copying msg and key in linear time
    		if(i < max) {
				if(i < clen)
					c[i] = cipher()[i];
				if(i < hydro_secretbox_KEYBYTES)
					k[i] = key()[i];
    		}
    		else
    			break;
    		i++;
    	}

    	context().toString(ctx, hydro_secretbox_CONTEXTBYTES);

    	if(hydro_secretbox_decrypt(msg, c, clen, msgid, ctx, k) != -1) {
    		SlibTimeCalcs tObj;
			tObj.registerTime("LightWeightEncryptionEndTimes.txt");
    		for(i = 0; i < clen - hydro_secretbox_HEADERBYTES; i++)
    			data()[i] = msg[i];
			STATUS() = "Last message decrypted.";
			QO() = 1;
			sendOutputEvent(scm_nEventCNFID);
    	}
    	else {
    		QO() = 0;
    		STATUS() = "Authentication Error!!!";
    	}

    	break;
  }
}




