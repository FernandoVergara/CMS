#include "LoadFiles.h"

LoadFiles::LoadFiles(): 
  Data_size(0),
  MC_size(0){
}


void LoadFiles::Init(string path){
  
  Input[0].open("config/Path/"+path+".in");
  Input[1].open("config/Cuts/Cuts.in");
  Input[2].open("config/Histos/Histos.in");
  Input[3].open("config/Histos/Histos2.in");
    

  UInt_t N_Config = 4;
  
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
  else if (!Input[3]){
    std::cout << "could not open file config/Histos2.in" <<std::endl;
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
  
  temp = "";
  label_ = "";  
    
  while(!Input[3].eof()){
      Input[3] >> temp;  
      Input[3] >> label_;
      Histos2.push_back(temp);
      Xaxis_Label2.push_back(label_); 
    }
    
  Histos2.pop_back();
  Xaxis_Label2.pop_back();  
  

  // filling the histogram paths
  Fill_Map();
  Fill_Map2();
  
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

void LoadFiles::Fill_Map2(){
  
  // The map is fill per Cut, each cut has all histograms.
  int key = 0;
  for(UInt_t i = 0; i < Cuts.size(); i++){
    for(UInt_t j = 0; j < Histos2.size(); j++){
      Histo_Label2[key] = (Cuts[i]+"/"+Histos2[j]).c_str();
      Labels2[key] = (Xaxis_Label2[j]).c_str();
      key++;
    }
  }
  
}


void LoadFiles::Show_Map(){
  
  std::map<UInt_t, string>::iterator it;
  for(it = Histo_Label.begin(); it != Histo_Label.end(); it++)
    std::cout << " Index: " << it->first << " Path to histogram: " << it->second << std::endl;
  std::cout << "For 2D Histograms: "<< std::endl;
  for(it = Histo_Label2.begin(); it != Histo_Label2.end(); it++)
  std::cout << " Index: " << it->first << " Path to 2D histogram: " << it->second << std::endl;
  
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
    cout << " Histos 1D: " << Histos[i] << endl;  
  }
  for(UInt_t i = 0; i < Histos2.size(); i++){
    cout << " Histos 2D: " << Histos2[i] << endl;  
  }
  cout << "-----------------" << endl;
  Show_Map(); 
  
}

void LoadFiles::LoadData(string subfolder_){

    TString out_dir = "Final/";
    gSystem->mkdir(out_dir, kTRUE);
    gSystem->mkdir(out_dir+subfolder_, kTRUE);


  for(UInt_t i = 0; i < Data_files.size(); i++){
    
    TString file_ = subfolder_+"/"+Data_files[i];
    const TString cmd = "cp data/"+file_+" "+out_dir+file_; 
    gSystem->Exec(cmd); 
    
    Data[i] = TFile::Open(("Final/"+ subfolder_ + "/" + Data_files[i]).c_str(),"UPDATE");
  }
  for(UInt_t i = 0; i < MC_files.size(); i++){

    TString file_ = subfolder_+"/"+MC_files[i];
    const TString cmd = "cp data/"+file_+" "+out_dir+file_; 
    gSystem->Exec(cmd); 

    MC[i] = TFile::Open(("Final/"+ subfolder_ + "/" + MC_files[i]).c_str(),"UPDATE");  
  }
}

void LoadFiles::CloseData(){
  for(UInt_t i = 0; i < Data_files.size(); i++){
    TString directory = Data[i]->GetName();   
    gDirectory->cd(directory+":/NRecoTau1");
    gDirectory->pwd(); 
   // Data[i]->Write("",TObject::kOverwrite); 
    cout << "Closing: " << Data_files[i] 	<< endl;  
    Data[i]->Close();
  }
  for(UInt_t i = 0; i < MC_files.size(); i++){
    TString directory = MC[i]->GetName();   
    gDirectory->cd(directory+":/NRecoTau1");
    gDirectory->pwd(); 
   
  //  MC[i]->Write("",TObject::kOverwrite);
    cout << "Closing: " << MC_files[i] << endl;
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

TH2D* LoadFiles::GetDataHisto2(Int_t index, string path){
  TH2D *h2 = (TH2D*)Data[index]->Get(path.c_str());
  if(!h2) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h2->Sumw2();
  return h2;  
}



TH1D* LoadFiles::GetMcHisto(Int_t index, string path){
  TH1D *h1 = (TH1D*)MC[index]->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  return h1;  
}

TH2D* LoadFiles::GetMcHisto2(Int_t index, string path){
  TH2D *h2 = (TH2D*)MC[index]->Get(path.c_str());
  if(!h2) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h2->Sumw2();
  return h2;  
}


void LoadFiles::Fill_Histos(string path_, Int_t type){
  
  for(UInt_t i = 0; i < Data_files.size() ; i++){

    if(type == 1){
    Data_histos[i] = GetDataHisto(i, path_);
    cout << Data_files[i] << " 1D " << " Integral: " <<  Data_histos[i]->Integral() << endl; 
    }
    else if(type == 2){
    Data_histos2[i] = GetDataHisto2(i, path_);
    cout << Data_files[i] << " 2D " << " Integral: " <<  Data_histos2[i]->Integral() << endl; 
    }
    else{
    std::cout << " No valid type: " << std::endl;
    exit(1); 
    }
  }
  
  for(UInt_t i = 0; i < MC_files.size() ; i++){ 

    if(type == 1){
    MC_histos[i] = GetMcHisto(i, path_);
    cout << MC_files[i] << " 1D " << " Integral: " <<  MC_histos[i]->Integral() << endl;
    }
    else if(type == 2){
    MC_histos2[i] = GetMcHisto2(i, path_);
    cout << MC_files[i] << " 2D " << " Integral: " <<  MC_histos2[i]->Integral() << endl;
    }
    else{
    std::cout << " No valid type: " << std::endl;
    exit(1); 
    }
 

  }
  
}


void LoadFiles::Scale_MC(){
  cout << " ----Scaling Backgrounds---- " << endl;
  for(UInt_t i = 0; i < MC_files.size() ; i++){ 
    MC_histos[i]->Scale(Scales[i]);
    cout << " Scaling: " << MC_files[i] << " Scale " << Scales[i] << " New Integral: "  << MC_histos[i]->Integral() << endl; 
  }
}

void LoadFiles::SubstractBack(TH1D **h1, UInt_t avoid){
  for(UInt_t i = 0; i < MC_files.size() ; i++){
  if(i == avoid) continue;
  else (*h1)->Add((*h1),MC_histos[i], 1, -1);
  }
}
void LoadFiles::SubstractBack2(TH2D **h2, UInt_t avoid){
  for(UInt_t i = 0; i < MC_files.size() ; i++){
  if(i == avoid) continue;
  else (*h2)->Add((*h2),MC_histos2[i], 1, -1);
  }
}



void LoadFiles::Init_AllBack(){
  Int_t bins = Data_histos[0]->GetXaxis()->GetNbins();
  AllBack = new TH1D("AllBack","AllBack", bins, Data_histos[0]->GetXaxis()->GetXmin(),Data_histos[0]->GetXaxis()->GetXmax());
  AllBack->Sumw2();
}



LoadFiles::~LoadFiles(){
}

