/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: HydroSignCreate
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#ifndef _HYDROSIGNCREATE_H_
#define _HYDROSIGNCREATE_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_byte.h>
#include <forte_int.h>
#include <forte_wstring.h>
#include <forte_array.h>

class FORTE_HydroSignCreate: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_HydroSignCreate)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BYTE *Message() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(0)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &Message_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(0));
  };

  CIEC_INT &MsgSize() {
    return *static_cast<CIEC_INT*>(getDI(1));
  };

  CIEC_WSTRING &Conext() {
    return *static_cast<CIEC_WSTRING*>(getDI(2));
  };

  CIEC_BYTE *prikey() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(3)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &prikey_Array() {
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

  CIEC_BYTE *Signatures() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDO(2)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &Signatures_Array() {
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
  FUNCTION_BLOCK_CTOR(FORTE_HydroSignCreate){
  };

  virtual ~FORTE_HydroSignCreate(){};

};

#endif //close the ifdef sequence from the beginning of the file

