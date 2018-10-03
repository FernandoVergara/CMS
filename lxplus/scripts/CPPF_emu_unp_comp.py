#! /usr/bin/env python

from ROOT import *
gROOT.SetBatch(False)

def main():


    #Load input files (unpacker data)
    in_dir = './'
    in_file_name = in_dir+'testRPCCPPF.root'
    #eumlator events
    emu_dir = './'
    emu_file_name = emu_dir + 'emu_events.txt'
    

    emu_file = open(emu_file_name, "r")
    out_file = TFile('plots/CPPFOUT.root','recreate')

    in_tree_name = 'Events'
    in_file = TFile.Open(in_file_name)
    in_tree = in_file.Get(in_tree_name)

    
    theta_shift = {}
    phi_shift = {}
    not_agree = {}
    well_agree={}
    almost_agree={}
    theta_phi_shift = {}

    for SR in ['12', '22', '32', '33', '42', '43']: ## Station / ring number
        theta_shift[SR] = TH2D('theta_shift'+SR, 'Theta shift SR_'+SR, 36, 0.5, 36.5, 3, 0.5, 3.5)
        phi_shift[SR] = TH2D('phi_shift'+SR, 'Phi shift SR_'+SR, 36, 0.5, 36.5, 3, 0.5, 3.5)
        theta_phi_shift[SR] = TH2D('theta_phi_shift'+SR, 'Both Theta and Phi shift SR_'+SR, 36, 0.5, 36.5, 3, 0.5, 3.5)
        not_agree[SR] = TH2D('not_agree'+SR, 'Totally not agree SR_'+SR, 36, 0.5, 36.5, 3, 0.5, 3.5)
        well_agree[SR] = TH2D('well_agree'+SR, 'Well agree SR_'+SR, 36, 0.5, 36.5, 3, 0.5, 3.5)
        almost_agree[SR] = TH2D('almost_agree'+SR, 'Almost agree SR_'+SR, 36, 0.5, 36.5, 3, 0.5, 3.5)


    number = in_tree.GetEntries()
    #number = 10000
    good_num=0
    not_agree_num=0
    well_agree_num=0
    phi_shift_num=0
    theta_shift_num=0
    theta_phi_shift_num=0
    ievent_emu = 0
    ibad_region = 0
    iunpacker = 0
    for iEny in range(0,number):
        in_tree.GetEntry(iEny)
        Event = in_tree.EventAuxiliary   
        CPPFRPCDigi = in_tree.l1tCPPFDigis_rpcCPPFRawToDigi__testRPCCPPF
        nhits=CPPFRPCDigi.size()
        print 'iEny=%6d;nhits=%3d' % (iEny, nhits)
        iunpacker=iunpacker + nhits
        while 1:
            line = emu_file.readline()
            if not line: break
            # Please refer to the CPPFEMU.py to see the data format of input file.
	    # There are two cases: If the line[0:4] is the string of 'iEny', then line[5:11] is the value of 'iEny'.
	    # Else the line is for event data:
	    # line  [0:2]  [2:3]   [3:4]   [4:5]    [5:6]   [6:7]     [7:8]  [8:12]  [12:16]   
	    #      endcap  ring  station   section  layer  subsection  roll  theta     phi
            if(line[0:4]=="iEny"):
	        if(int(line[5:11]) == iEny): continue
		elif(int(line[5:11]) == (iEny+1)): break
		else:
		    break 
		    print "ERROR"
            elif(nhits==0):
		ievent_emu = ievent_emu + 1 
		sr_string=line[3:4]+line[2:3]
		if(sr_string=='12' or sr_string=='22' or sr_string=='32' or sr_string=='33' or sr_string=='42' or sr_string=='43'):
		    section_num = (int(line[4:5])-1) * 6 + int(line[6:7])
		    not_agree[sr_string].Fill(section_num, int(line[7:8]))
		    not_agree_num = not_agree_num + 1
		    print "6Not agree iEny=%d" % (iEny)
		else:
		    ibad_region=ibad_region+1
		    print "Error Region %s in iEny=%d" % (sr_string, iEny)
	    else:
		ievent_emu = ievent_emu + 1
		sr_string=line[3:4]+line[2:3]
                if(sr_string!='12' and sr_string!='22' and sr_string!='32' and sr_string!='33' and sr_string!='42' and sr_string!='43'):
		    print "Wrong region iEny=%d %s" % (iEny, sr_string)
		    ibad_region = ibad_region + 1 
		    continue

                for ihit in range(nhits):
                    hit = CPPFRPCDigi.at(ihit)
		    DetId = hit.rpcId()
                    region = DetId.region()
                    ring = DetId.ring()
                    station = DetId.station()
                    sector = DetId.sector()
                    layer = DetId.layer()
                    subsector = DetId.subsector()
                    roll = DetId.roll()
                    theta = hit.theta_int()
                    phi = hit.phi_int()
                    bx = hit.bx()
 
		    section_num=(int(line[4:5])-1)*6+subsector
		
		    # The rpcId in unpacker and emulator are equal. The roll is not considered because the unpcaker is unable to assign correct value for 'roll', and it always be '0'.
                    if((region==int(line[0:2])) and (ring==int(line[2:3])) and (station==int(line[3:4])) and (sector==int(line[4:5])) and (subsector==int(line[6:7]))):
			# When the theta and phi are the same then the hit is well agree
			if(theta==(int(line[8:12])) and phi==(int(line[12:16]))):
			    well_agree[sr_string].Fill(section_num, int(line[7:8]))
			    almost_agree[sr_string].Fill(section_num, int(line[7:8]))
			    well_agree_num = well_agree_num + 1
			    good_num = good_num + 1
			    break
			# This is for phi shift case
			elif(theta==(int(line[8:12])) and (abs(int(line[12:16])-phi)<=3)):
			    phi_shift[sr_string].Fill(section_num, int(line[7:8]))
			    almost_agree[sr_string].Fill(section_num, int(line[7:8]))
			    phi_shift_num=phi_shift_num+1
			    good_num=good_num + 1
			    print "Phi shift at iEny=%d theta=%d phi=%d phi_unp=%d" % (iEny,theta, phi, int(line[12:16]))
			    break
			else:
			    if(ihit==(nhits-1)):
				not_agree[sr_string].Fill(section_num, int(line[7:8]))
				not_agree_num=not_agree_num+1
				print "3Not agree iEny=%d" % (iEny)
				break
		    # This case is caused by an error of unpacker, the value of 'sector' in some unpacker events maybe 1 unit less than the emulator. 
                    elif((region==int(line[0:2])) and (ring==int(line[2:3])) and (station==int(line[3:4])) and (sector==int(line[4:5])+1) and (subsector==int(line[6:7]))):
			if(phi==int(line[12:16]) and theta==int(line[8:12])) :
			    well_agree[sr_string].Fill(section_num, int(line[7:8]))
			    almost_agree[sr_string].Fill(section_num, int(line[7:8]))
			    well_agree_num=well_agree_num + 1
			    good_num = good_num + 1
			    break
			elif(theta==(int(line[8:12])) and (abs(int(line[12:16])-phi)<=3)):
			    phi_shift[sr_string].Fill(section_num, int(line[7:8]))
			    almost_agree[sr_string].Fill(section_num, int(line[7:8]))
			    phi_shift_num = phi_shift_num + 1
			    good_num = good_num + 1
			    print "Phi shift at iEny=%d theta=%d phi=%d phi_unp=%d" % (iEny,theta, phi, int(line[12:16]))
			    break
			else: 
			    if(ihit==(nhits-1)):
				not_agree[sr_string].Fill(section_num, int(line[7:8]))
				not_agree[sr_string].Fill(section_num, int(line[7:8]))
				not_agree_num=not_agree_num+1
				print "2Not agree iEny=%d" %(iEny)
				break
			    else: continue
                    else:
		        if(ihit==(nhits-1)): 
			    not_agree[sr_string].Fill(section_num, int(line[7:8]))
			    not_agree_num = not_agree_num + 1
			    print "1Not agree iEny=%d" % (iEny)
			    break
		        else: continue
                

    print "good_num=%d" % (good_num)
    print "not_agree_num=%d" % (not_agree_num)
    print "well_agree_num=%d" % (well_agree_num)
    print "phi_shift_num=%d" % (phi_shift_num)
    print "theta_shift_num=%d" % (theta_shift_num)
    print "theta_phi_shift_num=%d" % (theta_phi_shift_num)
    print "ievent_emu=%d" % (ievent_emu)
    print "ibad_region=%d" % (ibad_region)
    print "iunpacker=%d" % (iunpacker)
    out_file.cd()

    for SR in ['12', '22', '32', '33', '42', '43']:
        theta_shift[SR].GetXaxis().SetTitle('Section')
        theta_shift[SR].GetYaxis().SetTitle('Roll')
        theta_shift[SR].Write()

        phi_shift[SR].GetXaxis().SetTitle('Section')
        phi_shift[SR].GetYaxis().SetTitle('Roll')
        phi_shift[SR].Write()

        theta_phi_shift[SR].GetXaxis().SetTitle('Section')
        theta_phi_shift[SR].GetYaxis().SetTitle('Roll')
        theta_phi_shift[SR].Write()

        not_agree[SR].GetXaxis().SetTitle('Section')
        not_agree[SR].GetYaxis().SetTitle('Roll')
        not_agree[SR].Write()

        well_agree[SR].GetXaxis().SetTitle('Section')
        well_agree[SR].GetYaxis().SetTitle('Roll')
        well_agree[SR].Write()

        almost_agree[SR].GetXaxis().SetTitle('Section')
        almost_agree[SR].GetYaxis().SetTitle('Roll')
        almost_agree[SR].Write()

    out_file.Close()

    del in_tree
    in_file.Close()

if __name__ == '__main__':
    main()

