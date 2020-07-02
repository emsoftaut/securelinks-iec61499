/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibTLSRead
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/
#include "../../SlibTimeCalcs.h"
#include "SlibTLSRead.h"
#include "SlibTLS.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibTLSRead_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibTLSRead, g_nStringIdSlibTLSRead)

const CStringDictionary::TStringId FORTE_SlibTLSRead::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIddata};

const CStringDictionary::TStringId FORTE_SlibTLSRead::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const TForteInt16 FORTE_SlibTLSRead::scm_anEIWithIndexes[] = {-1, -1};
const CStringDictionary::TStringId FORTE_SlibTLSRead::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_SlibTLSRead::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_SlibTLSRead::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_SlibTLSRead::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibTLSRead::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  0,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  0,  0, 0, 
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

#define MAX_BYTES 32

void FORTE_SlibTLSRead::setInitialValues(){
  data_Array().fromString("0");
}


void FORTE_SlibTLSRead::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:

		sendOutputEvent(scm_nEventINITOID);
		break;
    case scm_nEventREQID:
    	uint8_t databuf[MAX_BYTES] = {0};

    	SlibTLS *slibObj = SlibTLS::Instance();

    	printf("Awais: Waiting for read\n");
		if(slibObj->opensslRead(slibObj->opensslGetSSLHandle(), databuf, MAX_BYTES) == SLIB_SUCCESS) {
			SlibTimeCalcs tObj;
			tObj.registerTime("TLSEncryptionEndTimes.txt");
			for(int i = 0; i < MAX_BYTES; i++)
				data()[i] = databuf[i];
			QO() = 1;
			STATUS() = "Data read.";
			sendOutputEvent(scm_nEventCNFID);
		}
		else{
			QO() = 0;
			STATUS() = "Data reading error!!!";
		}
		printf("Awais: passed read\n");
      break;
  }
}



