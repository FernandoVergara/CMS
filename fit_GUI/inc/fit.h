#include <memory>

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

class fit{

  RQ_OBJECT("fit");
 
 public:  
  fit(const TGWindow *p,UInt_t w,UInt_t h);
  ~fit();
  void Draw();
  void Fill(TH1F *Numerator, TH1F *Denominator, Int_t bins, Int_t min, Int_t max);
  void sizePad(double ratio, TVirtualPad* pad, bool isTop);
  void DeleteFill();
  void Run();
  void Clear();
  void Control();
  void PrintImage();
  void setTDRStyle();
  double ERROR(Double_t x, Double_t y, Double_t ex, Double_t ey);

 private:
 
  TPad *pad1, *pad2;
  TFile *f1, *f2;
  TLine *line1;
  TGFileInfo fi;
  TGFileDialog *TGfd;
  TGLayoutHints *l1, *l2;
  TGMainFrame *TMF1;
  TRootEmbeddedCanvas *EC1;
  TCanvas *c1;
  TGVerticalFrame  *VFO1, *VFO2;
  TGHorizontalFrame  *HF1, *HFN, *HFl, *HFK;
  TGHSlider *S1;
  TGTripleHSlider     *TS1;
  TGLabel *TGLPI, *TGLN, *TGLl, *TGLM;
  TGNumberEntryField *NEPIvalue;
  TGHProgressBar *PB;
  TRandom1 *r;
  TLine *li, *lr;
  TGNumberEntry *NEN, *NEl, *NEK, *MIN;              //NumberEntry Values  Number of Needles and Longitud Value
  TGStatusBar *SB;
  TGTextButton *TGBDraw, *TGBClear, *TGBRun, *TGBExit, *TGBEImage; 
  TGGroupFrame  *GF1, *GF2;              //Group Parameters, Options and Results.
  TTimer *Count;
  TH1F *H1F1, *H2F1, *H1F2, *H2F2, *H_bins_num, *H_bins_den, *clone1, *clone2,
  *cloneden;
  TGraphAsymmErrors *gr1, *gr2, *gr3;
  TMultiGraph *mg, *mg1;
  TLegend *leg;
  Int_t MP,mP,CP,P,nbins, bins, CountState, counter, counter2;
  Int_t content;
  Double_t binvalue1, binvalue2, error,error2, binserror[26];

  char WIDTH[20];
  char NBINS[20];
  char BINVALUE1[20];
  char ERROR1[20];
  char BINVALUE2[20];
  char ERROR2[20];



  ClassDef(fit,0);
};
