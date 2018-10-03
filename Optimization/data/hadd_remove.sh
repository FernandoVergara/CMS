# -------------------------------------------------
# -------     Universidad de los Andes      -------
# -------      Departamento de Física       -------
# -------     Manuel Alejandro Segura D     -------
# -------          Abril 2017               -------
# -------------------------------------------------

#--------------------------------------------------------------
#Directories 
#--------------------------------------------------------------

DATAFOLDER="/uscms_data/d3/msegura/Analyzer/CMSSW_8_0_10/src/optimization/data/JetPt"
VARIABLE="Pt_"

typeset -i start_cut=160
typeset -i end_cut=200
typeset -i delta=10

for ((i=$start_cut;i<=$end_cut;i=i+$delta))
do

echo RUNNING ---------------- Jet $i --------------------


cd $DATAFOLDER/$VARIABLE$i
pwd

echo -------------- Starting DY+jets process -----------------------------
rm DYJetsToLL_M-50_HT-100To200.root DYJetsToLL_M-50_HT-200To400.root DYJetsToLL_M-50_HT-400To600.root  
echo -------------- Starting W+jets process -----------------------------
rm WJetsToLNu_HT-0To70.root  WJetsToLNu_HT-100To200.root WJetsToLNu_HT-200To400.root WJetsToLNu_HT-400To600.root WJetsToLNu_HT-600To800.root  WJetsToLNu_HT-800To1200.root WJetsToLNu_HT-1200To2500.root WJetsToLNu_HT-2500ToInf.root
cd -

echo FINISH ---------------- Jet $i --------------------

done
