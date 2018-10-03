#include "src/Files.h"

std::vector<double> num_signal;
std::vector<double> num_back;

TCanvas *c1;
TGraph *g1;
TLegend *legend;

Double_t *X;
Double_t *Y;

std::map<int, int> plotting;
std::map<int, string> label_;
std::map<int, string> output_;
string subfolder = "pt_jet"; 

void fill_info(){
/*
plotting[0]=30;
plotting[1]=40;
plotting[2]=50;
plotting[3]=60;
plotting[4]=70;
plotting[5]=80;
plotting[6]=90;
*/

plotting[0]=100;
plotting[1]=110;
plotting[2]=120;
plotting[3]=130;
plotting[4]=140;
plotting[5]=150;


label_[0] = "m(#tilde{#chi}_{1}^{0})=50 GeV, m(#tilde{#tau})=75 GeV, m(#chi^{#pm}) = 100 GeV";
label_[1] = "m(#tilde{#chi}_{1}^{0})=60 GeV, m(#tilde{#tau})=80 GeV, m(#chi^{#pm}) = 100 GeV";
label_[2] = "m(#tilde{#chi}_{1}^{0})=70 GeV, m(#tilde{#tau})=85 GeV, m(#chi^{#pm}) = 100 GeV";
label_[3] = "m(#tilde{#chi}_{1}^{0})=80 GeV, m(#tilde{#tau})=90 GeV, m(#chi^{#pm}) = 100 GeV";
label_[4] = "m(#tilde{#chi}_{1}^{0})=90 GeV, m(#tilde{#tau})=95 GeV, m(#chi^{#pm}) = 100 GeV";
label_[5] = "m(#tilde{#chi}_{1}^{0})=150 GeV, m(#tilde{#tau})=175 GeV, m(#chi^{#pm}) = 200 GeV";
label_[6] = "m(#tilde{#chi}_{1}^{0})=160 GeV, m(#tilde{#tau})=180 GeV, m(#chi^{#pm}) = 200 GeV";
label_[7] = "m(#tilde{#chi}_{1}^{0})=170 GeV, m(#tilde{#tau})=185 GeV, m(#chi^{#pm}) = 200 GeV";
label_[8] = "m(#tilde{#chi}_{1}^{0})=180 GeV, m(#tilde{#tau})=190 GeV, m(#chi^{#pm}) = 200 GeV";
label_[9] = "m(#tilde{#chi}_{1}^{0})=190 GeV, m(#tilde{#tau})=195 GeV, m(#chi^{#pm}) = 200 GeV";
label_[10] = "m(#tilde{#chi}_{1}^{0})=250 GeV, m(#tilde{#tau})=275 GeV, m(#chi^{#pm}) = 300 GeV";
label_[11] = "m(#tilde{#chi}_{1}^{0})=260 GeV, m(#tilde{#tau})=280 GeV, m(#chi^{#pm}) = 300 GeV";
label_[12] = "m(#tilde{#chi}_{1}^{0})=270 GeV, m(#tilde{#tau})=285 GeV, m(#chi^{#pm}) = 300 GeV";
label_[13] = "m(#tilde{#chi}_{1}^{0})=280 GeV, m(#tilde{#tau})=290 GeV, m(#chi^{#pm}) = 300 GeV";
label_[14] = "m(#tilde{#chi}_{1}^{0})=290 GeV, m(#tilde{#tau})=295 GeV, m(#chi^{#pm}) = 300 GeV";
label_[15] = "m(#tilde{#chi}_{1}^{0})=350 GeV, m(#tilde{#tau})=375 GeV, m(#chi^{#pm}) = 400 GeV";
label_[16] = "m(#tilde{#chi}_{1}^{0})=360 GeV, m(#tilde{#tau})=380 GeV, m(#chi^{#pm}) = 400 GeV";
label_[17] = "m(#tilde{#chi}_{1}^{0})=370 GeV, m(#tilde{#tau})=385 GeV, m(#chi^{#pm}) = 400 GeV";
label_[18] = "m(#tilde{#chi}_{1}^{0})=380 GeV, m(#tilde{#tau})=390 GeV, m(#chi^{#pm}) = 400 GeV";
label_[19] = "m(#tilde{#chi}_{1}^{0})=390 GeV, m(#tilde{#tau})=395 GeV, m(#chi^{#pm}) = 400 GeV";
label_[20] = "m(#tilde{#chi}_{1}^{0})=450 GeV, m(#tilde{#tau})=475 GeV, m(#chi^{#pm}) = 500 GeV";
label_[21] = "m(#tilde{#chi}_{1}^{0})=460 GeV, m(#tilde{#tau})=480 GeV, m(#chi^{#pm}) = 500 GeV";
label_[22] = "m(#tilde{#chi}_{1}^{0})=470 GeV, m(#tilde{#tau})=485 GeV, m(#chi^{#pm}) = 500 GeV";
label_[23] = "m(#tilde{#chi}_{1}^{0})=480 GeV, m(#tilde{#tau})=490 GeV, m(#chi^{#pm}) = 500 GeV";
label_[24] = "m(#tilde{#chi}_{1}^{0})=490 GeV, m(#tilde{#tau})=495 GeV, m(#chi^{#pm}) = 500 GeV";

output_[0] = "LSP50";
output_[1] = "LSP60";
output_[2] = "LSP70";
output_[3] = "LSP80";
output_[4] = "LSP90";
output_[5] = "LSP150";
output_[6] = "LSP160";
output_[7] = "LSP170";
output_[8] = "LSP180";
output_[9] = "LSP190";
output_[10] = "LSP250";
output_[11] = "LSP260";
output_[12] = "LSP270";
output_[13] = "LSP280";
output_[14] = "LSP290";
output_[15] = "LSP350";
output_[16] = "LSP360";
output_[17] = "LSP370";
output_[18] = "LSP380";
output_[19] = "LSP390";
output_[20] = "LSP450";
output_[21] = "LSP460";
output_[22] = "LSP470";
output_[23] = "LSP480";
output_[24] = "LSP490";
}
void plot_declar(){
//Plotting
 
 c1 = new TCanvas("c1","Optmization", 289,160,823,502);
 c1->Range(12.96275,0.007746655,97.65043,0.00978996);
 c1->SetFillColor(0);
 c1->SetBorderMode(0);
 c1->SetBorderSize(2);
 c1->SetLeftMargin(0.1303289);
 c1->SetRightMargin(0.01948843);
 c1->SetBottomMargin(0.1218487);

 c1->SetFrameBorderMode(0);
 c1->SetFrameBorderMode(0); 

// gPad->SetTickx(); 
// gPad->SetTicky(); 

}

