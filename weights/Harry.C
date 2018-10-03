#include "src/LoadFiles.h"
#include "src/binner.h"

void Harry(){
/*
string Path_rootfiles = "CRC";
string Subfolder = "CRC"; 
string bin_input = "bins";
//sring bin_input = "bins_1";
*/

string Path_rootfiles = "CRB";
string Subfolder = "CRB"; 
string bin_input = "bins";


bool dividebinwidth = false;

LoadFiles *F1 = new LoadFiles();
F1->Init(Path_rootfiles);
F1->Show();
F1->LoadData(Subfolder);

//Choose the label to obtain the histos (Index)
cout << " Choose the index for the histogram. " << endl;
UInt_t index = 0;
cin >> index; 
cout << " Choose the index for the 2D histogram. " << endl;
UInt_t index2 = 0;
cin >> index2; 
///////////////////////////////////////////
string histo_path = F1->Histo_Label[index];
string Xlabel = F1->Labels[index];
string histo_path2 = F1->Histo_Label2[index2];
string Xlabel2 = F1->Labels2[index2];
F1->Fill_Histos(histo_path, 1);
F1->Fill_Histos(histo_path2, 2);
F1->Scale_MC(); // Scaling method

//The names for the histograms are Data_histos and MC_histos
UInt_t size_data = F1->Data_size;
UInt_t size_mc = F1->MC_size;

// Rebinning histograms
binner *bin1 = new binner(); 
bin1->Init(bin_input);
bin1->Weight_Init("weights_Z_MC");

binner *bin2 = new binner(); 
bin2->Init(bin_input);
bin2->Weight_Init("weights_W_MC");

// For data
for(UInt_t i = 0 ; i < size_data ; i++){
F1->Data_histos[i] = bin1->Rebinner1(F1->Data_histos[i]);
F1->Data_histos2[i] = bin1->Rebinner2(F1->Data_histos2[i]);
}
//For MC
for(UInt_t i = 0 ; i < size_mc ; i++){
F1->MC_histos[i] = bin1->Rebinner1(F1->MC_histos[i]);
F1->MC_histos2[i] = bin1->Rebinner2(F1->MC_histos2[i]);
}

for(UInt_t i = 0 ; i < size_data ; i++){
F1->SubstractBack(&F1->Data_histos[i],0);
F1->SubstractBack2(&F1->Data_histos2[i],0);
}



for(UInt_t i = 0 ; i < size_data ; i++){
bin1->ApplyWeight(&F1->Data_histos2[i]);
}

Double_t Total_E = 0.;
for(UInt_t i = 0 ; i < size_data ; i++){
F1->Data_histos[i] = bin1->Proyection_X(&F1->Data_histos2[i], Total_E, 0.95, 1);
}

/*
UInt_t Nbins = F1->Data_histos[0]->GetXaxis()->GetNbins();
double error_ = 0;
for(UInt_t i = 1; i <= Nbins; i++){
 error_ += pow(F1->Data_histos[0]->GetBinError(i),2);
 cout << F1->Data_histos[0]->GetBinError(i) << " " << sqrt(error_) <<endl;
}
*/

cout << "New Integral " << F1->Data_histos[0]->Integral() << " " << sqrt(Total_E) << endl;

F1->Data_histos[0]->SetLineColor(2);
F1->Data_histos[0]->Draw();


/*
F1->Data_histos2[0]->Draw("colz");
F1->Data_histos2[0]->SetStats(kFALSE);
F1->Data_histos2[0]->GetXaxis()->SetRangeUser(20.,40.);
F1->Data_histos2[0]->GetXaxis()->SetTitle("p_{T}(#tau_{h})");
F1->Data_histos2[0]->GetYaxis()->SetTitle("m_{T}(#tau_{h}, E_{T}^{miss})");
*/
//saving in the new file///////////////////////////////

for(UInt_t i = 0 ; i < size_data ; i++){
    TString directory = F1->Data[i]->GetName();   
    gDirectory->cd(directory+":/NRecoTau1");
//    gDirectory->cd(directory+":/METCut");
 
F1->Data_histos[i]->Write("Tau1MetMt",TObject::kOverwrite);
//F1->Data_histos2[i]->Write("Tau1MetMt_Pt",TObject::kOverwrite);
}

for(UInt_t i = 0 ; i < size_mc ; i++){
    TString directory = F1->MC[i]->GetName();   
    gDirectory->cd(directory+":/NRecoTau1");
//    gDirectory->cd(directory+":/METCut");
 
F1->MC_histos[i]->Write("Tau1MetMt",TObject::kOverwrite);
//F1->MC_histos2[i]->Write("Tau1MetMt_Pt",TObject::kOverwrite);

}
F1->CloseData();
}

int main(){
Harry();
return 0;
}
