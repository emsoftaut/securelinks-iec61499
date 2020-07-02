/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroKeyGen
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#include "HydroKeyGen.h"
#include "hydrogen.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HydroKeyGen_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_HydroKeyGen, g_nStringIdHydroKeyGen)

const CStringDictionary::TStringId FORTE_HydroKeyGen::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdKey};

const CStringDictionary::TStringId FORTE_HydroKeyGen::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdARRAY, 32, g_nStringIdBYTE};

const TForteInt16 FORTE_HydroKeyGen::scm_anEIWithIndexes[] = {-1, -1};
const CStringDictionary::TStringId FORTE_HydroKeyGen::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_HydroKeyGen::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_HydroKeyGen::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_HydroKeyGen::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_HydroKeyGen::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  0,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  0,  0, 0, 
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_HydroKeyGen::setInitialValues(){
  Key_Array().fromString("0");
}


void FORTE_HydroKeyGen::executeEvent(int pa_nEIID){
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
    	if(QO() == 1) {
			uint8_t masterkey[hydro_kdf_KEYBYTES] = {0};
			hydro_kdf_keygen(masterkey);
			for(int i = 0; i < hydro_kdf_KEYBYTES; i++)
				Key()[i] = masterkey[i];
			STATUS() = "Ok";
			sendOutputEvent(scm_nEventCNFID);
    	}
    	else
    		STATUS() = "Initialization error!!!";

      break;
  }
}



