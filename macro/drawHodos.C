#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TPaveStats.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TTree.h"
#include "TChain.h"
#include "TVirtualFitter.h"
#include "TMath.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <map>
#include <algorithm>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <vector>

void drawHodos(){

  gStyle->SetOptStat(0);

  //

  /*
  TH2F* h1_Plana1_hodo2 = new TH2F("h1_Plana1_hodo2", "", 30, -15, 15, 30, -15, 15);
  TH2F* h1_Plana1_hodo1 = new TH2F("h1_Plana1_hodo1", "", 30, -15, 15, 30, -15, 15);

  TH2F* h1_Plana2_hodo2 = new TH2F("h1_Plana2_hodo2", "", 30, -15, 15, 30, -15, 15);
  TH2F* h1_Plana2_hodo1 = new TH2F("h1_Plana2_hodo1", "", 30, -15, 15, 30, -15, 15);

  TH2F* h1_Plana3_hodo2 = new TH2F("h1_Plana3_hodo2", "", 30, -15, 15, 30, -15, 15);
  TH2F* h1_Plana3_hodo1 = new TH2F("h1_Plana3_hodo1", "", 30, -15, 15, 30, -15, 15);

  TH2F* h1_Plana4_hodo2 = new TH2F("h1_Plana4_hodo2", "", 30, -15, 15, 30, -15, 15);
  TH2F* h1_Plana4_hodo1 = new TH2F("h1_Plana4_hodo1", "", 30, -15, 15, 30, -15, 15);

  //
  TH2F* h2_Plana1_hodo2 = new TH2F("h2_Plana1_hodo2", "", 30, -15, 15, 30, -15, 15);
  TH2F* h2_Plana1_hodo1 = new TH2F("h2_Plana1_hodo1", "", 30, -15, 15, 30, -15, 15);

  TH2F* h2_Plana2_hodo2 = new TH2F("h2_Plana2_hodo2", "", 30, -15, 15, 30, -15, 15);
  TH2F* h2_Plana2_hodo1 = new TH2F("h2_Plana2_hodo1", "", 30, -15, 15, 30, -15, 15);

  TH2F* h2_Plana3_hodo2 = new TH2F("h2_Plana3_hodo2", "", 30, -15, 15, 30, -15, 15);
  TH2F* h2_Plana3_hodo1 = new TH2F("h2_Plana3_hodo1", "", 30, -15, 15, 30, -15, 15);

  TH2F* h2_Plana4_hodo2 = new TH2F("h2_Plana4_hodo2", "", 30, -15, 15, 30, -15, 15);
  TH2F* h2_Plana4_hodo1 = new TH2F("h2_Plana4_hodo1", "", 30, -15, 15, 30, -15, 15);
  */
  TCanvas* c1 = new TCanvas();
  c1->cd();
  

  
    
  TFile* f2 = TFile::Open("ntuples/reco_Planacon_OFF_HVScan.root");
  TTree* ntu2 = (TTree*)f2->Get("reco_tree");
  ntu2->Draw("pos_hodoY2:pos_hodoX2 >> h2_Plana1_hodo2", "charge[0] > 138 && charge[1] > 155");
  h2_Plana1_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h2_Plana1_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h2_Plana1_hodo2->GetZaxis()->SetRangeUser(0., 300.);
  h2_Plana1_hodo2->Draw("colz");
  c1->Print("macro/plots/h2_OFF_HVS_Plana1_hodo2.png", ".png");
  ntu2->Draw("pos_hodoY1:pos_hodoX1 >> h2_Plana1_hodo1", "charge[0] > 138 && charge[1] > 155");
  h2_Plana1_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h2_Plana1_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h2_Plana1_hodo1->GetZaxis()->SetRangeUser(0., 300.);
  h2_Plana1_hodo1->Draw("colz");
  c1->Print("macro/plots/h2_OFF_HVS_Plana1_hodo1.png", ".png");


  ntu2->Draw("pos_hodoY2:pos_hodoX2 >> h2_Plana2_hodo2", "charge[0] > 138 && charge[2] > 151");
  h2_Plana2_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h2_Plana2_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h2_Plana2_hodo2->GetZaxis()->SetRangeUser(0., 300.);
  h2_Plana2_hodo2->Draw("colz");
  c1->Print("macro/plots/h2_OFF_HVS_Plana2_hodo2.png", ".png");
  ntu2->Draw("pos_hodoY1:pos_hodoX1 >> h2_Plana2_hodo1", "charge[0] > 138 && charge[2] > 151");
  h2_Plana2_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h2_Plana2_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h2_Plana2_hodo1->GetZaxis()->SetRangeUser(0., 300.);
  h2_Plana2_hodo1->Draw("colz");
  c1->Print("macro/plots/h2_OFF_HVS_Plana2_hodo1.png", ".png");


  ntu2->Draw("pos_hodoY2:pos_hodoX2 >> h2_Plana3_hodo2", "charge[0] > 138 && charge[3] > 159");
  h2_Plana3_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h2_Plana3_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h2_Plana3_hodo2->GetZaxis()->SetRangeUser(0., 300.);
  h2_Plana3_hodo2->Draw("colz");
  c1->Print("macro/plots/h2_OFF_HVS_Plana3_hodo2.png", ".png");
  ntu2->Draw("pos_hodoY1:pos_hodoX1 >> h2_Plana3_hodo1", "charge[0] > 138 && charge[3] > 159");
  h2_Plana3_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h2_Plana3_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h2_Plana3_hodo1->GetZaxis()->SetRangeUser(0., 300.);
  h2_Plana3_hodo1->Draw("colz");
  c1->Print("macro/plots/h2_OFF_HVS_Plana3_hodo1.png", ".png");


  ntu2->Draw("pos_hodoY2:pos_hodoX2 >> h2_Plana4_hodo2", "charge[0] > 138 && charge[4] > 164");
  h2_Plana4_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h2_Plana4_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h2_Plana4_hodo2->GetZaxis()->SetRangeUser(0., 300.);
  h2_Plana4_hodo2->Draw("colz");
  c1->Print("macro/plots/h2_OFF_HVS_Plana4_hodo2.png", ".png");
  ntu2->Draw("pos_hodoY1:pos_hodoX1 >> h2_Plana4_hodo1", "charge[0] > 138 && charge[4] > 164");
  h2_Plana4_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h2_Plana4_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h2_Plana4_hodo1->GetZaxis()->SetRangeUser(0., 300.);
  h2_Plana4_hodo1->Draw("colz");
  c1->Print("macro/plots/h2_OFF_HVS_Plana4_hodo1.png", ".png");
  

  TFile* f3 = TFile::Open("ntuples/reco_Planacon_OFF_X0Scan.root");
  TTree* ntu3 = (TTree*)f3->Get("reco_tree");
  ntu3->Draw("pos_hodoY2:pos_hodoX2 >> h3_Plana1_hodo2", "charge[0] > 138 && charge[1] > 155");
  h3_Plana1_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h3_Plana1_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h3_Plana1_hodo2->GetZaxis()->SetRangeUser(0., 1000.);
  h3_Plana1_hodo2->Draw("colz");
  c1->Print("macro/plots/h3_OFF_X0S_Plana1_hodo2.png", ".png");
  ntu3->Draw("pos_hodoY1:pos_hodoX1 >> h3_Plana1_hodo1", "charge[0] > 138 && charge[1] > 155");
  h3_Plana1_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h3_Plana1_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h3_Plana1_hodo1->GetZaxis()->SetRangeUser(0., 1000.);
  h3_Plana1_hodo1->Draw("colz");
  c1->Print("macro/plots/h3_OFF_X0S_Plana1_hodo1.png", ".png");


  ntu3->Draw("pos_hodoY2:pos_hodoX2 >> h3_Plana2_hodo2", "charge[0] > 138 && charge[2] > 151");
  h3_Plana2_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h3_Plana2_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h3_Plana2_hodo2->GetZaxis()->SetRangeUser(0., 1000.);
  h3_Plana2_hodo2->Draw("colz");
  c1->Print("macro/plots/h3_OFF_X0S_Plana2_hodo2.png", ".png");
  ntu3->Draw("pos_hodoY1:pos_hodoX1 >> h3_Plana2_hodo1", "charge[0] > 138 && charge[2] > 151");
  h3_Plana2_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h3_Plana2_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h3_Plana1_hodo1->GetZaxis()->SetRangeUser(0., 1000.);
  h3_Plana2_hodo1->Draw("colz");
  c1->Print("macro/plots/h3_OFF_X0S_Plana2_hodo1.png", ".png");


  ntu3->Draw("pos_hodoY2:pos_hodoX2 >> h3_Plana3_hodo2", "charge[0] > 138 && charge[3] > 159");
  h3_Plana3_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h3_Plana3_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h3_Plana3_hodo2->GetZaxis()->SetRangeUser(0., 1000.);
  h3_Plana3_hodo2->Draw("colz");
  c1->Print("macro/plots/h3_OFF_X0S_Plana3_hodo2.png", ".png");
  ntu3->Draw("pos_hodoY1:pos_hodoX1 >> h3_Plana3_hodo1", "charge[0] > 138 && charge[3] > 159");
  h3_Plana3_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h3_Plana3_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h3_Plana3_hodo1->GetZaxis()->SetRangeUser(0., 1000.);
  h3_Plana3_hodo1->Draw("colz");
  c1->Print("macro/plots/h3_OFF_X0S_Plana3_hodo1.png", ".png");


  ntu3->Draw("pos_hodoY2:pos_hodoX2 >> h3_Plana4_hodo2", "charge[0] > 138 && charge[4] > 164");
  h3_Plana4_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h3_Plana4_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h3_Plana4_hodo2->GetZaxis()->SetRangeUser(0., 1000.);
  h3_Plana4_hodo2->Draw("colz");
  c1->Print("macro/plots/h3_OFF_X0S_Plana4_hodo2.png", ".png");
  ntu3->Draw("pos_hodoY1:pos_hodoX1 >> h3_Plana4_hodo1", "charge[0] > 138 && charge[4] > 164");
  h3_Plana4_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h3_Plana4_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h3_Plana4_hodo1->GetZaxis()->SetRangeUser(0., 1000.);
  h3_Plana4_hodo1->Draw("colz");
  c1->Print("macro/plots/h3_OFF_X0S_Plana4_hodo1.png", ".png");



  // HV ON 
  TFile* f1 = TFile::Open("ntuples/reco_Planacon_ON_HVScan.root");
  TTree* ntu = (TTree*)f1->Get("reco_tree");

  ntu->Draw("pos_hodoY2:pos_hodoX2 >> h1_Plana1_hodo2", "charge[0] > 138 && charge[1] > 155");
  h1_Plana1_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h1_Plana1_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h1_Plana1_hodo2->GetZaxis()->SetRangeUser(0., 3000.);
  h1_Plana1_hodo2->Draw("colz");
  c1->Print("macro/plots/h1_ON_HVS_Plana1_hodo2.png", ".png");
  ntu->Draw("pos_hodoY1:pos_hodoX1 >> h1_Plana1_hodo1", "charge[0] > 138 && charge[1] > 155");
  h1_Plana1_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h1_Plana1_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h1_Plana1_hodo1->GetZaxis()->SetRangeUser(0., 3000.);
  h1_Plana1_hodo1->Draw("colz");
  c1->Print("macro/plots/h1_ON_HVS_Plana1_hodo1.png", ".png");

  ntu->Draw("pos_hodoY2:pos_hodoX2 >> h1_Plana2_hodo2", "charge[0] > 138 && charge[2] > 151");
  h1_Plana2_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h1_Plana2_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h1_Plana2_hodo2->GetZaxis()->SetRangeUser(0., 3000.);
  h1_Plana2_hodo2->Draw("colz");
  c1->Print("macro/plots/h1_ON_HVS_Plana2_hodo2.png", ".png");
  ntu->Draw("pos_hodoY1:pos_hodoX1 >> h1_Plana2_hodo1", "charge[0] > 138 && charge[2] > 151");
  h1_Plana2_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h1_Plana2_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h1_Plana2_hodo1->GetZaxis()->SetRangeUser(0., 3000.);
  h1_Plana2_hodo1->Draw("colz");
  c1->Print("macro/plots/h1_ON_HVS_Plana2_hodo1.png", ".png");

  ntu->Draw("pos_hodoY2:pos_hodoX2 >> h1_Plana3_hodo2", "charge[0] > 138 && charge[3] > 159");
  h1_Plana3_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h1_Plana3_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h1_Plana3_hodo2->GetZaxis()->SetRangeUser(0., 3000.);
  h1_Plana3_hodo2->Draw("colz");
  c1->Print("macro/plots/h1_ON_HVS_Plana3_hodo2.png", ".png");
  ntu->Draw("pos_hodoY1:pos_hodoX1 >> h1_Plana3_hodo1", "charge[0] > 138 && charge[3] > 159");
  h1_Plana3_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h1_Plana3_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h1_Plana3_hodo1->GetZaxis()->SetRangeUser(0., 3000.);
  h1_Plana3_hodo1->Draw("colz");
  c1->Print("macro/plots/h1_ON_HVS_Plana3_hodo1.png", ".png");

  ntu->Draw("pos_hodoY2:pos_hodoX2 >> h1_Plana4_hodo2", "charge[0] > 138 && charge[4] > 164");
  h1_Plana4_hodo2->GetXaxis()->SetRangeUser(-10, 10);
  h1_Plana4_hodo2->GetYaxis()->SetRangeUser(-10, 10);
  h1_Plana4_hodo2->GetZaxis()->SetRangeUser(0., 3000.);
  h1_Plana4_hodo2->Draw("colz");
  c1->Print("macro/plots/h1_ON_HVS_Plana4_hodo2.png", ".png");
  ntu->Draw("pos_hodoY1:pos_hodoX1 >> h1_Plana4_hodo1", "charge[0] > 138 && charge[4] > 164");
  h1_Plana4_hodo1->GetXaxis()->SetRangeUser(-10, 10);
  h1_Plana4_hodo1->GetYaxis()->SetRangeUser(-10, 10);
  h1_Plana4_hodo1->GetZaxis()->SetRangeUser(0., 3000.);
  h1_Plana4_hodo1->Draw("colz");
  c1->Print("macro/plots/h1_ON_HVS_Plana4_hodo1.png", ".png");



}
