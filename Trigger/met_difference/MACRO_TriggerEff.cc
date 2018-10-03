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

void setTDRStyle();

void MACRO_TriggerEff(){
  
  cout << "working" << endl;
  
  setTDRStyle();
  
  TCanvas* c1 = new TCanvas("c1","c1",200,200,800,700);
  c1->SetGrid();
  
  TFile *f1 = TFile::Open("data/Data_muisnu.root","READ");
  TFile *f2 = TFile::Open("data/Data_muisnotnu.root","READ");
  if (f1 == 0 || f2 ==0) {
    printf("Error: cannot open Trig Eff root file \n");
    return;
  }
  
 TH1F *Numerator = (TH1F*)f1->Get("NRecoTriggers2/Met");
 TH1F *Denominator = (TH1F*)f2->Get("NRecoTriggers2/Met");
 
//  TH1F *Numerator = (TH1F*)f1->Get("METCut/Met");
//  TH1F *Denominator = (TH1F*)f2	->Get("METCut/Met");
  
  
  /*
  f2->SetTitle("E^{miss}_{T} comparasion");
  f2->GetXaxis()->SetTitle("E^{miss}_{T} [GeV]");
  //f2->GetXaxis()->SetTitle("p_{T}(leading \ jet) [GeV]");
  f2->GetXaxis()->SetLabelFont(42);
  f2->GetXaxis()->SetLabelSize(0.035);
  f2->GetXaxis()->SetTitleSize(0.05);
  f2->GetXaxis()->SetTitleOffset(0.89);
  f2->GetXaxis()->SetTitleFont(42);
  f2->GetYaxis()->SetTitle("#epsilon");
  f2->GetYaxis()->SetLabelFont(42);
  f2->GetYaxis()->SetLabelSize(0.035);
  f2->GetYaxis()->SetTitleSize(0.06);
  f2->GetYaxis()->SetTitleOffset(0.69);
  f2->GetYaxis()->SetTitleFont(42);
  */	
  Double_t  INT_1=Numerator->Integral(0, 10000);
  Double_t  INT_2=Denominator->Integral(0, 10000);

  Double_t scale1=1/INT_1;
  Double_t scale2=1/INT_2;
  
 Numerator->Scale(scale1);
 Denominator->Scale(scale2);

  Numerator->Draw();
  Numerator->SetTitle("");
  Numerator->GetXaxis()->SetTitle("E^{miss}_{T} [GeV]");
  Numerator->GetYaxis()->SetTitle("");
  Numerator->SetLineColor(2);
  Numerator->SetLineWidth(3);
  Denominator->SetLineColor(4);
  Denominator->SetLineWidth(2);
  Denominator->Draw("same");

TLegend *leg = new TLegend(0.7404453,0.7122374,0.9787998,0.8845668,NULL,"brNDC");
gStyle->SetLegendFont(60);
leg->SetTextSize(0.03446589);
leg->SetFillColor(0);
leg->SetFillStyle(1002);
//leg->AddEntry(Numerator, "Trigger Cut");
//leg->AddEntry(Denominator, "Met Cut");
leg->AddEntry(Numerator, "#mu is #nu");
leg->AddEntry(Denominator, "#mu is not #nu");
leg->Draw();


}

void setTDRStyle(){
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  
  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);
  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);
  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);
  
  // For the histo:
  tdrStyle->SetHistFillColor(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  tdrStyle->SetErrorX(0.);
  
  tdrStyle->SetMarkerStyle(20);
  
  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);
  
  //For the date:
  tdrStyle->SetOptDate(0);
  
  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat("e"); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kGray);
  tdrStyle->SetStatFont(42);
  
  tdrStyle->SetTextSize(11);
  tdrStyle->SetTextAlign(11);
  
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(0);
  tdrStyle->SetStatX(1.); //Starting position on X axis
  tdrStyle->SetStatY(1.); //Starting position on Y axis
  tdrStyle->SetStatFontSize(0.025); //Vertical Size
  tdrStyle->SetStatW(0.25); //Horizontal size 
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  
  // Margins:
  tdrStyle->SetPadTopMargin(0.095);
  tdrStyle->SetPadBottomMargin(0.125);
  tdrStyle->SetPadLeftMargin(0.14);
  tdrStyle->SetPadRightMargin(0.1);
  
  // For the Global title:
  
  //  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  tdrStyle->SetTitleH(0.045); // Set the height of the title box
  //tdrStyle->SetTitleW(0); // Set the width of the title box
  tdrStyle->SetTitleX(0.15); // Set the position of the title box
  tdrStyle->SetTitleY(1.0); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  tdrStyle->SetTitleBorderSize(0);
  
  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.0);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset
  
  // For the axis labels:
  
  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.03, "XYZ");
  
  // For the axis:
  
  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);
  
  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);
  
  tdrStyle->cd();
}
TF1* fitGamma(TGraphAsymmErrors* g, double q, double p)
{
  
  double  fitf(double *v, double *par){
    double arg = 0;
    if (par[3] != 0){
    //if (par[1] >= 1 && par[0] >0 ){
      arg = (TMath::Sqrt(v[0]) - TMath::Sqrt(par[2]))/(2*par[3]);
      double fitval =  par[0] + par[1]*TMath::Freq(arg);
      
      //double fitval =  crystalball_integrall(v[0], par[0], par[1], par[2], par[3]); 
      
      return fitval;
    }
  }
  
  TF1 *fit = new TF1("fit",fitf, 0, 300,4);
  fit->SetParameters(q, p, g->GetMean(1),g->GetRMS(1));
  fit->SetParNames("P0", "P1", "Mean","Sigma");
  fit->SetLineColor(2);
  fit->SetLineWidth(3);
  g->Fit("fit","R", 0, 300);
  return fit;
}

