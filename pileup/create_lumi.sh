#!/bin/bash

Data[0]="MET"
Data[1]="SingleMuon"
Data[2]="Tau"

for data in `seq 0 2` ;
do
mkdir -p ${Data[$data]}
echo ${Data[$data]} 

   typeset -i i=0
   for x in `cat ../${Data[$data]}.txt` ; do
	echo working $x ...
        das_client --query="run, lumi, dataset=$x" > ${Data[$data]}/lumis_$i &
        i=$i+1 
      #  echo $i 
        wait	
	done

done

