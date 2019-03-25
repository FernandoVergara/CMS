#ifndef L1Trigger_RPCTriggerPrimitives_RPCProcessor_h
#define L1Trigger_RPCTriggerPrimitives_RPCProcessor_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHit.h"

#include "DataFormats/RPCRecHit/interface/RPCRecHit.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"

#include "RecoLocalMuon/RPCRecHit/interface/RPCRecHitAlgoFactory.h"

#include "CondFormats/DataRecord/interface/RPCMaskedStripsRcd.h"
#include "CondFormats/DataRecord/interface/RPCDeadStripsRcd.h"
#include "CondFormats/RPCObjects/interface/RPCMaskedStrips.h"
#include "CondFormats/RPCObjects/interface/RPCDeadStrips.h"
#include "CondFormats/Serialization/interface/Serializable.h"


#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string> 
#include <sstream>
#include <vector>
#include <boost/cstdint.hpp>

class RPCProcessor{
  
 public:

  explicit RPCProcessor();
  ~RPCProcessor();
  
  void Process(const edm::Event& iEvent,
	       const edm::EventSetup& iSetup,
	       const edm::EDGetToken& RPCDigiToken,
	       RPCRecHitCollection& primitivedigi,
               std::unique_ptr<RPCMaskedStrips>& theRPCMaskedStripsObj,
	       std::unique_ptr<RPCDeadStrips>& theRPCDeadStripsObj,
	       std::unique_ptr<RPCRecHitBaseAlgo>& theAlgo) const;
 
   struct Map_structure {

     std::string linkboard_;
     int linkboard_ID;
     std::string chamber1_;
     std::string chamber2_;
     COND_SERIALIZABLE;     	
   };

  std::vector<Map_structure> const & GetMapVector() const {return MapVec;}
  std::vector<Map_structure> MapVec;

 
  COND_SERIALIZABLE;
  
 private:
  
  std::shared_ptr<RPCRecHit> digi_pointer;
  
  // The reconstruction algorithm
  std::unique_ptr<RPCRecHitBaseAlgo> theAlgo; 
};
#endif

