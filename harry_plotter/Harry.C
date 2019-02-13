#include "src/LoadFiles.h"
#include "src/binner.h"
#include "src/plotter.h"
#include "src/systematic.h"

void Harry(){

const TString cmd = "echo $HOME | head -1";
const TString home = gSystem->GetFromPipe(cmd);


/*
string Path_rootfiles = "Zmumu";
string folder = string(home)+"/Dropbox/CMS/Data/Zmumu";
string Subfolder = "new_pileup"; 
*/

string Path_rootfiles = "CRD";
string folder = string(home)+"/Dropbox/CMS/Data/CRD";
string Subfolder = "/"; 


string bin_input = "bins";
string colors_input = "colors_CRD";
//Double_t range[4] = {-1000.,0.01,0.,300000.};
Double_t range[4] = {0.,0.01,500.,200.};


/*
string Path_rootfiles = "njets1";
string Subfolder = "njets1"; 
string bin_input = "bins_njets1";
string colors_input = "colors_njets1";
Double_t range[4] = {200.,0.01,2000.,120.};
*/

/*
string Path_rootfiles = "CRD_MC";
string Subfolder = "CRD_MC"; 
string bin_input = "bins";
string colors_input = "colors_CRD";
Double_t range[4] = {0.,0.01,500.,150.};
*/

/*
string Path_rootfiles = "njets2";
string Subfolder = "njets2"; 
string bin_input = "bins_njets2";
string colors_input = "colors_njets2";
Double_t range[4] = {200.,0.01,2000.,120.};
*/

//Do plot by bin width
bool dividebinwidth = false;

LoadFiles *F1 = new LoadFiles();
F1->Init(Path_rootfiles);
F1->Show();
F1->LoadData(folder, Subfolder);

//Choose the label to obtain the histos (Index)
cout << " Choose the index for the histogram. " << endl;
UInt_t index = 0;
cin >> index; 
string histo_path = F1->Histo_Label[index];
string Xlabel = F1->Labels[index];
F1->Fill_Histos(histo_path);
F1->Scale_MC(); // Scaling method


//The names for the histograms are Data_histos and MC_histos
UInt_t size_data = F1->Data_size;
TH1D* Data_[size_data];  
UInt_t size_mc = F1->MC_size;
TH1D* MC_[size_mc];  
for(UInt_t i = 0 ; i < size_data ; i++) Data_[i] = F1->Data_histos[i];
for(UInt_t i = 0 ; i < size_mc ; i++) MC_[i] = F1->MC_histos[i];

// Rebinning histograms
binner *bin1 = new binner(); 

bin1->Init(bin_input);
F1->Init_AllBack(bin1->N_bins, bin1->BINS); // Initialize Total background 


// For data
for(UInt_t i = 0 ; i < size_data ; i++){
bin1->Rebinner(&Data_[i], i);
}
//For MC
for(UInt_t i = 0 ; i < size_mc ; i++){
bin1->Rebinner(&MC_[i], i);
}
//Adding all backgrounds
bin1->Rebinner(&F1->AllBack, 200); // this index does not matter

//bin1->Weight_Init("weights_recoil");
bin1->Weight_Init("weights_inverted");


//Calculate total background, The systematic L=2.5%, Pileup=5%, Closure=5% 


for(UInt_t i = 0 ; i < size_mc ; i++){
//bin1->ApplyWeight(&MC_[i]);
F1->AllBack->Add(MC_[i]);
}

systematic *Syst = new systematic();
Syst->Init("Zmumu"); 
Syst->Show();
//Syst->ApplySyst(&F1->AllBack);


if(dividebinwidth == true){

for(UInt_t i = 0 ; i < size_data ; i++){
bin1->BinWidth(&Data_[i]);
}
for(UInt_t i = 0 ; i < size_mc ; i++){
bin1->BinWidth(&MC_[i]);
}
bin1->BinWidth(&F1->AllBack);

}

// create possion error for Data (case 0 events in bin i)
for(UInt_t i = 1 ; i < size_data ; i++){
cout << i << endl;
//bin1->Poisson_error(&Data_[i], dividebinwidth);
Data_[0]->Add(Data_[0], Data_[i],1,1);
}


//Style stuff

plotter *COLOR = new plotter();
COLOR->Init(colors_input);
//COLOR->ShowColor();
for(UInt_t i = 0 ; i < size_data ; i++){
COLOR->SetColorData(&Data_[i], "", "Events");
Data_[i]->GetXaxis()->SetRangeUser(range[0],range[2]);
//Data_[i]->GetYaxis()->SetRangeUser(range[1],range[3]);
}
for(UInt_t i = 0 ; i < size_mc ; i++){
COLOR->SetColorMC(&MC_[i], i, "", "Events");
MC_[i]->GetXaxis()->SetRangeUser(range[0],range[2]);
//MC_[i]->GetYaxis()->SetRangeUser(range[1],range[3]);
}
F1->AllBack->GetXaxis()->SetRangeUser(range[0],range[2]);
COLOR->SetColorAllBack(&F1->AllBack, "", "Events");

//Create Stack for MC
THStack *Hs = new THStack("Hs", "");
for(UInt_t i = 0 ; i < size_mc ; i++){
Hs->Add(MC_[i]);
}
/*
Hs->Add(MC_[4]);
Hs->Add(MC_[1]);
Hs->Add(MC_[3]);
Hs->Add(MC_[2]);
Hs->Add(MC_[0]);
*/


//true for log scale
COLOR->Create_Canvas(false,false);
COLOR->c->cd();

// Pad1 --------------------------
COLOR->pad1->cd();

Hs->Draw("HIST");
Hs->SetMaximum(Data_[0]->GetMaximum()); 
Hs->GetXaxis()->SetTitle("");
if(!dividebinwidth) Hs->GetYaxis()->SetTitle("Events");
else Hs->GetYaxis()->SetTitle("Events/GeV");

Hs->GetYaxis()->SetTitleSize(0.05);
Hs->GetYaxis()->SetTitleOffset(0.90);

F1->AllBack->Draw("e2same");
Data_[0]->Draw("e1psame");

gPad->RedrawAxis();

//Legend stuff
COLOR->CreateLegend();
//Data
for(UInt_t i = 0 ; i < size_data ; i++){
if(i != 0) continue;
COLOR->LegendAdd(Data_[i],true,F1->Data_Labels[i]);
}
//MC
for(UInt_t i = 0 ; i < size_mc ; i++){
COLOR->LegendAdd(MC_[i],false,F1->MC_Labels[i]);
}
// All background
COLOR->LegendAdd(F1->AllBack,false,"BG stat. uncer.");
COLOR->LegendDraw();

COLOR->CMSLabels();
//COLOR->OtherLabels();

COLOR->pad1->Modified();
COLOR->pad1->Update();



// Pad2 -------------------------
COLOR->pad2->cd();


TH1D *Data_Clone = (TH1D*)Data_[0]->Clone();
TH1D *MC_Clone = (TH1D*)F1->AllBack->Clone();
Data_Clone->Divide(MC_Clone);

//string Ylabel = "#frac{Sum MC BG}{MC}";
string Ylabel = "#frac{Data}{MC}";
COLOR->SetColorDataClone(&Data_Clone, Xlabel, Ylabel);


Data_Clone->GetXaxis()->SetRangeUser(range[0],range[2]);
Data_Clone->GetYaxis()->SetRangeUser(0.5,2.);
Data_Clone->Draw("ep");
COLOR->CreateLine(range[0], range[2]);  


//Create errors from AllBackground    // the last value is the systematic error 
TGraphErrors* errorstack = COLOR->CreateERROR(F1->AllBack, Syst->Syst);
errorstack->Draw("sameE2");

COLOR->ShowRatioValue(Data_Clone, Data_Clone->GetXaxis()->GetNbins());


COLOR->pad2->Modified();
COLOR->pad2->Update();


  
COLOR->c->Modified();
COLOR->c->Update();
COLOR->c->SaveAs(("templates/"+Path_rootfiles+".pdf").c_str());


//F1->CloseData();

}

int main(){
Harry();
return 0;
}
