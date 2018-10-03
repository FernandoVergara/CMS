#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TTreePlayer.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TEfficiency.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>

#include <vector>
#include "math.h"

#include <TMultiGraph.h>

using namespace std;

vector<string> in_put; 
vector<string> folder;
std::vector<string> Histo;


void fill(){
  
  in_put.push_back("WJetsToLNu_HT-800To1200.root");
   
  folder.push_back("NRecoTriggers1"); 
/*
  folder.push_back("WJetsToLNu_HT-100To200");
  folder.push_back("WJetsToLNu_HT-200To400");
  folder.push_back("WJetsToLNu_HT-400To600");
  folder.push_back("WJetsToLNu_HT-600To800");
  folder.push_back("WJetsToLNu_HT-800To1200");
  folder.push_back("WJetsToLNu_HT-1200To2500");
  folder.push_back("WJetsToLNu_HT-2500ToInf"); 
  */
//  Histo.push_back("GenTauFraction");
//  Histo.push_back("GenTauResolution");
  Histo.push_back("GenTauResolutionR1");
  Histo.push_back("GenTauResolutionR2");
Histo.push_back("GenTauResolutionR3");
Histo.push_back("GenTauResolutionR4");
Histo.push_back("GenTauResolutionR5");
Histo.push_back("GenTauResolutionR6");
Histo.push_back("GenTauResolutionR7");
  
//  Histo.push_back("GenTauIDRecoPt");
//  Histo.push_back("GenTauIDPt");
//  Histo.push_back("GenTauMatchedPt");
//  Histo.push_back("GenHadTauPt"); 
  

}


void plot_1(){

  cout << "working" << endl;
  fill();


  TCanvas *c1 = new TCanvas("c1", "c1",245,158,756,727);
  c1->Range(-20.38653,-0.005764521,153.3666,0.04198848);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetLeftMargin(0.1173305);
  c1->SetRightMargin(0.01937567);
  c1->SetTopMargin(0.01937407);
  c1->SetBottomMargin(0.1207154);
  c1->SetFrameBorderMode(0);
  c1->SetFrameBorderMode(0);

   TFile* file1 = TFile::Open(in_put[0].c_str(), "READ");
   
  
  for (int i = 0 ; i < 1; i++ ){
   TH1F *h0 = (TH1F*)file1->Get((folder[0]+"/"+Histo[0]).c_str());
   TH1F *h1 = (TH1F*)file1->Get((folder[0]+"/"+Histo[1]).c_str());
   TH1F *h2 = (TH1F*)file1->Get((folder[0]+"/"+Histo[2]).c_str());
   TH1F *h3 = (TH1F*)file1->Get((folder[0]+"/"+Histo[3]).c_str());
   TH1F *h4 = (TH1F*)file1->Get((folder[0]+"/"+Histo[4]).c_str());
   TH1F *h5 = (TH1F*)file1->Get((folder[0]+"/"+Histo[5]).c_str());
   TH1F *h6 = (TH1F*)file1->Get((folder[0]+"/"+Histo[6]).c_str());
  
   float integral = h0->Integral();
   h0->Scale(1.0/integral); 
   integral = h1->Integral(); 
   h1->Scale(1.0/integral);
   integral = h2->Integral(); 
   h2->Scale(1.0/integral);
   integral = h3->Integral(); 
   h3->Scale(1.0/integral);
   integral = h4->Integral(); 
   h4->Scale(1.0/integral);
   integral = h5->Integral(); 
   h5->Scale(1.0/integral);
   integral = h6->Integral(); 
   h6->Scale(1.0/integral);

   double n = 0.9;

   h0->SetMarkerSize(n);
   h1->SetMarkerSize(n);   
   h2->SetMarkerSize(n);
   h3->SetMarkerSize(n);   
   h4->SetMarkerSize(n);
   h5->SetMarkerSize(n);   
   h6->SetMarkerSize(n);
  


   h0->SetMarkerStyle(20);
   h1->SetMarkerStyle(20);   
   h2->SetMarkerStyle(20);
   h3->SetMarkerStyle(20);   
   h4->SetMarkerStyle(20);
   h5->SetMarkerStyle(20);   
   h6->SetMarkerStyle(20);
  
   h0->SetMarkerColor(1); 
   h1->SetMarkerColor(2); 
   h2->SetMarkerColor(3); 
   h3->SetMarkerColor(4); 
   h4->SetMarkerColor(11); 
   h5->SetMarkerColor(6); 
   h6->SetMarkerColor(7); 
  

   h0->SetLineColor(1);
   h1->SetLineColor(2); 
   h2->SetLineColor(3);
   h3->SetLineColor(4);
   h4->SetLineColor(11);
   h5->SetLineColor(6);
   h6->SetLineColor(7);
  

 

   h1->Draw("L");
   h1->SetTitle("");
   h1->SetStats(kFALSE);

   h1->GetYaxis()->SetTitle("a.u.");
   if(i==1)   h1->GetXaxis()->SetTitle("p_{T}^{#tau,Reco}/p_{T}^{#tau_{gen}}");
   else if(i==0) h1->GetXaxis()->SetTitle("(p_{T}(#tau_{Reco})-p_{T}(#tau_{h}^{gen}))/p_{T}(#tau_{h}^{gen}) [GeV]");


   else if (i==7){ 
   h0->GetXaxis()->SetRangeUser(0. ,200.);
   h0->GetXaxis()->SetTitle("p_{T}(#tau^{Reco}(matched))");
   h0->GetYaxis()->SetTitle("#epsilon_{ID}");
   h0->GetYaxis()->SetRangeUser(0.9 ,1.0); 
   
   }
   else if (i==8) {
   h0->GetXaxis()->SetTitle("p_{T}(#tau_{h}^{Gen}(matched))"); 
   h0->GetYaxis()->SetTitle("#epsilon_{Matching}");
   h0->GetXaxis()->SetRangeUser(0. ,200.);
   h0->GetYaxis()->SetRangeUser(0.7 ,1.0); 
   }
   else{
   h0->GetXaxis()->SetTitle("p_{T}^{#tau,Reco}/p_{T}^{#tau_{gen}}"); 
   h0->GetYaxis()->SetTitle("a.u.");
   
   } 
 
   h1->GetXaxis()->SetTitleOffset(0.90);
   h1->GetXaxis()->SetTitleSize(0.06); 
   h1->GetYaxis()->SetTitleOffset(0.95);
   h1->GetYaxis()->SetTitleSize(0.06);


   h0->Draw("same");
   h2->Draw("same");
   h3->Draw("same");
   h4->Draw("same");
   h5->Draw("same");
   h6->Draw("same");

 //  h7->Draw("hist same p");


   
  TLegend *leg = new TLegend(0.6312997,0.1405797,0.969496,0.5898551,NULL,"brNDC");
  leg->SetBorderSize(1);
  leg->SetTextFont(62);
  leg->SetTextSize(0.04);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetHeader("p_{T}^{#tau_{gen}}[GeV]","C");
  //leg->AddEntry(h0, "10 - 20 ");
  leg->AddEntry(h0, "8 - 15");
  leg->AddEntry(h1, "15 - 30");
  leg->AddEntry(h2, "30 - 45");
  leg->AddEntry(h3, "45 - 60");
  leg->AddEntry(h4, "60 - 70");
  leg->AddEntry(h5, "70 - 90");
  leg->AddEntry(h6, "90 - #infty");
  leg->Draw();
 
  c1->SaveAs(("templates/"+Histo[i]+".pdf").c_str());
  }
 
}
