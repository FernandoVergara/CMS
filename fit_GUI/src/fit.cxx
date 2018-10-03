#include "../inc/fit.h"
#include "../inc/style.h"
#include "../inc/Fill.h"
#include "TApplication.h"
#include "TBenchmark.h"
#include <iostream>
using namespace std;

fit::fit(const TGWindow *p,UInt_t w,UInt_t h){
  
  //Origin files
  
  f1 = new TFile("data/mu_isnotnu/met50/Data-clean.root","READ"); 
  f2 = new TFile("data/mu_isnotnu/met50/Data.root","READ");
  if (f1 == 0 || f2 == 0) {
    printf("Error: cannot open any files \n");
    gApplication->Terminate(0);
    return;
  }
  
  H1F1 = (TH1F*)f1->Get("NRecoTriggers2/Met");
  H2F1 = (TH1F*)f1->Get("METCut/Met");
  
  H1F2 = (TH1F*)f2->Get("NRecoTriggers2/Met");
  H2F2 = (TH1F*)f2->Get("METCut/Met");
  
  l1 = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY ,8,8,8,8);
  l2 = new TGLayoutHints(kLHintsCenterX | kLHintsCenterY ,8,8,8,8);
  
  TMF1 = new TGMainFrame(p,h,w);
  TMF1 -> SetWMSize(w,h);
  TMF1->SetWindowName("Fit software");
  TMF1->SetWMSizeHints(w,h,w,h,1,1);
  //Horizontal frame 
  HF1 = new TGHorizontalFrame(TMF1,2,2);  
  
  //Left Group Frames 
  //first vertical frame
  VFO1 = new TGVerticalFrame(HF1,2,2);
  //first group 
  GF1 = new TGGroupFrame(VFO1,"Parameters",kVerticalFrame);
  
  HFN = new TGHorizontalFrame(GF1);
  TGLN = new TGLabel(HFN,"Bin Number");
  NEN = new TGNumberEntry(HFN,0);
  NEN->SetNumStyle(TGNumberFormat::kNESInteger);  
  NEN->SetLimits(TGNumberFormat::kNELLimitMinMax,0,100);
  HFN->AddFrame(TGLN,l2);
  HFN->AddFrame(NEN,l2);
   TGLM = new TGLabel(HFN,"Min value");
     MIN = new TGNumberEntry(HFN, 50);
       MIN->SetNumStyle(TGNumberFormat::kNESInteger);
         MIN->SetLimits(TGNumberFormat::kNELLimitMinMax ,0.,1000.);

  HFN->AddFrame(TGLM,l2);
  HFN->AddFrame(MIN,l2);
  GF1->AddFrame(HFN,l1);
  
  
  HFl = new TGHorizontalFrame(GF1);
  TGLl = new TGLabel(HFl,"Max Value");
  NEl = new TGNumberEntry(HFl,300);
  NEl->SetNumStyle(TGNumberFormat::kNESInteger); 
  NEl->SetLimits(TGNumberFormat::kNELLimitMinMax ,0.,1000.);
  HFl->AddFrame(TGLl,l2);
  HFl->AddFrame(NEl,l2);
  GF1->AddFrame(HFl,l1);
  
  HFK = new TGHorizontalFrame(GF1); 
  NEK = new TGNumberEntry(HFK,1.0);
  HFK->AddFrame(NEK, l2);
  GF1->AddFrame(HFK, l1);
  
  S1 = new TGHSlider(GF1, 100, kSlider1|kScaleBoth, kHorizontalFrame);
  S1->SetRange(10.0, 110.0);
  S1->SetPosition(10.0);
  S1->Connect("GetPosition()","fit", this, "Run()");
  GF1->AddFrame(S1,l1);
  
  TS1 = new TGTripleHSlider(GF1, 100, kDoubleScaleBoth, kVerticalFrame);                                                                                  
  TS1->SetRange(50.0, 150.0);
  TS1->Connect("PointerPositionChanged()","fit", this, "Run()");
  TS1->Connect("PositionChanged()","fit", this, "Run()");
  TS1->SetPosition(50.0,150.0);
  TS1->SetPointerPosition(50.0);
  GF1->AddFrame(TS1, l1);
  
  
  
  VFO1->AddFrame(GF1, new TGLayoutHints(kLHintsTop | kLHintsCenterX));
  
  //Second Group
  GF2 = new TGGroupFrame(VFO1,"Options",kVerticalFrame);
  
  
  TGBDraw = new TGTextButton(GF2,"&Draw",1);
  TGBDraw->Connect("Clicked()","fit",this,"Draw()");
  GF2->AddFrame(TGBDraw,l1); 
  
  TGBRun = new TGTextButton(GF2, "&Start", 2);
  TGBRun->Connect("Clicked()", "fit", this, "Control()");
  TGBRun->SetState(kButtonUp);
  GF2->AddFrame(TGBRun,l1);
  
  
  TGBClear = new TGTextButton(GF2,"&Clear",3);
  TGBClear->Connect("Clicked()","fit",this,"Clear()");
  GF2->AddFrame(TGBClear,l1);
  
  
  VFO1->AddFrame(GF2, new TGLayoutHints(kLHintsTop | kLHintsCenterX));
  
  //Exit Buttom 
  TGBExit = new TGTextButton(VFO1,"&Exit","gApplication->Terminate(0)");
  VFO1->AddFrame(TGBExit, new TGLayoutHints(kLHintsBottom | kLHintsCenterX,3,3,3,3));
  //Save Buttom 
  TGBEImage = new TGTextButton(VFO1,"P&rint",2);
  TGBEImage->Connect("Clicked()","fit",this,"PrintImage()");
  // TGBEImage->SetEnabled(false);
  VFO1->AddFrame(TGBEImage, new TGLayoutHints(kLHintsBottom | kLHintsCenterX,3,3,3,3));
  
  
  
  //Adding first vertical group to the main horizontal frame
  HF1->AddFrame(VFO1,new TGLayoutHints(kLHintsExpandY,10,10,10,10));
  
  //Right frame (Canvas) Second vertical frame
  VFO2 = new TGVerticalFrame(HF1,2,2,2,2);
  
  TRootEmbeddedCanvas *EC1 = new TRootEmbeddedCanvas("EC1",VFO2,600,500);   
  c1 = EC1->GetCanvas();
  fit::setTDRStyle();
  VFO2->AddFrame(EC1,new TGLayoutHints(kLHintsNormal,1,1,1,1));
  
  PB = new TGHProgressBar(VFO2,TGProgressBar::kFancy, 600);
  PB->SetFillType(TGProgressBar::kSolidFill);
  PB->ShowPosition();
  PB->SetBarColor("blue");
  VFO2->AddFrame(PB,new TGLayoutHints(kLHintsNormal,1,1,1,1));
  
  //Adding second vertical group to the main horizontal frame
  HF1->AddFrame(VFO2,new TGLayoutHints(kLHintsNormal,10,10,10,10));
  
  
  //Creating a status bar
  SB = new TGStatusBar(TMF1);
  SB->SetParts(6);
  
  
  
  //Adding HF1 to the main frame
  TMF1->AddFrame(HF1);
  TMF1->AddFrame(SB, new TGLayoutHints(kLHintsExpandX,1,1,1,1));
  
  
  //necessary setup
  TMF1->MapSubwindows();
  TMF1->Resize(TMF1->GetDefaultSize());
  TMF1->MapWindow();
  
  
  //Timer for loops
  CountState=2;
  Count = new TTimer(100);
  Count->Connect("Timeout()","fit",this,"Run()");
  
  
  P=10; MP=0; CP=0; mP=0; counter=1; counter2=1;
  TGBClear->SetEnabled(false);
  TGBRun->SetEnabled(false);


}
void fit::Draw(){
 
  c1->Clear();
  PB->Reset();
  c1->Update();


  pad1 = new TPad("pad1", "pad1", 0, 1 / (1.0 + 3.0), 1, 1, 0);
  pad1->SetPad("pad1", "pad1", 0, 1 / (1.0 + 3.0), 1, 1, 0);
  pad1->Draw();
  pad2 = new TPad("pad2", "pad2", 0, 0, 1, 1 / (1.0 + 3.0), 0);
  pad2->SetPad("pad2", "pad2", 0, 0, 1, 1 / (1.0 + 2.5), 0);
  pad2->SetMargin(0.14,0.1,0.2,0.1);
  pad2->SetTitle("");
  pad2->Draw();


  pad1->cd();
  fit::Fill(H1F1, H2F1, 25, 50, 300);
  gr1 = new TGraphAsymmErrors(H_bins_num, H_bins_den,"b(1,1) mode");  
  gr1->SetMarkerColor(4);
  gr1->SetLineColor(1);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1.5); 
  fit::DeleteFill(); 
  
  fit::Fill(H1F2, H2F2, 25, 50, 300);
  gr2 = new TGraphAsymmErrors(H_bins_num, H_bins_den,"b(1,1) mode");
  gr2->SetMarkerColor(2);
  gr2->SetLineColor(1);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.5);
  fit::DeleteFill();
  
  mg = new  TMultiGraph();
  mg->SetTitle("Trigger Efficiency HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;E^{miss}_{T} [GeV]; #epsilon");
  //mg->SetMinimum(0.);
  //mg->SetMaximum(1.2);
  mg->Add(gr1);
  mg->Add(gr2);
  
  mg->Draw("AP");
  mg->GetXaxis()->SetLimits(MIN->GetNumber()-10,NEl->GetNumber()+10);


  leg = new TLegend(0.5513784,0.3010432,0.8621554,0.4739195,NULL,"brNDC");
  leg->SetTextFont(62);
  leg->SetTextSize(0.03446589);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1002); 
  leg->AddEntry(gr1, "Data-withoutBG");
  leg->AddEntry(gr2, "Data");
  leg->Draw();
  
  pad1->Modified();
  

  c1->Modified(); 
  c1->Update();

  pad2->cd(); // Modify pad2  
  line1 = new TLine(MIN->GetNumber()-10, 1.0, NEl->GetNumber()+10, 1.0);
  line1->SetLineColor(kBlue);
  line1->SetLineWidth(3.0);
  line1->SetLineStyle(3);
  line1->Draw();
  pad2->Modified();
  
  c1->Modified();
  c1->Update();

  

  NEl->SetState(true);
  NEN->SetState(true);

  TGBDraw->SetEnabled(false);
  TGBRun->SetEnabled(true);
  TGBClear->SetEnabled(true);
  
}
void fit::Run(){

  Count->TurnOn(); 

  pad1->cd();  
  P=S1->GetPosition();
  MP=NEl->GetNumber();
  //MP=TS1->GetMaxPosition();
  CP=TS1->GetPointerPosition();
  mP=MIN->GetNumber();
  
  nbins=(MP-mP)/(P);
  NEN->SetLimits(TGNumberFormat::kNELLimitMinMax,0,nbins);
  fit::Fill(H1F1, H2F1, nbins , mP, MP);
  gr1 = new TGraphAsymmErrors(H_bins_num, H_bins_den,"b(1,1) mode");  
  gr1->SetMarkerColor(4);
  gr1->SetLineColor(1);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1.5); 
  error=gr1->GetErrorY(counter-1);
  clone1 = (TH1F*)H_bins_num->Clone("clone1");
  clone1->Divide(H_bins_den);
  binvalue1 = clone1->GetBinContent(counter-1);
  fit::DeleteFill(); 
  
  fit::Fill(H1F2, H2F2, nbins, mP, MP);
  gr2 = new TGraphAsymmErrors(H_bins_num, H_bins_den,"b(1,1) mode");
  gr2->SetMarkerColor(2);
  gr2->SetLineColor(1);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.5); 
  error2=gr2->GetErrorY(counter-1);
  clone2 = (TH1F*)H_bins_num->Clone("clone2");
  clone2->Divide(H_bins_den);
  binvalue2 = clone2->GetBinContent(counter-1);
  fit::DeleteFill();
  
  
  mg = new  TMultiGraph();
  mg->SetTitle("Trigger Efficiency HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;E^{miss}_{T} [GeV]; #epsilon");
