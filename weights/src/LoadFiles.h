#ifndef LOADFILES_H
#define LOADFILES_H

#include "TROOT.h"
#include "TRint.h"

#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TSystem.h>
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
  void Fill_Map2();
  void Show_Map();
  void LoadData(string subfolder_);
  void CloseData();
  
  
  TH1D* GetDataHisto(Int_t index, string path);
  TH1D* GetMcHisto(Int_t index, string path);
  TH2D* GetDataHisto2(Int_t index, string path);
  TH2D* GetMcHisto2(Int_t index, string path);

 
  void Fill_Histos(string path_, Int_t type);

  void Scale_MC();
  void Init_AllBack();
  void SubstractBack(TH1D **h1, UInt_t avoid);
  void SubstractBack2(TH2D **h2, UInt_t avoid);
  
  TH1D *Data_histos[20];
  TH1D *MC_histos[20];
  TH2D *Data_histos2[20];
  TH2D *MC_histos2[20];

  UInt_t Data_size;
  UInt_t MC_size;
  
  TH1D *AllBack;
  
  std::map<UInt_t, string> Histo_Label;
  std::map<UInt_t, string> Labels;
  std::map<UInt_t, string> Histo_Label2;
  std::map<UInt_t, string> Labels2;


  std::vector<string> Data_Labels;
  std::vector<string> MC_Labels; 
  
  TFile *Data[20];
  TFile *MC[20];

 private:
  std::ifstream Input[4];
  
  std::vector<string> Data_files;
  std::vector<string> MC_files;
  std::vector<string> Cuts;
  std::vector<string> Histos;
  std::vector<string> Histos2;
  std::vector<string> Xaxis_Label;
  std::vector<string> Xaxis_Label2;

  std::vector<Double_t> Scales;
  
  
  
  
};

#endif