double crystalball_integrall(double x, double alpha, double n, double mean, double sigma)
{
  // compute the integral of the crystal ball function (ROOT::Math::crystalball_function)
  // If alpha > 0 the integral is the right tail integral.
  // If alpha < 0 is the left tail integrals which are always finite for finite x.     
  // parameters:
  // alpha : is non equal to zero, define the # of sigma from which it becomes a power-law function (from mean-alpha*sigma)
  // n > 1 : is integrer, is the power of the low  tail
  // add a value xmin for cases when n <=1 the integral diverges 
  if (sigma == 0)   return 0;
  if (alpha==0)
    {
      MATH_ERROR_MSG("crystalball_integral","CrystalBall function not defined at alpha=0");
      return 0.;
    }
  bool useLog = (n == 1.0); 
  if (n<=0)   MATH_WARN_MSG("crystalball_integral","No physical meaning when n<=0");
  
  double z = (x-mean)/sigma;
  double zz = (sqrt(x)-sqrt(mean))/(2*sigma);
  if (alpha < 0 ){
    z = -z;
    zz = -zz;}
  
   double abs_alpha = abs(alpha);   
   double intgaus = 0.;
   double intpow  = 0.;
   const double sqrtpiover2 = sqrt(TMath::Pi()/2.);
   if (z <= -abs_alpha)
    {
    double A = std::pow(n/abs_alpha,n) * std::exp(-0.5 * alpha*alpha);
    double B = n/abs_alpha - abs_alpha;
     if (!useLog) {
	double C = (n/abs_alpha) * (1./(n-1)) * std::exp(-alpha*alpha/2.);
	intpow  = C - A /(n-1.) * std::pow(B-z,-n+1) ;
      }
      else {
	// for n=1 the primitive of 1/x is log(x)
	intpow = -A * std::log( n / abs_alpha ) + A * std::log(B-z );
      }

       intgaus =   TMath::Freq(zz); 
    }
   if (z>= -abs_alpha)
     {
     double intgaus = TMath::Freq(zz);
     intpow = 0;
     } 
  
   return intgaus + intpow;
}

// otra funcion 

double crystalball_integral(double x, double alpha, double n, double mean, double sigma)
{
  // compute the integral of the crystal ball function (ROOT::Math::crystalball_function)
  // If alpha > 0 the integral is the right tail integral.
  // If alpha < 0 is the left tail integrals which are always finite for finite x.     
  // parameters:
  // alpha : is non equal to zero, define the # of sigma from which it becomes a power-law function (from mean-alpha*sigma)
  // n > 1 : is integrer, is the power of the low  tail
  // add a value xmin for cases when n <=1 the integral diverges 
  if (sigma == 0)   return 0;
  if (alpha==0)
    {
      MATH_ERROR_MSG("crystalball_integral","CrystalBall function not defined at alpha=0");
      return 0.;
    }
  bool useLog = (n == 1.0); 
  if (n<=0)   MATH_WARN_MSG("crystalball_integral","No physical meaning when n<=0");
  
  double z = (x-mean)/sigma;
  double zz = (sqrt(x)-sqrt(mean))/2*sigma;
  if (alpha < 0 ) z = -z;
  if (alpha < 0 ) zz = -zz;
  
  double abs_alpha = abs(alpha);
  
  
  //double D = *(1.+ROOT::Math::erf(abs_alpha/std::sqrt(2.)));
  //double N = 1./(sigma*(C+D));
  double intgaus = 0.;
  double intpow  = 0.;
  
  const double sqrtpiover2 = sqrt(TMath::Pi()/2.);
  const double sqrt2pi = sqrt( 2.*TMath::Pi()); 
  const double oneoversqrt2 = 1./sqrt(2.);
  if (z <= -abs_alpha)
    {
      double A = std::pow(n/abs_alpha,n) * std::exp(-0.5 * alpha*alpha);
      double B = n/abs_alpha - abs_alpha;
      
      if (!useLog) {
	double C = (n/abs_alpha) * (1./(n-1)) * std::exp(-alpha*alpha/2.);
	intpow  = C - A /(n-1.) * std::pow(B-z,-n+1) ;
      }
      else {
	// for n=1 the primitive of 1/x is log(x)
	intpow = -A * std::log( n / abs_alpha ) + A * std::log( B -z );
      }
      // intgaus =  sqrtpiover2*(1.+ROOT::Math::erf(abs_alpha*oneoversqrt2));
      intgaus =   sqrtpiover2*(1.+TMath::Freq(zz));
    }
  else
    {
      intgaus = ROOT::Math::gaussian_cdf_c(z, 1);
      intgaus *= sqrt2pi;
      intpow  =  0;  
    }
  return sigma * (intgaus + intpow);
}

