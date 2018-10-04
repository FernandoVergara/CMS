#include "binner.h"

#ifndef PLOTTER_H
#define PLOTTER_H

class plotter{
  
 public:
  
  plotter();
  ~plotter();
  void Init(string file);
  Double_t GetColor(string color, string sign, Double_t number); 
  void ShowColor();
  void SetColorData(TH1D **h1, string x_label, string y_label);
  void SetColorDataClone(TH1D **h1, string x_label, string y_label);
  void SetColorMC(TH1D **h1, UInt_t index, string x_label, string y_label);
  void SetColorAllBack(TH1D **h1, string x_label, string y_label);
  void Create_Canvas(bool logscale_1, bool logscale_2);
  void CreateLine(Double_t xmin, Double_t xmax);
  void CreateLegend();
  void LegendAdd(TH1D *h1, bool isData, string label_);
  void LegendDraw();
  void CMSLabels();
  void OtherLabels();
  TGraphErrors* CreateERROR(TH1D *h1, UInt_t Data_bins, Double_t sys_error);
  void ShowRatioValue(TH1D *h1, UInt_t Data_bins);
  
  TCanvas *c;
  TPad *pad1;
  TPad *pad2;
  TLine *line;
  TLegend *legend;


 private:
  
  std::ifstream Input[5];
  std::vector<string> colors;
  std::vector<string> sign;
  std::vector<Double_t> number;
  
  std::map<string, Double_t> map_color;
  Double_t Color_final;
  
  TPaveText *pt;
  TPaveText *pt2;
  TPaveText *pt3;   
  
  TLatex *tex_2;
  TLatex *tex_3;
  
  TH1D *H_systematic;
  TH1D *H_Back;
  
  Double_t* mcX;
  Double_t* mcY;
  Double_t* mcErrorX;
  Double_t* mcErrorY;
  
  TGraphErrors *McError; 
};

#endif
