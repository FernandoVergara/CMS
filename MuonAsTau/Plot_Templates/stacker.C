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
vector<string> Histo;
vector<string> Histo2;
vector<string> Cut;
vector<double> xsec;


void fill(){
  
  //in_put.push_back("/home/alejandro/CMS/data/data_muonastau/tau_nomatch/");
  in_put.push_back("/home/alejandro/CMS/data/data_muonastau/tau_match/");
  in_put.push_back("/home/alejandro/CMS/data/data_muonastau/muon/");

  in_put.push_back("/home/alejandro/CMS/data/data_muonastau/muonastau/method_2/effi/"); 
  in_put.push_back("/home/alejandro/CMS/data/data_muonastau/muonastau/method_2/non_effi/");
 	
 // folder.push_back("WJetsToLNu_HT-70To100"); 
 folder.push_back("WJetsToLNu_HT-100To200");
  folder.push_back("WJetsToLNu_HT-200To400");
  folder.push_back("WJetsToLNu_HT-400To600");
  folder.push_back("WJetsToLNu_HT-600To800");
  folder.push_back("WJetsToLNu_HT-800To1200");
  folder.push_back("WJetsToLNu_HT-1200To2500");
  folder.push_back("WJetsToLNu_HT-2500ToInf");
  
  
  xsec.push_back(1600.97);
  xsec.push_back(1632.53);
  xsec.push_back(436.59);   
  xsec.push_back(59.36);    
  xsec.push_back(14.62);
  xsec.push_back(6.67);
  xsec.push_back(1.61);
  xsec.push_back(0.039); 
  

  Cut.push_back("NRecoTriggers1");
  Cut.push_back("NRecoTau1");
  Cut.push_back("NRecoMuon1"); 
  Cut.push_back("METCut"); 

  Histo.push_back("Tau1Pt");
  Histo.push_back("Tau1Energy");
  Histo.push_back("Tau1MetMt");
  Histo.push_back("Met");
  
  Histo2.push_back("Muon1Pt");
  Histo2.push_back("Muon1Energy");
  Histo2.push_back("Muon1MetMt");
  Histo2.push_back("Met");
}


