#include "../inc/Effi.h"
#include "TBenchmark.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstring> 
using namespace std;


int main(int argc, char *argv[]) {
  
  ifstream infile;
  infile.open("config/output_name.in");
  if(!infile) {
    std::cout << "could not open file config/output_name.in" <<std::endl;
    exit(1);
  }
  
  int sig_counter = 0;
  vector<string> name_vector(0);
  while(!infile.eof()){
    char name_i[100];
    infile >> name_i;
    name_vector.push_back(name_i);
    sig_counter++; 
  }

  FILE *output[sig_counter-1];
 
  for(int k=0; k<=sig_counter-2;++k){
    string chain = ("");
    chain += name_vector.at(k); 
    char *name = new char[chain.length()+1];
    std::strcpy(name, chain.c_str());
    output[k] = fopen(name, "w");
  }
   
  ifstream infile1;          
  infile1.open("config/path.in");
  if(!infile1) {
    std::cout << "could not open file config/path.in" <<std::endl;
    exit(1);
  }
  
  ifstream infile2;
  infile2.open ("config/parameters.in", ios::in);
  if(!infile2) { 
    std::cout << "could not open file config/paramters.in" <<std::endl;
    exit(1);
  }
  
  TEnv *params = new TEnv ("config_file");
  params->ReadFile ("config/parameters.in", kEnvAll);
  
  Double_t Luminosity  = params->GetValue ("Luminosity", 0.);
  Int_t min_value  = params->GetValue ("min_value", 0.);
  Int_t max_value  = params->GetValue ("max_value", 0.);
  Int_t step  = params->GetValue ("step", 0.);
  TString input_folder = params->GetValue ("input_folder", "");
  TString first_folder = params->GetValue ("first_folder", "");
  TString second_folder = params->GetValue ("second_folder", "");  
  
  vector<string> path(0);
  vector<string> type(0);
  string mainfolder ("");
  mainfolder = input_folder;
  string folder1 ("");
  string folder2 ("");
  vector<double> xsec(0); 
  char ref[100];
  char ref_type[100];
  string first_dir ("");
  string last_dir ("");
  first_dir = first_folder;
  last_dir = second_folder;
  Double_t xsection=0.;
  stringstream stream; 
  Double_t Int1=0., Int2=0., Scale1=0., Scale2=0.;
  double eff=0., B_error=0., Events=0.;
  double SIGNAL[100]={0}, ERRSIGNAL[100]={0};
  double BACK[100]={0}, ERRBACK[100]={0};
  double ALLBACK=0., ALLERRBACK=0.;
  Int_t counter1,counter2 = 0;
  double cuadratic_error=0.;
  double significance[500][500]={0,0}; 
  double errsignificance[500][500]={0,0};
  double Pt[100]={0.};
  double errPt[100]={0.};
  double sig[1000]={0.0};
  double errsig[1000]={0.0};
 
 
  while(!infile1.eof()){
    infile1 >> ref;
    infile1 >> xsection;
    infile1 >> ref_type;
    path.push_back(ref);
    xsec.push_back(xsection); 
    type.push_back(ref_type);
  }
  
  for(int i=min_value; i<=max_value; i=i+step)
    {
      folder1 = mainfolder;
      stream << i;
      folder1 += stream.str();
      folder1 += "/";
      ALLBACK=0.;
      ALLERRBACK=0.;  
      counter1=0;
      for (int j=0; j< path.size()-1;++j)
	{
	  
	  folder2 = folder1;
	  folder2 += path.at(j);
	  char *finalfolder = new char[folder2.length()+1];
	  std::strcpy(finalfolder, folder2.c_str());
	  TFile *f1 = TFile::Open(finalfolder,"READ");
	  char *first_dirt = new char[first_dir.length()+1];
	  std::strcpy(first_dirt, first_dir.c_str());
	  char *last_dirt = new char[last_dir.length()+1];
	  std::strcpy(last_dirt, last_dir.c_str());
	  TH1F *H1 = (TH1F*)f1->Get(first_dirt); 
	  TH1F *H2 = (TH1F*)f1->Get(last_dirt);
	  Int1=H1->Integral();
	  Int2=H2->Integral();
	  if(Int1 !=0.){
	    eff=Int2/Int1;
	    Events=xsec.at(j)*Luminosity*eff;
	    B_error=TMath::Sqrt(eff*(1.0-eff)/Int1);
            if(type.at(j)=="sig"){
	      SIGNAL[counter1]=Events;
	      ERRSIGNAL[counter1]=B_error;
              cout << path.at(j) << " Initial Events " << Int1 << " Final Events " << Int2 <<endl; 
              cout << "Signal xsec "<< xsec.at(j) << " Expected events " << SIGNAL[counter1] << " +- " << ERRSIGNAL[counter1] <<endl;
	      counter1++;
	    }
	    else{
	      BACK[counter2]=Events;
	      ERRBACK[counter2]=B_error;
	      ALLBACK += BACK[counter2];
	      cuadratic_error += ERRBACK[counter2]*ERRBACK[counter2];
	      ALLERRBACK = TMath::Sqrt(cuadratic_error);
              cout << path.at(j) << " Initial Events " << Int1 << " Final Events " << Int2 <<endl; 
	      cout << "Back xsec "<< xsec.at(j) << " Expected events " << BACK[counter2] << " +- " << ERRBACK[counter2] <<endl;
	      cout << "Accumulative Background " << ALLBACK << " +- " << ALLERRBACK <<endl;
              cout << "---------------------------------------------------------" << endl;
	      counter2++; 
	    }
	  }          
	  
	}
      stream.str("");
      double totalB = ALLBACK;
      double totalB_error = ALLERRBACK;
      for(int k = 0; k< counter1;++k){ 
        significance[i][k]=SIGNAL[k]/TMath::Sqrt(SIGNAL[k]+totalB);
        //errsignificance[i][k]=significance[i][k]*1.0/(2*(SIGNAL[k]+totalB))*TMath::Sqrt(pow(2.0*totalB/SIGNAL[k]+1,2)*(pow(ERRSIGNAL[k],2))+pow(totalB_error,2));
      cout << path.at(k) <<" Significance at Pt_"<< i <<"   "<< significance[i][k] <<" +- "<<errsignificance[i][k] <<endl;
      }
      cout <<"Total background events " << totalB <<"  +-  "<<totalB_error << " for PT_"<<i<<endl;  
      Pt[i]=(int)i;      

 
     
       for(int k = 0; k< counter1;++k){
       fprintf(output[k], "%f %f %f\n", Pt[i], significance[i][k], errsignificance[i][k]); 
       }

     }
  
  
  
}

Effi::Effi() {
}


Effi::~Effi(){
}


