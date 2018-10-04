#include "LoadFiles.h" 

#ifndef BINNER_H
#define BINNER_H

class binner{
  
 public:
  
  binner();
  ~binner();
  void Init(string file);
  void Rebinner(TH1D **h_old, UInt_t key);
  void BinWidth(TH1D **h1);
  void Poisson_error(TH1D **h1, bool binW);

  void Weight_Init(string file);
  void ApplyWeight(TH1D **h1);
   
  Double_t *BINS;
  UInt_t N_bins;
 private:
  std::ifstream Input[5];
  
  std::vector<Double_t> bins;
 
  TH1D *h_new;
  
  std::vector<Double_t> weights;
  std::vector<Double_t> errors;

  std::map<Int_t, Double_t> Weight;
  std::map<Int_t, Double_t> Error;

};

#endif
