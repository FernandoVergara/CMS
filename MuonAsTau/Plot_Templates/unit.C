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
std::vector<string> Histo2;
std::vector<string> Cut;

void fill(){
  
  //in_put.push_back("/home/alejandro/CMS/data/data_muonastau/tau_all/");
  //in_put.push_back("/home/alejandro/CMS/data/data_muonastau/muonastau/"); 

   in_put.push_back("allData");
   in_put.push_back("allData_emu");

   
   folder.push_back("W+Jets");
 /*	
  folder.push_back("WJetsToLNu_HT-0To70"); 
  folder.push_back("WJetsToLNu_HT-70To100"); 
  folder.push_back("WJetsToLNu_HT-100To200");
  folder.push_back("WJetsToLNu_HT-200To400");
  folder.push_back("WJetsToLNu_HT-400To600");
  folder.push_back("WJetsToLNu_HT-600To800");
  folder.push_back("WJetsToLNu_HT-800To1200");
  folder.push_back("WJetsToLNu_HT-1200To2500");
  folder.push_back("WJetsToLNu_HT-2500ToInf");
  */

  Cut.push_back("NRecoTriggers1");
  Cut.push_back("NRecoTau1");
  Cut.push_back("METCut"); 

  Histo.push_back("Tau1Pt");
  Histo.push_back("Tau1Eta");
  Histo.push_back("Tau1Energy");
  Histo.push_back("Tau1MetMt");
  Histo.push_back("Tau1PtMetCosPhi1");
  Histo.push_back("Tau1PtMetCosPhi2");
  Histo.push_back("Tau1Met1");
  Histo.push_back("Tau1Met2");
    
  
   Histo2.push_back("Muon1PtMetCosPhi1");
   Histo2.push_back("Muon1PtMetCosPhi2");
   Histo2.push_back("Muon1Met1");
   Histo2.push_back("Muon1Met2");
}


