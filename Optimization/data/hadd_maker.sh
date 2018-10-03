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

typeset -i start_cut=150
typeset -i end_cut=160
typeset -i delta=10

for ((i=$start_cut;i<=$end_cut;i=i+$delta))
do

echo RUNNING ---------------- Jet $i --------------------


cd $DATAFOLDER/$VARIABLE$i
pwd

echo -------------- Starting DY+jets process -----------------------------
hadd DYJetsToLL_M-50_HT-100To200.root DYJetsToLL_M-50_HT-100To200_ext1-v1_RunIISummer16MiniAODv2.root DYJetsToLL_M-50_HT-100To200_v1_RunIISummer16MiniAODv2.root
hadd DYJetsToLL_M-50_HT-200To400.root DYJetsToLL_M-50_HT-200To400_ext1-v1_RunIISummer16MiniAODv2.root DYJetsToLL_M-50_HT-200To400_v1_RunIISummer16MiniAODv2.root
hadd  DYJetsToLL_M-50_HT-400To600.root  DYJetsToLL_M-50_HT-400To600_ext1-v1_RunIISummer16MiniAODv2.root DYJetsToLL_M-50_HT-400To600_v1_RunIISummer16MiniAODv2.root
echo -------------- Starting W+jets process -----------------------------
hadd WJetsToLNu_HT-0To70.root WJetsToLNu_HT-0To70_ext2-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-0To70_v1_RunIISummer16MiniAODv2.root
hadd WJetsToLNu_HT-100To200.root WJetsToLNu_HT-100To200_ext1-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-100To200_ext2-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-100To200_v1_RunIISummer16MiniAODv2.root
hadd WJetsToLNu_HT-200To400.root WJetsToLNu_HT-200To400_ext1-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-200To400_ext2-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-200To400_v1_RunIISummer16MiniAODv2.root
hadd WJetsToLNu_HT-400To600.root WJetsToLNu_HT-400To600_ext1-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-400To600_v1_RunIISummer16MiniAODv2.root
hadd WJetsToLNu_HT-600To800.root WJetsToLNu_HT-600To800_ext1-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-600To800_v1_RunIISummer16MiniAODv2.root
hadd WJetsToLNu_HT-800To1200.root WJetsToLNu_HT-800To1200_ext1-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-800To1200_v1_RunIISummer16MiniAODv2.root
hadd WJetsToLNu_HT-1200To2500.root WJetsToLNu_HT-1200To2500_ext1-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-1200To2500_v1_RunIISummer16MiniAODv2.root
hadd WJetsToLNu_HT-2500ToInf.root WJetsToLNu_HT-2500ToInf_ext1-v1_RunIISummer16MiniAODv2.root WJetsToLNu_HT-2500ToInf_v1_RunIISummer16MiniAODv2.root

cd -

echo FINISH ---------------- Jet $i --------------------

done
