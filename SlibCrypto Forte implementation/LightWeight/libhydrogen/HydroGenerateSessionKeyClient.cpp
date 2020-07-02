/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroGenerateSessionKeyClient
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "HydroGenerateSessionKeyClient.h"
#include "hydrogen.h"
#include <stdio.h>
//#include <windows.h>
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroGenerateSessionKeyClient_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroGenerateSessionKeyClient, g_nStringIdHydroGenerateSessionKeyClient)

const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyClient::scm_anDataInputNames[] = {g_nStringIdserver_pk, g_nStringIdpsk};

const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyClient::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyClient::scm_anDataOutputNames[] = {g_nStringIdtx, g_nStringIdrx, g_nStringIdpacket, g_nStringIdSTATUS, g_nStringIdQO};

const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyClient::scm_anDataOutputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdWSTRING, g_nStringIdBOOL};

const TForteInt16 FORTE_HydroGenerateSessionKeyClient::scm_anEIWithIndexes[] = {-1, 0};
const TDataIOID FORTE_HydroGenerateSessionKeyClient::scm_anEIWith[] = {0, 1, 255};
const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyClient::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroGenerateSessionKeyClient::scm_anEOWith[] = {3, 4, 255, 0, 1, 2, 3, 4, 255};
const TForteInt16 FORTE_HydroGenerateSessionKeyClient::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroGenerateSessionKeyClient::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroGenerateSessionKeyClient::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  5,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroGenerateSessionKeyClient::setInitialValues(){
  server_pk_Array().fromString("0");
  psk_Array().fromString("0");
  tx_Array().fromString("0");
  rx_Array().fromString("0");
  packet_Array().fromString("0");
}


void FORTE_HydroGenerateSessionKeyClient::executeEvent(int pa_nEIID){
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
      hydro_kx_session_keypair kp;
      uint8_t packet1[hydro_kx_N_PACKET1BYTES];
      uint8_t spk[hydro_kx_PUBLICKEYBYTES]; //server public key
      uint8_t preshared_key[hydro_kx_PSKBYTES];

      for(int i = 0 ; i < hydro_kx_PUBLICKEYBYTES; i++) {
    	  spk[i] = server_pk()[i];
    	  preshared_key[i] = psk()[i];
      }

      if(hydro_kx_n_1(&kp, packet1, (const uint8_t*)preshared_key, (const uint8_t*)spk) == 0) {
    	  for(int i = 0; i < hydro_kx_SESSIONKEYBYTES; i++) { //since hydro_kx_SESSIONKEYBYTES = hydro_kx_N_PACKET1BYTES
    		  tx()[i] = kp.tx[i];
    		  rx()[i] = kp.rx[i];
    		  packet()[i] = packet1[i];
    	  }
    	  STATUS() = "Keys generated";
    	  sendOutputEvent(scm_nEventCNFID);
      }
      else
    	  STATUS() = "Keys generation error!!!";

      break;
  }
}



