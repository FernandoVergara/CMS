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
vector<string> input; 
vector<string> folder;
vector<string> Histo1;
vector<string> Histo2;


void fill(){

  //  Data_dir.push_back("EW+Jets");
 // Data_dir.push_back("W+Jets");
//  Data_dir.push_back("SingleMuon_ETau");
  Data_dir.push_back("Met_Etau");
  
  input.push_back("allData");
 // input.push_back("W+Jets");
/*
  input.push_back("WJetsToLNu_HT-0To70");
  input.push_back("WJetsToLNu_HT-70To100"); 
  input.push_back("WJetsToLNu_HT-100To200");
  input.push_back("WJetsToLNu_HT-200To400");
  input.push_back("WJetsToLNu_HT-400To600");
  input.push_back("WJetsToLNu_HT-600To800");
  input.push_back("WJetsToLNu_HT-800To1200");
  input.push_back("WJetsToLNu_HT-1200To2500");
  input.push_back("WJetsToLNu_HT-2500ToInf"); 
*/
  
  folder.push_back("NRecoMuon1");
  folder.push_back("NRecoTau1");
  folder.push_back("METCut");

  Histo1.push_back("Tau1Pt");
  Histo1.push_back("Tau1Energy");
  Histo1.push_back("Tau1Eta");
  Histo1.push_back("Tau1Phi");
  Histo1.push_back("Tau1MetMt");
  Histo1.push_back("Tau1DphiMet");      

  Histo2.push_back("Muon1Pt");
  Histo2.push_back("Muon1Energy");
  Histo2.push_back("Muon1Eta");
  Histo2.push_back("Muon1Phi"); 
  Histo2.push_back("Muon1MetMt"); 
  Histo2.push_back("Muon1DphiMet"); 


 
}


void  Tau_by_Muon(){

  fill();  
  TString outputdir = "Final/";
  gSystem->mkdir(outputdir, kTRUE);

  int tau_index = 0;
  int muon_index = 0;

  for(int i = 0; i < Data_dir.size(); i++){
  gSystem->mkdir(outputdir+Data_dir[i], kTRUE);

   for(int j = 0; j < input.size(); j++){
   TString file = Data_dir[i]+"/"+input[j]+".root ";
   const TString cmd = "cp "+file+outputdir+file;
   cout << "cmd exit status = " << gSystem->Exec(cmd) << endl;
   

   TFile *f1 = TFile::Open(outputdir+file,"UPDATE"); 
   cout << "processing: " << outputdir+file << endl;
 
    

    for(int k=0; k<folder.size();k++){
      
	if(k==0) continue; 
        else if(k==1) {
        tau_index = k;
        muon_index = k-1;
	}
        else if(k==2) tau_index = muon_index = k;  
          
        
	for(int l=0; l<Histo1.size();l++){
        
  	TH1F *Tau = (TH1F*)f1->Get((folder[tau_index]+"/"+Histo1[l]).c_str());
        TH1F *Muon = (TH1F*)f1->Get((folder[muon_index]+"/"+Histo2[l]).c_str());
 	Tau->Add(Tau, Muon, 1, +1);
  	//Muon->Add(Muon, Tau, 1, +1);
        cout << folder[tau_index]+"/"+Histo1[l] << endl;
        cout << folder[muon_index]+"/"+Histo2[l] << endl;
        cout << "------------------ --------------------" << endl;
        
        //delete Tau,Muon; 
    	}
        
   } //loop over folders

  f1->Write("",TObject::kOverwrite);     
  f1->Close();

   } //loop over input files

  } //loop over data_dir

}  
