double year[8] = {1987,1989,1990,1997,2012,2012,2014,2018}; 
double energy[8] = {0.048,0.048,0.138,0.011,0.138,0.615,0.615,1.}; //13
double luminosity[8] = {0.00001986,0.0020,0.0020,0.055,0.144,0.523,0.540,1.}; //36
double gluino[8]={0.026,0.039,0.036,0.2,0.912,0.912,0.912,1.}; //2000 
double chargino[8]={0.00001,0.00001,0.00001,0.136,0.197,0.263,0.947,1.}; //760
double neutralino[8]={0.00001,0.00001,0.00001,0.092,0.131,0.263,0.947,1.}; //730 
double slepton[8]={0.00001,0.00001,0.00001,0.222,0.222,0.333,0.577,1.}; //450

void timeline(){
auto c1 = new TCanvas("c1","c1",600,400);

cout << year[3] << endl;
auto gr1 = new TGraph(); 
auto gr2 = new TGraph(); 
auto gr3 = new TGraph(); 
auto gr4 = new TGraph(); 
auto gr5 = new TGraph(); 
auto gr6 = new TGraph(); 

gr1->SetLineColor(kBlue);
gr1->SetMarkerStyle(20);
gr1->SetMarkerColor(4);
gr1->SetMarkerSize(1.2);

gr2->SetLineColor(kBlue);
gr2->SetMarkerStyle(20);
gr2->SetMarkerColor(2);
gr2->SetMarkerSize(1.2);

gr3->SetLineColor(kBlue);
gr3->SetMarkerStyle(22);
gr3->SetMarkerColor(3);
gr3->SetMarkerSize(1.5);

gr4->SetLineColor(kBlue);
gr4->SetMarkerStyle(29);
gr4->SetMarkerColor(6);
gr4->SetMarkerSize(1.5);

gr5->SetLineColor(kBlue);
gr5->SetMarkerStyle(3);
gr5->SetMarkerColor(7);
gr5->SetMarkerSize(1.5);

gr6->SetLineColor(kBlue);
gr6->SetMarkerStyle(2);
gr6->SetMarkerColor(1);
gr6->SetMarkerSize(1.5);

 for (int i=0; i<8; i++) {
  gr1->SetPoint(i,year[i],energy[i]);
  gr2->SetPoint(i,year[i],luminosity[i]);
  gr3->SetPoint(i,year[i],gluino[i]);
  gr4->SetPoint(i,year[i],chargino[i]);
  gr5->SetPoint(i,year[i],neutralino[i]);
  gr6->SetPoint(i,year[i],slepton[i]);
 
 }


 auto mg = new TMultiGraph();
 mg->Add(gr1);
 mg->Add(gr2);
 mg->Add(gr3);
 mg->Add(gr4);
 mg->Add(gr5);
 mg->Add(gr6);


 mg->GetXaxis()->SetTitle("");
 mg->GetXaxis()->SetTitleOffset(1.0);
 mg->GetXaxis()->SetRangeUser(1980,2020);




  TPaveText *pt = new TPaveText(0.08695652,0.02156334,0.2073579,0.08355795,"NBNDC");
 pt->SetFillStyle(0);
 pt->SetBorderSize(0);
 pt->SetTextAlign(12);
 pt->SetTextSize(0.03);
 
 pt->AddText("UA1   UA2 CDF                             LEP                                                                    Tevatron  LHC             LHC");
  
 mg->Draw("AP");

 
 

 auto legend = new TLegend(0.1,0.7,0.48,0.9);
 legend->SetLineWidth(0);
 legend->AddEntry(gr1,"#sqrt{s}^{max}=13 TeV","p");
 legend->AddEntry(gr2,"L^{max}=36.0 fb^{-1}","p");
 legend->AddEntry(gr3,"m_{#tilde{g}}^{max}=2000 GeV","p");
 legend->AddEntry(gr4,"m_{#tilde{#chi}^{#pm}}^{max}=760 GeV","p");
 legend->AddEntry(gr5,"m_{#tilde{#chi}^{0}}^{max}=730 GeV","p");
 legend->AddEntry(gr6,"m_{#tilde{l}}^{max}=450 GeV","p");

 legend->Draw();
 pt->Draw();

}


int main(){
timeline();
return 0;
}
