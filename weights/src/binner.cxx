#include "binner.h"

binner::binner(): 
  N_bins(0){
}

void binner::Init(string file){
  
  Input[0].open(("config/Bins/"+file+".in").c_str());
  if(!Input[0]) {
    std::cout << "could not open file config bin file" <<std::endl;
    exit(1);
  } 
  
  Double_t bins_ = 0;
  while(!Input[0].eof()){
    Input[0] >> bins_;
    bins.push_back(bins_);    
  }
  bins.pop_back();
  
  BINS = new Double_t[bins.size()];
  N_bins = bins.size()-1;
  int i=0;
  for(std::vector<Double_t>::iterator it = bins.begin(); it != bins.end(); it++, i++){
    BINS[i] = (*it);
  }
  
  //Histogram to rebinning
   
}

void binner::Weight_Init(string file){

   Input[1].open(("config/Weights/"+file+".in").c_str());
   if(!Input[1]) {
    std::cout << "could not open file weights file" <<std::endl;
    exit(1);
  } 

  Double_t weights_ = 0;
  Double_t errors_ = 0;

  while(!Input[1].eof()){
    Input[1] >> weights_;
    Input[1] >> errors_;
    weights.push_back(weights_);    
    errors.push_back(errors_);    

  }
  weights.pop_back();
  errors.pop_back();

 
}

void binner::ApplyWeight(TH2D **h2){
  
  TF1 *f1 = new TF1("f1","-0.0039*(x-20.)+0.30", 18., 42.);
  
  Int_t NbinsX =  (*h2)->GetXaxis()->GetNbins();
  Int_t NbinsY =  (*h2)->GetYaxis()->GetNbins();

  
 //Fill the maps of weights
  for(Int_t i = 1; i <= NbinsX; i++){
  if(i >= 11 && i < 20){
  Weight[i] = weights[i-11];
//  Weight[i] = f1->Eval(i+10); // fit option 
  Error[i] = errors[i-11]; 
  }
  else{
	 Weight[i] = 1.0;
         Error[i] = 0.;
	}
  }

    for(Int_t i = 1; i <= NbinsX; i++){
   // cout <<  i << " " <<Weight[i] <<  " " << Error[i] <<endl;
    }

  Double_t value=0.;
  Double_t error=0.;
  Double_t ratio=0.;
  for(Int_t j = 1; j <=  NbinsY; j++){
	 for(Int_t i = 1; i <=  NbinsX; i++){
         if((*h2)->GetBinContent(i,j) != 0.) 
		ratio = (*h2)->GetBinError(i,j)/(*h2)->GetBinContent(i,j);
         else ratio = 0.;

         value = Weight[i]*(*h2)->GetBinContent(i,j);
	 error = (pow(value,2))*(pow(ratio,2)+pow(Error[i]/Weight[i],2));

       //  error += value; //poissonian error      
         
         if(sqrt(error) > value) error = TMath::Power(value,2); 
  
         if(error > 0.) cout << i << " new "  << sqrt(error) << " old " << (*h2)->GetBinError(i,j) <<  " ratio  "<< ratio << " ratio_H " <<  Error[i]/Weight[i] << " entry " << (*h2)->GetBinContent(i,j) << " value " << value << endl; 
         
          (*h2)->SetBinContent(i,j, value);
          (*h2)->SetBinError(i,j, sqrt(error));
         
         }
  }
}

TH1D* binner::Proyection_X(TH2D **h2, Double_t &Total_E, Double_t E_weight, bool poisson){

  h1_X = new TH1D((*h2)->GetName(), (*h2)->GetName(), N_bins ,BINS); 
  h1_X->Sumw2();

  Int_t NbinsX =  (*h2)->GetXaxis()->GetNbins();
  Int_t NbinsY =  (*h2)->GetYaxis()->GetNbins();

  Double_t value=0.;
  Double_t error=0.; 
  for(Int_t j = 1; j <=  NbinsY; j++){
  value=0.;
  error=0.; 
	for(Int_t i = 1; i <=  NbinsX; i++){
        value += (*h2)->GetBinContent(i,j);
        error += TMath::Power((*h2)->GetBinError(i,j),2);
   	}
  h1_X->SetBinContent(j, E_weight*value);
  if(poisson) h1_X->SetBinError(j, E_weight*sqrt(error+E_weight*value));
  else h1_X->SetBinError(j, E_weight*sqrt(error));
  cout << h1_X->GetBinLowEdge(j) << " Content " << h1_X->GetBinContent(j) << " Error " << h1_X->GetBinError(j) 
       << " Relative "  << h1_X->GetBinError(j)/h1_X->GetBinContent(j)  << endl; 
  Total_E += pow(E_weight,2)*error;
  }

  return h1_X;
  delete h1_X;
}



