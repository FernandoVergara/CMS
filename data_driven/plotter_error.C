#include <TLegend.h> 
vector<string> input;
vector<string> Cuts;
vector<string> Histo;
vector<string> label_;

TCanvas *c1;
TPad *pad1;
TPad *pad2; 
TGraphAsymmErrors *gr1;
TLegend *legend;
TFile *Tf[4];
TF1 *FIT;
TH1D *Histos_[3];
TH1D *Clones_[3];

void fill(){
input.push_back("Final/CR1/QCD");
input.push_back("Final/CR2/QCD");
Cuts.push_back("NRecoTau1");
Cuts.push_back("METCut");
Histo.push_back("Tau1MetMt");
label_.push_back("CR1 (#tau isolation)");
label_.push_back("CR2 (Fail #tau isolation)");
}


void plotter_error(){
fill();

for(int i = 0; i < input.size(); i++){
TFile *g = TFile::Open((input[i]+".root").c_str(),"READ");
Tf[i] = g;
} 


/*
for(int j = 0; j < input.size(); j++){
    TH1F* h;
    h = (TH1F*)Tf[j]->Get((Cuts[0]+"/"+Histo[0]).c_str());  
    
    Histos_[j] = h; 
}
*/
  TH1D* h1 = (TH1D*)Tf[0]->Get((Cuts[0]+"/"+Histo[0]).c_str()); 
  h1->Sumw2();
  TH1D* h2 = (TH1D*)Tf[1]->Get((Cuts[1]+"/"+Histo[0]).c_str()); 
  h2->Sumw2();

 int nb = 9;
 float BINS[10] = {70.0, 80.0, 90.0, 100.0, 120.0, 140.0, 160.0, 180.0, 200.0, 500.};  
 

  Histos_[0] = new TH1D("h1", "h1", nb, BINS);;
  Histos_[1] = new TH1D("h2", "h2", nb, BINS);;

  

  Int_t old_nbins = h1->GetXaxis()->GetNbins(); 
 Int_t new_nbins = Histos_[0]->GetXaxis()->GetNbins();
 
 for (int b = 1; b <= new_nbins; b++ ){
  Double_t Right_edge_new = Histos_[0]->GetXaxis()->GetBinLowEdge(b)+Histos_[0]->GetXaxis()->GetBinWidth(b);
  Double_t Edge_new = Histos_[0]->GetXaxis()->GetBinLowEdge(b);
  Double_t Num_back = 0.;
  Double_t error = 0.; 
 
  cout << Edge_new << " "<< Right_edge_new << " ------------------- " <<endl;
  for (int i = 1; i <= old_nbins; i++ ){
  Double_t Right_edge_old = h1->GetXaxis()->GetBinLowEdge(i)+h1->GetXaxis()->GetBinWidth(i);

  if(Right_edge_old <= Right_edge_new && Right_edge_old > Edge_new){
  cout << Right_edge_new << " " << Right_edge_old <<endl;
  Num_back += h1->GetBinContent(i);
  error += h1->GetBinError(i);
  
  }
  else continue;

  Histos_[0]->SetBinContent(b, Num_back);
  Histos_[0]->SetBinError(b, error);
 
  } // loop over the old hist
 } // loop over the new hist
 
 TRandom *r1       = new TRandom();
   Int_t old_nbins_ = h2->GetXaxis()->GetNbins(); 
 Int_t new_nbins_ = Histos_[1]->GetXaxis()->GetNbins();
 
 for (int b = 1; b <= new_nbins_; b++ ){
  Double_t Right_edge_new = Histos_[1]->GetXaxis()->GetBinLowEdge(b)+Histos_[1]->GetXaxis()->GetBinWidth(b);
  Double_t Edge_new = Histos_[1]->GetXaxis()->GetBinLowEdge(b);
  Double_t Num_back = 0.;
  Double_t Num_back_1 = 0.;
  Double_t error = 0.;

  cout << Edge_new << " "<< Right_edge_new << " ------------------- " <<endl;
  for (int i = 1; i <= old_nbins_; i++ ){
  Double_t Right_edge_old = h2->GetXaxis()->GetBinLowEdge(i)+h2->GetXaxis()->GetBinWidth(i);

  if(Right_edge_old <= Right_edge_new && Right_edge_old > Edge_new){
  cout << Right_edge_new << " " << Right_edge_old <<endl;
  Num_back += h2->GetBinContent(i);
  error += h2->GetBinError(i);
  
  }
  else continue;

  Histos_[1]->SetBinContent(b, Num_back);
  Histos_[1]->SetBinError(b, error);
  } // loop over the old hist
 } // loop over the new hist




//   Histos_[0] = h1;
//  Histos_[1] = h2;



  c1 = new TCanvas("c1","QCD", 100,100,500,500 ); 
  legend = new TLegend(0.70,0.70,0.9,0.9, NULL,"brNDC");

   gStyle->SetOptFit(1011); 

  pad1 = new TPad("pad1", "pad1",0.01,0.33,0.99,0.99);
  pad1->Draw();
  pad2 = new TPad("pad2", "pad2",0.01,0.0,0.99,0.32);
  pad2->Draw();

  
  pad1->cd();

  for(int j = 0; j < input.size(); j++){
//  Histos_[j]->Sumw2();
  //Histos_[j]->Rebin(2);
  Histos_[j]->SetTitle("");
  Histos_[j]->SetLineColor(j+1);
  Histos_[j]->SetMarkerColor(j+1);
  Histos_[j]->SetLineWidth(2);
//  Histos_[j]->SetStats(kFALSE);
  Histos_[j]->GetXaxis()->SetTitle("m_{T}(#tau, E_{T}^{miss})");
  Histos_[j]->GetXaxis()->SetRangeUser(60.,500.);

  Histos_[j]->GetYaxis()->SetTitle("Events");
  Histos_[j]->GetYaxis()->SetTitleSize(0.05);

  double integral = Histos_[j]->Integral();
  Histos_[j]->Scale(1.0/integral);  


  Clones_[j] = (TH1D*)Histos_[j]->Clone(); 

 
  Histos_[j]->GetYaxis()->SetTitle("a.u.");
 
  
  cout << Histos_[j]->Integral() << " " << Histos_[j]->GetBinContent(10)  << " " << Histos_[j]->GetBinError(10) << endl;
 
  
 if(j==0) Histos_[j]->Draw();
  else Histos_[j]->Draw("same");  

  //Legend
  TLegendEntry *entry=legend->AddEntry("Histos_[j]",label_[j].c_str(),"lpf");
  entry->SetLineColor(j+1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(2);
  entry->SetMarkerColor(j+1);
  entry->SetMarkerStyle(21);

  
  
  }

  legend->Draw();


  
  pad2->cd();

  TLine *line = new TLine(60,1,500,1);
  line->SetLineColor(kRed);
  line->SetLineWidth(2);
  line->SetLineStyle(2);
 

  Clones_[0]->Divide(Clones_[1]);
  double value = Clones_[0]->GetBinContent(10); 
  double lowedge = Clones_[0]->GetXaxis()->GetBinLowEdge(10);
  double error = Clones_[0]->GetBinError(10);
  cout << value << " " << error << " " << lowedge <<endl;
  Clones_[0]->SetTitle("");
 
  Clones_[0]->GetXaxis()->SetLabelSize(0.08);
  Clones_[0]->GetXaxis()->SetTitle("");
  Clones_[0]->GetYaxis()->SetLabelSize(0.08);
  Clones_[0]->GetYaxis()->SetTitle("CR1/CR2");
  Clones_[0]->GetYaxis()->SetTitleSize(0.1);
  Clones_[0]->GetYaxis()->SetTitleOffset(0.35);
  
  //Clones_[0]->Draw("hist");
  Clones_[0]->Draw();
  line->Draw("L same");
  
  FIT = new TF1("FIT","[1]*x+[0]", 70, 300);
  FIT->SetParName(0,"b");
  FIT->SetParName(1,"m");
  FIT->SetLineColor(4);
 
 /*
  FIT->SetParameter(0, 0);
  FIT->SetParameter(1, 1);
   */
  
  Clones_[0]->Fit("FIT");
  
  

}


int main(){
plotter_error();
return 0;
}
