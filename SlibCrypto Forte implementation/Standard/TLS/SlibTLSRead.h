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

#ifndef _SLIBTLSREAD_H_
#define _SLIBTLSREAD_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_byte.h>
#include <forte_wstring.h>
#include <forte_array.h>

class FORTE_SlibTLSRead: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_SlibTLSRead)

private:
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
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventCNFID = 1;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_FB_DATA_ARRAY(2, 0, 3, 0);

virtual void setInitialValues();

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_SlibTLSRead){
  };

  virtual ~FORTE_SlibTLSRead(){};

};

#endif //close the ifdef sequence from the beginning of the file

