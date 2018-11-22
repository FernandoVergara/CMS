#!/bin/bash

Data[0]="MET"
Data[1]="SingleMuon"
Data[2]="Tau"

CERTIFICATE=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt

for data in `seq 0 2` ;
do
echo ${Data[$data]} 
 
   cd ${Data[$data]}   
   ls lumis_* > files.dat
   mkdir -p json
   typeset -i i=0
   for x in `cat files.dat` ; do
	echo working $x ...
        python ../txt2json.py $x
        echo txt2json done ...
	wait
        compareJSON.py --and json/$x.json $CERTIFICATE json/final_$x.json
        wait	
	done
  rm files.dat
  cd ..
done

