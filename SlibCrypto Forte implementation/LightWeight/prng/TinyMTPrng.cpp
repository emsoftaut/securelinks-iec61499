/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: TinyMTPrng
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "TinyMTPrng.h"
#include "tinymt32.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "TinyMTPrng_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_TinyMTPrng, g_nStringIdTinyMTPrng)

const CStringDictionary::TStringId FORTE_TinyMTPrng::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdSeed};

const CStringDictionary::TStringId FORTE_TinyMTPrng::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdDINT};

const CStringDictionary::TStringId FORTE_TinyMTPrng::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdRand};

const CStringDictionary::TStringId FORTE_TinyMTPrng::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdUDINT};

const TForteInt16 FORTE_TinyMTPrng::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_TinyMTPrng::scm_anEIWith[] = {0, 1, 255, 0, 255};
const CStringDictionary::TStringId FORTE_TinyMTPrng::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_TinyMTPrng::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_TinyMTPrng::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_TinyMTPrng::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_TinyMTPrng::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

tinymt32_t ctx = {0};

void FORTE_TinyMTPrng::initialilzePrng() {
	uint32_t seed = 1;
	if(Seed() > 1)
		seed = Seed();
	tinymt32_init(&ctx, seed);
	Seed() = seed;
	QI() = 1;
}

uint32_t FORTE_TinyMTPrng::generateRandom32() {
	return tinymt32_generate_uint32(&ctx);
}

void FORTE_TinyMTPrng::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
    	initialilzePrng();
    	sendOutputEvent(scm_nEventINITOID);

      break;
    case scm_nEventREQID:
    	if(QI() == 1) {
    		Rand() = generateRandom32();
    		STATUS() = "Ok";
    		QO() = 1;
    		sendOutputEvent(scm_nEventCNFID);
    	}
    	else {
    		STATUS() = "Initialization error!!!";
    		Rand() = 0;
    	}

      break;
  }
}



