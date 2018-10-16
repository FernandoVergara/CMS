#include "LoadFiles.h" 

#ifndef SYSTEMATIC_H
#define SYSTEMATIC_H

class systematic{
  
 public:
 systematic();
 ~systematic();
 void Init(string file);
 void Show();
 void ApplySyst(TH1D **h1);

 string *Label;
 Double_t *Syst;

 private:
 std::ifstream Input[5];
 
 std::vector<string> label;
 std::vector<Double_t> syst;


};

#endif
