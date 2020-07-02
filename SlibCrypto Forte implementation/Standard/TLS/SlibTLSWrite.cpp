/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibTLSWrite
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "../../SlibTimeCalcs.h"
#include "SlibTLSWrite.h"
#include "SlibTLS.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibTLSWrite_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SlibTLSWrite, g_nStringIdSlibTLSWrite)

const CStringDictionary::TStringId FORTE_SlibTLSWrite::scm_anDataInputNames[] = {g_nStringIddata, g_nStringIddatalen};

const CStringDictionary::TStringId FORTE_SlibTLSWrite::scm_anDataInputTypeIds[] = {g_nStringIdARRAY, 32, g_nStringIdBYTE, g_nStringIdUINT};

const CStringDictionary::TStringId FORTE_SlibTLSWrite::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};

const CStringDictionary::TStringId FORTE_SlibTLSWrite::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TForteInt16 FORTE_SlibTLSWrite::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_SlibTLSWrite::scm_anEIWith[] = {0, 1, 255, 0, 1, 255};
const CStringDictionary::TStringId FORTE_SlibTLSWrite::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_SlibTLSWrite::scm_anEOWith[] = {0, 1, 255, 0, 1, 255};
const TForteInt16 FORTE_SlibTLSWrite::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_SlibTLSWrite::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_SlibTLSWrite::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_SlibTLSWrite::setInitialValues(){
  data_Array().fromString("0");
}

#define MAX_BYTES 32

void FORTE_SlibTLSWrite::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
		sendOutputEvent(scm_nEventINITOID);
		break;
    case scm_nEventREQID:
    	uint8_t databuf[MAX_BYTES] = {0};
    	int dsize = datalen();

    	for(int i = 0; i < MAX_BYTES; i++)
    		databuf[i] = data()[i];

    	SlibTLS *slibObj = SlibTLS::Instance();
		SlibTimeCalcs tObj;
		tObj.registerTime("TLSEncryptionStartTimes.txt");
    	if(slibObj->opensslWrite(slibObj->opensslGetSSLHandle(), databuf, dsize) == SLIB_SUCCESS) {
    		QO() = 1;
			STATUS() = "Data written.";
    		sendOutputEvent(scm_nEventCNFID);
    	}
    	else{
			QO() = 0;
			STATUS() = "Data writting error!!!";
    	}
		break;
  }
}



