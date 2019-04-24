import FWCore.ParameterSet.Config as cms

primitiveRPCProducer = cms.EDProducer("L1TMuonRPCTriggerPrimitivesProducer",
				Primitiverechitlabel = cms.InputTag("rpcdigis"),		
				Mapsource = cms.string('L1Trigger/RPCTriggerPrimitives/input/Linkboard_rpc_roll_mapping_lb_chamber2.txt'),
			        LinkBoardCut = cms.vint32(2), # Number of clusters per linkboard greater than (default >2) are rejected
			        ClusterSizeCut = cms.vint32(3), # Clustersize greater than (default >3) is rejected 
				maskSource = cms.string('File'),
    				maskvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCMaskVec.dat'),
    				deadSource = cms.string('File'),
				deadvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCDeadVec.dat'),
				recAlgoConfig = cms.PSet(),
				recAlgo = cms.string('RPCRecHitStandardAlgo')	
)
