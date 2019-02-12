#include "plotter.h"

plotter::plotter(){
}

void plotter::Init(string file){
  
  Input[0].open(("config/Colors/"+file+".in").c_str());
  if(!Input[0]) {
    std::cout << "could not open file config/colors.in" <<std::endl;
    exit(1);
  } 
  
  string colors_ = "";
  string sign_ = "";
  Double_t number_ = 0.;
  while(!Input[0].eof()){
    Input[0] >> colors_;
    Input[0] >> sign_;
    Input[0] >> number_;
    colors.push_back(colors_);
    sign.push_back(sign_);
    number.push_back(number_); 
  }
  colors.pop_back();
  sign.pop_back();
  number.pop_back();
  
}

Double_t plotter::GetColor(string color, string sign, Double_t number){
  
  map_color["kMagenta"] = 616;
  map_color["kBlue"] = 600;
  map_color["kCyan"] = 432;
  map_color["kRed"] = 632;
  map_color["kGreen"] = 416;
  map_color["kOrange"] = 800;
  map_color["kYellow"] = 400;
  
  Double_t Color = map_color[color];
  if(sign=="+") Color += number;
  else if(sign=="-") Color -= number;
  
  return Color;
}

void plotter::ShowColor(){
  for(UInt_t i = 0 ; i < colors.size() ; i++){
    std::cout << colors[i] << std::endl;
  }
}


void plotter::SetColorData(TH1D **h1, string x_label, string y_label){
  
  (*h1)->SetLineColor(kBlack);
  (*h1)->SetMarkerStyle(20);
  (*h1)->SetMarkerColor(kBlack);
  (*h1)->SetStats(kFALSE);
  (*h1)->SetTitle("");
  
  //X axis
  (*h1)->GetXaxis()->SetRange(2,10);
  (*h1)->GetXaxis()->SetTitle(x_label.c_str());  
  (*h1)->GetXaxis()->SetTitleSize(0.035);
  (*h1)->GetXaxis()->SetTitleOffset(1.0);
  (*h1)->GetXaxis()->SetTitleFont(42);

  (*h1)->GetXaxis()->SetLabelSize(0.035);
  (*h1)->GetXaxis()->SetLabelOffset(0.015);
  (*h1)->GetXaxis()->SetLabelFont(42);
  
  // Y axis
  (*h1)->GetYaxis()->SetTitle(y_label.c_str());  
  (*h1)->GetYaxis()->SetTitleSize(0.05);
  (*h1)->GetYaxis()->SetTitleOffset(0.9);
  (*h1)->GetYaxis()->SetTitleFont(42);

  (*h1)->GetYaxis()->SetLabelSize(0.035);
  (*h1)->GetYaxis()->SetLabelOffset(0.01);
  (*h1)->GetYaxis()->SetLabelFont(42);
  
  // (*h1)->GetYaxis()->CenterTitle("kFALSE");
  // (*h1)->GetYaxis()->SetNdivisions(5,5,0,kTRUE);
  
}

void plotter::SetColorDataClone(TH1D **h1, string x_label, string y_label){
  
  (*h1)->SetTitle("");
  //X axis 
  (*h1)->GetXaxis()->SetRange(2,10);
  (*h1)->GetXaxis()->SetTitle(x_label.c_str());
  (*h1)->GetXaxis()->SetTitleSize(0.14);
  (*h1)->GetXaxis()->SetTitleOffset(1.2);
  (*h1)->GetXaxis()->SetTitleFont(42);
  
  (*h1)->GetXaxis()->SetLabelSize(0.13);
  (*h1)->GetXaxis()->SetLabelOffset(0.05);
  (*h1)->GetXaxis()->SetLabelFont(42);
  
  // Y axis
  (*h1)->GetYaxis()->SetTitle(y_label.c_str());  
  (*h1)->GetYaxis()->SetTitleSize(0.15);
  (*h1)->GetYaxis()->SetTitleOffset(0.27);
  (*h1)->GetYaxis()->SetTitleFont(42);
  
  (*h1)->GetYaxis()->SetLabelSize(0.14);
  (*h1)->GetYaxis()->SetLabelOffset(0.006);
  (*h1)->GetYaxis()->SetLabelFont(42);
  
  (*h1)->GetYaxis()->CenterTitle("kTRUE");
  (*h1)->GetYaxis()->SetNdivisions(5,5,0,kTRUE);
  
}


