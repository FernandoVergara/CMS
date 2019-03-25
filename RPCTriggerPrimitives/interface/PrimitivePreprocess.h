#ifndef L1Trigger_RPCTriggerPrimitives_PrimitivePreprocess_h
#define L1Trigger_RPCTriggerPrimitives_PrimitivePreprocess_h

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHit.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CondFormats/RPCObjects/interface/RPCMaskedStrips.h"
#include "CondFormats/RPCObjects/interface/RPCDeadStrips.h"
#include "CondFormats/DataRecord/interface/RPCMaskedStripsRcd.h"
#include "CondFormats/DataRecord/interface/RPCDeadStripsRcd.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"

#include "RecoLocalMuon/RPCRecHit/interface/RPCRecHitBaseAlgo.h"
#include "RecoLocalMuon/RPCRecHit/interface/RPCRecHitAlgoFactory.h"

#include "L1Trigger/RPCTriggerPrimitives/interface/RPCProcessor.h"


#include <string>
#include <fstream>

class PrimitivePreprocess{
  
 public:
  explicit PrimitivePreprocess(const edm::ParameterSet& iConfig, edm::ConsumesCollector&& iConsumes);
  ~PrimitivePreprocess();

  void beginRun(const edm::EventSetup& );
 
  void Preprocess(const edm::Event& iEvent, const edm::EventSetup& iSetup, RPCRecHitCollection& primitivedigi);
  

 private:
  
  const edm::EDGetTokenT<RPCDigiCollection> rpcToken_; 
  std::array<RPCProcessor, 1> processorvector_;
 
  edm::FileInPath Mapsource_;
  std::vector<RPCProcessor::Map_structure> Final_MapVector;
  std::vector<int> ClusterSizeCut_;
  std::vector<int> LinkBoardCut_;

  //masking from rpcrechit module

  enum class MaskSource { File, EventSetup } maskSource_, deadSource_;

  std::vector<RPCMaskedStrips::MaskItem> MaskVec;
  std::vector<RPCDeadStrips::DeadItem> DeadVec;

  std::unique_ptr<RPCMaskedStrips> theRPCMaskedStripsObj;
  // Object with mask-strips-vector for all the RPC Detectors
  
  std::unique_ptr<RPCDeadStrips> theRPCDeadStripsObj;
  // Object with dead-strips-vector for all the RPC Detectors

  // The reconstruction algorithm
  std::unique_ptr<RPCRecHitBaseAlgo> theAlgo;
};
#endif
