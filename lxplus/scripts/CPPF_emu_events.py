#! /usr/bin/env python

from ROOT import *
gROOT.SetBatch(False)

def main():


    ################################
    #####   Load input files   #####
    ################################

    in_dir = './'
    in_file_name = in_dir + 'test_cppf_emulator.root'
    out_dir = './'
    out_file_name = out_dir + 'emu_events.txt'

    in_tree_name = 'Events'

    in_file = TFile.Open(in_file_name)
    in_tree = in_file.Get(in_tree_name)
    
    out_file = open(out_file_name,'w')

    #Event = in_tree.EventAuxiliary    #RPCDetIdRPCDigiMuonDigiCollection_RPCCPPFRawToDigi__testRPCCPPF#RPCCPPFDigis_RPCCPPFRawToDigi__testRPCCPPF

    #Product = in_tree.EventProductProvenance
    number=in_tree.GetEntries()
    #number = 10000
    for iEny in range(0,number):
        in_tree.GetEntry(iEny)
        CPPFDigi = in_tree.l1tCPPFDigis_emulatorCppfDigis_recHit_DIGI#in_tree.RPCAMCLinkCounters_RPCCPPFRawToDigi__testRPCCPPF
        #CPPFRPCDigi = in_tree.l1tCPPFDigis_simCppfDigis_recHit_DIGI
        nhits=CPPFDigi.size()
        print >>out_file, 'iEny=%6d  nhits=%d' % (iEny, nhits)
        icount=0
        for ihit in range(nhits):
            hit = CPPFDigi.at(ihit)
            #rpcId = hit.RPCId()
            rpcId = hit.rpcId()
	    if(hit.bx() != 0): continue
	    if(icount==0): rpcId_last = rpcId
	    if(icount !=0 and rpcId == rpcId_last): continue
	    rpcId_last = rpcId
	    icount = icount + 1
            print >> out_file, '%2d%d%d%d%d%d%d%4d%4d' % (rpcId.region(),rpcId.ring(),rpcId.station(),rpcId.sector(),rpcId.layer(),rpcId.subsector(),rpcId.roll(),hit.theta_int(), hit.phi_int()) 
    #out_file.Close()
    del in_tree
    out_file.close()
    in_file.Close()

if __name__ == '__main__':
    main()

