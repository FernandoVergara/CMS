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
input.push_back("QCD");

Cuts.push_back("METCut");
Histo.push_back("Tau1MetMt");

//Cuts.push_back("NMuon1Tau1Combinations");
//Histo.push_back("Muon1Tau1ReconstructableMass");
}


void scale_(){
fill();

//string folder = "CR_Zloose/";
string folder = "Final/Last_CR_noiso/";
gSystem->mkdir("QCD", kTRUE);
const TString cmd = "cp "+folder+input[0]+".root"+" "+"QCD/QCD.root"; 
gSystem->Exec(cmd);

for(int i = 0; i < input.size(); i++){
TFile *g = TFile::Open("QCD/QCD.root","UPDATE");
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
  Histos_[j]->Scale(0.08);
  cout << "New integral: " <<  Histos_[j]->Integral() << endl;	
  
  } 

  for(int i = 0; i < input.size(); i++){
  Tf[i]->Write("",TObject::kOverwrite);
  Tf[i]->Close();
  }
}


int main(){
scale_();
return 0;
}
