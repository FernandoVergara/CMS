import FWCore.ParameterSet.Config as cms

primitiveRPCProducer = cms.EDProducer("L1TMuonRPCTriggerPrimitivesProducer",
				Primitiverechitlabel = cms.InputTag("rpcdigis"),		
				Mapsource = cms.string('L1Trigger/RPCTriggerPrimitives/input/Linkboard_rpc_roll_mapping_lb_chamber2.txt'),
				ClusterSizeCut = cms.vint32(3),
			        LinkBoardCut = cms.vint32(2),
				maskSource = cms.string('File'),
    				maskvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCMaskVec.dat'),
    				deadSource = cms.string('File'),
				deadvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCDeadVec.dat'),
				recAlgoConfig = cms.PSet(),
				recAlgo = cms.string('RPCRecHitStandardAlgo')	
)
