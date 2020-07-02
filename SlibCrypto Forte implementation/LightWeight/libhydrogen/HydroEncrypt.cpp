/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroEncrypt
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0:
 *************************************************************************/
#include "HydroEncrypt.h"
#include "hydrogen.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroEncrypt_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroEncrypt, g_nStringIdHydroEncrypt)

const CStringDictionary::TStringId FORTE_HydroEncrypt::scm_anDataInputNames[] = {g_nStringIdkey, g_nStringIddata, g_nStringIddatalen, g_nStringIdcontext};

const CStringDictionary::TStringId FORTE_HydroEncrypt::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 1024, g_nStringIdBYTE, g_nStringIdUINT, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_HydroEncrypt::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdcipher};

const CStringDictionary::TStringId FORTE_HydroEncrypt::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdARRAY, 1024, g_nStringIdBYTE};

const TForteInt16 FORTE_HydroEncrypt::scm_anEIWithIndexes[] = {0, 5};
const TDataIOID FORTE_HydroEncrypt::scm_anEIWith[] = {0, 1, 3, 2, 255, 0, 2, 3, 1, 255};
const CStringDictionary::TStringId FORTE_HydroEncrypt::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroEncrypt::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_HydroEncrypt::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroEncrypt::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroEncrypt::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  4,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroEncrypt::setInitialValues(){
  key_Array().fromString("0");
  data_Array().fromString("0");
  cipher_Array().fromString("0");
}

#define MSG_MAX_BYTES 1024

void FORTE_HydroEncrypt::executeEvent(int pa_nEIID){
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
    	uint8_t msg[MSG_MAX_BYTES] = {0};
    	uint8_t k[hydro_secretbox_KEYBYTES] = {0};

    	char ctx[hydro_secretbox_CONTEXTBYTES] = {0};
    	int msglen = datalen();
    	int msgid = 0, i = 0, max = 0;

    	//uint8_t c[hydro_secretbox_HEADERBYTES + msglen] = {0}; //might not work for compilers other than GCC
		uint8_t c[1024] = {0};
    	(msglen > hydro_secretbox_KEYBYTES) ? max = msglen : max = hydro_secretbox_KEYBYTES;

    	while(1) { //copying msg and key in linear time
    		if(i < max) {
				if(i < msglen)
					msg[i] = data()[i];
				if(i < hydro_secretbox_KEYBYTES)
					k[i] = key()[i];
    		}
    		else
    			break;
    		i++;
    	}

    	context().toString(ctx, hydro_secretbox_CONTEXTBYTES);
    	hydro_secretbox_encrypt(c, msg, msglen, msgid, ctx, k);

    	for(i = 0; i < hydro_secretbox_HEADERBYTES + msglen; i++)
    		cipher()[i] = c[i];

    	sendOutputEvent(scm_nEventCNFID);
    	break;
  }
}


