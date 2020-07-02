/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: ByteToByte
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#ifndef _BYTETOBYTE_H_
#define _BYTETOBYTE_H_

#include <funcbloc.h>
#include <forte_byte.h>
#include <forte_array.h>

class FORTE_ByteToByte: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_ByteToByte)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BYTE *In() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(0)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &In_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(0));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BYTE *Out() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDO(0)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &Out_Array() {
    return *static_cast<CIEC_ARRAY*>(getDO(0));
  };

  static const TEventID scm_nEventREQID = 0;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventCNFID = 0;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_FB_DATA_ARRAY(1, 1, 1, 0);

virtual void setInitialValues();

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_ByteToByte){
  };

  virtual ~FORTE_ByteToByte(){};

};

#endif //close the ifdef sequence from the beginning of the file

