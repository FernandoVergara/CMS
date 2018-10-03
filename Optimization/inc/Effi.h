#ifndef _EFFI_H_
#define _EFFI_H_

#include <memory>
#include <sys/types.h>
#include <dirent.h>
#include <TROOT.h>
#include <RQ_OBJECT.h>
#include <TGClient.h>
#include <TGFrame.h>
#include <TQObject.h>
#include "TGTextEntry.h"
#include <TRootEmbeddedCanvas.h>
#include <TCanvas.h>
#include <TGNumberEntry.h>
#include <TGLabel.h>
#include <TGProgressBar.h>
#include <TRandom1.h>
#include <TLine.h>
#include <TGStatusBar.h>
#include <TMath.h>
#include <TTimer.h>
#include "TGTripleSlider.h"
#include "TGSlider.h"
#include <TGClient.h>
#include <TGFileDialog.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TAttAxis.h>
#include <TAttBBox.h>
#include <TAttBBox2D.h>
#include <TAttCanvas.h>
#include <TAttFill.h>
#include <TAttImage.h>
#include <TAttLine.h>
#include <TAttMarker.h>
#include <TAttPad.h>
#include <TAttText.h>
#include <TPad.h>
#include <TAttPad.h>
#include <TAxis.h>
#include <TPaveText.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TVirtualPad.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <array>
#include <cmath>
#include "TEnv.h"

class Effi{

 // RQ_OBJECT("Effi");
 
 public:
 Effi();
// Effi(vector<string>);
 ~Effi();
 //void setUse() {if(use == 2) use = 1;}
 //vector<string> input;
 //vector<double> skim, xsec, SF;
 //string output, type="";
 //double lumi;


 private:

 // ClassDef(Effi,0);
};

#endif