//  mg->SetMinimum(0.6);
//  mg->SetMaximum(1.);
  mg->Add(gr1);
  mg->Add(gr2); 
  mg->Draw("AP");
  mg->GetXaxis()->SetLimits(MIN->GetNumber()-10,NEl->GetNumber()+10);
  leg->Draw();
  
 
  binserror[counter-1] = fit::ERROR(binvalue1,binvalue2,error,error2);
  counter++;
  sprintf(BINVALUE1,"Bin value: %.4f", binvalue1);
    SB->SetText(BINVALUE1,2);
      sprintf(ERROR1,"Bin error: %.4f", error);
        SB->SetText(ERROR1,3);
          sprintf(BINVALUE2,"Bin value: %.4f", binvalue2);
            SB->SetText(BINVALUE2,4);
              sprintf(ERROR2,"Bin error: %.4f", error2);
                SB->SetText(ERROR2,5);


  if(counter==24){Count->TurnOff();}

//  pad1->Modified();

  c1->Modified();
  c1->Update();
  

  pad2->cd();
/*  gr3 = new TGraphAsymmErrors(clone1, clone2,"b(1,1) mode"); 
  gr3->SetMarkerColor(1);
  gr3->SetLineColor(1);
  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(1.1);
  gr3->GetXaxis()->SetLabelSize(0.1);
  gr3->GetYaxis()->SetLabelSize(0.1);
  mg1 = new TMultiGraph();
 // mg1->SetMinimum(0.);
 // mg1->SetMaximum(2.);
 
  mg1->Add(gr3);
  //mg1->Draw("AP");
  mg1->GetXaxis()->SetLimits(40.0,310.0);
  mg1->GetXaxis()->SetLabelSize(0.1);
  mg1->GetYaxis()->SetLabelSize(0.1);
  
*/

  Count->TurnOn();
  if(counter2==25){Count->TurnOff();}
  gStyle->SetOptStat(0);
  clone1->Divide(clone1, clone2, 1, 1, "B");
  for(Int_t i=0; i<25;++i){
  clone1->SetBinError(i+1, binserror[i]);
  }
  clone1->SetStats("kFALSE");
  clone1->SetMarkerStyle(20);
  clone1->SetLineWidth(1);
  clone1->SetMarkerSize(1.0);
  clone1->SetTitle("");
  clone1->GetXaxis()->SetLabelSize(0.1);
  clone1->GetXaxis()->SetTitleOffset(0.7);
  clone1->GetYaxis()->SetLabelSize(0.1);
  clone1->GetYaxis()->SetTitleOffset(0.7); 
  clone1->Draw("PE1");
  clone1->SetAxisRange(MIN->GetNumber()-10, NEl->GetNumber()+10);
  clone1->SetMaximum(1.05);
  clone1->SetMinimum(-0.5);
  
  line1->Draw();
  pad2->Modified();

  c1->Modified();
  c1->Update();
 
  PB->Increment(100.0/25.0);

  sprintf(WIDTH,"Bin Width: %i",P);
  SB->SetText(WIDTH,0);
  sprintf(NBINS,"N bins: %i",nbins);
  SB->SetText(NBINS,1);

  sprintf(BINVALUE1,"Bin value: %.4f", binvalue1);
  SB->SetText(BINVALUE1,2);
  sprintf(ERROR1,"Bin error: %.6f", error);
  SB->SetText(ERROR1,3);
  sprintf(BINVALUE2,"Bin value: %.4f", binvalue2);
  SB->SetText(BINVALUE2,4);
  sprintf(ERROR2,"Bin error: %.6f", error2);
  SB->SetText(ERROR2,5);
  counter2++;

  TGBClear->SetEnabled(false);

}
void fit::Control(){
  if(CountState==0){
    Count->TurnOff();
    CountState=1;                                     //State->Pause
    TGBRun->SetText("C&ont");
    TGBDraw->SetEnabled(true);
    TGBClear->SetEnabled(true);
  }
  else if(CountState==2){
    CountState=0;                                     //State->Run
    TGBRun->SetText("&Pause");
    fit::Run();
  }
  else if(CountState==1){
    Count->TurnOn();
    CountState=0;                                     //State->Run
    TGBRun->SetText("&Pause");
  }
}

