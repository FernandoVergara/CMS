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

void efficiency(){
  
  cout << "working" << endl;
  
  setTDRStyle();
  
  TCanvas* c1 = new TCanvas("c1","c1",200,200,800,700);
  c1->SetGrid();
  
  TFile *f1 = TFile::Open("data/Data_dirty.root","READ");
  TFile *f2 = TFile::Open("data/allback.root","READ");

 /* TFile *f1 = TFile::Open("data/Data_muisnu.root","READ");
  TFile *f2 = TFile::Open("data/W+jets_muisnu.root","READ");
*/
 
  if (f1 == 0) {
    printf("Error: cannot open Trig Eff root file \n");
    return;
  }
  
  
  TH1F *Numerator = (TH1F*)f1->Get("NRecoTriggers2/Met");
  TH1F *Denominator = (TH1F*)f1->Get("METCut/Met");

   TH1F *Numerator1 = (TH1F*)f2->Get("NRecoTriggers2/Met");
   TH1F *Denominator1 = (TH1F*)f2->Get("METCut/Met");



  /*
    TH1F *Numerator = (TH1F*)f1->Get("NRecoTriggers2/FirstLeadingJetPt");
    TH1F *Denominator = (TH1F*)f1->Get("METCut/FirstLeadingJetPt");
  */
  
  Int_t nbins   = Denominator->GetXaxis()->GetNbins();
  Int_t nbins1   = Denominator1->GetXaxis()->GetNbins();
   //Int_t nbins  = 20;
  
  cout<<"Numerator "<< Numerator->Integral()<<"   Denominator "<< Denominator->Integral()<<endl;
  cout<<"Numerator "<< Numerator->GetXaxis()->GetNbins()<<"   Denominator "<< Denominator->GetXaxis()->GetNbins() <<endl;
  
  int nb = 22;
  
  float BINSJET[35] = {10.0, 20.0,  30.0, 40.0, 50.0, 60.0, 70.0, 80.5, 90.0, 100.0, 
		       150.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0,
		       600.0, 700.0, 800.0, 900.0, 1000.0};  
  
  
  float BINS[48] = {50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 150.0, 
                    160.0, 170.0, 180.0, 190.0, 200.0, 210.0, 220.0, 230.0, 240.0, 250.0,
                    260.0, 270.0, 280.0, 290.0, 300.0, 310.0, 320.0, 330.0, 340.0, 350.0,
                    360.0, 370.0, 380.0, 390.0, 400.0, 410.0, 420.0, 430.0, 440.0, 450.0,
                    460.0, 470.0, 480.0, 490.0, 500.0};
  
  
  TH1F *H_bins_num = new TH1F("h_NUM", "h_NUM", 25, 50,300);
  TH1F *H_bins_den = new TH1F("h_DEN", "h_DEN", 25, 50,300);
   
  TH1F *H_bins_num1 = new TH1F("h_NUM1", "h_NUM1", 25, 50,300);
  TH1F *H_bins_den1 = new TH1F("h_DEN1", "h_DEN1", 25, 50,300);

  /*
  
  
    TH1F *H_bins_num = new TH1F("h_NUM", "h_NUM", nb, BINSJET);
    TH1F *H_bins_den = new TH1F("h_DEN", "h_DEN", nb, BINSJET);
    
  */
  for (int b = 1; b <= H_bins_den->GetXaxis()->GetNbins(); b++ ){
    int num_bin = 0;
    int den_bin = 0;
    
    for (int i = 1; i < nbins; i++ ){
      
      if(((( Denominator->GetXaxis()->GetBinLowEdge(i)) + (Denominator->GetXaxis()->GetBinWidth(i))) <= ((H_bins_den->GetXaxis()->GetBinLowEdge(b))+ (H_bins_den->GetXaxis()->GetBinWidth(b)))) &&
	 ((( Denominator->GetXaxis()->GetBinLowEdge(i))+ (Denominator->GetXaxis()->GetBinWidth(i))) > ((H_bins_den->GetXaxis()->GetBinLowEdge(b))))){
	
	num_bin += Numerator->GetBinContent(i);
	den_bin += Denominator->GetBinContent(i);
	
      }else{
	continue;
      }
      cout << num_bin << endl;
      H_bins_num->SetBinContent(b, num_bin);
      H_bins_den->SetBinContent(b, den_bin);
      
    }
    
  }
  //Para el segundo histograma 
  for (int b = 1; b <= H_bins_den1->GetXaxis()->GetNbins(); b++ ){
    int num_bin = 0;
    int den_bin = 0;
    
    for (int i = 1; i < nbins1; i++ ){
      
      if(((( Denominator1->GetXaxis()->GetBinLowEdge(i)) + (Denominator1->GetXaxis()->GetBinWidth(i))) <= ((H_bins_den1->GetXaxis()->GetBinLowEdge(b))+ (H_bins_den1->GetXaxis()->GetBinWidth(b)))) &&
	 ((( Denominator1->GetXaxis()->GetBinLowEdge(i))+ (Denominator1->GetXaxis()->GetBinWidth(i))) > ((H_bins_den1->GetXaxis()->GetBinLowEdge(b))))){
	
	num_bin += Numerator1->GetBinContent(i);
	den_bin += Denominator1->GetBinContent(i);
	
      }else{
	continue;
      }
      cout << num_bin << endl;
      H_bins_num1->SetBinContent(b, num_bin);
      H_bins_den1->SetBinContent(b, den_bin);
      
    }
    
  }
    


  for(int i = 0; i < nbins; i++){
    if(Denominator->GetXaxis()->GetNbins() >= i ){
      cout << "  Bin: " << i <<  " NumBinnned: "<< H_bins_num->GetBinContent(i) <<"  DenBinned: "<< H_bins_den->GetBinContent(i)<<  " Num: "<<Numerator->GetBinContent(i) <<"  Den: "<<Denominator->GetBinContent(i)<<endl;
    }else{
      cout << "  Bin: " << i <<  " NumBinnned: "<< " --- " <<"  DenBinned: "<< " --- " <<  " Num: "<<Numerator->GetBinContent(i) <<"  Den: "<<Denominator->GetBinContent(i)<<endl;
    }
  }
  
  
  TGraphAsymmErrors* gr1 = new TGraphAsymmErrors( H_bins_num, H_bins_den, "b(1,1) mode" );
  TGraphAsymmErrors* gr2 = new TGraphAsymmErrors( H_bins_num1, H_bins_den1, "b(1,1) mode" );
  
  
  TMultiGraph *mg = new TMultiGraph();
  
 
  mg->Add(gr1);
  mg->Add(gr2);
  
  mg->Draw("AP");

 // TF1* gr_fit = fitGamma(gr1, 0.5, 0.8);
//  TF1* gr2_fit = fitGamma1(gr2, 0.5, 0.9);

  gr1->SetMarkerColor(4);
  gr1->SetLineColor(2);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1.5);

  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.5);
 // gr1->Draw("AEP");
