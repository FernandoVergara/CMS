#!/bin/bash

Data[0]="MET"
Data[1]="SingleMuon"
Data[2]="Tau"

PILEUPJSON=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PileUp/pileup_latest.txt

for data in `seq 0 2` ;
do
echo ${Data[$data]} 


   cd ${Data[$data]}
   mkdir -p Results
   ls json/final_* > files.dat
   typeset -i i=0
   for x in `cat files.dat` ; do
	echo working $x ...
        pileupCalc.py -i $x --inputLumiJSON $PILEUPJSON --calcMode true --minBiasXsec 69200 --maxPileupBin 75 --numPileupBins 75 Results/PileupData_2017_$i.root
	i=$i+1
        wait	
	done
   rm files.dat
   cd ..

done