void unit(){
  
  cout << "working" << endl;
  fill();

  int i = 0;

   TFile *f1 = TFile::Open((in_put[0]+".root").c_str(),"READ");
   TFile *f2 = TFile::Open((in_put[1]+".root").c_str(),"READ");

    
  int j = 1;
  
  int k=4;

  TH1F *h1 = (TH1F*)f1->Get((Cut[j]+"/"+Histo[k]).c_str());  
  TH1F *h2 = (TH1F*)f2->Get((Cut[j]+"/"+Histo2[0]).c_str()); 

   
  double integral_1 = h1->Integral();
  cout << "Reco tau events " << integral_1 <<endl;
  if(integral_1 != 0){h1->Scale(1.0/integral_1);}
  
  double integral_2 = h2->Integral();
  cout << "Reco muon events " <<integral_2 <<endl;
  if(integral_2 != 0){h2->Scale(1.0/integral_2);} 

  double scale= 0;
  if(integral_2 != 0) scale = integral_1/integral_2;
  cout << scale<< endl;

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
  




 TPad *pad1 = new TPad("pad1", "pad1", 0, 1 / (1.0 + 3.0), 1, 1, 0);
  pad1->Range(-30.45587,-0.01034407,225.8002,0.0918629);
 // pad1->SetPad("pad1", "pad1", 0, 1 / (1.0 + 3.0), 1, 1, 0);
  pad1->Draw();
   TPad *pad2 = new TPad("pad2", "",0,0,1,0.25);
   pad2->Draw();
   pad2->cd();
   pad2->Range(-126.2458,-0.5350439,1126.246,2.101958);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetBottomMargin(0.2028985);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameBorderMode(0);
  
 // pad2->Draw();

  pad1->cd();

  


  h2->SetTitle("");
  h2->SetFillColor(0);
  h2->SetFillStyle(0);
 
  h2->GetXaxis()->SetTitle("#Delta #phi(E_{T}^{miss}, l)");
 // h2->GetXaxis()->SetTitle("E_{T}^{miss}");

  if(Histo[k] == "Tau1Pt" || Histo[k] == "Muon1Pt" ) {
 	h2->GetXaxis()->SetTitle("p_{T} [GeV]");
  	h2->GetXaxis()->SetRangeUser(30.,80.);
h1->GetXaxis()->SetTitle("p_{T} [GeV]");
  	h1->GetXaxis()->SetRangeUser(30.,80.); 
	}
  if(Histo[k] == "Tau1Energy" || Histo[k] == "Muon1Energy" ) {
   h2->GetXaxis()->SetTitle("Energy [GeV]");
   h2->GetXaxis()->SetRangeUser(0., 200.);
h1->GetXaxis()->SetTitle("Energy [GeV]");
   h1->GetXaxis()->SetRangeUser(0., 200.);
   
   }
  else if(Histo[k] == "Tau1MetMt" || Histo[k] == "Muon1MetMt" ) { 
       h2->GetXaxis()->SetTitle("m_{T} [GeV]"); 
       h2->GetXaxis()->SetRangeUser(15., 350.);
        h1->GetXaxis()->SetTitle("m_{T} [GeV]"); 
       h1->GetXaxis()->SetRangeUser(15., 350.);
     
       }
  else if (Histo[k] == "Met") h1->GetXaxis()->SetTitle("MET [GeV]");

  h1->GetXaxis()->SetTitleOffset(1);
  h1->GetXaxis()->SetTitleSize(0.06);
  h1->SetLineColor(2);
  h1->GetYaxis()->SetTitle("a.u.");
  h1->GetYaxis()->SetTitleOffset(0.8);
  h1->GetYaxis()->SetTitleSize(0.05);
  h2->SetStats(kFALSE);
  h1->SetTitleSize(0.05);



 h2->Draw();
 h1->Draw("same");
  
  
 
  
  TLegend *leg = new TLegend(0.5530504,0.7347826,0.9708223,0.9695652,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);

 
  leg->AddEntry(h1, "#tau");
  //leg->AddEntry(h2, "#mu");
  leg->AddEntry(h2, "Emulated #tau");   
      
  leg->Draw();

  pad1->Modified();
 
  pad2->cd();
  TH1F *clone1  = (TH1F*)h1->Clone("clone1");
  TH1F *clone_1  = (TH1F*)h2->Clone("clone_1");
 

  clone_1->Divide(clone1);
  
 
  

 
   clone1->SetStats(0);
   clone1->SetFillColor(1);
   clone1->SetFillStyle(3002);
   clone1->SetMarkerStyle(7);
   clone1->SetMarkerColor(2);
 //  clone1->SetLineColor(2);
   clone1->GetYaxis()->SetTitle("Ratio(Emulated/Real)");
   clone1->GetXaxis()->SetTitle("");
   clone1->GetYaxis()->SetLabelFont(42);
   clone1->GetYaxis()->SetLabelSize(0.07);
   clone1->GetXaxis()->SetLabelSize(0.08);
   clone1->GetYaxis()->SetTitleSize(0.08);
   clone1->GetYaxis()->SetTitleOffset(0.45);
   clone1->GetYaxis()->SetTitleFont(42);
   
   
 //  clone_1->SetLineColor(3);
   clone_1->SetMarkerColor(4);
   clone_1->SetFillColor(1);
   clone_1->SetFillStyle(3001);
   clone_1->SetMarkerStyle(7);

  // clone_1->Draw("E2");

  
   int xmin = 0;
  int xmax = 0;   
 
  if(Histo[k] == "Tau1Pt") { xmin = 15.; xmax = 46.;}
  if(Histo[k] == "Tau1Energy") { xmin = 0. ; xmax = 200.;}
  if(Histo[k] == "Tau1MetMt" ) { xmin = 15. ; xmax = 350.;}
  if(Histo[k] == "Met" ) { xmin = 0. ; xmax = 1000.;}  
   TLine *line1 = new TLine(xmin, 1.0, xmax, 1.0);
   line1->SetLineColor(kBlue);
  line1->SetLineWidth(1);
  line1->SetLineStyle(2);
 
    
   line1->Draw();      


   

    pad2->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
  
 
 
}  
