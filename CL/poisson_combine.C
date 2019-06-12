TCanvas *c1;
TF1 *Hnull;
TF1 *Halt;
TH1D *Hdata;
TLatex *text;
TLine *line;

// likelihood histos
TH1F *CL_SB;
TH1F *CL_ratio; 
TH1F *CL_ratio2; 

TH1F *cl_90; 
TH1F *cl_95; 
TH1F *cl_99; 

TLegend *legend;

Double_t CLb=0.;
Double_t CLb2=0.;

Double_t CLsb=0.;
Double_t CLsb2=0.;

Double_t CL=0.;
Double_t CL2=0.;
Double_t CL_combined=0.;

Double_t maxCLsb=0.;
Double_t maxCLratio=0.;
Double_t maxCLratio2=0.;
Double_t maxCLratioCB=0.;


Double_t upper_limit_signal_CLsb = 0;  
Double_t upper_limit_signal_CLratio = 0;
Double_t upper_limit_signal_CLratioCB = 0;

Double_t Bk = 4; 
Double_t Signal = 11;
unsigned data = 7;

Double_t Bk1 = 7; 
Double_t Signal1 = 12;
unsigned data1 = 7;



void SetFunction(unsigned nbins_, Double_t min_, Double_t max_){
  
  Hnull = new TF1("Hnull","TMath::Poisson(x,[0])",min_,max_); 
  Hnull->SetLineColor(3);
  Hnull->SetParameter( 0, Bk);
  
  Halt = new TF1("Halt","TMath::Poisson(x,[0])",min_,max_); 
  Halt->SetLineColor(2);
  Halt->SetParameter( 0, Bk+Signal);
  
  Hdata = new TH1D("Hdata", "", nbins_,min_,max_);
  Hdata->SetStats("kFALSE");
  Hdata->Sumw2();
  Hdata->GetYaxis()->SetRangeUser(0, 0.5);
  
}

void SetCLHistos(unsigned nbins_, Double_t min_, Double_t max_){
  
  CL_SB = new TH1F("CL_SB","Confidence Level",nbins_,min_,max_);
  CL_SB->SetStats("kFALSE");
  CL_SB->GetXaxis()->SetTitle("Signal yield s");
  CL_SB->GetYaxis()->SetTitle("Confidence Level");
  //  CL_S->GetYaxis()->SetRangeUser(0.00001,1.0);
  CL_SB->SetMarkerStyle(8);
  CL_SB->SetMarkerSize(1);
  CL_SB->SetMarkerColor(kBlue);
  
  CL_ratio = new TH1F("CL_ratio","CL_ratio",nbins_,min_,max_);
  CL_ratio->GetXaxis()->SetTitle("Signal yield s");
  CL_ratio->GetYaxis()->SetTitle("Confidence Level");
  CL_ratio->SetMarkerStyle(8);
  CL_ratio->SetMarkerSize(1);
  CL_ratio->SetMarkerColor(kRed);

  
  CL_ratio2 = new TH1F("CL_ratio2","CL_ratio2",nbins_,min_,max_);
  CL_ratio2->GetXaxis()->SetTitle("Signal yield s");
  CL_ratio2->GetYaxis()->SetTitle("Confidence Level");
  CL_ratio2->SetMarkerStyle(8);
  CL_ratio2->SetMarkerSize(1);
  CL_ratio2->SetMarkerColor(kRed+2);
  
}

void CreateCLlines(Double_t min_, Double_t max_){
  cl_90 = new TH1F("cl90","",1,min_,max_);
  cl_95 = new TH1F("cl95","",1,min_,max_);
  cl_99 = new TH1F("cl99","",1,min_,max_);
  cl_90->SetBinContent(1,0.1);
  cl_95->SetBinContent(1,0.05);
  cl_99->SetBinContent(1,0.01);
}


void CalculateCL(unsigned nbins_, Double_t max_){
  
  
  CLb=Hnull->Integral(0,data);
  Hnull->SetParameter( 0, Bk1);
  CLb2=Hnull->Integral(0,data1);
  
  cout << CLb << " " << CLb2 << endl;

  double pvalue = Hnull->Integral(data, 100);

  for (unsigned entries=0; entries < nbins_; entries++){
    
    double new_signal = (max_)*entries/nbins_;
    
    Halt->SetParameter(0, Bk+new_signal); //New signal point    
    CLsb=Halt->Integral(0,data);
    CL = 1-CLsb/CLb;

    Halt->SetParameter(0, Bk1+new_signal); //New signal point2    
    CLsb2=Halt->Integral(0,data1);
    CL2 = 1-CLsb2/CLb2;

    CL_combined = CLsb/CLb*(CLsb2/CLb2);    

       cout<< "Signal: "<< new_signal << " CLsb: "<< CLsb << " CLratio " << CLsb/CLb  << " CL: "<< CL <<endl;
       cout<< "Signal2: "<< new_signal << " CLsb2: "<< CLsb2 << " CLratio " << CLsb2/CLb2  << " CL2: "<< CL2 <<endl;
        

    if(CLsb/CLb < 0.05 && upper_limit_signal_CLsb == 0){
      upper_limit_signal_CLsb = new_signal;
      maxCLsb = CLsb/CLb;  
      cout<< " CLsb signal: "<< new_signal <<endl;
    } 
    
    if(CLsb2/CLb2 < 0.05 && upper_limit_signal_CLratio == 0){
      upper_limit_signal_CLratio = new_signal;
      maxCLratio = CLsb2/CLb2; 
      cout<< " CLratio signal: "<< new_signal <<endl;
    }
    if(CL_combined < 0.05 && upper_limit_signal_CLratioCB == 0){
      upper_limit_signal_CLratioCB = new_signal;
      maxCLratioCB=CL_combined;
      cout<< " CLcombined signal: "<< new_signal <<endl;
    }    

    
    CL_SB->SetBinContent(entries, CLsb/CLb);
    CL_ratio->SetBinContent(entries, CLsb2/CLb2);
    CL_ratio2->SetBinContent(entries, CL_combined);
  }
  cout << "pvalue: " << pvalue << endl;  
  
}



