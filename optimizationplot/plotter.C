#include "TGraph.h"
#include "TLatex.h"
#include <stdarg.h>

std::vector<Double_t> X;
std::vector<Double_t> Y;
std::vector<string> Label;
std::vector<string> Xlabel;
Double_t Max = 0.;

void fill(){

 ifstream file;
// file.open("data/TauLSP270.txt", ios::in);
// file.open("data/TauLSP360.txt", ios::in);
 file.open("data/TauLSP450.txt", ios::in);

 Double_t x,y;
 while(!file.eof()){
 file >> x;
 file >> y;
 X.push_back(x);
 Y.push_back(y);
 }
 X.pop_back();
 Y.pop_back();

 file.close();

 Label.push_back("m(#tilde{#chi}^{#pm})=300,m(#tilde{#tau})=285,m(#tilde{#chi}_{0}^{1})=270 GeV");
 Label.push_back("m(#tilde{#chi}^{#pm})=400,m(#tilde{#tau})=380,m(#tilde{#chi}_{0}^{1})=360 GeV");
 Label.push_back("m(#tilde{#chi}^{#pm})=500,m(#tilde{#tau})=475,m(#tilde{#chi}_{0}^{1})=450 GeV");

 Xlabel.push_back("p_{#font[12]{T}}(#tau_{h})[GeV]");
 Xlabel.push_back("p_{#font[12]{T}}(j^{lead})[GeV]");
}

void GetMax(Double_t &Max_){

  for(auto& it : Y){
  if(it > Max_) Max_ = it;
  }

}

void plotter(){

 fill();
 for(UInt_t i = 0; i < X.size(); i++){
 std:cout << "pt:" << X[i] << " S: " << Y[i] << std::endl;
 }

 GetMax(Max); std::cout << " Max: " << Max <<std::endl;
   
 std::string Smax = to_string(Max);
 size_t tamaño= Smax.length(); 
 Smax.erase(tamaño-1); 
 Smax.erase(tamaño-2);
 Smax.erase(tamaño-3); 
 
 Int_t Npoints = X.size();
 Double_t *X_ = new Double_t[Npoints];
 Double_t *Y_ = new Double_t[Npoints];
 
 Int_t i=0;
 for(auto& it : X) {
	X_[i] = it;
	i++;
	}
        i=0;
 for(auto& it : Y){
	Y_[i] = it/Max;
	i++;
	}


 
 TCanvas *c1 = new TCanvas("c1", "Significanca",510,81,700,500);
 c1->Range(43.73344,-0.1814691,139.5011,1.230598);
 c1->SetFillColor(0);
 c1->SetBorderMode(0);
 c1->SetBorderSize(2);
 c1->SetLeftMargin(0.1246418);
 c1->SetBottomMargin(0.1380042);
 c1->SetFrameBorderMode(0);
 c1->SetFrameBorderMode(0);

 TGraph *gr = new TGraph(Npoints,X_,Y_);
 gr->GetXaxis()->SetTitle(Xlabel[0].c_str());
 gr->GetXaxis()->SetTitleSize(0.06);
 gr->GetXaxis()->SetTitleOffset(1.0);
 gr->GetXaxis()->SetLabelSize(0.05);
 gr->GetYaxis()->SetTitle("#it{S}/#bf{S_{max}}");
 gr->GetYaxis()->SetTitleSize(0.06);
 gr->GetYaxis()->SetTitleOffset(1.0);
 gr->GetYaxis()->SetLabelSize(0.05);

 gr->GetYaxis()->SetRangeUser(0.,1.4);

 gr->SetTitle("");
 gr->SetMarkerColor(4);
 gr->SetMarkerStyle(20); 
 gr->SetMarkerSize(1.5);
 gr->Draw("AP");

 gROOT->ForceStyle();
 gStyle->SetLegendBorderSize(0);

 TLegend *leg = new TLegend(0.2621777,0.8004246,0.8868195,0.8832272,NULL,"brNDC");
 leg->SetBorderSize(0);
 leg->SetLineColor(1);
 leg->SetLineStyle(1);
 leg->SetLineWidth(1);
 leg->SetFillColor(0);
 leg->SetFillStyle(1001);
 TLegendEntry *entry=leg->AddEntry(gr,Label[1].c_str(),"p");
 entry->SetTextFont(42);
 leg->Draw();


 TLatex latex;
 latex.SetTextSize(0.05);
 latex.SetTextFont(52);
 latex.DrawLatex(54.1,1.103929,("#bf{S_{max}}="+Smax).c_str());

 delete[] X_;
 delete[] Y_;
}

int main(){
plotter();
return 0;
}


