#include "systematic.h"

systematic::systematic(){
}

void systematic::Init(string file){
  Input[0].open(("config/Systematics/"+file+".in").c_str());
  if(!Input[0]) {
    std::cout << "could not open file systematics file" <<std::endl;
    exit(1);
  }

  string   label_ = "";
  Double_t syst_ = 0;
  while(!Input[0].eof()){
    Input[0] >> label_;
    Input[0] >> syst_;
    label.push_back(label_);
    syst.push_back(syst_);    
  }
  label.pop_back();
  syst.pop_back();

  Label = new string[label.size()];
  Syst = new Double_t[syst.size()];
 
  int i=0;
  for(std::vector<string>::iterator it = label.begin(); it != label.end(); it++, i++){
    Label[i] = (*it);
  }

  i=0;
  for(std::vector<Double_t>::iterator it = syst.begin(); it != syst.end(); it++, i++){
    Syst[i] = (*it);
  }

}

void systematic::Show(){
cout << " The systematic errors are: " << endl;

for(UInt_t i = 0; i < syst.size(); i++){
cout <<  Label[i] << "  " << Syst[i] << endl;
}

}


void systematic::ApplySyst(TH1D **h1){

  Int_t bins = (*h1)->GetXaxis()->GetNbins();
  Double_t content = 0.;
  Double_t error = 0.;
  Double_t new_error = 0.;
  Double_t Serror = 0.;
  Double_t Tsyst = 0.;

  for(Int_t i = 1; i <= bins; i++){
  Double_t error = (*h1)->GetBinError(i);
  Double_t content = (*h1)->GetBinContent(i);
  Tsyst = 0.;

        Serror = TMath::Power(error,2);
	for(UInt_t j = 0; j < syst.size(); j++){
        if(Label[j]=="Others") continue;
        else{ 
            Serror += TMath::Power(content*Syst[j],2);
            Tsyst += TMath::Power(Syst[j],2);
	    }		
        }

  new_error = TMath::Sqrt(Serror);
  if (new_error > error*(1.+sqrt(Tsyst)) ) new_error = error*(1.+sqrt(Tsyst));

  cout << " Old " <<  error << " new " << new_error << endl;
  (*h1)->SetBinError(i, new_error); 
  }

}


systematic::~systematic(){ 
}
