void run(){
gSystem->mkdir("templates", kTRUE);
gROOT->Reset();

Int_t a = 0;
cout << "0 for compile 1 for loading the classes: " << endl;
cin >> a;

if(a==0){
gROOT->ProcessLine(".x src/LoadFiles.cxx++");
gROOT->ProcessLine(".x src/binner.cxx++");
gROOT->ProcessLine(".x src/plotter.cxx++");
gROOT->ProcessLine(".x src/systematic.cxx++");
gROOT->ProcessLine(".L Harry.C");
gROOT->ProcessLine("Harry()");
}
else{
gSystem->Load("src/LoadFiles_cxx.so");
gSystem->Load("src/binner_cxx.so");
gSystem->Load("src/plotter_cxx.so");
gSystem->Load("src/systematic_cxx.so");
gROOT->ProcessLine(".L Harry.C");
gROOT->ProcessLine("Harry()");
}
}
