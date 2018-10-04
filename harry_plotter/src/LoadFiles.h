#ifndef LOADFILES_H
#define LOADFILES_H

#include "TROOT.h"
#include "TRint.h"

#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLegendEntry.h> 
#include <TTimer.h>
#include <TControlBar.h>
#include <TMath.h> 
#include <TRandom3.h>
#include <TLine.h>
#include <TLatex.h>
#include <TPaveText.h> 

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

class LoadFiles{
  
 public:
  LoadFiles();
  ~LoadFiles();
  void Init(string path);
  void Show(); 
  void Fill_Map();
  void Show_Map();
  void LoadData(string folder, string subfolder_);
  void CloseData();
  
  
  TH1D* GetDataHisto(Int_t index, string path);
  TH1D* GetMcHisto(Int_t index, string path);
  
  void Fill_Histos(string path_);
  void Scale_MC();
  void Init_AllBack(UInt_t N_bins, Double_t *BINS);
  
  TH1D *Data_histos[20];
  TH1D *MC_histos[20];
  UInt_t Data_size;
  UInt_t MC_size;
  
  TH1D *AllBack;
  
  std::map<UInt_t, string> Histo_Label;
  std::map<UInt_t, string> Labels;

  std::vector<string> Data_Labels;
  std::vector<string> MC_Labels; 
  
 private:
  std::ifstream Input[3];
  
  std::vector<string> Data_files;
  std::vector<string> MC_files;
  std::vector<string> Cuts;
  std::vector<string> Histos;
  std::vector<string> Xaxis_Label;

  std::vector<Double_t> Scales;
  
  TFile *Data[20];
  TFile *MC[20];
  
  
  
};

#endif
