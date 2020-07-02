/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroSignCreate
 *** Description: Service Interface Function Block Type
 *** Version: 
 *************************************************************************/
#include <stdio.h>
#include "HydroSignCreate.h"
#include "hydrogen.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroSignCreate_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroSignCreate, g_nStringIdHydroSignCreate)

const CStringDictionary::TStringId FORTE_HydroSignCreate::scm_anDataInputNames[] = {g_nStringIdMessage, g_nStringIdMsgSize, g_nStringIdConext, g_nStringIdprikey};

const CStringDictionary::TStringId FORTE_HydroSignCreate::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdINT, g_nStringIdWSTRING, g_nStringIdARRAY, 64, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_HydroSignCreate::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdSignatures};

const CStringDictionary::TStringId FORTE_HydroSignCreate::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdARRAY, 64, g_nStringIdBYTE};

const TForteInt16 FORTE_HydroSignCreate::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_HydroSignCreate::scm_anEIWith[] = {0, 1, 255, 0, 2, 3, 255};
const CStringDictionary::TStringId FORTE_HydroSignCreate::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroSignCreate::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_HydroSignCreate::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroSignCreate::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroSignCreate::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  4,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroSignCreate::setInitialValues(){
  Message_Array().fromString("0");
  prikey_Array().fromString("0");
  Signatures_Array().fromString("0");
}


void FORTE_HydroSignCreate::executeEvent(int pa_nEIID){
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
    	char context[hydro_sign_CONTEXTBYTES] = {0};
    	uint8_t signature[hydro_sign_BYTES];
    	uint8_t sk[hydro_sign_SECRETKEYBYTES];
    	uint8_t msg[hydro_kx_SESSIONKEYBYTES];

    	int msize = MsgSize();

    	for(int i = 0; i < hydro_sign_SECRETKEYBYTES; i++) {
    		sk[i] = prikey()[i];
    		if(i < 32)
    			msg[i] = Message()[i];
    	}

    	Conext().toString(context, hydro_sign_CONTEXTBYTES);

    	if(hydro_sign_create(signature, msg, msize, context, sk) == 0) {
    		for(int i = 0; i < hydro_sign_BYTES; i++)
    			Signatures()[i] = signature[i];

    		STATUS() = "Signitures generated";
			sendOutputEvent(scm_nEventCNFID);
    	}
      break;
  }
}



