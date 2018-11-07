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
#include <stdlib.h>
#include "math.h"
#include <TMultiGraph.h>

using namespace std;

vector<string> Data_dir;
vector<string> Data;
vector<string> Back_dir;
vector<string> Back;
vector<string> Cuts;
vector<string> Histo;
TFile *TData[10] ;
TFile *TBack[10] ;

string folder;

void fill_info(){
  //for data
  const TString cmd = "echo $HOME | head -1";
  const TString home = gSystem->GetFromPipe(cmd);
  folder = string(home)+"/Dropbox/CMS/Data/data_driven/";
  folder += "Z_tight";
  //folder += "Z_loose";

  Data_dir.push_back(folder);
 
  Data.push_back("allData");
 
  //for background
  Back_dir.push_back(folder);
 
 Back.push_back("DY+Jets");
  
  Back.push_back("W+Jets");
 // Back.push_back("QCD");  
  
  Back.push_back("SingleTop");
  Back.push_back("tt");
  Back.push_back("VV");
  //Cuts
  Cuts.push_back("NRecoTriggers1");
 // Cuts.push_back("NRecoTau1");
  Cuts.push_back("METCut");
 // Cuts.push_back("NRecoFirstLeadingJet");
  //Histograms
/*
  Histo.push_back("Events");
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
  Histo.push_back("Dphi1");   
*/
  Histo.push_back("Tau1Pt");
 //Histo.push_back("Tau1MetMt");
//  Histo.push_back("Muon1Tau1ReconstructableMass");
 
}




