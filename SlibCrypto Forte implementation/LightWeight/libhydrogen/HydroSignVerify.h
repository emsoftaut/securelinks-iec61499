/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroSignVerify
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#ifndef _HYDROSIGNVERIFY_H_
#define _HYDROSIGNVERIFY_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_byte.h>
#include <forte_int.h>
#include <forte_wstring.h>
#include <forte_array.h>

class FORTE_HydroSignVerify: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_HydroSignVerify)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BYTE *Signatures() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(0)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &Signatures_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(0));
  };

  CIEC_BYTE *Message() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(1)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &Message_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(1));
  };

  CIEC_INT &MsgSize() {
    return *static_cast<CIEC_INT*>(getDI(2));
  };

  CIEC_WSTRING &Context() {
    return *static_cast<CIEC_WSTRING*>(getDI(3));
  };

  CIEC_BYTE *pubkey() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(4)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &pubkey_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(4));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &Verified() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_WSTRING &STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(1));
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

   FORTE_FB_DATA_ARRAY(2, 5, 2, 0);

virtual void setInitialValues();

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_HydroSignVerify){
  };

  virtual ~FORTE_HydroSignVerify(){};

};

#endif //close the ifdef sequence from the beginning of the file

