/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibTLSClientHandShake
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     
 *************************************************************************/
#include "../../SlibTimeCalcs.h"
#include "SlibTLSClientHandShake.h"
#include "SlibTLS.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibTLSClientHandShake_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibTLSClientHandShake, g_nStringIdSlibTLSClientHandShake)

const CStringDictionary::TStringId FORTE_SlibTLSClientHandShake::scm_anDataInputNames[] = {g_nStringIdip, g_nStringIdport, g_nStringIdciphersuite};

const CStringDictionary::TStringId FORTE_SlibTLSClientHandShake::scm_anDataInputTypeIds[] = {g_nStringIdWSTRING, g_nStringIdUINT, g_nStringIdUINT};

const CStringDictionary::TStringId FORTE_SlibTLSClientHandShake::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};

const CStringDictionary::TStringId FORTE_SlibTLSClientHandShake::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TForteInt16 FORTE_SlibTLSClientHandShake::scm_anEIWithIndexes[] = {0, 4};
const TDataIOID FORTE_SlibTLSClientHandShake::scm_anEIWith[] = {0, 1, 2, 255, 0, 1, 2, 255};
const CStringDictionary::TStringId FORTE_SlibTLSClientHandShake::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_SlibTLSClientHandShake::scm_anEOWith[] = {0, 1, 255, 0, 1, 255};
const TForteInt16 FORTE_SlibTLSClientHandShake::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_SlibTLSClientHandShake::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibTLSClientHandShake::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  3,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_SlibTLSClientHandShake::setInitialValues(){
  ciphersuite() = 1;
}


static bool initialized = false;

void FORTE_SlibTLSClientHandShake::executeEvent(int pa_nEIID){
	SlibTLS *sslObj = SlibTLS::Instance();
	uint16_t p = port();
	char *p_ip;
	char ip_str[128] = {0};
	uint8_t cs = ciphersuite();
	SlibTimeCalcs tObj;
  switch(pa_nEIID){
    case scm_nEventINITID:

		tObj.registerTime("TLSHandShakeStartTimes.txt");
    	sslObj->opensslClientInit();

    	if(!sslObj->opensslClientCreateContext()) {
    		QO() = 0;
    		initialized = false;
			STATUS() = "Context creation error!!!";
			return;
    	}

    	if(sslObj->opensslSetCiphers(sslObj->opensslGetContext(), cs) != SLIB_SUCCESS) {
    		QO() = 0;
			initialized = false;
			STATUS() = "cipher list error!!!";
			return;
    	}

    	if(sslObj->opensslClientCreateSocket() == -1) {
			QO() = 0;
			initialized = false;
			STATUS() = "Socket creation error!!!";
			return;
		}
    	QO() = 1;
    	initialized = true;
		STATUS() = "Initialization successful";
    	sendOutputEvent(scm_nEventINITOID);
    	break;
    case scm_nEventREQID:
    	if(initialized) {

        	ip().toString(ip_str, 128);
        	p_ip = &ip_str[1];
        	p_ip[strlen(p_ip) - 1] = 0;

    		STATUS() = "Waiting for handshake ...";

    		if(sslObj->opensslClientHandshake(p_ip, p)) {
    			QO() = 1;
    			STATUS() = "Handshake succeeded";
    			sendOutputEvent(scm_nEventCNFID);
    		}
    		else {
    			QO() = 0;
    			STATUS() = "Handshake error!!!";
    		}
    	}
    	else
			STATUS() = "Initialization error!!!";
    	break;
  }
}



