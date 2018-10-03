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

vector<string> out_put;  
string input = "./data";
vector<string>  inputfolder;
vector<string> folder;
std::vector<string> Cut; 
std::vector<string> Histo;


void fill(){
  
  
 
  out_put.push_back("Tau_Inf.root");
  
  
  
  inputfolder.push_back("");
inputfolder.push_back("");
  
  
  folder.push_back("WJetsToLNu_HT-0To70");
  folder.push_back("WJetsToLNu_HT-70To100"); 
  folder.push_back("WJetsToLNu_HT-100To200");
  folder.push_back("WJetsToLNu_HT-200To400");
  folder.push_back("WJetsToLNu_HT-400To600");
  folder.push_back("WJetsToLNu_HT-600To800");
  folder.push_back("WJetsToLNu_HT-800To1200");
  folder.push_back("WJetsToLNu_HT-1200To2500");
  folder.push_back("WJetsToLNu_HT-2500ToInf"); 
  folder.push_back("NoWJets"); 
  folder.push_back("DeltaPhi"); 
  
  Cut.push_back("NRecoTriggers1");
  Cut.push_back("NRecoTau1");
  Cut.push_back("METCut");
  
  
 
  Histo.push_back("GenTauFractionR1");
  Histo.push_back("GenTauFractionR2");
  Histo.push_back("GenTauFractionR3");
  Histo.push_back("GenTauFractionR4");
  Histo.push_back("GenTauFractionR5");
  Histo.push_back("GenTauIDRecoPt");
  Histo.push_back("GenTauIDPt");
  Histo.push_back("GenTauMatchedPt");
  Histo.push_back("GenHadTauPt"); 
  Histo.push_back("Tau1Eta");
  Histo.push_back("Tau1DphiMet");  
  
 
    
    
    
   
  
}


void generator(){
  
  cout << "working" << endl;
  fill();
  
  
  for (int i = 0 ; i < out_put.size(); i++ ){   
    TFile* file = TFile::Open(out_put[i].c_str(), "RECREATE");
    
    cout << out_put[i]  << endl;
    for(int j = 0; j < folder.size(); j++){
  
      
   TFile *f1 = TFile::Open((input+"/"+inputfolder[i]+"/"+folder[j]+".root").c_str(),"READ");
     
      if (f1 == 0) {
	printf("Error: cannot open Trig Eff root file \n");
	return;
      }
      cout << folder[j] << endl;
	int cut_position = 1;
       
 
      if(folder[j]=="DeltaPhi") {
      cut_position = 2;
      }
     
      
      file->mkdir(folder[j].c_str());
      file->cd(folder[j].c_str());
      
      if(folder[j]=="DeltaPhi"){
        
        TH1F *h1 = (TH1F*)f1->Get((Cut[cut_position]+"/"+Histo[10]).c_str());
        double integral = h1->Integral();
        if(integral !=0.) h1->Scale(1.0/integral);
        h1->Write();
	}

      
      for(int k = 0; k< Histo.size(); k++){
        if((Histo[k] == "GenTauIDPt") || (Histo[k] == "GenHadTauPt")) continue;	
        if(folder[j]=="DeltaPhi") continue;
        
        
	TH1F *h1 = (TH1F*)f1->Get((Cut[cut_position]+"/"+Histo[k]).c_str());
        	
	if((Histo[k] == "GenTauIDRecoPt") || (Histo[k] == "GenTauMatchedPt")) { 
         
	  TH1F *h2 = (TH1F*)f1->Get((Cut[cut_position]+"/"+Histo[k+1]).c_str());
	  h1->Divide(h2);
	  h1->Write();  
	
	}


        


        
        else {double integral = h1->Integral();
        if(integral !=0.) h1->Scale(1.0/integral);
        h1->Write();
        }
      
      }
       
    }
    
    file->Close();
  }
  
  
}

  
   
  
  
 
