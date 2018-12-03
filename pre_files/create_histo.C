void create_histo(){
  
  std::ifstream Input[2];
  
  Input[0].open("input.in");
  Input[1].open("root.in");
  
  std::vector<string> input;
  std::vector<string> output;
  
  string input_="";
  string output_="";
  
  while(!Input[0].eof()){
    Input[0] >> input_;
    input.push_back(input_);
  }
  input.pop_back();
  
  
  while(!Input[1].eof()){
    Input[1] >> input_;
    output.push_back(input_);
  }
  output.pop_back();
  
  
  for(UInt_t i=0;i<input.size();i++){
    //	std::cout << input[i] << " " << output[i] << " " << std::endl;
  }
  
  std::vector<string> Cuts;
  std::vector<string> Histos;
  
  Cuts.push_back("NRecoTriggers1");
  Cuts.push_back("NRecoBJet");
  Cuts.push_back("METCut");
  
  Histos.push_back("NVertices");
  Histos.push_back("Tau1MetMt");
  Histos.push_back("Met");
  
  
  TFile *Data[30];
  TFile *Out[30];
  
  for(UInt_t i = 0; i < input.size(); i++){
    Data[i] = TFile::Open((input[i]).c_str(),"READ");
  }
  for(UInt_t i = 0; i < output.size(); i++){
    Out[i] = TFile::Open(("results/"+output[i]).c_str(),"RECREATE");
  }
  
  TH1D *Histo[30];
  
  for(UInt_t ii = 0; ii < Cuts.size(); ii++){
    
    for(UInt_t i = 0; i < output.size(); i++){
      Out[i]->mkdir(Cuts[ii].c_str());
    }
    
    for(UInt_t jj = 0; jj < Histos.size(); jj++){
      
      string path = Cuts[ii]+"/"+Histos[jj];
      
      for(UInt_t i = 0; i < input.size(); i++){
	TH1D *h1 = (TH1D*)Data[i]->Get(path.c_str());
	h1->Sumw2();
        Histo[i] = h1;
      }
      
      for(UInt_t j = 0; j < output.size(); j++){
	Out[j]->cd(Cuts[ii].c_str());
        Histo[j]->Write();
	gDirectory->pwd();
	std::cout << Cuts[ii] << " " << Histo[j]->GetName() << std::endl;
      }
      
      
    }
  }
  
  
  
  for(UInt_t i = 0; i < output.size(); i++) Out[i]->Close();
  
  
  
}

int main(){
  create_histo();
  return 0;
}

