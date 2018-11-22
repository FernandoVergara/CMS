void pileup(){

TFile *f1 = TFile::Open("PileupMC_2017.root","READ");
TFile *f2 = TFile::Open("PileupMC_2017_v1.root","RECREATE");

TH1D *h1 = (TH1D*)f1->Get("pileup");

TH1D *pileup = new TH1D("pileup", "pileup", 75, 0, 75);


 for(int i = 1; i <= 75; i++){
 Double_t content = h1->GetBinContent(i);
 pileup->SetBinContent(i,content);
 }

pileup->Write();

f2->Close();

}
