#include <TLegend.h> 
vector<string> input;
vector<string> Cuts;
vector<string> Histo;
vector<string> label_;

TCanvas *c1;
TLegend *legend;
TFile *Tf[4];
TH1D *Histos_[3];


  Double_t* mcX;
  Double_t* mcY;
  Double_t* mcErrorX;
  Double_t* mcErrorY;

void fill(){
//input.push_back("CR2/QCD");
//input.push_back("Final/CR2/QCD");

input.push_back("W_tight/met_30/W+Jets");
input.push_back("W_loose/met_30/W+Jets");

//input.push_back("Z_tight/met_30/DY+Jets");
//input.push_back("Z_loose/met_30/DY+Jets");

//input.push_back("Final/Z_tight/new/DY+Jets");
//input.push_back("Final/Z_loose/new/DY+Jets");

//input.push_back("Z_tight/DY+Jets");
//input.push_back("Z_loose/DY+Jets");


//Cuts.push_back("NRecoTau1");
Cuts.push_back("METCut");
//Cuts.push_back("NRecoFirstLeadingJet");

//Histo.push_back("Tau1MetMt");
 Histo.push_back("Tau1Pt");
//Histo.push_back("Muon1Tau1ReconstructableMass");

}

void printvalues(UInt_t bins){

 for (UInt_t i = 0; i < bins; i++){
 if(mcY[i] < 0.0001) continue;
 cout << mcY[i] << " "  << mcErrorY[i] << endl;  
 }
 cout << "Errors: "<< endl; 
 for (UInt_t i = 0; i < bins; i++){
 if(mcY[i] < 0.0001) continue;
 cout << mcErrorY[i] << endl;  
 }

  
}


TGraphErrors* CreateERROR(TH1D *h1, TH1D *h2, Double_t weight){
  
  TH1D *H1 = (TH1D*)h1->Clone();
  TH1D *H2 = (TH1D*)h2->Clone();
  
 
  
  TGraphErrors *McError; 

  UInt_t bins = H1->GetXaxis()->GetNbins();
 

  mcX = new Double_t[bins];
  mcY = new Double_t[bins];
  mcErrorX = new Double_t[bins];
  mcErrorY = new Double_t[bins];
  
  H1->Divide(h2); 

  cout << bins << endl;
  for (UInt_t i = 0; i < bins; i++){
    
    if(H1->GetBinContent(i+1) == 0.) continue;
   
    mcY[i] = H1->GetBinContent(i+1)*weight;
    cout << H1->GetBinContent(i+1) << endl;
    mcErrorY[i] = H1->GetBinError(i+1);
    mcX[i] = H2->GetBinCenter(i+1);
    mcErrorX[i] = H2->GetBinWidth(i+1) * 0.5;

  }

  printvalues(bins); 


  McError = new TGraphErrors(bins,mcX,mcY,mcErrorX,mcErrorY);
  McError->SetLineWidth(2);
  McError->SetFillColor(1);
  McError->SetFillStyle(3004);
  McError->SetFillColor(kRed+2);
  // McError->SetFillColor(kMagenta+1);
 
  delete mcX;
  delete mcY;
  delete mcErrorX;
  delete mcErrorY;

  return McError;
}




void integral_1(){
fill();

gStyle->SetOptFit(1111);

for(int i = 0; i < input.size(); i++){
TFile *g = TFile::Open((input[i]+".root").c_str(),"READ");
Tf[i] = g;
} 



for(int j = 0; j < input.size(); j++){
    TH1D* h;
    h = (TH1D*)Tf[j]->Get((Cuts[0]+"/"+Histo[0]).c_str());  
    h->Sumw2();
    Histos_[j] = h; 
}
   for(int j = 0; j < input.size(); j++){
   Histos_[j]->SetTitle("");
   Histos_[j]->SetLineColor(1);
   Histos_[j]->SetLineWidth(2);
   Histos_[j]->SetMarkerSize(1.5);
   Histos_[j]->SetMarkerStyle(20);
   Histos_[j]->SetMarkerColor(2);
   Histos_[j]->GetXaxis()->SetRangeUser(20.,40.);
   Histos_[j]->GetXaxis()->SetRange(20.,40.);
   }
    
    
   TGraphErrors* gr1 = CreateERROR(Histos_[0], Histos_[1], 0.95); 
   
    gr1->SetTitle("");
 
    gr1->GetXaxis()->SetLabelOffset(0.005);
    gr1->GetXaxis()->SetLabelSize(0.05);
    gr1->GetXaxis()->SetTitleOffset(1.0);
    gr1->GetXaxis()->SetTitleSize(0.05);

    gr1->GetXaxis()->SetTitle("p_{T}(#tau_{h}) [Gev]");
 
    gr1->GetXaxis()->SetRangeUser(20.,40.);
   
    gr1->GetYaxis()->SetLabelOffset(0.005);
    gr1->GetYaxis()->SetLabelSize(0.05);
    gr1->GetYaxis()->SetTitleOffset(1.0);
    gr1->GetYaxis()->SetTitleSize(0.05);

    gr1->GetYaxis()->SetTitle("Ratio_{Loose}^{Tight}/Bin");

    gr1->SetMarkerStyle(20);
    gr1->SetMarkerSize(2);
    gr1->SetMarkerColor(2);
    gr1->Draw("AP");

     TF1 *FIT = new TF1("FIT","[1]*(x-20.)+[0]", 20, 40);
     FIT->SetParName(0,"b");
     FIT->SetParName(1,"m");
     FIT->SetLineColor(4);
     gr1->Fit("FIT");

     
 
}


int main(){
integral_1();
return 0;
}
