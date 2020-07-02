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

#ifndef _HYDROGENERATESESSIONKEYSERVER_H_
#define _HYDROGENERATESESSIONKEYSERVER_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_byte.h>
#include <forte_wstring.h>
#include <forte_array.h>

class FORTE_HydroGenerateSessionKeyServer: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_HydroGenerateSessionKeyServer)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BYTE *server_sk() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(0)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &server_sk_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(0));
  };

  CIEC_BYTE *packet1() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(1)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &packet1_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(1));
  };

  CIEC_BYTE *server_pk() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(2)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &server_pk_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(2));
  };

  CIEC_BYTE *psk() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(3)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &psk_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(3));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_WSTRING &STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(1));
  };

  CIEC_BYTE *tx() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDO(2)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &tx_Array() {
    return *static_cast<CIEC_ARRAY*>(getDO(2));
  };

  CIEC_BYTE *rx() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDO(3)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &rx_Array() {
    return *static_cast<CIEC_ARRAY*>(getDO(3));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventREQID = 1;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventCNFID = 1;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_FB_DATA_ARRAY(2, 4, 4, 0);

virtual void setInitialValues();

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_HydroGenerateSessionKeyServer){
  };

  virtual ~FORTE_HydroGenerateSessionKeyServer(){};

};

#endif //close the ifdef sequence from the beginning of the file

