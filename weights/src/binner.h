#include "LoadFiles.h" 

#ifndef BINNER_H
#define BINNER_H

class binner{
  
 public:
  
  binner();
  ~binner();
  void Init(string file);
  TH1D* Rebinner1(TH1D *h_old);
  TH2D* Rebinner2(TH2D *h_old);
  
  void Weight_Init(string file);
  void ApplyWeight(TH2D **h2);
  TH1D* Proyection_X(TH2D **h2, Double_t &Total_E, Double_t E_weight, bool poisson);

  void BinWidth(TH1D **h1);
  void Poisson_error(TH1D **h1, bool binW);
  
 private:
  std::ifstream Input[6];
  
  std::vector<Double_t> bins;
  Double_t *BINS;
  Double_t *XBINS;
  UInt_t N_bins;
  TH1D *h_new;
  TH2D *h2;
  
  TH1D *h1_X;
  
  std::vector<Double_t> weights;
  std::vector<Double_t> errors;

  std::map<Int_t, Double_t> Weight;
  std::map<Int_t, Double_t> Error;

};

#endif
