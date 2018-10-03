{
#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <iomanip>
 ifstream infile;
  infile.open("config/output_name.in");
  if(!infile) {
    std::cout << "could not open file config/output_name.in" <<std::endl;
    exit(1);
  }

 unsigned int sig_counter = 0;	

  vector<string> name_vector(0);
  while(!infile.eof()){
    char name_i[100];
    infile >> name_i;
    name_vector.push_back(name_i);
    sig_counter++;
  }

  ifstream input_files[sig_counter-1];
  for(int k=0; k<=sig_counter-2;++k){
  string chain = ("files/");
  chain += name_vector.at(k);
  char *name = new char[chain.length()+1];
  std::strcpy(name, chain.c_str());
  input_files[k].open(name);
  }
  
  

Double_t x[1000]={0}, y[1000]={0}, ex[1000]={0}, ey[1000]={0};                                                        
Double_t dat1=0., dat2=0., dat3=0.;
TList * allgraphs = new TList();

for(int k=0; k<=24;++k){
Int_t n=0;
while(!input_files[k].eof()){   
input_files[k] >> dat1;  
input_files[k] >> dat2;
input_files[k] >> dat3;
x[n]=dat1;
y[n]=dat2; 
ex[n]=dat3;
cout << n <<" "<< x[n] <<" "<< y[n] <<" "<< ex[n]<< " " << ey[n] <<endl;               
n++;
}
graphs = new TGraphErrors(n,x,y,ey,ex); 
allgraphs->Add(graphs);
}
 
//Setup TCanvas
TCanvas *c1=new TCanvas("c1","Significance",180,10,1000,600);                   
c1->Range(0,0,1,1);
c1->SetFillColor(0);
c1->SetBorderMode(0);
c1->SetBorderSize(2);
c1->SetFrameBorderMode(0);
c1->Divide(1,1);
//Setup pad
 
 TPad *c1_1 = new TPad("c1_1", "c1_1",0.01,0.01,0.99,0.99);
   c1_1->Draw();
   c1_1->cd();
   c1_1->Range(-28.53875,0.006817153,223.7949,0.01827447);
   c1_1->SetFillColor(0);
   c1_1->SetBorderMode(0);
   c1_1->SetBorderSize(2);
   c1_1->SetLeftMargin(0.1130993);
   c1_1->SetRightMargin(0.01503913);
   c1_1->SetBottomMargin(0.1408311);
   c1_1->SetFrameBorderMode(0);
   c1_1->SetFrameBorderMode(0);

//////////////////////////////////////////////////

 c1_1->cd();//TGraph *gr1=new TGraph(n,x,y);     //Dibujar los datos
//TGraphErrors *
  
 int color[sig_counter]={1};
 for (int j=0; j<=24; j++){
  if(j==0) color[j]=j;
  else color[j] = 3;
 }
  
  typedef pair<double, string> C;
  map<double, string> legend;
  legend.insert( C(0.,"050") );
  legend.insert( C(1.,"060") );
  legend.insert( C(2.,"070") );
  legend.insert( C(3.,"080") );
  legend.insert( C(4.,"090") );
  legend.insert( C(5.,"150") );
  legend.insert( C(6.,"160") ); 
  legend.insert( C(7.,"170") );
  legend.insert( C(8.,"180") );
  legend.insert( C(9.,"190") );
  legend.insert( C(10.,"250") );
  legend.insert( C(11.,"260") );
  legend.insert( C(12.,"270") );
  legend.insert( C(13.,"280") ); 
  legend.insert( C(14.,"290") );
  legend.insert( C(15.,"350") );
  legend.insert( C(16.,"360") );
  legend.insert( C(17.,"370") );
  legend.insert( C(18.,"380") );
  legend.insert( C(19.,"390") );
  legend.insert( C(20.,"450") );
  legend.insert( C(21.,"460") );
  legend.insert( C(22.,"470") );
  legend.insert( C(23.,"480") );
  legend.insert( C(24.,"490") ); 
  
 int signal = 16;
  
 TLegend *leg = new TLegend(0.8783076,0.4955324,0.9795305,0.8922585,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
  leg->SetFillStyle(1002);
  leg->SetHeader("LSP Mass");

 for(int k=0; k <= signal; k=k+signal) {
 if (k==0){
 ((TGraph*)allgraphs->At(k))->SetMarkerStyle(20);
 ((TGraph*)allgraphs->At(k))->SetMarkerSize(2.5);
 ((TGraph*)allgraphs->At(k))->SetMarkerColor(color[k]);
 ((TGraph*)allgraphs->At(k))->SetLineWidth(2);
 ((TGraph*)allgraphs->At(k))->SetMinimum(0.001);
 ((TGraph*)allgraphs->At(k))->SetMaximum(20);
 ((TGraph*)allgraphs->At(k))->Draw("AP"); 
 ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLimits(90, 210);
 ((TGraph*)allgraphs->At(k))->SetTitle("");
 ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitle("p_{T}(j) [GeV]");
 ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitleOffset(1);	
 ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitleSize(0.05);	 
 ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitle("#frac{S}{#sqrt{S+B}}");
 ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitleOffset(1);
 ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitleSize(0.05);
 //map<double, string>::iterator p = legend.find(k);
 //leg->AddEntry(((TGraph*)allgraphs->At(k)), p->second.c_str(), "lep");
 } else {
 ((TGraph*)allgraphs->At(k))->SetMinimum(0.01);
 ((TGraph*)allgraphs->At(k))->SetMaximum(10.);
 ((TGraph*)allgraphs->At(k))->SetMarkerStyle(20);
 ((TGraph*)allgraphs->At(k))->SetMarkerSize(2.5);
 ((TGraph*)allgraphs->At(k))->SetMarkerColor(color[k]);
 ((TGraph*)allgraphs->At(k))->SetLineWidth(2); 
 if(k==signal){
 ((TGraph*)allgraphs->At(k))->Draw("P"); 
 map<double, string>::iterator p = legend.find(k);
 leg->AddEntry(((TGraph*)allgraphs->At(k)), p->second.c_str(), "lep");
 } 
 }   
 }

  
 leg->Draw();
  
//gr1=new TGraphErrors(n,x,y,ex,ey);     //Dibujar los datos
//gr1->SetTitle("Significance-Signal (LSP: 250 GeV)");
//gr1->SetTitle("Significance-Signal(LSP 150, s#tau 175, Chargino 200)");
//gr1->SetTitle("Significance-Signal(LSP 150, s#tau 175, Chargino 200)");
///////////////////////////////////////////////////////////////////////////
//gr1->GetXaxis()->SetTitle("PT(#tau_{1}) [GeV]");
//gr1->GetXaxis()->SetTitle("TauJet_Pt (GeV)");
//gr1->GetXaxis()->SetTitle("M_{jj} (GeV)");
//gr1->GetXaxis()->SetTitle("#Delta#eta");
//gr1->GetXaxis()->SetLabelSize(0.04);
//gr1->GetXaxis()->SetTitleOffset(1);						//Tamaño de los numeros
//gr1->GetXaxis()->SetTitleSize(0.060);						//Tamaño del los labels
///////////////////////////////////////////////////////////////////////////
//gr1->GetYaxis()->SetTitle("#frac{S}{#sqrt{S+B}}");
//gr1->GetYaxis()->SetLabelSize(0.04);
//gr1->GetYaxis()->SetTitleOffset(0.85);	
//gr1->GetYaxis()->SetTitleSize(0.060);
///////////////////////////////////////////////////////////////////////////

//gr1->SetMarkerStyle(20);
//gr1->SetMarkerSize(1);
//gr1->SetMarkerColor(4);
//gr1->Draw("AP"); 
//gr2->Draw("same");
 c1->Update();
TPaveText *pt = new TPaveText(0.2430776,0.9328105,0.7569224,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   //TText *AText = pt->AddText("Significance-Signal(LSP 000, s#tau 050, Chargino 100)");
   //TText *AText = pt->AddText("Significance-Signal(LSP 050, s#tau 295, Chargino 300)");
   //TText *AText = pt->AddText("Significance-Signal(LSP 150, s#tau 165, Chargino 200)");
   pt->Draw();
   c1_1->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);

}

