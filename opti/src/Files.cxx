#include "Files.h"

Files::Files(){
}


Files::Files(double Luminosity_): 
Luminosity(Luminosity_),
integral_1(0.),
integral_2(0.),
efficiency(0.),
signal_size(0){
}

void Files::Init(string folders_){

  file1.open("config/path.in");
  if(!file1) {
    std::cout << "could not open file config/path.in" <<std::endl;
    exit(1);
  }

   string ref="";
   string ref_type="";
   double xsection=0.;

   while(!file1.eof()){
    file1 >> ref;
    file1 >> xsection;
    file1 >> ref_type;
    path.push_back(ref);
    xsec.push_back(xsection); 
    type.push_back(ref_type);
  }
    path.pop_back();
    xsec.pop_back();
    type.pop_back();

  file2.open(("config/"+folders_).c_str());
  if(!file2) {
    std::cout << "could not open file config/folder.in" <<std::endl;
    exit(1);
  }
    
    string folder_="";
    while(!file2.eof()){
    file2 >> folder_;
    folder.push_back(folder_);  
    }
    folder.pop_back();
  
   std::cout << " Running with the luminosity: " <<Luminosity << std::endl;
   std::cout << " Run for more files: " << " ulimit -n 2048 " << std::endl; 
}


std::vector<double> Files::Get_Signal(string sub_, string folder_, string first_, string second_){

  folder_+="/";
  double N_events = 0.;
  std::vector<double> number_signal;
  
  for(unsigned int i = 0; i < path.size(); i++){
  if(type[i] != "sig") continue;
  f_signal = TFile::Open(("data/"+sub_+"/"+folder_+path[i]).c_str(),"READ");
  numerator = (TH1F*)f_signal->Get(first_.c_str()); 
  denominator = (TH1F*)f_signal->Get(second_.c_str());
  integral_1 = numerator->Integral();
  integral_2 = denominator->Integral();
  if(integral_1 != 0.) efficiency = integral_2/integral_1;
  else std::cout << "zero events for: " << path[i] << std::endl;
  N_events = xsec[i]*Luminosity*efficiency;
  number_signal.push_back(N_events);
//  std:cout << path[i] << " " << xsec[i] << " " << Luminosity << " " << integral_1 << " " << integral_2 << " "<< N_events <<std::endl;
  f_signal->Close();
  
  }
  signal_size = number_signal.size(); 
  return number_signal;
}

std::vector<double> Files::Get_Back(string sub_, string folder_, string first_, string second_){

  folder_+="/";
  double N_events = 0.;
  std::vector<double> number_back;
  
  for(unsigned int i = 0; i < path.size(); i++){
  if(type[i] != "bg") continue;
  
  f_back = TFile::Open(("data/"+sub_+"/"+folder_+path[i]).c_str(),"READ");
  numerator = (TH1F*)f_back->Get(first_.c_str()); 
  denominator = (TH1F*)f_back->Get(second_.c_str());
  integral_1 = numerator->Integral();
  integral_2 = denominator->Integral();
  if(integral_1 != 0.) efficiency = integral_2/integral_1;
  else std::cout << "zero events: " << path[i] << std::endl;
  N_events = xsec[i]*Luminosity*efficiency;
  number_back.push_back(N_events);
  
 // std:cout << path[i] << " " << xsec[i] << " " << Luminosity << " " << integral_1 << " " << integral_2 << " "<< N_events <<std::endl;
  f_back->Close();
  
  }
  return number_back;
}



Files::~Files(){
}

