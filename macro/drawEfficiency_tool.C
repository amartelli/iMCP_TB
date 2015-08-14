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

void drawEfficiency_tool()
{

  std::vector<std::string> nameCh;
  nameCh.push_back("Plana4");
  nameCh.push_back("Plana3");
  nameCh.push_back("Plana2");
  nameCh.push_back("Plana1");


  std::string analysisType;
  analysisType = "eff";
  //  analysisType = "timeCFD";
  //  analysisType = "timeLED";


  std::string HVE;
  HVE = "ON_HVScan";
  //    HVE = "OFF_HVScan";
  //  HVE = "OFF_X0Scan";


  std::string XaxisLabel;
  if(HVE == "ON_HVScan" || HVE == "OFF_HVScan") XaxisLabel = "HV1";
  if(HVE == "OFF_X0Scan") XaxisLabel = "X0";


    int nCh = 4;
    TFile** inF = new TFile*[4];
    //    TMultiGraph *mg = new TMultiGraph();
    TGraphErrors** gr = new TGraphErrors*[4];
    TGraphErrors** gr_Sat = new TGraphErrors*[4];


    int markerStyleExt[4] = {4, 20, 5, 25};
    float markerSizeExt[4] = {1, 1, 1, 1};
    int lineWidthExt[4] = {2, 2, 2, 2};
    int colorsExt[4] = {kRed+2, kBlue+2, kGreen+2, kCyan};

    std::vector<int> markerStyle;
    std::vector<int> markerSize;
    std::vector<int> lineWidth;
    std::vector<int> colors;
    for(int posVec = 0; posVec<nCh; ++posVec){
      markerStyle.push_back(markerStyleExt[posVec]);
      markerSize.push_back(markerSizeExt[posVec]);
      lineWidth.push_back(lineWidthExt[posVec]);
      colors.push_back(colorsExt[posVec]);
    }

    //Plana1_HV1_Planacon_ON_HVScan.root
    //Plana1_X0_Planacon_OFF_X0Scan.root
    
    for(int iCh=0; iCh<nCh; ++iCh){
      //      for(int iCh=0; iCh<1; ++iCh){
      if(analysisType == "eff"){
	inF[iCh] = TFile::Open(("plots/efficiency_studies/"+nameCh.at(iCh)+"_"+XaxisLabel+"_Planacon_"+HVE+".root").c_str());
	gr[iCh] = (TGraphErrors*)inF[iCh]->Get("eff");
      }
      if(analysisType == "timeCFD"){
	inF[iCh] = TFile::Open(("plots/resCFD_studies/"+nameCh.at(iCh)+"_"+XaxisLabel+"_Planacon_"+HVE+".root").c_str());
	gr[iCh] = (TGraphErrors*)inF[iCh]->Get("resCFD");
      }
      if(analysisType == "timeLED"){
	inF[iCh] = TFile::Open(("plots/resLED_studies/"+nameCh.at(iCh)+"_"+XaxisLabel+"_Planacon_"+HVE+".root").c_str());
	gr[iCh] = (TGraphErrors*)inF[iCh]->Get("resLED");
      }
      gr_Sat[iCh] = (TGraphErrors*)inF[iCh]->Get("frac_saturated");
      std::cout << "name = " << inF[iCh]->GetName() << std::endl;



    //settings
    gr[iCh]->SetMarkerColor(colors.at(iCh));
    gr[iCh]->SetLineColor(colors.at(iCh));
    
    gr[iCh]->SetMarkerStyle(markerStyle.at(iCh));
    gr[iCh]->SetLineWidth(lineWidth.at(iCh));

    gr_Sat[iCh]->SetMarkerColor(colors.at(iCh));
    gr_Sat[iCh]->SetLineColor(colors.at(iCh));
    
    gr_Sat[iCh]->SetMarkerStyle(markerStyle.at(iCh));
    gr_Sat[iCh]->SetLineWidth(lineWidth.at(iCh));
  }


  TLegend *legC = new TLegend(0.50,0.20,0.79,0.4,NULL,"brNDC");
  legC->SetTextFont(42);
  legC->SetTextSize(0.03);
  legC->SetFillColor(kWhite);
  legC->SetLineColor(kWhite);
  legC->SetShadowColor(kWhite);
  for(int iCh=0; iCh<nCh; ++iCh){
    legC->AddEntry(gr[iCh], (nameCh.at(iCh)).c_str(), "p");
  }

  TCanvas* c_eff = new TCanvas();
  gPad->SetTicks();
  gr[0]->SetTitle( HVE.c_str());
  gr[0]->GetXaxis()->SetTitle(XaxisLabel.c_str());
  if(analysisType == "eff")
    gr[0]->GetYaxis()->SetTitle("Efficiency");
  if(analysisType == "timeCFD" || analysisType == "timeLED")
    gr[0]->GetYaxis()->SetTitle("time resolution");
  if(analysisType == "eff")
    gr[0]->GetYaxis()->SetRangeUser(0., 1.);
  if(analysisType == "timeCFD" || analysisType == "timeLED")
    gr[0]->GetYaxis()->SetRangeUser(0., 300.);
  gr[0]->Draw("apl");  
  for(int iCh=1; iCh<nCh; ++iCh){
    gr[iCh]->Draw("pl, same");
      }
  legC->Draw("same");

  if(analysisType == "eff")
    c_eff->Print(("plots/efficiency_studies/"+HVE+".png").c_str(), "png");
  if(analysisType == "timeCFD")
    c_eff->Print(("plots/resCFD_studies/"+HVE+".png").c_str(), "png");
  if(analysisType == "timeLED")
    c_eff->Print(("plots/resLED_studies/"+HVE+".png").c_str(), "png");


  ////////Saturation
  TCanvas* c_sat = new TCanvas();
  gPad->SetTicks();
  gr_Sat[0]->SetTitle( HVE.c_str());
  gr_Sat[0]->GetXaxis()->SetTitle(XaxisLabel.c_str());
  if(analysisType == "eff")
    gr_Sat[0]->GetYaxis()->SetTitle("Efficiency");
  if(analysisType == "timeCFD" || analysisType == "timeLED")
    gr_Sat[0]->GetYaxis()->SetTitle("time resolution");
  if(analysisType == "eff")
    gr_Sat[0]->GetYaxis()->SetRangeUser(0., 1.);
  if(analysisType == "timeCFD" || analysisType == "timeLED")
    gr_Sat[0]->GetYaxis()->SetRangeUser(0., 300.);
  gr_Sat[0]->Draw("apl");  
  for(int iCh=1; iCh<nCh; ++iCh){
    gr_Sat[iCh]->Draw("pl, same");
      }
  legC->Draw("same");

  if(analysisType == "eff")
    c_sat->Print(("plots/efficiency_studies/SatFrac_"+HVE+".png").c_str(), "png");
  if(analysisType == "timeCFD")
    c_sat->Print(("plots/resCFD_studies/SatFrac_"+HVE+".png").c_str(), "png");
  if(analysisType == "timeLED")
    c_sat->Print(("plots/resLED_studies/SatFrac_"+HVE+".png").c_str(), "png");

}
