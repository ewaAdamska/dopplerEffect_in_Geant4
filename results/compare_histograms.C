int compare_histograms () {

    Int_t                  id;
    Double_t               energy;

    TFile *f = new TFile("output.root");
    TTree *t = (TTree*) f->Get ("tree");

    t->SetBranchAddress ("id" , &id  );
    t->SetBranchAddress ("energy" , &energy  );

    TCanvas *c1 = new TCanvas("c1","c1",1200,800);
    gStyle->SetOptStat(0);

//    gStyle->SetNdivisions (804, "X");
//    gStyle->SetNdivisions (504, "Y");


    gStyle->SetLabelSize (0.06, "XY");
    gStyle->SetTitleSize (0.09, "t");





//    TLatex *L = new TLatex();
//    L->SetNDC (kTRUE);
//    L->SetTextSize (0.05);
//    L->SetTextColor (1);
//    L->SetTextAngle (0.);


    TH1F *hist1 = new TH1F("hist1", "", 516, 0, 3500);
    TH1F *hist2 = new TH1F("hist2", "", 516, 0, 3500);

    TH1F *hist3 = new TH1F("hist3", "", 516, 0, 3500);
    TH1F *hist4 = new TH1F("hist4", "", 516, 0, 3500);

    hist1->SetTitle("Widmo #gamma z detektorow LaBr_{3}");


    /*
    // checkout
    for (int i=0; i<t->GetEntries(); i++) {
      t->GetEntry (i);
      //cout<< energy<<"    " << pileup << endl;
      //hist1->Fill(energy);

    }
    */



    //t->Print();
    TCut cut_det0 ("id==0") ;
    TCut cut_det5 ("id==5") ;
    TCut cut_det1 ("id==1") ;
    TCut cut_det2 ("id==2") ;

    
    t->Project("hist1", "energy", cut_det0);
    t->Project("hist2", "energy", cut_det5);

    t->Project("hist3", "energy", cut_det1);
    t->Project("hist4", "energy", cut_det2);


    c1->Divide(1,2,0.01, 0.01);
    c1->cd(1);

    hist1->SetLineWidth(2);
    hist2->SetLineWidth(2);
    hist1->SetLineColor(kBlack);
    hist2->SetLineColor(kRed);

    hist1->GetXaxis()->SetTitle("E [keV]");
    hist1->GetXaxis()->SetTitleSize(0.05);
    hist1->GetXaxis()->SetLabelSize(0.055);

    hist1->Draw();
    hist2->Draw("same");




    TLegend *legend = new TLegend(0.15, 0.88,0.45,0.68);
    //legend->SetHeader(legend_text, "C");
    legend->SetTextSize(0.08);
    legend->AddEntry(hist1, "detektor 0, #phi = 0#circ", "l");
    legend->AddEntry(hist2, "detektor 5, #phi = 180#circ", "l");
    legend->Draw("same");



    c1->cd(2);


    hist3->GetXaxis()->SetTitle("E [keV]");
    hist3->GetXaxis()->SetTitleSize(0.05);
    hist3->GetXaxis()->SetLabelSize(0.055);


    hist3->SetLineWidth(2);
    hist4->SetLineWidth(2);

    hist3->SetLineColor(kOrange);
    hist3->Draw("same");
    hist4->SetLineColor(kBlue);
    hist4->Draw("same");


    TLegend *legend = new TLegend(0.15, 0.88,0.45,0.68);
    //legend->SetHeader(legend_text, "C");
    legend->SetTextSize(0.08);
    legend->AddEntry(hist3, "detektor 1, #phi = 36#circ", "l");
    legend->AddEntry(hist4, "detektor 2, #phi = 62#circ", "l");
    legend->Draw("same");



    c1->SaveAs("LaBr3_doppler_effect.png");


    return 0;
}