TH1D* binner::Rebinner1(TH1D *h_old){
  
  h_new = (TH1D*)h_old->Clone("h_new");

  h_new->SetBins(bins.size()-1, BINS);  
 
  
  Int_t old_nbins = h_old->GetXaxis()->GetNbins(); 
  Int_t new_nbins = h_new->GetXaxis()->GetNbins();

  for (int b = 1; b <= new_nbins; b++ ){
    Double_t Right_edge_new = h_new->GetXaxis()->GetBinLowEdge(b)+h_new->GetXaxis()->GetBinWidth(b);
    Double_t Edge_new = h_new->GetXaxis()->GetBinLowEdge(b);
    Double_t Num_back = 0.;
    Double_t error_back = 0.;
    
    for (int i = 1; i <= old_nbins; i++ ){
      Double_t Right_edge_old = h_old->GetXaxis()->GetBinLowEdge(i)+h_old->GetXaxis()->GetBinWidth(i);
      
      if((Right_edge_old <= Right_edge_new) && (Right_edge_old > Edge_new)){ //Relevant Condition
	
	Num_back += h_old->GetBinContent(i);
	error_back += TMath::Power( h_old->GetBinError(i), 2 ) ;
	
      }
      else continue;

      h_new->SetBinContent(b, Num_back);
      h_new->SetBinError(b, TMath::Sqrt(error_back));
      
    } // loop over the old hist
  } // loop over the new hist
 
 
  return h_new;
   
}

TH2D* binner::Rebinner2(TH2D *h_old){
  

  h2 = (TH2D*)h_old->Clone("h2");


  XBINS = new Double_t[h_old->GetXaxis()->GetNbins()];
  Int_t width = h_old->GetXaxis()->GetBinWidth(1);
  for(Int_t i = 0; i <= h_old->GetXaxis()->GetNbins(); i++){
  XBINS[i] = width*i;
  }

  h2->SetBins(h_old->GetXaxis()->GetNbins(), XBINS, bins.size()-1, BINS); 

  
 
  Int_t old_nbins = h_old->GetYaxis()->GetNbins(); 
  Int_t new_nbins = h2->GetYaxis()->GetNbins(); 
 
  
  for(Int_t x = 1; x <= h_old->GetXaxis()->GetNbins(); x++){  // loop over the X axis
    
    
    
    for(Int_t b = 1; b <= new_nbins; b++){
      Double_t Right_edge_new = h2->GetYaxis()->GetBinLowEdge(b)+h2->GetYaxis()->GetBinWidth(b);
      Double_t Edge_new = h2->GetYaxis()->GetBinLowEdge(b);
      Double_t Num_back = 0.;
      Double_t error_back = 0.;
      
      
      for (int i = 1; i <= old_nbins; i++ ){
	Double_t Right_edge_old = h_old->GetYaxis()->GetBinLowEdge(i)+h_old->GetYaxis()->GetBinWidth(i);
	if((Right_edge_old <= Right_edge_new) && (Right_edge_old > Edge_new)){ //Relevant Condition
	  
	//  if(h_old->GetBinContent(x,i) == 0.) continue;
	  Num_back += h_old->GetBinContent(x,i);
	  error_back += TMath::Power( h_old->GetBinError(x,i), 2 ) ;
	  
	}
	else continue;
	
	
	h2->SetBinContent(x, b, Num_back);
	h2->SetBinError(x, b, TMath::Sqrt(error_back));
      }
    } 
    
  }

 
    return h2; 
  
}






void binner::BinWidth(TH1D **h1){

  UInt_t bins = (*h1)->GetXaxis()->GetNbins();
  UInt_t BinWidth = 0; 
  for (UInt_t b = 1; b <= bins; b++ ){
  BinWidth = BINS[b]-BINS[b-1];
  //BinWidth = (*h1)->GetXaxis()->GetBinWidth(b);   
  (*h1)->SetBinContent(b,(*h1)->GetBinContent(b)/BinWidth); 
  (*h1)->SetBinError(b,(*h1)->GetBinError(b)/BinWidth); 
  }
 
}


void binner::Poisson_error(TH1D **h1, bool binW){
  
 UInt_t Nbins = (*h1)->GetXaxis()->GetNbins(); 
 
 Double_t bincontent = 0.;
 UInt_t binwidth = 0;
 for(UInt_t i = 0; i < Nbins ; i++){
 
 bincontent = (*h1)->GetBinContent(i+1);
 binwidth = (*h1)->GetXaxis()->GetBinWidth(i+1);

 if(bincontent <= 0.){  

   if(binW){
   cout << " bin empty for Data: " << i+1 << " --- Calculating the error in this bin --- " << 1.84/binwidth << endl;  
   (*h1)->SetBinError(i+1, 1.84/binwidth);
   }
   else{
   cout << " bin empty for Data: " << i+1 << " --- Calculating the error in this bin --- " << 1.84 << endl;  
   (*h1)->SetBinError(i+1, 1.84);
   }
 
 }

 }

}





binner::~binner(){ 
  //delete[] BINS;
}

