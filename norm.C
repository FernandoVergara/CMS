#include "TEfficiency.h"
#include "TH1F.h"
#include "TArray.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TSystem.h"
#include "TFile.h"
#include <vector>

std::vector<string> File;
std::vector<string> Cut;
std::vector<string> Histo;

void filldata(){

  File.push_back("Test.root");
  Cut.push_back("no_cuts");
  Histo.push_back("MET");

}

void Normalize(TH1F **h1, double scale){

  // The histogram is pass as reference 
  Double_t ScaleFactor=1.0;
  if((*h1)->Integral() != 0){
    ScaleFactor = scale/((*h1)->Integral()); 
    }
  else{
    std::cout << (*h1)->GetName() << " non-normalizable " << std::endl;
    return; 
  }
 
  (*h1)->Scale(ScaleFactor);

}

void norm(){

  filldata();
  
  TFile *file = TFile::Open(File[0].c_str());
  if(!file) { // debes proteger el codigo de punteros nullptr
   std::cout << "File no found: " << File[0] << std::endl;
   exit(1);
  }

   
  file->cd();
  file->cd(Cut[0].c_str());
  gDirectory->pwd();
  //gDirectory->ls();

  TH1F *MET_ =new TH1F("MET_", "MET_", 500, 0., 200.);
  //file->GetObject("no_cuts/MET", MET_); // or  
   gDirectory->GetObject("MET", MET_);
 
  Normalize(&MET_, 1.0); // Normalize to unity

  MET_->Draw();
}


int main(){
  norm();
  return 0;
}