void plotter::SetColorMC(TH1D **h1, UInt_t index, string x_label, string y_label){
  Double_t Color = GetColor(colors[index], sign[index], number[index]); 
  (*h1)->SetFillColor(Color);
  (*h1)->SetLineColor(Color);
  (*h1)->GetXaxis()->SetTitle(x_label.c_str());
  (*h1)->GetYaxis()->SetTitle(y_label.c_str());  
  
}

void plotter::SetColorAllBack(TH1D **h1, string x_label, string y_label){
  (*h1)->SetFillStyle(3002);
  (*h1)->SetFillColor(1);
  (*h1)->SetLineColor(1);

 // (*h1)->SetFillColor(kMagenta+1);
 // (*h1)->SetLineColor(kMagenta+1);
  
  (*h1)->GetXaxis()->SetTitle(x_label.c_str());
  (*h1)->GetYaxis()->SetTitle(y_label.c_str());   
}

void plotter::Create_Canvas(bool logscale_1, bool logscale_2){
  
  c = new TCanvas("c1", "",165,113,1015,547);
  c->UseCurrentStyle(); 
  
  pad1 = new TPad("pad1", "pad1",0,0.04852686,1,1); 
  pad1->Range(-62.40412,-57.37633,2230.179,136.5634); 
  pad1->SetFillColor(0);
  pad1->SetBorderMode(0);
  pad1->SetBorderSize(2);
  pad1->SetLeftMargin(0.112);
  pad1->SetTopMargin(0.09);
  pad1->SetBottomMargin(0.3);
  pad1->SetFrameBorderMode(0);
  if(logscale_1) pad1->SetLogy();
  pad1->SetTickx(1);
  pad1->SetTicky(1);
  pad1->Draw();
 
  pad2 = new TPad("pad2", "pad2",0,0.003642987,1,0.2522627);
  pad2->Range(-21.05264,-1.461812,2225.564,3.525037);
  pad2->SetFillColor(0);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(2);
  pad2->SetLeftMargin(0.112);
  pad1->SetTopMargin(0.09);
  pad2->SetBottomMargin(0.4);
  pad2->SetFrameBorderMode(0);
  if(logscale_2) pad1->SetLogy();
  pad2->SetTickx(1);
  pad2->SetTicky(1);
  pad2->Draw(); 
  
}


