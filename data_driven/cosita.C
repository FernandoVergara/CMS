#include <TLegend.h> 
vector<string> input;
vector<string> Cuts;
vector<string> Histo;
vector<string> label_;

TCanvas *c1;
TLegend *legend;
TFile *Tf[6];
TH1D *Histos_[3];

void fill(){
input.push_back("allData");
input.push_back("DY+Jets");
input.push_back("QCD");
input.push_back("tt");
input.push_back("VV");
input.push_back("W+Jets");

Cuts.push_back("METCut");
Histo.push_back("Dphi1");

//Cuts.push_back("NMuon1Tau1Combinations");
//Histo.push_back("Muon1Tau1ReconstructableMass");
}


void cosita(){
fill();

//string folder = "CR_Zloose/";
string folder = "Last_CR_noiso/";

for(int i = 0; i < input.size(); i++){
TFile *g = TFile::Open((folder+input[i]+".root").c_str(),"READ");
Tf[i] = g;
} 



for(int j = 0; j < input.size(); j++){
    TH1D* h;
    h = (TH1D*)Tf[j]->Get((Cuts[0]+"/"+Histo[0]).c_str());  
    h->Sumw2();
    Histos_[j] = h; 
}



  for(int j = 0; j < input.size(); j++){
  double integral = Histos_[j]->Integral();
  cout << integral << endl; 
  
  } 

  
  
  
}


int main(){
cosita();
return 0;
}
