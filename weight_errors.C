#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TTreePlayer.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TEfficiency.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "math.h"
#include <TMultiGraph.h>

using namespace std;

vector<Double_t> Old_X;
vector<Double_t> Old_Y;

vector<Double_t> Y;
vector<Double_t> X;

void weight_errors(){

Old_X.push_back(1.);
Old_X.push_back(3.);
Old_X.push_back(5.);
Old_X.push_back(7.);
Old_X.push_back(9.);
Old_X.push_back(11.);
Old_X.push_back(13.);
Old_X.push_back(15.);
Old_X.push_back(17.);
Old_X.push_back(19.);




//For W
Old_Y.push_back(0.36);
Old_Y.push_back(0.30);
Old_Y.push_back(0.31);
Old_Y.push_back(0.31);
Old_Y.push_back(0.31);
Old_Y.push_back(0.31);
Old_Y.push_back(0.29);
Old_Y.push_back(0.21);
Old_Y.push_back(0.20);
Old_Y.push_back(0.21);




/*
//For Z
Old_Y.push_back(0.37);
Old_Y.push_back(0.36);
Old_Y.push_back(0.38);
Old_Y.push_back(0.36);
Old_Y.push_back(0.29);
Old_Y.push_back(0.30);
Old_Y.push_back(0.29);
Old_Y.push_back(0.34);
Old_Y.push_back(0.25);
Old_Y.push_back(0.42);
*/



// 1 W 2 for Z
/*
TF1 *f1 = new TF1("f1","-0.00796*(x-20.)+0.3692",20,40);
Double_t m = -0.00796;
Double_t b = 0.3692;
*/
Double_t dm = 0.001744;
Double_t db = 0.01474;



TF1 *f1 = new TF1("f1","-0.00390*(x-20.)+0.3823",20,40);
Double_t m = 0.007118;
Double_t b = 0.05736;


Int_t n = 0; 

for(Int_t i = 21; i < 40; i = i+2){
X.push_back(Double_t(i-20));
Y.push_back(f1->Eval(i));
}
n = X.size();


Double_t S = 0.;
Double_t delta = 0.;
Double_t SumX = 0.;
Double_t SumX2 = 0.; 

for(UInt_t i = 0; i < X.size(); i++){
delta += pow(Old_Y[i] - m*Old_X[i] - b,2);
SumX += Old_X[i];
SumX2 += pow(Old_X[i],2);
cout << Old_X[i] << " " << Old_Y[i] << "  "  << SumX << " " << SumX2 << endl;
}

S = sqrt(delta/(n-2));
Double_t Xmean = SumX/n;
cout << " S "  <<  S  << " SumX " <<SumX << " SumX2 "  << SumX2  << " Xmean " << Xmean << endl; 


Double_t tstudent = 2.306; // t 0.05/2, 10-2 

Double_t y_error = 0.;
for(UInt_t i = 0; i < X.size(); i++){
y_error = tstudent*S*sqrt(1./Double_t(n) +  (Double_t(n)* pow(X[i]-Xmean,2)) / (Double_t(n)*SumX2- pow(SumX,2)) );
//cout << setprecision(3) << "$"  << Y[i] << " \\pm " << setprecision(3) << y_error  << "$"  << endl;
printf("$%2.3f \\pm %2.3f$\n", Y[i], y_error);
}


/*
cout << setprecision(3) << " f1 " << C1 << " \\pm " << setprecision(2) << Te_1 << 
" & " << setprecision(3) << C2 << " \\pm  " << setprecision(3) << Te_2 << " & " << 
setprecision(3) << (abs(C1-C2)/C2)*100.<< "\\% \\ \\"  << endl;
*/



}

int main(){
weight_errors();
return 0;
}