void update_plot(int k_, int Size, double X_[], double Y_[]){



  g1 = new TGraph(Size,X_,Y_);
  g1->SetTitle("");
  g1->SetLineColor(kBlue);
  g1->SetMarkerStyle(20);
  g1->SetMarkerSize(1.2);
  g1->SetMarkerColor(2);
  g1->GetXaxis()->SetTitle("p_{T}(#tau) [GeV]");
  g1->GetXaxis()->SetTitle("p_{T}(j) [GeV]");
 
  g1->GetXaxis()->SetTitleSize(0.05);
  g1->GetXaxis()->SetTitleOffset(1);
  g1->GetYaxis()->SetTitle("#frac{S}{#sqrt{S+B}}");
  g1->GetYaxis()->SetTitleSize(0.05);
  g1->GetYaxis()->SetTitleOffset(1);
  g1->Draw("AP");

  legend = new TLegend(0.362972,0.7668067,0.9464068,0.894958,NULL,"brNDC");
  legend->SetBorderSize(0);
  legend->SetLineColor(1);
  legend->SetLineStyle(1);
  legend->SetLineWidth(1);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  TLegendEntry *entry=legend->AddEntry("g1",label_[k_].c_str(),"PL");
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(2);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(21);
  legend->Draw(); 
 
  c1->Modified();
  c1->Update();
  c1->SaveAs(("templates/"+subfolder+"/"+output_[k_]+".pdf").c_str());

}


void plot(){

Files *FF = new Files(35870.);
FF->Init("folder_2.in");
fill_info();

string first_ = "NRecoTriggers1/Met";
string second_ = "METCut/Met";

int size_pt = FF->folder.size();

X = new Double_t[size_pt];
Y = new Double_t[size_pt];

double total_back = 0.;
double signal = 0.;

 
plot_declar();

for(int k = 0; k < 25; k++){

if(k != 12) continue;


for(int i = 0; i < size_pt; i++){
num_signal = FF->Get_Signal(subfolder,FF->folder[i], first_, second_);
num_back = FF->Get_Back(subfolder, FF->folder[i], first_, second_);

total_back = 0.;
for(unsigned int j = 0; j < num_back.size(); j++){
total_back += num_back[j];
}
signal = num_signal[k];
X[i] = plotting[i];
Y[i] = signal/TMath::Sqrt(signal+total_back);
std::cout << i << " " << X[i]  << " " << signal/TMath::Sqrt(signal+total_back) << std::endl;
}



update_plot(k,size_pt,X,Y);

}

delete[] X;
delete[] Y;
//delete legend;
//delete g1;

}

int main(){
plot();
return 0;
}
