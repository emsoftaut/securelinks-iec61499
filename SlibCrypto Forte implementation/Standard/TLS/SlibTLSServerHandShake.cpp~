/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibTLSServerHandShake
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/
#include "../../SlibTimeCalcs.h"
#include "SlibTLSServerHandShake.h"
//#include "SlibSslServer.h"
#include "SlibTLS.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibTLSServerHandShake_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibTLSServerHandShake, g_nStringIdSlibTLSServerHandShake)

const CStringDictionary::TStringId FORTE_SlibTLSServerHandShake::scm_anDataInputNames[] = {g_nStringIdip, g_nStringIdport, g_nStringIdcertfile, g_nStringIdkeyfile};

const CStringDictionary::TStringId FORTE_SlibTLSServerHandShake::scm_anDataInputTypeIds[] = {g_nStringIdWSTRING, g_nStringIdUINT, g_nStringIdWSTRING, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_SlibTLSServerHandShake::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};

const CStringDictionary::TStringId FORTE_SlibTLSServerHandShake::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TForteInt16 FORTE_SlibTLSServerHandShake::scm_anEIWithIndexes[] = {0, 5};
const TDataIOID FORTE_SlibTLSServerHandShake::scm_anEIWith[] = {0, 1, 2, 3, 255, 0, 2, 1, 3, 255};
const CStringDictionary::TStringId FORTE_SlibTLSServerHandShake::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_SlibTLSServerHandShake::scm_anEOWith[] = {0, 1, 255, 0, 1, 255};
const TForteInt16 FORTE_SlibTLSServerHandShake::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_SlibTLSServerHandShake::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibTLSServerHandShake::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  4,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

static bool initialized = false;

void FORTE_SlibTLSServerHandShake::executeEvent(int pa_nEIID){
	SlibTLS *sslObj = SlibTLS::Instance();
	uint16_t p = port();
	char cert_file[256] = {0};
	char key_file[256] = {0};
	char ip_str[64] = {0};
	char *p_cert, *p_key, p_ip;
  switch(pa_nEIID){
    case scm_nEventINITID:
    	certfile().toString(cert_file, 256);
    	keyfile().toString(key_file, 256);

    	// triming first and last character
    	p_cert = &cert_file[1];
    	p_cert[strlen(p_cert) - 1] = 0;
    	p_key = &key_file[1];
		p_key[strlen(p_key) - 1] = 0;

		sslObj->opensslServerInit();

		if(sslObj->opensslServerCreateContext() &&
						sslObj->opensslServerConfigureContext(sslObj->opensslGetContext(), p_cert, p_key) &&
						sslObj->opensslServerCreateSocket(p)) {

			if(sslObj->opensslSetCiphers(sslObj->opensslGetContext(), SLIB_CIPHER_SUITE_TLS2_NULL_SHA) != SLIB_SUCCESS) {
				QO() = 0;
				initialized = false;
				STATUS() = "cipher list error!!!";
				return;
    		}

			initialized = true;
			QO() = 1;
			STATUS() = "Initialization successful";
			sendOutputEvent(scm_nEventINITOID);
		}
		else {
			QO() = 0;
			STATUS() = "Initialization error!!!";
		}
    	break;
    case scm_nEventREQID:
    	if(initialized) {
    		STATUS() = "Waiting for handshake ...";

    		if(sslObj->opensslServerHandshakeWait()) {
    			SlibTimeCalcs tObj;
					tObj.registerTime("TLSHandShakeEndTimes.txt");
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



