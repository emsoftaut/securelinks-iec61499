/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibConcat16_1024
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#ifndef _SLIBCONCAT16_1024_H_
#define _SLIBCONCAT16_1024_H_

#include <funcbloc.h>
#include <forte_byte.h>
#include <forte_array.h>

class FORTE_SlibConcat16_1024: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_SlibConcat16_1024)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BYTE *A16() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(0)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &A16_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(0));
  };

  CIEC_BYTE *A1024() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDI(1)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &A1024_Array() {
    return *static_cast<CIEC_ARRAY*>(getDI(1));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BYTE *AOut() {
    return (CIEC_BYTE*)(*static_cast<CIEC_ARRAY *>(getDO(0)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY &AOut_Array() {
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

   FORTE_FB_DATA_ARRAY(1, 2, 1, 0);

virtual void setInitialValues();

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_SlibConcat16_1024){
  };

  virtual ~FORTE_SlibConcat16_1024(){};

};

#endif //close the ifdef sequence from the beginning of the file

