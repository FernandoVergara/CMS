#include "L1Trigger/RPCTriggerPrimitives/interface/RPCProcessor.h"

RPCProcessor::RPCProcessor():
  digi_pointer(nullptr){
}

RPCProcessor::~RPCProcessor(){
}

void RPCProcessor::Process(const edm::Event& iEvent,
			   const edm::EventSetup& iSetup,
			   const edm::EDGetToken& RPCDigiToken,
			   RPCRecHitCollection& primitivedigi,
			   std::unique_ptr<RPCMaskedStrips>& theRPCMaskedStripsObj,
                           std::unique_ptr<RPCDeadStrips>& theRPCDeadStripsObj,
			   std::unique_ptr<RPCRecHitBaseAlgo>& theAlgo) const{
 
  // Get the RPC Geometry
  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
  // Get the RPC Digis
  edm::Handle<RPCDigiCollection> rpcdigis;
  iEvent.getByToken(RPCDigiToken, rpcdigis);
  // Pass the EventSetup to the algo
  //theAlgo->setES(iSetup); 
  if(theAlgo == nullptr) std::cout << " fdfdf " << std::endl;

  edm::OwnVector<RPCRecHit> recHits;
 
  for ( auto rpcdgIt = rpcdigis->begin(); rpcdgIt != rpcdigis->end(); ++rpcdgIt ) {

    // The layerId
    const RPCDetId& rpcId = (*rpcdgIt).first;
    std::cout << rpcId.rawId() << " "  << std::endl;

   // Get the GeomDet from the setup
   const RPCRoll* roll = rpcGeom->roll(rpcId);
   if (roll == nullptr){
     edm::LogError("BadDigiInput")<<"Failed to find RPCRoll for ID "<<rpcId;
     continue;
   }


   // Get the iterators over the digis associated with this LayerId
   const RPCDigiCollection::Range& range = (*rpcdgIt).second;
 
    RollMask mask;
    const int rawId = rpcId.rawId();
    for ( const auto& tomask : theRPCMaskedStripsObj->MaskVec ) {
      if ( tomask.rawId == rawId ) {
        const int bit = tomask.strip;
        mask.set(bit-1);
      }
    }

    for ( const auto& tomask : theRPCDeadStripsObj->DeadVec ) {
      if ( tomask.rawId == rawId ) {
        const int bit = tomask.strip;
        mask.set(bit-1);
      }
    }

 
   // Call the reconstruction algorithm    
   // edm::OwnVector<RPCRecHit> recHits = theAlgo->reconstruct(*roll, rpcId, range, mask);
  
    // LocalError tmpErr;
    // LocalPoint point; 
    
     

   // auto digi_pointer = std::make_shared<RPCRecHit>(  RPCRecHit(rpcId, 0, 0, 0, point, tmpErr) );
   // recHits.push_back(*digi_pointer.get());

    primitivedigi.put(rpcId, recHits.begin(), recHits.end());   
  } // end for loop
  
}
