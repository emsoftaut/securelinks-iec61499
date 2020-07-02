/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SlibTLSServerHandShake
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0:
 *************************************************************************/

#ifndef _SLIBTLSSERVERHANDSHAKE_H_
#define _SLIBTLSSERVERHANDSHAKE_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_uint.h>
#include <forte_wstring.h>

class FORTE_SlibTLSServerHandShake: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_SlibTLSServerHandShake)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_WSTRING &ip() {
    return *static_cast<CIEC_WSTRING*>(getDI(0));
  };

  CIEC_UINT &port() {
    return *static_cast<CIEC_UINT*>(getDI(1));
  };

  CIEC_WSTRING &certfile() {
    return *static_cast<CIEC_WSTRING*>(getDI(2));
  };

  CIEC_WSTRING &keyfile() {
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

   FORTE_FB_DATA_ARRAY(2, 4, 2, 0);

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_SlibTLSServerHandShake){
  };

  virtual ~FORTE_SlibTLSServerHandShake(){};

};

#endif //close the ifdef sequence from the beginning of the file

