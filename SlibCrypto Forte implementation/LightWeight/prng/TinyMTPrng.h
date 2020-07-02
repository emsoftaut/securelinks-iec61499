/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: TinyMTPrng
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     1.0: 
 *************************************************************************/

#ifndef _TINYMTPRNG_H_
#define _TINYMTPRNG_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_dint.h>
#include <forte_udint.h>
#include <forte_wstring.h>

class FORTE_TinyMTPrng: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_TinyMTPrng)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_DINT &Seed() {
    return *static_cast<CIEC_DINT*>(getDI(1));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_WSTRING &STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(1));
  };

  CIEC_UDINT &Rand() {
    return *static_cast<CIEC_UDINT*>(getDO(2));
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

   FORTE_FB_DATA_ARRAY(2, 2, 3, 0);

  void executeEvent(int pa_nEIID);
  void initialilzePrng();
  uint32_t generateRandom32();

public:
  FUNCTION_BLOCK_CTOR(FORTE_TinyMTPrng){
  };

  virtual ~FORTE_TinyMTPrng(){};

};

#endif //close the ifdef sequence from the beginning of the file

