/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroGenerateSessionKeyServer
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/
#include <stdio.h>
#include "HydroGenerateSessionKeyServer.h"
#include "hydrogen.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroGenerateSessionKeyServer_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroGenerateSessionKeyServer, g_nStringIdHydroGenerateSessionKeyServer)

const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyServer::scm_anDataInputNames[] = {g_nStringIdserver_sk, g_nStringIdpacket1, g_nStringIdserver_pk, g_nStringIdpsk};

const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyServer::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyServer::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdtx, g_nStringIdrx};

const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyServer::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const TForteInt16 FORTE_HydroGenerateSessionKeyServer::scm_anEIWithIndexes[] = {-1, 0};
const TDataIOID FORTE_HydroGenerateSessionKeyServer::scm_anEIWith[] = {0, 2, 1, 3, 255};
const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyServer::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroGenerateSessionKeyServer::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 3, 255};
const TForteInt16 FORTE_HydroGenerateSessionKeyServer::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyServer::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroGenerateSessionKeyServer::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  4,  scm_anDataInputNames, scm_anDataInputTypeIds,
  4,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroGenerateSessionKeyServer::setInitialValues(){
  server_sk_Array().fromString("0");
  packet1_Array().fromString("0");
  server_pk_Array().fromString("0");
  psk_Array().fromString("0");
  tx_Array().fromString("0");
  rx_Array().fromString("0");
}


void FORTE_HydroGenerateSessionKeyServer::executeEvent(int pa_nEIID){

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
    	hydro_kx_keypair server_kp = {0};
    	hydro_kx_session_keypair kp = {0};
    	uint8_t packet[hydro_kx_N_PACKET1BYTES];
    	uint8_t preshared_key[hydro_kx_PSKBYTES];

    	for(int i = 0; i < hydro_kx_PUBLICKEYBYTES; i++) {
			server_kp.pk[i] = server_pk()[i];
			server_kp.sk[i] = server_sk()[i];
			packet[i] = packet1()[i];
			preshared_key[i] = psk()[i];
    	}

    	if(hydro_kx_n_2(&kp, (const uint8_t*)packet, (const uint8_t*)preshared_key, (const hydro_kx_keypair*)&server_kp) == 0) {
    		for(int i = 0; i < hydro_kx_SESSIONKEYBYTES; i++) { //since hydro_kx_SESSIONKEYBYTES = hydro_kx_N_PACKET1BYTES
				  tx()[i] = kp.tx[i];
				  rx()[i] = kp.rx[i];
				  STATUS() = "Keys generated";
			}
    		sendOutputEvent(scm_nEventCNFID);
    	}
    	else
		  STATUS() = "Keys generation error!!!";
    	break;
  }
}



