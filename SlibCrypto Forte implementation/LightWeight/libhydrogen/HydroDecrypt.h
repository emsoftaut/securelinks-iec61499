/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroDecrypt
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***    
 *************************************************************************/

#ifndef _HYDRODECRYPT_H_
#define _HYDRODECRYPT_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_byte.h>
#include <forte_uint.h>
#include <forte_wstring.h>
#include <forte_array.h>

class FORTE_HydroDecrypt: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_HydroDecrypt)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BYTE *key() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(0)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &key_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(0));
  };

  CIEC_BYTE *cipher() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(1)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &cipher_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(1));
  };

  CIEC_UINT &cipherlen() {
    return *static_cast<CIEC_UINT*>(getDI(2));
  };

  CIEC_WSTRING &context() {
    return *static_cast<CIEC_WSTRING*>(getDI(3));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_WSTRING &STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(1));
  };

  CIEC_BYTE *data() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDO(2)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &data_Array() {
    return *static_cast<CIEC_ARRAY*>(getDO(2));
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

   FORTE_FB_DATA_ARRAY(2, 4, 3, 0);

virtual void setInitialValues();

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_HydroDecrypt){
  };

  virtual ~FORTE_HydroDecrypt(){};

};

#endif //close the ifdef sequence from the beginning of the file

