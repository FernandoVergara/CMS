#include <TLegend.h> 
vector<string> input;
vector<string> Cuts;
vector<string> Histo;
vector<string> label_;

TCanvas *c1;
TLegend *legend;
TFile *Tf[4];
TFile *OUTPUT[4];
TH1F *Histos_[3];

void fill(){
input.push_back("Final/Last_CR/QCD");
Cuts.push_back("METCut");
Histo.push_back("Tau1MetMt");
label_.push_back("CR1 (#tau isolation)");
label_.push_back("CR2 (Fail #tau isolation)");
}


void qcd_creator(){
fill();

for(int i = 0; i < input.size(); i++){
TFile *g = TFile::Open((input[i]+".root").c_str(),"READ");
Tf[i] = g;
} 

OUTPUT[0] = new TFile("QCD_SR.root", "RECREATE");;


for(int j = 0; j < input.size(); j++){
    TH1F* h;
    h = (TH1F*)Tf[j]->Get((Cuts[0]+"/"+Histo[0]).c_str());  
    h->Sumw2();
    Histos_[j] = h; 
}


  c1 = new TCanvas("c1","QCD", 100,100,500,500 ); 
  legend = new TLegend(0.70,0.70,0.9,0.9, NULL,"brNDC");

  for(int j = 0; j < input.size(); j++){
  Histos_[j]->Rebin(2);
  Histos_[j]->SetTitle("");
  Histos_[j]->SetLineColor(j+1);
  Histos_[j]->SetMarkerColor(j+1);
  Histos_[j]->SetLineWidth(2);
  Histos_[j]->SetStats(kFALSE);
  Histos_[j]->GetXaxis()->SetTitle("m_{T}(#tau, E_{T}^{miss})");
  Histos_[j]->GetXaxis()->SetRangeUser(0.,300.);

  Histos_[j]->GetYaxis()->SetTitle("Events");

  double integral = Histos_[j]->Integral();
  Histos_[j]->Scale(1467./integral);  

 // Histos_[j]->GetYaxis()->SetTitle("a.u.");
 // Histos_[j]->GetYaxis()->SetRangeUser(0.,200.);
  
  cout << Histos_[j]->Integral() << endl;
 
  if(j==0) Histos_[j]->Draw();
  else Histos_[j]->Draw("same");  

  //Legend
  TLegendEntry *entry=legend->AddEntry("Histos_[j]",label_[j].c_str(),"lpf");
  entry->SetLineColor(j+1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(2);
  entry->SetMarkerColor(j+1);
  entry->SetMarkerStyle(21);

  OUTPUT[0]->cd();
  Histos_[j]->Write();
  OUTPUT[0]->Close();
  
  }
  legend->Draw();


}


int main(){
qcd_creator();
return 0;
}