void  data_driven(){
  
  fill_info();
  TString out_dir = "Final/";
  gSystem->mkdir(out_dir, kTRUE);
  int NData = Data_dir.size();
  int NBack = Back_dir.size();

  

  cout << "..........Loading Background Files.........." << endl;
  
  for(Int_t i = 0; i < Back_dir.size(); i++){
    gSystem->mkdir(out_dir+Back_dir[i], kTRUE);
    for(Int_t j = 0; j < Back.size(); j++){
      TString Backfile = Back_dir[i]+"/"+Back[j]+".root ";
      const TString cmd = "cp "+Backfile+out_dir+Backfile; 
      gSystem->Exec(cmd);
      /////////////////////////////////////////////////
      TFile *g = TFile::Open(out_dir+Backfile,"READ"); // the back are not modifying!!!!
      /////////////////////////////////////////////////   
      TBack[j] = g;
      //g->GetListOfKeys()->Print();
      cout << "loading: " << TBack[j]->GetName() << endl;
      gDirectory->pwd();
    }
  }
  
  
  cout << "..........Loading Data Files.........." << endl;
  
  for(Int_t i = 0; i < Data_dir.size(); i++){
    gSystem->mkdir(out_dir+Data_dir[i], kTRUE);
    int j = 0; // index for data input
    TString Datafile = Data_dir[i]+"/"+Data[j]+".root ";
    const TString cmd = "cp "+Datafile+out_dir+Datafile; 
    gSystem->Exec(cmd);
    /////////////////////////////////////////////////
    TFile *f = TFile::Open(out_dir+Datafile,"UPDATE");
    /////////////////////////////////////////////////   
    TData[i] = f;
    cout << "loading: " << TData[i]->GetName() << endl;
    gDirectory->pwd();
  }
  
  cout << "................................" <<endl; 
  
  //////////////////////////////////////////////////////
  for(int i = 0; i < Back.size(); i++){
    cout << i << " For: " << Back[i] << endl; 
  }
  cout << "Which background do you want to calculate?" << endl;
  int index = 0 ;  // index of the derided background contribution 
  cin >> index;
  if (index > Back.size()) {
    cout << "No valid Option" << endl;
    exit(1);} 
  //////////////////////////////////////////////////////
  
  
  
  int NHistos = Histo.size(); 
  int NCuts = Cuts.size();
  
  TH1F* Data_histo[Data_dir.size()];
  TH1F* Back_histo[Back.size()];
  
  
  for (int j = 0; j < NCuts; j++){
    //if(j!=1) continue;
    
    for (int k = 0; k < NHistos; k++){
      //if(k!=4) continue;
      
      cout << "------------------------------------------------" << endl;
      cout << "Cut: " << Cuts[j] << " Histogram: " << Histo[k] << endl;
      cout << "------------------------------------------------" << endl;
      
      cout << "..........Filling histograms for Background.........." << endl;  
      
      for(int l = 0; l < Back.size(); l++){
	TH1F* h;
        
	TString directory = TBack[l]->GetName();   
	gDirectory->cd(directory+":/"); 
	h = (TH1F*)TBack[l]->Get((Cuts[j]+"/"+Histo[k]).c_str());
        h->Sumw2();          
	Back_histo[l] = h; 
	cout << "Saving for background: " << Back[l] << " Cut: "<< Back_histo[l]->GetName() << endl;
	gDirectory->pwd();
      }  
      
      
      cout << "..........Filling histograms for Data.........." << endl; 
      
      for(int m = 0; m < Data_dir.size(); m++){
	TH1F* h;
          TString directory = TData[m]->GetName();   
          gDirectory->cd(directory+":/");
          h = (TH1F*)TData[m]->Get((Cuts[j]+"/"+Histo[k]).c_str());
          h->Sumw2();      
	  Data_histo[m] = h; 
	  cout << "Saving for Data: " << Data_dir[m]+"/"+Data[0] << " Cut: "<< Data_histo[m]->GetName() << endl;
 	  gDirectory->pwd();
      } 
      
      cout << "------------------------------------------------" << endl;
      cout << "Substracting background contributions... " << endl;  
      cout << "------------------------------------------------" << endl;
      
      for(int i = 0; i < Data_dir.size(); i++){	

        
	for(int j = 0; j < Back.size(); j++){
	  
	  if(j==index) { 
	    cout << "Omiting: " << Back[j] << endl; 
	    continue;
	  }
	  TString directory = TData[i]->GetName();   
	  gDirectory->cd(directory+":/"); 
	  gDirectory->pwd(); cout << "**************" << endl; 
          cout << "OLd integral: " << Data_histo[i]->Integral() << "Bin content:" << Data_histo[i]->GetBinContent(2)  <<endl;
          cout << " Integral backgrounds " << Back_histo[i]->Integral() << "Bin content:" << Back_histo[j]->GetBinContent(2) << endl;
	  Data_histo[i]->Add(Data_histo[i], Back_histo[j], 1,-1); 
	  cout << " ----------Subtracting the contribution: " << Back[j]  << endl;        
	  cout << "New integral: " << Data_histo[i]->Integral() << "Bin content:" << Data_histo[i]->GetBinContent(2) <<endl;
          
	  
	}
                         
         
          TString directory = TData[i]->GetName();   
	  gDirectory->cd(directory+":/"); 
	  gDirectory->pwd(); cout << "**************" << endl;  
	  double integral = Data_histo[i]->Integral();
  //        Data_histo[i]->Scale((196.8 *2.97)/integral);
	  cout << "after scale " << Data_histo[i]->Integral() << endl; 

        /*

          TH1D *Clone_ = (TH1D*)Data_histo[i]->Clone();
          Clone_->Sumw2();
          for(int jj = 1; jj <= Clone_->GetNbinsX(); jj++){
             
           Clone_->SetBinContent(jj, 1.);
           Clone_->SetBinError(jj, 0.77);
           
          }
          Data_histo[i]->Multiply(Clone_);     
          cout << "after propagate uncertainty " << Data_histo[i]->Integral() << endl;   
*/
            int bins = (int)Data_histo[i]->GetNbinsX();
          cout << bins << endl;
       
          for(int kk = 1; kk <= bins; kk++){
          double bin_value =  Data_histo[i]->GetBinContent(kk);
          double error_value = Data_histo[i]->GetBinError(kk);
         // cout << " V " << bin_value << " Error " << error_value << endl;

           if(error_value >= abs(bin_value)){ 
          Data_histo[i]->SetBinError(kk, bin_value); 
         // cout << " New " << Data_histo[i]->GetBinContent(kk) << " Error " << Data_histo[i]->GetBinError(kk) << endl;
          } 

        //  if(bin_value < 0.) { 
	//	Data_histo[i]->SetBinContent(kk, 0.);
          //      Data_histo[i]->SetBinError(kk, 0.);
//                             }

         
          //Deleting negative entries
          }


         // integral = Data_histo[i]->Integral();
         // Data_histo[i]->Scale(0.35);






  
      } // loop over data      
      
	/////////////////////////////////////////////////////
      
    } // loop for histos 
    
  } // loop for cuts
  
  
  
  
  
  //Closing files
  for(int i = 0; i < Back_dir.size(); i++){
    for(int j = 0; j < Back.size(); j++){
      cout << "Closing: " << Back_dir[i]+"/"+Back[j]+".root "<< endl;
      TBack[j]->Close(); 
    }
  }
  
  
  for(int i = 0; i < Data_dir.size(); i++){
    cout << "Closing: " << Data_dir[i]+"/"+Data[0]+".root "<< endl;
    TData[i]->Write("",TObject::kOverwrite);    
    TData[i]->Close(); 
  }
  
  //Constructing the right names

  for(int i = 0; i < Data_dir.size(); i++){
  TString Backfile = Data_dir[i]+"/"+Data[0]+".root ";
  TString file_f = Back[index]+".root";
      const TString cmd = "mv "+out_dir+Backfile+out_dir+Data_dir[i]+"/"+file_f; 
    //  cout << cmd << endl;
      gSystem->Exec(cmd);
  }

}



int main (int argc, char** argv){
  
  data_driven();
  return 0;
}  