void PlotLatex(unsigned data_, Double_t Bk_, Double_t Signal_){
  text = new TLatex();
  text->SetTextSize(0.04);
  text->SetTextColor(1);
  text->DrawLatex(data_,0.2, "Data");
  text->DrawLatex(Bk_,0.2, "N_{Bk}");  
  text->DrawLatex(Bk_+Signal_,0.3, "N_{Bk+Signal}");  
}

void PlotLineUpper(){
  line = new TLine();
  line->SetLineStyle(2);
  line->SetLineWidth(3);
  line->SetLineColor(kBlue);
  line->DrawLine(upper_limit_signal_CLsb, maxCLsb, upper_limit_signal_CLsb, 0.0);
  line->SetLineColor(kRed);
  line->DrawLine(upper_limit_signal_CLratio, maxCLratio, upper_limit_signal_CLratio, 0.0);
  line->SetLineColor(1);
  line->DrawLine(upper_limit_signal_CLratioCB, maxCLratioCB, upper_limit_signal_CLratioCB, 0.0);

}

void PlotLegend(){
  
  legend = new TLegend(0.5893189,0.7439329,0.888595,0.8940455,NULL,"brNDC");
  TLegendEntry *entry=legend->AddEntry(CL_SB,"CL_{s+b} 1","p");
  TLegendEntry *entry1=legend->AddEntry(CL_ratio,"CL_{s+b} 2","p");
  TLegendEntry *entry2=legend->AddEntry(CL_ratio2,"CL_{s+b} combined","p");
  entry->SetTextFont(42);
  entry1->SetTextFont(42);
  legend->Draw();
  
}

void PlotCLO(){
  TF1 *flog=new TF1("flog","log10(x)",0.00001,1);
  TGaxis *A_CLs = new TGaxis(-3.,0.00001,-3,1,"flog",505,"G");
  A_CLs->SetTitle("Confidence level CL_{s}");
  A_CLs->SetLabelSize(0.0375);
  A_CLs->SetTitleSize(0.0375);
  A_CLs->SetLineColor(kRed);
  A_CLs->SetTextColor(kRed);
  A_CLs->SetLabelColor(kRed);
  A_CLs->SetTitleOffset(1.0); // Axis title automatically placed
  A_CLs->Draw();
}

void Plot(){
  
  c1->cd(1);
  Hdata->Draw("p");
  Hnull->SetParameter( 0, Bk);
  TF1 *Hnull_c = (TF1*)Hnull->Clone();
  Hnull_c->Draw("same");
  Hnull->SetParameter( 0, Bk1);
  Hnull->Draw("same");

  Halt->SetParameter( 0, Bk+Signal);  
  TF1 *Halt_c = (TF1*)Halt->Clone();
  Halt_c->Draw("same");
  Halt->SetParameter( 0, Bk1+Signal1);  
  Halt->Draw("same");


  PlotLatex(data, Bk, Signal);
  
  c1->cd(2);
  gPad->SetLogy(1);
  CL_SB->Draw("p");
  CL_ratio->Draw("p,same");
  CL_ratio2->Draw("p,same");
  
  cl_90->Draw("Hdata,same");
  cl_95->Draw("Hdata,same");
  cl_99->Draw("Hdata,same");  
  PlotLineUpper(); 
  PlotLegend(); 
  // PlotCLO();
}





void poisson_combine(){
  
  gStyle->SetOptStat(0);  
  c1 = new TCanvas("c1","Poisson Likelihood",100,200,900,600);
  c1->Divide(2,1);
  
  unsigned nbins=100;
  Double_t min=0.;

  //  Double_t max=Bk+Signal+10.;
  Double_t max=15.;
  
  SetFunction(nbins,min,Bk+Signal+10.);
  
  SetCLHistos(nbins, min, max);
  
  Hdata->Fill(data);
  Hdata->Fill(data1);

  Hdata->Scale(0.3);
  
  CreateCLlines(min,max);
  CalculateCL(nbins,max);
  
  
  Plot();
  
  
}

int main(){
  poisson_combine();
  return 0;
}