//  gr2_fit->Draw("same");  


 
  //gr2->Draw("AEP");
//  gr_fit->Draw("same");
  
  mg->SetTitle("Trigger Efficiency HLT_PFMETNoMu120_PFMHTNoMu120_IDTight");
  mg->GetXaxis()->SetTitle("E^{miss}_{T} [GeV]");
  //mg->GetXaxis()->SetTitle("p_{T}(leading \ jet) [GeV]");
  mg->GetXaxis()->SetLabelFont(42);
  mg->GetXaxis()->SetLabelSize(0.035);
  mg->GetXaxis()->SetTitleSize(0.05);
  mg->GetXaxis()->SetTitleOffset(0.89);
  mg->GetXaxis()->SetTitleFont(42);
  mg->GetYaxis()->SetTitle("#epsilon");
  mg->GetYaxis()->SetLabelFont(42);
  mg->GetYaxis()->SetLabelSize(0.035);
  mg->GetYaxis()->SetTitleSize(0.06);
  mg->GetYaxis()->SetTitleOffset(0.69);
  mg->GetYaxis()->SetTitleFont(42);
 
  TLegend *leg = new TLegend(0.7404453,0.7122374,0.9787998,0.8845668,NULL,"brNDC");
 gStyle->SetLegendFont(60);
leg->SetTextSize(0.03446589);
leg->SetFillColor(0);
leg->SetFillStyle(1002);

leg->AddEntry(gr1, "Data-dirty");
leg->AddEntry(gr2, "All backgrounds");

/*leg->AddEntry(gr1, "Data-clean");
leg->AddEntry(gr2, "W+jets");

*/leg->Draw();


 
}

void setTDRStyle(){
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  
  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(500); //Height of canvas
  tdrStyle->SetCanvasDefW(500); //Width of canvas
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
  tdrStyle->SetPadBottomMargin(0.15);
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

TF1* fitGamma1(TGraphAsymmErrors* g, double q, double p)
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
  fit->SetLineColor(4);
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

