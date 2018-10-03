void fit::Fill(TH1F *Numerator, TH1F *Denominator, Int_t nbins, Int_t min, Int_t max){
  
  bins = Denominator->GetXaxis()->GetNbins();
  
  H_bins_num = new TH1F("H_bins_num", "Numerator", nbins, min,max);
  H_bins_den = new TH1F("H_bins_den", "Denominator", nbins, min, max);

  for (int b = 1; b <= H_bins_den->GetXaxis()->GetNbins(); b++ ){
    int num_bin = 0;
    int den_bin = 0;
    
    for (int i = 1; i < bins; i++ ){
      
      if(((( Denominator->GetXaxis()->GetBinLowEdge(i)) + (Denominator->GetXaxis()->GetBinWidth(i))) <= ((H_bins_den->GetXaxis()->GetBinLowEdge(b))+ (H_bins_den->GetXaxis()->GetBinWidth(b)))) &&
	 ((( Denominator->GetXaxis()->GetBinLowEdge(i))+ (Denominator->GetXaxis()->GetBinWidth(i))) > ((H_bins_den->GetXaxis()->GetBinLowEdge(b))))){
	
	num_bin += Numerator->GetBinContent(i);
	den_bin += Denominator->GetBinContent(i);
	
      }
      else{continue;}
      H_bins_num->SetBinContent(b, num_bin);
      H_bins_den->SetBinContent(b, den_bin);      
    }
    
  }
  
}
void fit::DeleteFill(){
  delete H_bins_num;
  delete H_bins_den;
}
