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

vector<string> Data_dir;
vector<string> Data;
vector<string> Back_dir;
vector<string> Back;
vector<string> Cuts;
vector<string> Histo;
TFile *TBack[100];
TFile *TData[100];

void fill_info(){
  //for data
  //Data_dir.push_back("Tau_tau");
  Data_dir.push_back("Met_tau");
  
 // Data.push_back("allData");
  Data.push_back("W+Jets");
  
  //for background
  Back_dir.push_back("W+Jets"); // Real W+Jets
//  Back_dir.push_back("EW+Jets"); // Emulated W+Jets
  Back_dir.push_back("Met_Etau");  // Emulated using MET Sample

  Back.push_back("W+Jets");
 
  //Cuts
 // Cuts.push_back("NRecoTriggers1"); 
  Cuts.push_back("NRecoTau1");
  Cuts.push_back("METCut");
  //Histograms
  Histo.push_back("Tau1Pt");
  Histo.push_back("Tau1Energy");
  Histo.push_back("Tau1Eta");
  Histo.push_back("Tau1Phi");
  Histo.push_back("Tau1MetMt");
  Histo.push_back("Tau1DphiMet");  
  Histo.push_back("Met");
  Histo.push_back("MHT");
  Histo.push_back("HT");
  Histo.push_back("Meff");
  
}




void  scale_wjets(){
  
  fill_info();
  TString out_dir = "Final/";
  gSystem->mkdir(out_dir, kTRUE);
  
  
  cout << "..........Loading Background Files.........." << endl;
  
  for(Int_t i = 0; i < Back_dir.size(); i++){
    gSystem->mkdir(out_dir+Back_dir[i], kTRUE);
      int j = 0; // index for data input
    //for(Int_t j = 0; j < Back.size(); j++){
      TString Backfile = Back_dir[i]+"/"+Back[j]+".root ";
      const TString cmd = "cp "+Backfile+out_dir+Backfile; 
      gSystem->Exec(cmd);
      /////////////////////////////////////////////////
      TFile *g = TFile::Open(out_dir+Backfile,"UPDATE"); // the back are not modifying!!!!
      /////////////////////////////////////////////////   
      TBack[i] = g;
      cout << "loading: " << TBack[i]->GetName() << endl;
      gDirectory->pwd();
    //}
  }
  
  
  cout << "..........Loading Data Files.........." << endl;
  
  for(Int_t i = 0; i < Data_dir.size(); i++){
    gSystem->mkdir(out_dir+Data_dir[i], kTRUE);
    int j = 0; // index for data input
    TString Datafile = Data_dir[i]+"/"+Data[j]+".root ";
    const TString cmd = "cp "+Datafile+out_dir+Datafile; 
    gSystem->Exec(cmd);
    /////////////////////////////////////////////////
    TFile *f = TFile::Open(out_dir+Datafile,"READ");
    /////////////////////////////////////////////////   
    TData[i] = f;
    cout << "loading: " << TData[i]->GetName() << endl;
    gDirectory->pwd();
  }
  
  cout << "................................" <<endl; 
  
   
  
  int NHistos = Histo.size(); 
  int NCuts = Cuts.size();
  
  
  TH1F* Data_histo[10];
  TH1F* Back_histo[10];
  
  
  for (int j = 0; j < NCuts; j++){
    //if(j!=1) continue;
    
    for (int k = 0; k < NHistos; k++){
      //if(k!=4) continue;
      
      cout << "------------------------------------------------" << endl;
      cout << "Cut: " << Cuts[j] << " Histogram: " << Histo[k] << endl;
      cout << "------------------------------------------------" << endl;
      
      
       cout << "..........Filling histograms for Data.........." << endl; 
      
      for(int m = 0; m < Data_dir.size(); m++){
	TH1F* h;
          TString directory = TData[m]->GetName();   
          gDirectory->cd(directory+":/");
          h = (TH1F*)TData[m]->Get((Cuts[j]+"/"+Histo[k]).c_str());
	  Data_histo[m] = h; 
	  cout << "Saving for Data: " << Data_dir[m]+"/"+Data[0] << " Cut: "<< Data_histo[m]->GetName() << endl;
 	  gDirectory->pwd();
      } 

      cout << "..........Filling histograms for Background.........." << endl;  
      
      for(int l = 0; l < Back_dir.size(); l++){
	TH1F* h;
	TString directory = TBack[l]->GetName();   
	gDirectory->cd(directory+":/"); 
	h = (TH1F*)TBack[l]->Get((Cuts[j]+"/"+Histo[k]).c_str());          
	Back_histo[l] = h; 
	cout << "Saving for background: " << Back[0] << " Cut: "<< Back_histo[l]->GetName() << endl;
	gDirectory->pwd();
      }  
      
     cout << "------------------------------------------------" << endl; 
     cout << "..........Estimating scaling factor.........." << endl;  
     cout << "------------------------------------------------" << endl; 
     
      double integral_data = 0.;
      double integral_back = 0.;
      double scale = 0.;
      for(int i = 0; i < Data_dir.size(); i++){	
        /* TString directory = TData[i]->GetName();   
	  gDirectory->cd(directory+":/"); 
	  gDirectory->pwd(); 
	*/for(int j = 0; j < Back_dir.size(); j++){
	  
	  TString directory = TBack[j]->GetName();   
	  gDirectory->cd(directory+":/"); 
	  gDirectory->pwd(); 
          if(Back_histo[j]->Integral()!=0.) scale = Data_histo[i]->Integral()/Back_histo[j]->Integral();
	  else cout << "No valid scale factor" << endl; 
	  cout << "Scale Factor: " << scale << " For: "<< Back_dir[j] << " Histo: "<<Back_histo[j]->GetName()  <<endl;
	  Back_histo[j]->Scale(scale);
          cout << "New Integral: " << Back_histo[j]->Integral() << " For: "<< Back_dir[j] << " Histo: "<<Back_histo[j]->GetName()  <<endl;
	}
	
	
      } // loop over data      
      
	/////////////////////////////////////////////////////
      
    } // loop for histos 
    
  } // loop for cuts
  
  
  
  
  
  //Closing files
  for(int i = 0; i < Back_dir.size(); i++){
    for(int j = 0; j < Back.size(); j++){
      cout << "Closing: " << Back_dir[i]+"/"+Back[j]+".root "<< endl;
      TBack[i]->Write("",TObject::kOverwrite);   
      TBack[i]->Close(); 
    }
  }
  
  
  for(int i = 0; i < Data_dir.size(); i++){
    cout << "Closing: " << Data_dir[i]+"/"+Data[0]+".root "<< endl;
    TData[i]->Close(); 
  }
  
}



int main (int argc, char** argv){
  
  scale_wjets();
  return 0;
}  

