

TCanvas *c1;
TF1 *Hnull;
TF1 *Halt;
TH1D *Hdata;
TLatex *text;

// likelihood histos
TH1F *CL_S;
TH1F *CL_SB; 

TH1F *cl_90; 
TH1F *cl_95; 
TH1F *cl_99; 

  Double_t Bk = 4; 
  Double_t Signal = 11;
  unsigned data = 7;

void SetFunction(unsigned nbins_, Double_t min_, Double_t max_){

  Hnull = new TF1("Hnull","TMath::Poisson(x,[0])",min_,max_); 
  Halt = new TF1("Halt","TMath::Poisson(x,[0])",min_,max_); 

  Hdata = new TH1D("Hdata", "Event Yield", nbins_,min_,max_);
  Hdata->Sumw2();
  Hdata->GetYaxis()->SetRangeUser(0, 0.5);

  Hnull->SetLineColor(3);
  Hnull->SetParameter( 0, Bk);
  Halt->SetLineColor(2);
  Halt->SetParameter( 0, Bk+Signal);


}
void SetCLHistos(unsigned nbins_, Double_t min_, Double_t max_){
CL_S = new TH1F("CL_S","CL_S",nbins_,min_,max_);
CL_S->GetXaxis()->SetTitle("Signal yield s");
CL_S->GetYaxis()->SetTitle("Confidence Level CL_{s+b}");
CL_S->GetYaxis()->SetRangeUser(0.00001,1.0);
CL_S->SetMarkerStyle(8);
CL_S->SetMarkerColor(1);

CL_SB = new TH1F("CL_SB","CL_SB",nbins_,min_,max_);
CL_SB->GetXaxis()->SetTitle("Signal yield s");
CL_SB->GetYaxis()->SetTitle("Confidence Level CL_{s}");
CL_SB->SetMarkerStyle(8);
CL_SB->SetMarkerColor(kBlue);
}

void CreateCL(){
cl_90 = new TH1F("cl90","",1,0,15);
cl_95 = new TH1F("cl95","",1,0,15);
cl_99 = new TH1F("cl99","",1,0,15);
cl_90->SetBinContent(1,0.1);
cl_95->SetBinContent(1,0.05);
cl_99->SetBinContent(1,0.01);
}


void CalculateCL(unsigned nbins_, Double_t max_){
   
     double upper_limit_signal_CLsb = 0;
     double upper_limit_signal_CLs = 0;

    double CLb=Hnull->Integral(0,data);
for (unsigned entries=0; entries < nbins_; ++entries){
    float new_signal = max_*entries/nbins_;
     Halt->SetParameter(0, Bk+new_signal);
    double CLsb=Halt->Integral(0,data);

    double CL = 1 - CLsb/CLb;

    cout<<"signal:"<<new_signal<<" CL:"<<CL
	<<" CLsb:"<<1-CLsb
	<<endl;

    if(CLsb/CLb < 0.05 && upper_limit_signal_CLs == 0){
      upper_limit_signal_CLs = new_signal;
      cout<<"CLs signal:"<< new_signal<<endl;
    }
 
    if(CLsb < 0.05 && upper_limit_signal_CLsb == 0){
      upper_limit_signal_CLsb = new_signal;
      cout<<"CLsb signal:"<<new_signal<<endl;
    } 


    CL_S->SetBinContent(entries, CLsb);
    CL_SB->SetBinContent(entries, CLsb/CLb);
}

}



void PlotLatex(unsigned data_, Double_t Bk_, Double_t Signal_){
text = new TLatex();
text->SetTextSize(0.04);
text->SetTextColor(1);
text->DrawLatex(data_,0.2, "Data");
text->DrawLatex(Bk_,0.2, "N_{Bk}");  
text->DrawLatex(Bk_+Signal_,0.2, "N_{Signal}");  
}

void Plot(){
c1->cd(1);
Hdata->Draw("E0");
Hnull->Draw("same");
Halt->Draw("same");
PlotLatex(data, Bk, Signal);
c1->cd(2);
gPad->SetLogy(1);
CL_S->Draw("p");
CL_SB->Draw("p,same");
cl_90->Draw("Hdata,same");
cl_95->Draw("Hdata,same");
cl_99->Draw("Hdata,same");

}





void poisson(){

c1 = new TCanvas("c1","Poisson Likelihood",100,200,900,600);
c1->Divide(2,1);

unsigned nbins=100;
Double_t min=0.;
Double_t max=30.;

SetFunction(nbins,min,max);
SetCLHistos(nbins, min, Bk+Signal);
Hdata->Fill(data);
Hdata->Scale(0.3);

CreateCL();
CalculateCL(nbins,max);

Plot();


}

int main(){
poisson();
return 0;
}
