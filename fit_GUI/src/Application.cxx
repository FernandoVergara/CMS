#ifndef __CINT__

#ifndef ROOT_TApplication
#include "TApplication.h"
#endif
#include "../inc/fit.h"
#endif

#ifdef __CINT__
#include "fit.cxx"
#endif

int Application(){
  fit *App = new fit(gClient->GetRoot(),1250,580);
  return 0;
}

#ifndef __CINT__
int main(int argc, char** argv){
  TApplication fit("fit", &argc, argv);
  int retVal = Application();
  fit.Run();
  return retVal;
}
#endif

