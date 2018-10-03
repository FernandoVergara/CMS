#include "TFile.h"
#include "TTree.h"

#include "TH1F.h"

#include "THStack.h"
#include "TLegend.h"
#include "TColor.h"
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
using namespace std;

void setTDRStyle();
void PLOTTER_Mass(){

  TCanvas* c1 = new TCanvas("c1","c1");

  c1->SetWindowSize(600, 800);
  c1->SetCanvasSize(600, 800);
  
  //gStyle->SetOptStat(0);

  int min = 200;
  int max = 900;
  int nb = 8;
  float BINS[9] = {200.0, 225.0, 250.0, 300.0, 350.0, 450.0, 600.0, 750.0, 900.0};  
  
  Int_t cVV = 17561; // color index                                                                     
  TColor *colorVV = new TColor(cVV, 222.0/255.0,  90.0/255.0, 106.0/255.0 );
  Int_t cWJet = 17562; // color index                                                                 
  TColor *colorWJet = new TColor(cWJet, 100.0/255.0, 182.0/255.0, 232.0/255.0 );
  Int_t cTT = 17563; // color index                                                                     
  TColor *colorTT = new TColor(cTT, 155.0/255.0, 152.0/255.0, 204.0/255.0 );
  Int_t cQCD = 17564; // color index                                                                    
  TColor *colorQCD = new TColor(cQCD, 250.0/255.0, 202.0/255.0, 255.0/255.0);
  Int_t cDY = 17565; // color index                                                                     
  TColor *colorDY = new TColor(cDY, 248.0/255.0, 206.0/255.0, 104.0/255.0);
    
  //-------------------------------SR_FILES------------------------------
  TFile *QCD_SR = TFile::Open("SR/QCD.root","READ");
  if (QCD_SR == 0) {
    printf("Error: cannot open QCD \n");
    return;
    }

  TFile *Data_SR = TFile::Open("SR/Data.root","READ");
  if (Data_SR == 0) {
    printf("Error: cannot open DY \n");
    return;
    }

  TFile *DY_SR = TFile::Open("SR/DY+Jets.root","READ");
  if (DY_SR == 0) {
    printf("Error: cannot open DY \n");
    return;
    }

  TFile *VV_SR = TFile::Open("SR/VV.root","READ");
  if (VV_SR == 0) {
    printf("Error: cannot open DiBoson \n");
    return;
    }

  TFile *WJ_SR = TFile::Open("SR/W+Jets.root","READ");
  if (WJ_SR == 0) {
    printf("Error: cannot open WJets \n");
    return;
    }

  TFile *TT_SR = TFile::Open("SR/tbar{t}.root","READ");
  if (TT_SR == 0) {
    printf("Error: cannot open TTbar_SR \n");
    return;
    }

  TFile *SR_1500 = TFile::Open("SR/Zprime1500.root","READ");
  if (TT_SR == 0) {
    printf("Error: cannot open Zprime1500 \n");
    return;
    }

  // SR MASS HISTOGRAMS-UNBINNED
  TH1D *Mass_QCD_SR = (TH1D*)QCD_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  Mass_QCD_SR->Sumw2();
  //  Mass_QCD_SR->Scale(1.34);
  TH1D *Mass_DY_SR = (TH1D*)DY_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_Data_SR = (TH1D*)Data_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_DiBoson_SR = (TH1D*)VV_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_WJ_SR = (TH1D*)WJ_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_TTbar_SR = (TH1D*)TT_SR->Get("NDiTauCombinations/DiTauReconstructableMass");

  TH1D *Mass_SR_1500 = (TH1D*)SR_1500->Get("NDiTauCombinations/DiTauReconstructableMass");
  
  // TOTAL MASS ERROR 
  TH1D *error_SR = new TH1D("error_SR", "error_SR", Mass_DY_SR->GetXaxis()->GetNbins(), Mass_DY_SR->GetXaxis()->GetXmin(), Mass_DY_SR->GetXaxis()->GetXmax() );
  error_SR->Sumw2();
  error_SR->Add(Mass_DiBoson_SR);
  error_SR->Add(Mass_WJ_SR);
  error_SR->Add(Mass_TTbar_SR);
  error_SR->Add(Mass_DY_SR);
  error_SR->Add(Mass_QCD_SR);
  error_SR->Sumw2();


  // binned MASS histos 
  TH1D *H_error_SR = new TH1D("h_error_SR", "h_error_SR", nb, BINS);
  TH1D *H_Mass_Data_SR = new TH1D("h_Data_SR", "h_Data_SR", nb, BINS);
  TH1D *H_Mass_DY_SR = new TH1D("h_DY_SR", "h_DY_SR", nb, BINS);
  TH1D *H_Mass_QCD_SR = new TH1D("h_QCD_SR", "h_QCD_SR", nb, BINS);
  TH1D *H_Mass_WJ_SR = new TH1D("h_WJ_SR", "h_WJ_SR", nb, BINS);
  TH1D *H_Mass_TTbar_SR = new TH1D("h_TTbar_SR", "h_TTbar_SR", nb, BINS);
  TH1D *H_Mass_DiBoson_SR = new TH1D("h_DiBoson_SR", "h_DiBoson_SR", nb, BINS);

  TH1D *H_Mass_SR_1500 = new TH1D("h_SR_1500", "h_SR_1500", nb, BINS);
  
  Int_t nbins   = Mass_Data_SR->GetXaxis()->GetNbins(); 

  for (int b = 1; b <= H_Mass_Data_SR->GetXaxis()->GetNbins(); b++ ){
    double num_DY = 0; 
    double num_QCD = 0;
    double num_DiBoson = 0;
    double num_WJets = 0;
    double num_TTbar = 0;
    double num_Data_SR = 0;

    double num_SR_1500 = 0;

    double num_error = 0;
    double num_error_error = 0;

    double num_DY_width = 0; 
    double num_QCD_width = 0;
    double num_DiBoson_width = 0;
    double num_WJets_width = 0;
    double num_TTbar_width = 0;
    double num_Data_SR_width = 0;

    double num_SR_1500_width = 0;
    
    double num_error_width = 0;
    double num_error_error_width = 0;



    for (int i = 1; i <= nbins; i++ ){
      if(((( Mass_Data_SR->GetXaxis()->GetBinLowEdge(i)) + (Mass_Data_SR->GetXaxis()->GetBinWidth(i))) <= ((H_Mass_Data_SR->GetXaxis()->GetBinLowEdge(b))+ (H_Mass_Data_SR->GetXaxis()->GetBinWidth(b)))) && ((( Mass_Data_SR->GetXaxis()->GetBinLowEdge(i))+ (Mass_Data_SR->GetXaxis()->GetBinWidth(i))) > ((H_Mass_Data_SR->GetXaxis()->GetBinLowEdge(b))))){
	
	num_Data_SR += Mass_Data_SR->GetBinContent(i);
	num_DY += Mass_DY_SR->GetBinContent(i);
	num_QCD += Mass_QCD_SR->GetBinContent(i);
	num_DiBoson += Mass_DiBoson_SR->GetBinContent(i);
	num_TTbar += Mass_TTbar_SR->GetBinContent(i);
	num_WJets += Mass_WJ_SR->GetBinContent(i);

	num_error += error_SR->GetBinContent(i);
	//	num_error_error += error->GetBinError(i);

	num_SR_1500 += Mass_SR_1500->GetBinContent(i);
	
      }else if( ( Mass_Data_SR->GetXaxis()->GetBinLowEdge(i)) >= (H_Mass_Data_SR->GetXaxis()->GetBinLowEdge(nb)+ (H_Mass_Data_SR->GetXaxis()->GetBinWidth(nb))) && b==nb){//---- ELSE ES SOLO PARA EL OVERFLOW... SI SE NO QUIERE OVERFLOW (QUITAR ESTE ELSE)

	num_Data_SR += Mass_Data_SR->GetBinContent(i);
	num_DY += Mass_DY_SR->GetBinContent(i);
	num_QCD += Mass_QCD_SR->GetBinContent(i);
	num_DiBoson += Mass_DiBoson_SR->GetBinContent(i);
	num_TTbar += Mass_TTbar_SR->GetBinContent(i);
	num_WJets += Mass_WJ_SR->GetBinContent(i);
	num_error += error_SR->GetBinContent(i);
	//	num_error_error += abs(error->GetBinError(i));
	
	num_SR_1500 += Mass_SR_1500->GetBinContent(i);

      }else if( ( Mass_Data_SR->GetXaxis()->GetBinLowEdge(i)) < (H_Mass_Data_SR->GetXaxis()->GetBinLowEdge(1)+ (H_Mass_Data_SR->GetXaxis()->GetBinWidth(1))) && b==1){//---- ELSE ES SOLO PARA EL UNDERFLOW... SI SE NO QUIERE OVERFLOW (QUITAR ESTE ELSE)
	num_Data_SR += Mass_Data_SR->GetBinContent(i);
	num_DY += Mass_DY_SR->GetBinContent(i);
	num_QCD += Mass_QCD_SR->GetBinContent(i);
	num_DiBoson += Mass_DiBoson_SR->GetBinContent(i);
	num_TTbar += Mass_TTbar_SR->GetBinContent(i);
	num_WJets += Mass_WJ_SR->GetBinContent(i);
	num_error += error_SR->GetBinContent(i);
	//	num_error_error += abs(error->GetBinError(i));

	num_SR_1500 += Mass_SR_1500->GetBinContent(i);
		
      }else{
	continue;
      }
      
      H_Mass_Data_SR->SetBinContent(b, num_Data_SR);
      H_Mass_DY_SR->SetBinContent(b, num_DY);
      H_Mass_QCD_SR->SetBinContent(b, num_QCD);
      H_Mass_DiBoson_SR->SetBinContent(b, num_DiBoson);
      H_Mass_WJ_SR->SetBinContent(b, num_WJets);
      H_Mass_TTbar_SR->SetBinContent(b, num_TTbar);

      H_error_SR->SetBinContent(b, num_error );
      //      H_error_SR->SetBinError(b, H_error->GetBinError(b));
      H_Mass_SR_1500->SetBinContent(b, num_SR_1500);
      
    }
  }

  double err = 0;
  double data =0;
  double dy = 0;
  double qcd =0;
  double wj =0;
  double tt = 0;
  double vv =0;
  double binwdith = 0;

  
  
  for (int b = 1; b <= H_Mass_Data_SR->GetXaxis()->GetNbins(); b++ ){
    binwidth = BINS[b]-BINS[b-1];

    // error 
    H_error_SR->SetBinError(b,H_error_SR->GetBinError(b)/binwidth); 

    H_Mass_Data_SR->SetBinError(b,H_Mass_Data_SR->GetBinError(b)/binwidth);
    H_Mass_DY_SR->SetBinError(b,H_Mass_DY_SR->GetBinError(b)/binwidth);
    H_Mass_QCD_SR->SetBinError(b,H_Mass_QCD_SR->GetBinError(b)/binwidth); 
    H_Mass_WJ_SR->SetBinError(b,H_Mass_WJ_SR->GetBinError(b)/binwidth); 
    H_Mass_TTbar_SR->SetBinError(b,H_Mass_TTbar_SR->GetBinError(b)/binwidth); 
    H_Mass_DiBoson_SR->SetBinError(b,H_Mass_DiBoson_SR->GetBinError(b)/binwidth);

    H_Mass_SR_1500->SetBinError(b,H_Mass_SR_1500->GetBinError(b)/binwidth); 

    // BIN CONTENT
    H_error_SR->SetBinContent(b,H_error_SR->GetBinContent(b)/binwidth);

    H_Mass_Data_SR->SetBinContent(b,H_Mass_Data_SR->GetBinContent(b)/binwidth); 
    H_Mass_DY_SR->SetBinContent(b,H_Mass_DY_SR->GetBinContent(b)/binwidth);
    H_Mass_QCD_SR->SetBinContent(b,H_Mass_QCD_SR->GetBinContent(b)/binwidth); 
    H_Mass_WJ_SR->SetBinContent(b,H_Mass_WJ_SR->GetBinContent(b)/binwidth); 
    H_Mass_TTbar_SR->SetBinContent(b,H_Mass_TTbar_SR->GetBinContent(b)/binwidth); 
    H_Mass_DiBoson_SR->SetBinContent(b,H_Mass_DiBoson_SR->GetBinContent(b)/binwidth); 

    H_Mass_SR_1500->SetBinContent(b,H_Mass_SR_1500->GetBinContent(b)/binwidth); 
    
  }


  //error bars stack plot
  int errorbins =  H_error_SR->GetXaxis()->GetNbins();
  Double_t* mcX = new Double_t[errorbins];
  Double_t* mcY = new Double_t[errorbins];
  Double_t* mcErrorX = new Double_t[errorbins];
  Double_t* mcErrorY = new Double_t[errorbins];
  
  for(int bin=0; bin < H_error_SR->GetXaxis()->GetNbins(); bin++) {
    mcY[bin] = H_error_SR->GetBinContent(bin+1);
    mcErrorY[bin] = H_error_SR->GetBinError(bin+1);
    mcX[bin] = H_error_SR->GetBinCenter(bin+1);
    mcErrorX[bin] = H_error_SR->GetBinWidth(bin+1) * 0.5;
  }
  
  TGraphErrors *mcError = new TGraphErrors(H_error_SR->GetXaxis()->GetNbins(),mcX,mcY,mcErrorX,mcErrorY);

  mcError->SetLineWidth(kGray+2);
  mcError->SetFillColor(kGray+2);
  mcError->SetFillStyle(3344);
  
  delete[] mcX;
  delete[] mcY;
  delete[] mcErrorX;
  delete[] mcErrorY;


  // stack style
  H_Mass_DY_SR->SetLineColor(1);
  H_Mass_DY_SR->SetFillColor(cDY);

  H_Mass_QCD_SR->SetLineColor(1);
  H_Mass_QCD_SR->SetFillColor(cQCD);

  H_Mass_DiBoson_SR->SetLineColor(1);
  H_Mass_DiBoson_SR->SetFillColor(cVV);

  H_Mass_WJ_SR->SetLineColor(1);
  H_Mass_WJ_SR->SetFillColor(cWJet);

  H_Mass_TTbar_SR->SetLineColor(1);
  H_Mass_TTbar_SR->SetFillColor(cTT);

  H_Mass_Data_SR->SetLineColor(1);
  H_Mass_Data_SR->SetMarkerStyle(20);

  H_Mass_SR_1500->SetLineColor(kBlue);
  H_Mass_SR_1500->SetLineStyle(2);

  
  TPad *pad1 = new TPad("pad1", "pad1",0.01,0.33,0.99,0.99);
  pad1->Draw();
  pad1->cd();
  pad1->SetLogy();

  pad1->SetFillColor(0);
  pad1->SetBorderMode(0);
  pad1->SetBorderSize(2);
  pad1->SetTickx(1);
  pad1->SetTicky(1);
  
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0.01);
  
  pad1->SetFrameFillStyle(0);
  pad1->SetFrameBorderMode(0);
  pad1->SetFrameFillStyle(0);
  pad1->SetFrameBorderMode(0);

  
  //--------------FIRSTPAD
  //  THStack *hs = new THStack("hs","CMS Preliminary 35.9 fb^{-1} (13 TeV)");7

  // stack
  THStack *hs = new THStack("hs","");
  hs->Add(H_Mass_DiBoson_SR);
  hs->Add(H_Mass_WJ_SR);
  hs->Add(H_Mass_TTbar_SR);
  hs->Add(H_Mass_QCD_SR);
  hs->Add(H_Mass_DY_SR);

  
  THStack* hsdraw = hs;

  hsdraw->Draw("HIST");


  // stack style
  hsdraw->GetYaxis()->SetTitle("Events / GeV");
  hsdraw->GetXaxis()->SetRangeUser(min, max);
  hsdraw->GetYaxis()->SetLabelFont(42);
  hsdraw->GetYaxis()->SetLabelOffset(0.007);
  hsdraw->GetYaxis()->SetNdivisions(510);
  hsdraw->GetYaxis()->SetTitleOffset(0.8);
  hsdraw->GetYaxis()->SetTitleSize(0.075);
  hsdraw->GetYaxis()->SetLabelSize(0.05);
  hsdraw->GetXaxis()->SetNdivisions(510);
  hsdraw->GetXaxis()->SetLabelOffset(10);
    
  
  hsdraw->SetMaximum(52); //logaritmic case
  //  hsdraw->SetMaximum(5); // normal case
  hsdraw->SetMinimum(0.001);


  //Signal Scale
  H_Mass_SR_1500->Scale(10);  

  H_Mass_Data_SR->Draw("E1 same");
  H_Mass_SR_1500->Draw("HIST same");  
  mcError->Draw("2");
  H_Mass_Data_SR->Draw("P same");    

  // legend
  TLegend *leg_massZprime = new TLegend(0.62, 0.6, 0.82, 0.88);

  leg_massZprime->SetFillColor(0);
  leg_massZprime->SetBorderSize(1);
  leg_massZprime->SetTextSize(0.03);
  leg_massZprime->SetBorderSize(0);
  leg_massZprime->SetTextSize(0.03);

  leg_massZprime->AddEntry(H_Mass_Data_SR,"Observed","lep");
  leg_massZprime->AddEntry(H_Mass_DY_SR,"Z/#gamma* #rightarrow ll","f");
  leg_massZprime->AddEntry(H_Mass_QCD_SR,"QCD","f");
  leg_massZprime->AddEntry(H_Mass_TTbar_SR,"t#bar{t}","f");
  leg_massZprime->AddEntry(H_Mass_WJ_SR,"W+Jets","f");
  leg_massZprime->AddEntry(H_Mass_DiBoson_SR,"VV","f");
  leg_massZprime->AddEntry(H_Mass_SR_1500,"10 x Z'(1500) #rightarrow#tau#tau","L");

  leg_massZprime->Draw();


  // CMS, lumi and channel text
  t = c1->GetTopMargin();
  l = c1->GetLeftMargin();
  ri = c1->GetRightMargin();
  b = c1->GetBottomMargin();

  texcms = new TLatex(0.15,1-t+0.2*t,"CMS");
  texcms->SetNDC();
  texcms->SetTextFont(61);
  texcms->SetTextSize(0.075);
  texcms->Draw("same");

  texlumi = new TLatex(0.52,1-t+0.2*t,"35.9 fb^{-1} (13 TeV)");
  texlumi->SetNDC();
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.06);
  texlumi->Draw("same");

  textautau = new TLatex(0.18,0.85,"#tau_{h}#tau_{h}");
  textautau->SetNDC();
  textautau->SetTextFont(42);
  textautau->SetTextSize(0.045);
  textautau->Draw("same");

  
  c1->cd();   
  

  //--------------RATIO PAD
  //  TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.3);
  TPad *pad2 = new TPad("pad2", "pad2",0.01,0.0,0.99,0.32);


  pad2->Draw();
  pad2->cd();

  // pad style
  pad2->SetFillColor(0);
  pad2->SetFillStyle(4000);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(2);
  pad2->SetTickx(1);
  pad2->SetTicky(1);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0.02);
  pad2->SetBottomMargin(0.3);
  pad2->SetFrameFillStyle(0);
  pad2->SetFrameBorderMode(0);


  TH1D *H_Sig = (TH1D*)H_Mass_Data_SR->Clone("data");
  TH1D *BKG = (TH1D*)H_error_SR->Clone("bkg");
  // set data error to zero
  for (int b = 1; b <= H_Sig->GetXaxis()->GetNbins(); b++ ){
    H_Sig->SetBinError(b, 0);
  }

  // ratio 
  H_Sig->Divide(BKG);

  H_Sig->SetStats(0);      // No statistics on lower plot


  //----- ERROR Ratio 
  
  TH1D *H_ERROR = (TH1D*)H_Sig->Clone("DataMCR");
  int errorbins1 =  H_ERROR->GetXaxis()->GetNbins();
  Double_t* mcX1 = new Double_t[errorbins1];
  Double_t* mcY1 = new Double_t[errorbins1];
  Double_t* mcErrorX1 = new Double_t[errorbins1];
  Double_t* mcErrorY1 = new Double_t[errorbins1];

  double errorhigher1;
  
 for(int bin=0; bin < H_ERROR->GetXaxis()->GetNbins(); bin++) {
   
   mcY1[bin] = 1.0;
   cout << H_ERROR->GetBinContent(bin+1) << "  +-  " << H_ERROR->GetBinError(bin+1) << " error  " << H_ERROR->GetBinError(bin+1)/H_ERROR->GetBinContent(bin+1) << endl;
   errorhigher1 = H_ERROR->GetBinError(bin+1)/H_ERROR->GetBinContent(bin+1);
   if(errorhigher1 >= 1.0){
     //     mcErrorY1[bin] = 1.0;  no systematics
     mcErrorY1[bin] = 1.0 + 0.1;
   }else{
     //     mcErrorY1[bin] = errorhigher1; // no systematics
     mcErrorY1[bin] = errorhigher1 + (0.1 * errorhigher1);
   }
   mcX1[bin] = H_ERROR->GetBinCenter(bin+1);
   mcErrorX1[bin] = H_ERROR->GetBinWidth(bin+1) * 0.5;
 }                                                                                                                                                                                    
  
 TGraphErrors *mcError1 = new TGraphErrors(H_ERROR->GetXaxis()->GetNbins(),mcX1,mcY1,mcErrorX1,mcErrorY1);
  mcError1->SetLineWidth(kGray);
  mcError1->SetFillColor(kGray);
  mcError1->SetFillStyle(3344);

  delete[] mcX1;                                                                                                  
  delete[] mcY1;                                                                                                                    
  delete[] mcErrorX1;                                                                                                                                                                 
  delete[] mcErrorY1; 


  // pad ratio style
  H_Sig->SetMinimum(0);  // Define Y ..
  H_Sig->SetMaximum(3); // .. range
  
  H_Sig->GetXaxis()->SetLabelFont(42);
  H_Sig->GetXaxis()->SetTitleFont(42);
  H_Sig->GetXaxis()->SetLabelSize(0.11);
  H_Sig->GetXaxis()->SetTitleSize(0.12);
  H_Sig->GetXaxis()->SetTitleOffset(0.9);
  H_Sig->GetXaxis()->SetLabelOffset(0.007);

  H_Sig->GetYaxis()->SetTitleFont(42);
  H_Sig->GetYaxis()->SetLabelFont(42);
  H_Sig->GetYaxis()->SetLabelSize(0.075);
  H_Sig->GetYaxis()->SetNdivisions(5,5,0);
  H_Sig->GetYaxis()->SetTitleSize(0.13);
  H_Sig->GetYaxis()->SetTitleOffset(0.44);
  H_Sig->GetYaxis()->SetLabelOffset(0.015);
  H_Sig->GetYaxis()->CenterTitle();

  H_Sig->SetLineColor(1);
  H_Sig->SetMarkerStyle(20);

  H_Sig->SetTitle("");
  H_Sig->GetYaxis()->SetTitle("Obs / Bkg");
  H_Sig->GetXaxis()->SetTitle("m(#tau_{h}, #tau_{h}, #slash{E}_{T}) [GeV]");

  // line ratio
  TLine *line = new TLine(min,1,max,1);
  line->SetLineColor(kRed);
  line->SetLineStyle(1);


  H_Sig->Draw("E1");    
  line->Draw("L same");
  mcError1->Draw("2 same");    
  H_Sig->Draw("P same");    

  return;
}  

