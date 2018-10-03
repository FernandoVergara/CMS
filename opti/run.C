void run(){
gSystem->mkdir("templates", kTRUE);
gROOT->Reset();
gROOT->ProcessLine(".x src/Files.cxx++");
gROOT->ProcessLine(".x plot.C++");

// se puede posteriormente 
//root -l 
//gSystem->Load("genetic_C.so")
//genetic() 
}
