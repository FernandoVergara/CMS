{
  TCanvas *c1 = new TCanvas("c1","c1",800,1000);  //instantiate a canvas.
  
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);  //instantiate the first pad.
  pad1->SetBottomMargin(0.1); 
  pad1->SetGridx();
  pad1->Draw();
  pad1->cd();

  gStyle->SetOptStat(0);

  //____________________________________________________________

  //__________GRAB THE M_T PLOT FOR NO SHIFT_________
  TFile *f1 = new TFile("DYJets_boost_0529.root");
  f1->cd("METCut");
  TH1F *mTShape1 = Tau1MetMt;
  Double_t nbins1 = mTShape1->GetNbinsX();
  Double_t xmax1 = 500.;
  TH1F *mTShiftnorebin = new TH1F("mTShiftnorebin","mTShiftnorebin",nbins1,0,xmax1);
  for(Int_t i=1;i<=nbins1;i++){
    mTShiftnorebin->SetBinContent(i,mTShape1->GetBinContent(i));
  }

  TFile *f2 = new TFile("DYJets_boostup_0529.root");
  f2->cd("METCut");
  TH1F *mTShape2 = Tau1MetMt;
  Double_t nbins2 = mTShape2->GetNbinsX();
  Double_t xmax2 = 500.;
  TH1F *mTShiftUprebin = new TH1F("mTShiftUprebin","mTShiftUprebin",nbins2,0,xmax2);
  for(Int_t i=1;i<=nbins2;i++){
    mTShiftUprebin->SetBinContent(i,mTShape2->GetBinContent(i));
  }

  TFile *f3 = new TFile("DYJets_boostdown_0529.root");
  f3->cd("METCut");
  TH1F *mTShape3 = Tau1MetMt;
  Double_t nbins3 = mTShape3->GetNbinsX();
  Double_t xmax3 = 500.;
  TH1F *mTShiftDownrebin = new TH1F("mTShiftDownrebin","mTShiftDownrebin",nbins3,0,xmax3);
  for(Int_t i=1;i<=nbins3;i++){
    mTShiftDownrebin->SetBinContent(i,mTShape3->GetBinContent(i));
  }

  Double_t xbins[22] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,500};
  //mTShiftno->Rebin(21,"mTShiftnorebin",xbins);
  mTShiftnorebin->Draw();
  
  mTShiftnorebin->SetLineColor(2);
  mTShiftnorebin->GetXaxis()->SetLimits(0.,500.);
  mTShiftnorebin->SetTitle("m_T for stau + ISR (DYJets)");
  mTShiftnorebin->GetXaxis()->SetTitle("m_T [GeV]");
  mTShiftnorebin->GetYaxis()->SetTitle("Events");
  //____________________________________________________________

  //mTShiftUp->Rebin(21,"mTShiftUprebin",xbins);  
  mTShiftUprebin->Draw("same");
  mTShiftUprebin->SetLineColor(4);
  //mTShiftDown->Rebin(21,"mTShiftDownrebin",xbins);  
  mTShiftDownrebin->Draw("same");
  mTShiftDownrebin->SetLineColor(8);
  //________________________________________________________________________________

  //__________LEGEND____________________________________
  Double_t xl1=.5, yl1=0.75, xl2=xl1+.3, yl2=yl1+.125;
  TLegend *leg = new TLegend(xl1,xl2,yl1,yl2);
  leg->AddEntry(mTShiftnorebin,"ISR wgt no shift","f");
  leg->AddEntry(mTShiftUprebin,"ISR wgt shift up","f");
  leg->AddEntry(mTShiftDownrebin,"ISR wgts shift down", "f");
  leg->Draw();
  c1->Update();
  //____________________________________________________

  //__________SET PARAMETERS OF RATIO PAD_________________
  c1->cd();
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0.125);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx();
  pad2->Draw();
  pad2->cd();
  //______________________________________________________

  //__________RATIO FOR UP SHIFT TO NO SHIFT______________
  TH1F *ratuprebin = (TH1F*)mTShiftUprebin->Clone("ratuprebin");
  ratuprebin->Sumw2();  //parameter for the error bars
  ratuprebin->SetStats(0);  //parameter for the error bars
  ratuprebin->Divide(mTShiftnorebin);
  //ratup->Rebin(21,"ratuprebin",xbins);
  //______________________________________________________

  //__________RATIO FOR DOWN SHIFT TO NO SHIFT____________
  TH1F *ratdownrebin = (TH1F*)mTShiftDownrebin->Clone("ratdownrebin");
  ratdownrebin->Sumw2();
  ratdownrebin->SetStats(0);
  ratdownrebin->Divide(mTShiftnorebin);
  //ratdown->Rebin(21,"ratdownrebin",xbins);
  //_______________________________________________________
  
  //__________STYLE PARAMETERS FOR RATIO PLOT_____________________________
  ratuprebin->SetLineColor(1);
  ratuprebin->SetMinimum(0.75);
  ratuprebin->SetMaximum(1.25);
  ratuprebin->GetXaxis()->SetLimits(0.,500.);
  ratuprebin->SetTitle(" ");
  ratuprebin->GetYaxis()->SetTitle("ratio");
  ratuprebin->GetYaxis()->SetTitleSize(20);
  ratuprebin->GetYaxis()->SetTitleFont(43);
  ratuprebin->GetYaxis()->SetTitleOffset(1.25);
  ratuprebin->GetYaxis()->SetLabelFont(43);
  ratuprebin->GetYaxis()->SetLabelSize(15);

  ratuprebin->SetMarkerStyle(7);
  ratuprebin->SetMarkerColor(4);
  ratuprebin->Draw("ep");
  ratdownrebin->SetMarkerColor(8);
  ratdownrebin->Draw("same");

  //__________TO DRAW A LINE AT 1 IF WE CONSIDER THE DEVIATIONS SEPARATELY...__________  
  const Int_t n = 5000;
  Double_t x[n], y[n];
  for (Int_t i=0;i<n;i++) {
    x[i] = i*0.1;
    y[i] = 1;
  }
  TGraph *gr = new TGraph(n,x,y);
  gr->SetLineColor(1);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(4);
  gr->Draw("same");
  //____________________________________________________________________________________

  c1->Update();
  c1->SaveAs("isrstau_boost_DYJets_05.29.root")

    }