void setTDRStyle(){
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  //  tdrStyle->SetCanvasDefH(600); //Height of canvas
  //  tdrStyle->SetCanvasDefW(600); //Width of canvas
  //  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  //  tdrStyle->SetCanvasDefY(0);
  // For the Pad:
  //  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  //  tdrStyle->SetPadGridX(false);
  //  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  //  tdrStyle->SetGridStyle(3);
  //  tdrStyle->SetGridWidth(1);
  // For the frame:
  //  tdrStyle->SetFrameBorderMode(0);
  //  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  //  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  //  tdrStyle->SetHistFillColor(0);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  //  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);
//  tdrStyle->SetEndErrorSize(0);


//  tdrStyle->SetErrorX(0.);


//  tdrStyle->SetErrorMarker(20);

  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  //  tdrStyle->SetFitFormat("5.4g");
  //tdrStyle->SetFuncColor(1);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat("e"); // To display the mean and RMS:   SetOptStat("mr");
  //tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatColor(kGray);
  //  tdrStyle->SetStatFont(42);

  tdrStyle->SetTextSize(11);
  //  tdrStyle->SetTextAlign(11);

  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  //  tdrStyle->SetStatBorderSize(0);
  tdrStyle->SetStatX(1.); //Starting position on X axis
  tdrStyle->SetStatY(1.); //Starting position on Y axis
  //  tdrStyle->SetStatFontSize(0.025); //Vertical Size
  tdrStyle->SetStatW(0.25); //Horizontal size 
  // tdrStyle->SetStatStyle(Style_t style = 1001);

  // Margins:
  tdrStyle->SetPadTopMargin(0.095);
  tdrStyle->SetPadBottomMargin(0.125);
  tdrStyle->SetPadLeftMargin(0.14);
  tdrStyle->SetPadRightMargin(0.1);

  // For the Global title:

  //  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  //  tdrStyle->SetTitleFontSize(0.05);
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
  //  tdrStyle->SetTitleXOffset(0.9);
  //  tdrStyle->SetTitleYOffset(1.0);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  //tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  //  tdrStyle->SetLabelSize(0.03, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  //  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);
  // Postscript options:
  // tdrStyle->SetPaperSize(15.,15.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);
  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();
}