void fit::Clear(){
  c1->Clear();
  c1->Update();
  PB->Reset();
  TGBDraw->SetEnabled(true);
  TGBRun->SetEnabled(false);
}

double fit::ERROR(Double_t x, Double_t y, Double_t ex, Double_t ey){
if(y != 0 && x!=0){
double error = (x/y)*TMath::Sqrt(TMath::Power(ex/x,2)+TMath::Power(ey/y,2));
return error;
}
else return 0.003;
}


void fit::sizePad(double ratio, TVirtualPad* pad, bool isTop) {
  if(isTop){ pad->SetPad("top", "top", 0, 1 / (1.0 + ratio), 1, 1, 0); 
             pad->Draw();
             }
    else  {
            pad->SetPad("bottom", "bottom", 0, 0, 1, 1 / (1.0 + ratio), 0);
            pad->SetMargin(0.14,0.1,0.2,0.1);
            pad->SetTitle("");
            pad->Draw();
}
}


fit::~fit(){
  TMF1->Cleanup();
  delete TMF1;
}

void fit::PrintImage(){
  const char *filetypes[] = { "PDF file",    "*.pdf",
			      "PNG file",    "*.png",
			      "EPS file",    "*.eps",
                  ".C file" ,    "*.C"  ,
                  "All files",     "*",
                  
			      0,  0};
  TGFileInfo fi;
  fi.fFileTypes = filetypes;
  TGfd = new TGFileDialog(gClient->GetRoot(),TMF1, kFDSave, &fi);
  TString FileName = fi.fFilename;
  if(FileName==""){
    cout << "Print Failed!"<<endl;
  }
  else{
    switch
      (fi.fFileTypeIdx){
    case
      0:
      FileName+=".pdf";
      break;
    case
      1:
      FileName+=".png";      
      break;
    case
      3:
      FileName+=".eps";
    case
      4:
      FileName+=".C";
      break;
    default:
      FileName+=".pdf";
      break;
    }
    c1->SaveAs(FileName,"");
  }
}