void plotter::CreateLine(Double_t xmin, Double_t xmax){
  
  line = new TLine(xmin,1.0,xmax,1.0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->SetLineColor(kRed);
  line->Draw();
  
}

void plotter::CreateLegend(){
  
  legend = new TLegend(0.4497992,0.5189444,0.8493976,0.8901938,NULL,"brNDC");
  legend->SetTextFont(42);
  legend->SetLineColor(1);
  legend->SetLineStyle(1);
  legend->SetLineWidth(1);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetBorderSize(0);
  legend->SetFillColor(kWhite);
  
}

void plotter::LegendAdd(TH1D *h1, bool isData, string label_){
  if(isData) legend->AddEntry(h1, label_.c_str(), "p");
  else{
    legend->AddEntry(h1, label_.c_str() , "f");
  }
}

void plotter::LegendDraw(){
  legend->Draw();
}


void plotter::CMSLabels(){
  
  pt = new TPaveText(0.7582897,0.914863,0.908377,0.9735782,"NBNDC");
  pt->AddText("35.9 fb^{-1} (13 TeV)");
  pt->SetTextFont(42);
  pt->SetTextAlign(32);
  pt->SetFillStyle(0);
  pt->SetBorderSize(0);
  pt->Draw();
  
  pt2 = new TPaveText(0.1186736,0.8370654,0.2390925,0.9075236,"NBNDC");
  pt2->AddText("CMS ");
  pt2->SetTextAlign(12);
  pt2->SetFillStyle(0);
  pt2->SetBorderSize(0);
  pt2->Draw();
  
  pt3 = new TPaveText(0.117801,0.7944969,0.2382199,0.8561478,"NBNDC");
 // pt3->AddText("Preliminary");
  pt3->AddText("Work in progress");
  pt3->SetTextSize(0.05);
  pt3->SetTextAlign(12);
  pt3->SetTextFont(52);
  pt3->SetFillStyle(0);
  pt3->SetBorderSize(0);
  pt3->Draw();
  
  
 
  
}

void plotter::OtherLabels(){

  tex_2 = new TLatex(219.375,170.2258,"QCD Multijet CRD");
  tex_2->SetTextSize(0.04);
  tex_2->Draw();
  
  tex_3 = new TLatex(407.4368,154.2249,"N_{j} < 2");
  tex_3->SetTextSize(0.04);
  tex_3->Draw();
}

TGraphErrors* plotter::CreateERROR(TH1D *h1, Double_t Syst[]){
  
  
  H_Back = (TH1D*)h1->Clone();
  H_systematic = (TH1D*)h1->Clone();

  UInt_t bins = h1->GetXaxis()->GetNbins();

  Double_t error=0.;
  Double_t Serror=0.;
  Double_t new_error = 0.;
  Double_t Tsyst = 0.;
  
  for (UInt_t i = 1; i <= bins; i++){
    H_Back->SetBinError(i, 0.);
    Tsyst = 0.;
    error = h1->GetBinError(i);
    
    Serror = TMath::Power(error,2);
    for(UInt_t k = 0; k < 3; k++){
    Serror += TMath::Power(error*Syst[k],2);
    Tsyst += TMath::Power(Syst[k],2);
    } 
    new_error = TMath::Sqrt(Serror);

    if (new_error > error*(1.+sqrt(Tsyst)) ) new_error = error*(1.+sqrt(Tsyst));
    
    cout << " old  " << error  << " new error "  << new_error <<  endl;
    H_systematic->SetBinError(i, new_error);

    
  }

  H_systematic->Divide(H_Back);
  
  mcX = new Double_t[bins];
  mcY = new Double_t[bins];
  mcErrorX = new Double_t[bins];
  mcErrorY = new Double_t[bins];
  
  Double_t error_i = 0.;
  for (UInt_t i = 0; i < bins; i++){
    
    mcY[i] = H_systematic->GetBinContent(i+1);
    error_i = H_systematic->GetBinError(i+1);
    mcErrorY[i] = error_i;
    mcX[i] = H_systematic->GetBinCenter(i+1);    
    mcErrorX[i] = H_systematic->GetBinWidth(i+1) * 0.5;
  }
  
  McError = new TGraphErrors(bins,mcX,mcY,mcErrorX,mcErrorY);
  McError->SetLineWidth(2);
  McError->SetFillColor(1);
  McError->SetFillStyle(3002);
  McError->SetFillColor(1);
//McError->SetFillColor(kMagenta+1);
  
  return McError;
}


void plotter::ShowRatioValue(TH1D *h1, UInt_t Data_bins){

 Double_t Content = 0.;
 Double_t Error = 0.;
 for (UInt_t i = 1; i <= Data_bins; i++){
 Content = h1->GetBinContent(i);
 Error = h1->GetBinError(i);
 cout << " Content: " << Content << " Error: " << Error << endl; 
 }

}

plotter::~plotter(){
}