void stacker(){
  
  cout << "working" << endl;
  fill();

  double lumi = 37.85; 
  bool  weight = true; 
  int ww = 1;                   
  if(weight) ww = 2; 

 

  TH1F *h_1 = new TH1F("h_1","h_1", 100, 0, 500);
  TH1F *h_2 = new TH1F("h_2","h_2", 100, 0, 500);
  TH1F *h_3 = new TH1F("h_3","h_3", 100, 0, 500); 
  TH1F *h_4 = new TH1F("h_4","h_4", 100, 0, 500);    
  TH1F *h_5 = new TH1F("h_5","h_5", 100, 0, 500);
 
  ////////////////////////////
  int k = 2;
  int j = 1; 

  int index_muon = 0;
  if (j==1) index_muon = j+1;
  else if ((j==0) || (j==3)) index_muon = j; 
  


  for(int i = 0; i < folder.size(); i++){    //Over samples

  // if(i  != 5 && i != 6 ) continue;
   TFile *f1 = TFile::Open((in_put[0]+folder[i]+".root").c_str(),"READ");
   TFile *f2 = TFile::Open((in_put[ww]+folder[i]+".root").c_str(),"READ");
   TFile *f3 = TFile::Open((in_put[3]+folder[i]+".root").c_str(),"READ");

  TH1F *h1 = (TH1F*)f1->Get((Cut[j]+"/"+Histo[k]).c_str());  
  TH1F *h2 = (TH1F*)f2->Get((Cut[index_muon]+"/"+Histo2[k]).c_str()); 
  TH1F *h3 = (TH1F*)f3->Get((Cut[index_muon]+"/"+Histo2[k]).c_str());

  double integral_1 = h1->Integral();
  double integral_2 = h2->Integral();
  double integral_3 = h3->Integral();
 
  double scale1 = 1.0*lumi*xsec[i]/(integral_1);
  double scale2 = 1.0*lumi*xsec[i]/(integral_2);
  double scale3 = 1.0*lumi*xsec[i]/(integral_3);   

   if(integral_1 != 0) h1->Scale(scale1);
  else cout << "Empty Reco" << endl;
  if(integral_2 != 0) h2->Scale(scale2);
  else cout << "Empty EReco" << endl;
  if(integral_3 != 0) h3->Scale(scale3);
  else cout << "Empty E2Reco" << endl;

  
 

 /*
 h_1->Sumw2(); 
 h_2->Sumw2(); 
 h_3->Sumw2(); 
 */

 h_1->Add(h1);
 h_2->Add(h2);
 h_3->Add(h3);
 
   
}
 
   h_1->SetTitle("");
  h_1->SetStats(0);
  h_1->SetFillColor(0);
  h_1->SetFillStyle(0);

   h_1->SetLineWidth(1); 
   h_2->SetLineWidth(2); 
   h_3->SetLineWidth(1); 

   h_1->SetLineColor(1);
   h_2->SetLineColor(4);
   h_3->SetLineColor(2);



 TH1F *clone1  = (TH1F*)h_1->Clone("clone1");
 TH1F *clone2  = (TH1F*)h_2->Clone("clone2");  
  TH1F *clone3  = (TH1F*)h_3->Clone("clone3");

  clone2->Divide(clone1);
  clone3->Divide(clone1);

 h_4->Add(clone2);
 h_5->Add(clone3);

  h_4->SetTitle("");
  h_4->SetStats(0);
  h_4->SetFillColor(0);
  h_4->SetFillStyle(0);

   h_4->SetLineWidth(1); 
   h_4->SetLineWidth(1); 
   h_4->SetLineWidth(2); 
   
h_5->SetLineWidth(1); 
  
   h_4->SetLineColor(4);
   h_5->SetLineColor(2);
  

  

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

 
 
  


  h_1->SetTitle("");

  h_1->SetFillColor(0);
  h_1->SetFillStyle(0);
 
  if(Histo[k] == "Tau1Pt" || Histo[k] == "Muon1Pt" ) {
 	h_2->GetXaxis()->SetTitle("p_{T} [GeV]");
  	h_2->GetXaxis()->SetRangeUser(15.,45.);
        h_1->GetXaxis()->SetTitle("p_{T} [GeV]");
  	h_1->GetXaxis()->SetRangeUser(15.,45.); 
	}
  if(Histo[k] == "Tau1Energy" || Histo[k] == "Muon1Energy" ) {
   h_2->GetXaxis()->SetTitle("Energy [GeV]");
   h_2->GetXaxis()->SetRangeUser(0., 200.);
   h_1->GetXaxis()->SetTitle("Energy [GeV]");
   h_1->GetXaxis()->SetRangeUser(0., 200.);
   
   }
  else if(Histo[k] == "Tau1MetMt" || Histo[k] == "Muon1MetMt" ) { 
       h_2->GetXaxis()->SetTitle("m_{T} [GeV]"); 
       h_2->GetXaxis()->SetRangeUser(15., 250.);
       h_1->GetXaxis()->SetTitle("m_{T} [GeV]"); 
       h_1->GetXaxis()->SetRangeUser(15., 250.);
     
       }
  else if (Histo[k] == "Met") h_1->GetXaxis()->SetTitle("MET [GeV]");

  h_1->GetXaxis()->SetTitleOffset(1);
  h_1->GetXaxis()->SetTitleSize(0.06);
  h_1->SetLineColor(1);
  h_1->GetYaxis()->SetTitle("a.u.");
  h_1->GetYaxis()->SetTitleOffset(0.8);
  h_1->GetYaxis()->SetTitleSize(0.05);

  h_1->SetStats(kFALSE);
  h_1->SetTitleSize(0.05);

  if(weight == false) { h_2->SetLineColor(3);
   h_1->SetLineWidth(1); 
   h_2->SetLineWidth(2); 
   h_3->SetLineWidth(1); 
   }
   else {h_2->SetLineColor(4);
   h_1->SetLineWidth(1); 
   h_2->SetLineWidth(2); 
   h_3->SetLineWidth(1); 
  }

  //h3->SetLineColor(1);


 
  TLegend *leg = new TLegend(0.5530504,0.7347826,0.9708223,0.9695652,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);


  
  
  h_1->Draw();
  h_2->Draw("same");
  h_3->Draw("same");


 
  leg->AddEntry(h_1, "RECO #tau");
  if(weight == false){
  leg->AddEntry(h_2, "RECO #mu");
  leg->AddEntry(h_3, "Emulated RECO #tau");   
   } 
  else {
  leg->AddEntry(h_2, "Weighted Emu RECO #tau");
  leg->AddEntry(h_3, "Unweighted Emu RECO #tau");   
  }
  leg->Draw();
  


  pad1->Modified();
 
  pad2->cd();
  

  h_5->GetYaxis()->SetLabelSize(0.1);
  h_5->GetXaxis()->SetLabelSize(0.1);
  h_5->SetStats(kFALSE);
  h_5->GetXaxis()->SetRangeUser(15., 250.);
 // h_4->GetYaxis()->SetRangeUser(0., 2.);
  h_5->SetTitle("");
  
  h_5->Draw();
  h_4->Draw("same"); 
  
   int xmin = 0;
  int xmax = 0;   
 
  if(Histo[k] == "Tau1Pt") { xmin = 15.; xmax = 46.;}
  if(Histo[k] == "Tau1Energy") { xmin = 0. ; xmax = 200.;}
  if(Histo[k] == "Tau1MetMt" ) { xmin = 15. ; xmax = 250.;}
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
  
    string new_directory = "templates/";
    if(weight) new_directory += "weighted/";
    if(!weight) new_directory += "unweighted/"; 


    new_directory += Cut[j];
    new_directory += "/";
    new_directory += "salida";//folder[8];
     
   
     //option 1   
  //  gSystem->Exec("mkdir  new_directory "); option 1
     // option 2
  //  gSystem->mkdir(new_directory.c_str(), kTRUE); 
    // option 3
    const TString outputdir = new_directory;
    gSystem->mkdir(outputdir, kTRUE);  


    c1->SaveAs((new_directory+"/"+Histo[k]+".pdf").c_str());
    
}  
