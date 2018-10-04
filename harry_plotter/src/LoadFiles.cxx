#include "LoadFiles.h"

LoadFiles::LoadFiles(): 
  Data_size(0),
  MC_size(0){
}


void LoadFiles::Init(string path){
  
  Input[0].open("config/Path/"+path+".in");
  Input[1].open("config/Cuts/Cuts.in");
  Input[2].open("config/Histos/Histos.in");
  
  UInt_t N_Config = 3;
  
  if(!Input[0]) {
    std::cout << "could not open file config/path.in" <<std::endl;
    exit(1);
  }
  else if (!Input[1]){
    std::cout << "could not open file config/Cuts.in" <<std::endl;
    exit(1);
  }
  else if (!Input[2]){
    std::cout << "could not open file config/Histos.in" <<std::endl;
    exit(1);
  }
  
  // Root files
  string files_=""; 
  string labels_="";
  string type_="";  
  string Scales_= "";  
  
  while(!Input[0].eof()){
    Input[0] >> files_;
    Input[0] >> type_; 
    Input[0] >> Scales_;
    labels_ = files_; 
    files_ += ".root";
    if(type_ == "Data"){
      Data_files.push_back(files_);
      Data_Labels.push_back("Data"); 
    }
    else { 
      MC_files.push_back(files_);
      MC_Labels.push_back(labels_);
      Scales.push_back(std::stod(Scales_)); 
    }   
  }
  
  MC_files.pop_back();
  MC_Labels.pop_back();
  
  Data_size = Data_files.size();
  MC_size = MC_files.size();
  
  //Cuts and Histos
  string temp = "";  
  while(!Input[1].eof()){
      Input[1] >> temp;  
      Cuts.push_back(temp);
    }  
  Cuts.pop_back();  


  temp = "";
  string label_ = "";  
    
  while(!Input[2].eof()){
      Input[2] >> temp;  
      Input[2] >> label_;
      Histos.push_back(temp);
      Xaxis_Label.push_back(label_); 
    }
    
  Histos.pop_back();
  Xaxis_Label.pop_back();  
  
  // filling the histogram paths
  Fill_Map();
  
  
}



void LoadFiles::Fill_Map(){
  
  // The map is fill per Cut, each cut has all histograms.
  int key = 0;
  for(UInt_t i = 0; i < Cuts.size(); i++){
    for(UInt_t j = 0; j < Histos.size(); j++){
      Histo_Label[key] = (Cuts[i]+"/"+Histos[j]).c_str();
      Labels[key] = (Xaxis_Label[j]).c_str();
      key++;
    }
  }
  
}

void LoadFiles::Show_Map(){
  
  std::map<UInt_t, string>::iterator it;
  for(it = Histo_Label.begin(); it != Histo_Label.end(); it++)
    std::cout << " Index: " << it->first << " Path to histogram: " << it->second << std::endl;
  
}

void LoadFiles::Show(){
  for(UInt_t i = 0; i < Data_files.size(); i++){
    cout << " Data: " << Data_files[i] << endl;
  }
  for(UInt_t i = 0; i < MC_files.size(); i++){
    cout << " MC: " << MC_files[i] << endl;
  }
  
  cout << "-----------------" << endl;
  for(UInt_t i = 0; i < Cuts.size(); i++){
    cout << " Cut: " << Cuts[i] << endl;  
  }
  cout << "-----------------" << endl;
  for(UInt_t i = 0; i < Histos.size(); i++){
    cout << " Histos: " << Histos[i] << endl;  
  }
  cout << "-----------------" << endl;
  Show_Map(); 
  
}

void LoadFiles::LoadData(string folder, string subfolder_){
  for(UInt_t i = 0; i < Data_files.size(); i++){
    Data[i] = TFile::Open((folder + "/" + subfolder_ + "/" + Data_files[i]).c_str(),"READ");
  }
  for(UInt_t i = 0; i < MC_files.size(); i++){
    MC[i] = TFile::Open((folder + "/" + subfolder_ + "/" + MC_files[i]).c_str(),"READ");  
  }
}

void LoadFiles::CloseData(){
  for(UInt_t i = 0; i < Data_files.size(); i++){
    Data[i]->Close();
  }
  for(UInt_t i = 0; i < MC_files.size(); i++){
    MC[i]->Close();  
  }
}


TH1D* LoadFiles::GetDataHisto(Int_t index, string path){
  TH1D *h1 = (TH1D*)Data[index]->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  return h1;  
}

TH1D* LoadFiles::GetMcHisto(Int_t index, string path){
  TH1D *h1 = (TH1D*)MC[index]->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  return h1;  
}


void LoadFiles::Fill_Histos(string path_){
  
  for(UInt_t i = 0; i < Data_files.size() ; i++){
    Data_histos[i] = GetDataHisto(i, path_);
    cout << Data_files[i] << " Integral: " <<  Data_histos[i]->Integral() << endl; 
  }
  
  for(UInt_t i = 0; i < MC_files.size() ; i++){ 
    MC_histos[i] = GetMcHisto(i, path_);
    cout << MC_files[i] << " Integral: " <<  MC_histos[i]->Integral() << endl; 
  }
  
}


void LoadFiles::Scale_MC(){
  cout << " ----Scaling Backgrounds---- " << endl;
  for(UInt_t i = 0; i < MC_files.size() ; i++){ 
    MC_histos[i]->Scale(Scales[i]);
    cout << " Scaling: " << MC_files[i] << " Scale " << Scales[i] << " New Integral: "  << MC_histos[i]->Integral() << endl; 
  }
}

void LoadFiles::Init_AllBack(UInt_t N_bins, Double_t *BINS){
  AllBack = new TH1D("AllBack","AllBack", N_bins, BINS);
  AllBack->Sumw2();
}

LoadFiles::~LoadFiles(){
}

