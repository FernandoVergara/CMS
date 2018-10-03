#include <TLegend.h> 
vector<string> input;
vector<string> Cuts;
vector<string> Histo;
vector<string> label_;

TCanvas *c1;
TLegend *legend;
TFile *Tf[4];
TH1D *Histos_[3];

void fill(){
//input.push_back("CR2/QCD");
//input.push_back("Final/CR2/QCD");

//input.push_back("Final/W_tight/met_30/W+Jets");
//input.push_back("Final/W_loose/met_30/W+Jets");

input.push_back("Final/Z_tight/met_30/DY+Jets");
input.push_back("Final/Z_loose/met_30/DY+Jets");

//input.push_back("Z_tight/DY+Jets");
//input.push_back("Z_loose/DY+Jets");


//Cuts.push_back("NRecoTau1");
Cuts.push_back("METCut");
//Cuts.push_back("NRecoFirstLeadingJet");

//Histo.push_back("Tau1MetMt");
 Histo.push_back("Tau1Pt");
//Histo.push_back("Muon1Tau1ReconstructableMass");

}


void integral(){
fill();

for(int i = 0; i < input.size(); i++){
TFile *g = TFile::Open((input[i]+".root").c_str(),"READ");
Tf[i] = g;
} 



for(int j = 0; j < input.size(); j++){
    TH1D* h;
    h = (TH1D*)Tf[j]->Get((Cuts[0]+"/"+Histo[0]).c_str());  
    h->Sumw2();
    Histos_[j] = h; 
}

   double numerator = 0.;
  double denominator = 0.;
  double error_numerator = 0.;
  double error_denominator = 0.;

  Double_t *Num;
  Double_t *ENum;
  Double_t *Den;
  Double_t *EDen;
  Double_t *PT;
  Double_t *EPT;
   Double_t *ratio;
  Double_t *eratio;
  Int_t points = 0;

  
  for(int i = 1; i <= Histos_[0]->GetNbinsX(); i++){
  double lowedge = Histos_[0]->GetBinLowEdge(i); 
  if(lowedge >= 20 && lowedge < 40){
  points++;
  } 
  }

  
  Num = new Double_t[points];
  Den = new Double_t[points];
  ENum = new Double_t[points];
  EDen = new Double_t[points];
  ratio = new Double_t[points];
  eratio = new Double_t[points];
   
  PT = new Double_t[points];
  EPT = new Double_t[points];

  

  for(int j = 0; j < input.size(); j++){
   
 
  double integral = Histos_[j]->Integral();
  
  cout << "Integral" << Histos_[j]->Integral()  <<endl;
 
  
  int counter1 = 0;
  int counter2 = 0;
  for(int i = 1; i <= Histos_[j]->GetNbinsX(); i++){
  double bincontent = Histos_[j]->GetBinContent(i);
  double lowedge = Histos_[j]->GetBinLowEdge(i);  
  if(lowedge >= 20 && lowedge < 40){
  cout << bincontent << " " << lowedge << " error " << Histos_[j]->GetBinError(i) << " Bin number " << i 	<< endl;
  if(j==0){
         PT[counter1] = lowedge+1;
         EPT[counter1] = 1.0;// Histos_[j]->GetBinWidth(i);
	 numerator += bincontent;
	 error_numerator += TMath::Power(Histos_[j]->GetBinError(i), 2);
         Num[counter1] = bincontent;
         ENum[counter1] = sqrt(TMath::Power(Histos_[j]->GetBinError(i), 2));
         counter1++;
  }          

  else if(j==1){

         denominator += bincontent;
         error_denominator += TMath::Power(Histos_[j]->GetBinError(i), 2);
         if(denominator != 0){
         Den[counter2] = bincontent;
         EDen[counter2] = sqrt(TMath::Power(Histos_[j]->GetBinError(i), 2));
         }
	else {  Den[counter2] = 0.01;
         EDen[counter2] = 0.01;
       }
         counter2++;
    }

         
   }
  } 


  if(j==0)  error_numerator = sqrt(error_numerator);
  else if (j==1) error_denominator = sqrt(error_denominator);
 
  cout << "numerator: " << numerator << " Denominator: " << denominator << endl;
  cout << " error numerator " << error_numerator << " error denominator " << error_denominator << endl;

  double transfer_factor = numerator/denominator;
  double error_transfer = transfer_factor*(TMath::Power( pow(error_numerator/numerator,2) + pow(error_denominator/denominator, 2), 0.5     ));

  cout << transfer_factor << "+-" << error_transfer << endl;
 
  double QCD_SR = 196.8;  
  double error_QCD_SR = 32.1;


  double predicted_QCD = QCD_SR*transfer_factor;
  double error_QCD = 0;
 
  error_QCD = predicted_QCD*(TMath::Power( pow(error_QCD_SR/QCD_SR, 2)+ pow(error_transfer/transfer_factor,2)  ,0.5)); 
 

  cout << " QCD predicted in the SR " << endl;
  cout << predicted_QCD << "+-" << error_QCD <<  " error " << error_QCD/predicted_QCD <<endl;




  }
  for(int  i= 0; i< points; i++){
  ratio[i] = Num[i]/Den[i];
  eratio[i] = ratio[i]*TMath::Power(  pow(ENum[i]/Num[i], 2)+ pow(EDen[i]/Den[i],2)  , 0.5);
  cout << ratio[i] << " error " <<  eratio[i]  <<endl;  
  }

  TGraphErrors *McError = new TGraphErrors(points,PT,ratio,EPT,eratio);
  McError->GetXaxis()->SetTitle("p_{T}(#tau_{h}) [Gev]");
  McError->GetYaxis()->SetTitle("Ratio_{Tight}^{Loose}/Bin");
  McError->SetTitle("");
  McError->SetLineWidth(2);
  McError->SetFillColor(1);
 // McError->SetFillStyle(3004);
  McError->SetFillColor(kRed+2); 
  McError->Draw("");  

  TF1 *FIT = new TF1("FIT","[1]*x-21*[1]+[0]", 20, 40);
  FIT->SetParName(0,"b");
  FIT->SetParName(1,"m");
  FIT->SetLineColor(4);
 
 /*
  FIT->SetParameter(0, 0);
  FIT->SetParameter(1, 1);
   */
  
  McError->Fit("FIT");

  
}


int main(){
integral();
return 0;
}
