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
std::vector<double> xsec;
void fill(){
  
 // in_put.push_back("/home/alejandro/CMS/data/data_muonastau/tau_nomatch/");
  in_put.push_back("/home/alejandro/CMS/data/data_muonastau/tau_all/");
  in_put.push_back("/home/alejandro/CMS/data/data_muonastau/muon/");
  in_put.push_back("/home/alejandro/CMS/data/data_muonastau/muonastau/"); 
 	
  folder.push_back("WJetsToLNu_HT-0To70"); 
  folder.push_back("WJetsToLNu_HT-70To100"); 
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


void run_plot(){
  
  cout << "working" << endl;
  fill();

  
  bool  weight = true; 
 
  THStack *reco = new THStack("reco","");    
  THStack *emu = new THStack("emu","");
  THStack *wemu = new THStack("wemu",""); 

  for(int i = 0; i<=8; i++){    //Over samples

   int ww = 1;
  
   if(weight) ww = 2; 

   TFile *f1 = TFile::Open((in_put[0]+folder[i]+".root").c_str(),"READ");
   TFile *f2 = TFile::Open((in_put[ww]+folder[i]+".root").c_str(),"READ");
   TFile *f3 = TFile::Open((in_put[3]+folder[i]+".root").c_str(),"READ");
  
 
   

  for(int j = 0; j <= 3; j++){  // over cuts 
   
   if(j==2) continue;
    
   for(int k = 0; k <=3; k++){   // over histos

  
  int index_muon = 0;
  
  if (j==1) index_muon = j+1;
  else if ((j==0) || (j==3)) index_muon = j; 
  

  TH1F *h3 = (TH1F*)f1->Get((Cut[j]+"/"+Histo[k]).c_str());  
  TH1F *h2 = (TH1F*)f2->Get((Cut[index_muon]+"/"+Histo2[k]).c_str()); 
  TH1F *h1 = (TH1F*)f3->Get((Cut[index_muon]+"/"+Histo2[k]).c_str());

  

  double integral_1 = h1->Integral();
  cout << "Reco tau events " << integral_1 <<endl;
  if(integral_1 != 0){h1->Scale(1.0/integral_1);}
  
  double integral_2 = h2->Integral();
  cout << "Reco muon events " <<integral_2 <<endl;
  if(integral_2 != 0){h2->Scale(1.0/integral_2);} 

  double integral_3 = h3->Integral();
  cout << "Emulated tau events  " <<integral_3 <<endl;
 if(integral_3 != 0){h3->Scale(1.0/integral_3);} 
 
  if(integral_2 != 0.)  cout << "efficiency "<< 100.0*integral_3/integral_2 << endl;

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

  


  h1->SetTitle("");
  h1->SetFillColor(0);
  h1->SetFillStyle(0);
 
  if(Histo[k] == "Tau1Pt" || Histo[k] == "Muon1Pt" ) {
 	h2->GetXaxis()->SetTitle("p_{T} [GeV]");
  	h2->GetXaxis()->SetRangeUser(15.,45.);
h1->GetXaxis()->SetTitle("p_{T} [GeV]");
  	h1->GetXaxis()->SetRangeUser(15.,45.); 
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
  h1->SetStats(kFALSE);
  h1->SetTitleSize(0.05);

  if(weight == false) { h2->SetLineColor(3);
   h1->SetLineWidth(2); 
   h2->SetLineWidth(1); 
   h3->SetLineWidth(3); 
   }
   else {h2->SetLineColor(4);
   h1->SetLineWidth(2); 
   h2->SetLineWidth(2); 
   h3->SetLineWidth(3); 
  }


 h2->Draw();
       h1->Draw("same");
  
  
  h3->SetLineColor(1);
  h3->Draw("same");
 
  
  TLegend *leg = new TLegend(0.5530504,0.7347826,0.9708223,0.9695652,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);

 
  leg->AddEntry(h3, "RECO #tau");
  if(weight == false){
  leg->AddEntry(h2, "RECO #mu");
  leg->AddEntry(h1, "Emulated RECO #tau");   
   } 
  else {
  leg->AddEntry(h2, "Weighted Emu RECO #tau");
  leg->AddEntry(h1, "Unweighted Emu RECO #tau");   
  }
  leg->Draw();

  pad1->Modified();
 
  pad2->cd();
  TH1F *clone1  = (TH1F*)h1->Clone("clone1");
  TH1F *clone_1  = (TH1F*)h2->Clone("clone_1");
  
  TH1F *clone2  = (TH1F*)h3->Clone("clone2");
 

  clone1->Divide(clone2);
  clone_1->Divide(clone2);
  
 
  

 
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

   clone1->Draw("E2");

   if(weight) clone_1->Draw("E2same");

  
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
    new_directory += folder[i];
     
   
     //option 1   
  //  gSystem->Exec("mkdir  new_directory "); option 1
     // option 2
  //  gSystem->mkdir(new_directory.c_str(), kTRUE); 
    // option 3
    const TString outputdir = new_directory;
    gSystem->mkdir(outputdir, kTRUE);  


    c1->SaveAs((new_directory+"/"+Histo[k]+".pdf").c_str());
    delete clone1; 
    delete clone_1;
    delete clone2; 
   
    delete h1;
    delete h2; 
    delete h3;
    delete c1;
    }
   }

  }//loop over folders

}  
