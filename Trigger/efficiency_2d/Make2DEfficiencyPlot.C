#include "TAxis.h"
#include <iomanip>
void Make2DEfficiencyPlot(){
   
  TCanvas *c = new TCanvas("c", "", 81,58,500,602);
   c->cd();
  
  TFile* f_n = new TFile("data/Data_muisnotnu.root");
  f_n->cd("NRecoTriggers2");  
  TH2D* DiJetMass_n = JetPtVsMET;

  TFile* f_d = new TFile("data/Data_muisnotnu.root");  
  f_d->cd("METCut");
  TH2D* DiJetMass_d = JetPtVsMET;
  
  double xbins[14]={0, 50, 100, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000};
  double ybins[28]={10, 20, 30 , 40, 50,  60,  70,  80,   90,   100,  110,  120,
  130,  140,  150,  160,  170,  180,  190,  200,  210,  220,  230, 240,   250,
  300, 350, 400};
 // TH2F *h_n = new TH2F("h_n",DiJetMass_n->GetTitle(),13,xbins,26,ybins);
  TH2F *h_n = new TH2F("h_n",DiJetMass_n->GetTitle(),100,0,1000,30,0,300); 

//  TH2F *h_d = new TH2F("h_d",DiJetMass_d->GetTitle(),13,xbins,26,ybins);
  TH2F *h_d = new TH2F("h_d",DiJetMass_d->GetTitle(),100,0,1000,30,0,300);
  TAxis* xnaxis = DiJetMass_n->GetXaxis();
  TAxis* ynaxis = DiJetMass_d->GetYaxis();  
 
  
  for (int j=1; j<=ynaxis->GetNbins();j++) {
    for (int i=1; i<=xnaxis->GetNbins();i++) {
      h_n->Fill(xnaxis->GetBinCenter(i),ynaxis->GetBinCenter(j),DiJetMass_n->GetBinContent(i,j));
      h_d->Fill(xnaxis->GetBinCenter(i),ynaxis->GetBinCenter(j),DiJetMass_d->GetBinContent(i,j));    
   }
  }
  
  gStyle->SetPaintTextFormat("4.2f");
  h_n->Divide(h_d);
  h_n->GetXaxis()->SetTitle("p_{T}(leading jet) [GeV]");
  h_n->GetXaxis()->SetLabelFont(42);
  h_n->GetXaxis()->SetLabelSize(0.035);
  h_n->GetXaxis()->SetTitleSize(0.05);
  h_n->GetXaxis()->SetTitleOffset(0.9);
  h_n->GetXaxis()->SetTitleFont(42);
  h_n->GetYaxis()->SetTitle("E^{miss}_{T} [GeV]");
  h_n->GetYaxis()->SetLabelFont(42);
  h_n->GetYaxis()->SetLabelSize(0.03);
  h_n->GetYaxis()->SetTitleSize(0.035);
  h_n->GetYaxis()->SetTitleOffset(1.37);
  h_n->GetYaxis()->SetTitleFont(42);
  h_n->GetZaxis()->SetLabelFont(42);
  h_n->GetZaxis()->SetLabelSize(0.035);
  h_n->SetMarkerSize(0.8);
  h_n->GetZaxis()->SetTitleSize(0.035);
  h_n->GetZaxis()->SetTitleFont(42);
  h_n->SetStats(kFALSE);
  h_n->Draw("COLTEXTZ") ;  
}
