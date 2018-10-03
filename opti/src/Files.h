#ifndef FILES_H
#define FILES_H

#include "TROOT.h"
#include "TRint.h"

#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TLegendEntry.h> 
#include <TTimer.h>
#include <TControlBar.h>
#include <TMath.h> 
#include <TRandom3.h>

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

class Files{

public:
  Files();
  Files(double Luminosity_);
  ~Files();
  //Methods
  void Init(string folders_);
  std::vector<double> Get_Signal(string sub_, string folder_, string first_, string second_);
  std::vector<double> Get_Back(string sub_, string folder_, string first_, string second_);

  std::vector<string> folder;
  int signal_size;

private:

 std::ifstream file1;
 std::ifstream file2;


 std::vector<string> path;
 std::vector<double> xsec;
 std::vector<string> type;

 double Luminosity;
 
 TFile *f_signal;
 TFile *f_back;
   
 TH1F *numerator;
 TH1F *denominator; 
 double integral_1;
 double integral_2;
 double efficiency;
 

};

#endif
