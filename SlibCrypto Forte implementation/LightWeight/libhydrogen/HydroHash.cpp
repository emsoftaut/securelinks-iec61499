/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroHash
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/
#include <stdio.h>
#include <time.h>
#include "../../SlibTimeCalcs.h"
#include "HydroHash.h"
#include "hydrogen.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroHash_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroHash, g_nStringIdHydroHash)

const CStringDictionary::TStringId FORTE_HydroHash::scm_anDataInputNames[] = {g_nStringIdkeyed, g_nStringIdkey, g_nStringIddata, g_nStringIddatalen, g_nStringIdcontext};

const CStringDictionary::TStringId FORTE_HydroHash::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 128, g_nStringIdBYTE, g_nStringIdUINT, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_HydroHash::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdout};

const CStringDictionary::TStringId FORTE_HydroHash::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const TForteInt16 FORTE_HydroHash::scm_anEIWithIndexes[] = {-1, 0};
const TDataIOID FORTE_HydroHash::scm_anEIWith[] = {0, 2, 1, 3, 4, 255};
const CStringDictionary::TStringId FORTE_HydroHash::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroHash::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_HydroHash::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroHash::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroHash::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  5,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroHash::setInitialValues(){
  key_Array().fromString("0");
  data_Array().fromString("0");
  out_Array().fromString("0");
}

#define HASH_MSG_MAX_BYTES 128

void FORTE_HydroHash::executeEvent(int pa_nEIID){
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
    	int i, ret;
    	//clock_t start, end, final;

    	size_t msglen = datalen();
    	if(msglen > HASH_MSG_MAX_BYTES) {
    		STATUS() = "Message size exceeded limit (128 bytes).";
    		QO() = 0;
    		return;
    	}

    	bool useKey = keyed();
    	uint8_t k[hydro_hash_KEYBYTES] = {0};
    	uint8_t msg[HASH_MSG_MAX_BYTES] = {0};

    	uint8_t hash[hydro_hash_BYTES] = {0};
    	char ctx[hydro_secretbox_CONTEXTBYTES] = {0};

    	context().toString(ctx, hydro_secretbox_CONTEXTBYTES);

    	//going to trim first and last bytes
    	char *p = ctx;
    	p++;
    	p[strlen(p) - 1] = 0;
    	////////////

    	for(i = 0; i < msglen; i++)
    		msg[i] = data()[i];

		SlibTimeCalcs tObj;
		tObj.registerTime("LightWeightStartHashTimes.txt");
    	if(!useKey)
    		ret = hydro_hash_hash(hash, sizeof hash, (const uint8_t*)msg, msglen, (const char*)p, NULL);
    	else {
    		for(i = 0; i < hydro_hash_KEYBYTES; i++)
    			k[i] = key()[i];
    		//start = clock();
    		ret = hydro_hash_hash(hash, sizeof hash, msg, msglen, p, k);
    		//end = clock();

    		//final = (end - start) / (CLOCKS_PER_SEC / 1000);
    		//printf("start %u, end %u, final %u\n", start, end, final);
    	}
		tObj.registerTime("LightWeightHashEndTimes.txt");
    	/*for(i = 0; i < hydro_hash_BYTES; i++)
    		printf("%d ", hash[i]);*/

    	//printf("\n%d", ret);

    	for(i = 0; i < hydro_hash_BYTES; i++)
    		out()[i] = hash[i];

		STATUS() = "Hash produced.";
		QO() = 1;

		sendOutputEvent(scm_nEventCNFID);
		break;
  }
}



