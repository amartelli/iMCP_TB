/*******************************************************************************
THIS PROGRAM READ THE RAW DATA AND PRODUCE THE RECO FILE USED FOR THE ANALYSIS
-

BE CAREFUL: the number of channels MUST coincide with the number of channel in the cfg file

*******************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream> 
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <iomanip>
#include <ctime>
#include <map>
#include <math.h>

#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TChain.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TMath.h"
#include "TString.h"
#include "TClass.h"
#include "TApplication.h"

#include "../interface/analysis_tools.h"
#include "../interface/init_tree_H4.h"
#include "../interface/init_Reco_Tree.h"
#include "../interface/MCPMap.h"
#include "../interface/CfgManager.h"
#include "../interface/TagHelper.h"
#include "../interface/HodoCluster.h"
#include "../interface/AlignmentOfficer.h"

using namespace std;

// 2015 hodo mapping
map<int, int> ADC_to_PMT_map;
map<int, int> PMT_to_hodoX_map;
map<int, int> PMT_to_hodoY_map;


#define wcXl 0
#define wcXr 1
#define wcYd 3
#define wcYu 2

#define nFibersHodo 64
//#define nBGOChannels 8
//#define nSCINTChannels 0
#define nHODOSMALLChannels 8
//#define emptyChannelIndex 4


#define HODOX1_CHANNELS 64
#define HODOY1_CHANNELS 64
#define HODOX2_CHANNELS 64
#define HODOY2_CHANNELS 64

#define HODOSMALLX_CHANNELS 4
#define HODOSMALLY_CHANNELS 4

void assignValues( std::vector<float> &target, std::vector<float> source, unsigned int startPos );
void assignValuesBool( std::vector<bool> &target, std::vector<bool> source, unsigned int startPos );
//void computeCherenkov(std::vector<float> &cher,std::vector<float> wls);
void doHodoReconstructionBool( std::vector<bool> values, int &nClusters, int *nFibres, float *pos, float fibreWidth, int clusterMaxFibres, float Cut );
std::vector<HodoCluster*> getHodoClustersBool( std::vector<bool> hodo, float fibreWidth, int nClusterMax, float Cut );

void doHodoReconstruction( std::vector<float> values, int &nClusters, int *nFibres, float *pos, float fibreWidth, int clusterMaxFibres, float Cut );
std::vector<HodoCluster*> getHodoClusters( std::vector<float> hodo, float fibreWidth, int nClusterMax, float Cut );
std::vector<HodoCluster*> getHodoClustersMultipleCuts( std::vector<float> hodo, float fibreWidth, int nClusterMax, std::vector<float> Cut );
void copyArray( int n, float *source, float *target );
void doHodoReconstructionMultipleCuts( std::vector<float> values, int &nClusters, int *nFibres, float *pos, float fibreWidth, int clusterMaxFibres, std::vector<float> Cut );
//float timeSampleUnit(int drs4Freq);



void FillMaps()
{  
    // PMT In - PNT Out  [both 0->63]
    ADC_to_PMT_map.insert(pair<int,int>(0,35));
    ADC_to_PMT_map.insert(pair<int,int>(1,41));
    ADC_to_PMT_map.insert(pair<int,int>(2,48));
    ADC_to_PMT_map.insert(pair<int,int>(3,56));
    ADC_to_PMT_map.insert(pair<int,int>(4,57));
    ADC_to_PMT_map.insert(pair<int,int>(5,49));
    ADC_to_PMT_map.insert(pair<int,int>(6,58));
    ADC_to_PMT_map.insert(pair<int,int>(7,50));
    ADC_to_PMT_map.insert(pair<int,int>(8,32));
    ADC_to_PMT_map.insert(pair<int,int>(9,59));
    ADC_to_PMT_map.insert(pair<int,int>(10,33));
    ADC_to_PMT_map.insert(pair<int,int>(11,51));
    ADC_to_PMT_map.insert(pair<int,int>(12,40));
    ADC_to_PMT_map.insert(pair<int,int>(13,60));
    ADC_to_PMT_map.insert(pair<int,int>(14,34));
    ADC_to_PMT_map.insert(pair<int,int>(15,52));
    ADC_to_PMT_map.insert(pair<int,int>(16,42));
    ADC_to_PMT_map.insert(pair<int,int>(17,61));
    ADC_to_PMT_map.insert(pair<int,int>(18,43));
    ADC_to_PMT_map.insert(pair<int,int>(19,53));
    ADC_to_PMT_map.insert(pair<int,int>(20,62));
    ADC_to_PMT_map.insert(pair<int,int>(21,44));
    ADC_to_PMT_map.insert(pair<int,int>(22,63));
    ADC_to_PMT_map.insert(pair<int,int>(23,54));
    ADC_to_PMT_map.insert(pair<int,int>(24,36));
    ADC_to_PMT_map.insert(pair<int,int>(25,55));
    ADC_to_PMT_map.insert(pair<int,int>(26,46));
    ADC_to_PMT_map.insert(pair<int,int>(27,45));
    ADC_to_PMT_map.insert(pair<int,int>(28,47));
    ADC_to_PMT_map.insert(pair<int,int>(29,38));
    ADC_to_PMT_map.insert(pair<int,int>(30,37));
    ADC_to_PMT_map.insert(pair<int,int>(31,39));
    ADC_to_PMT_map.insert(pair<int,int>(32,29));
    ADC_to_PMT_map.insert(pair<int,int>(33,31));
    ADC_to_PMT_map.insert(pair<int,int>(34,21));
    ADC_to_PMT_map.insert(pair<int,int>(35,30));
    ADC_to_PMT_map.insert(pair<int,int>(36,23));
    ADC_to_PMT_map.insert(pair<int,int>(37,28));
    ADC_to_PMT_map.insert(pair<int,int>(38,22));
    ADC_to_PMT_map.insert(pair<int,int>(39,15));
    ADC_to_PMT_map.insert(pair<int,int>(40,20));
    ADC_to_PMT_map.insert(pair<int,int>(41,14));
    ADC_to_PMT_map.insert(pair<int,int>(42,7));
    ADC_to_PMT_map.insert(pair<int,int>(43,27));
    ADC_to_PMT_map.insert(pair<int,int>(44,6));
    ADC_to_PMT_map.insert(pair<int,int>(45,13));
    ADC_to_PMT_map.insert(pair<int,int>(46,3));
    ADC_to_PMT_map.insert(pair<int,int>(47,5));
    ADC_to_PMT_map.insert(pair<int,int>(48,12));
    ADC_to_PMT_map.insert(pair<int,int>(49,4));
    ADC_to_PMT_map.insert(pair<int,int>(50,11));
    ADC_to_PMT_map.insert(pair<int,int>(51,19));
    ADC_to_PMT_map.insert(pair<int,int>(52,10));
    ADC_to_PMT_map.insert(pair<int,int>(53,18));
    ADC_to_PMT_map.insert(pair<int,int>(54,2));
    ADC_to_PMT_map.insert(pair<int,int>(55,17));
    ADC_to_PMT_map.insert(pair<int,int>(56,9));
    ADC_to_PMT_map.insert(pair<int,int>(57,16));
    ADC_to_PMT_map.insert(pair<int,int>(58,1));
    ADC_to_PMT_map.insert(pair<int,int>(59,0));
    ADC_to_PMT_map.insert(pair<int,int>(60,25));
    ADC_to_PMT_map.insert(pair<int,int>(61,8));
    ADC_to_PMT_map.insert(pair<int,int>(62,26));
    ADC_to_PMT_map.insert(pair<int,int>(63,24));

    // PMT Out - Hodo X  [both 0->63]
    PMT_to_hodoX_map.insert(pair<int,int>(0,28));
    PMT_to_hodoX_map.insert(pair<int,int>(1,17));
    PMT_to_hodoX_map.insert(pair<int,int>(2,16));
    PMT_to_hodoX_map.insert(pair<int,int>(3,15));
    PMT_to_hodoX_map.insert(pair<int,int>(4,14));
    PMT_to_hodoX_map.insert(pair<int,int>(5,13));
    PMT_to_hodoX_map.insert(pair<int,int>(6,12));
    PMT_to_hodoX_map.insert(pair<int,int>(7,0));
    PMT_to_hodoX_map.insert(pair<int,int>(8,29));
    PMT_to_hodoX_map.insert(pair<int,int>(9,18));
    PMT_to_hodoX_map.insert(pair<int,int>(10,19));
    PMT_to_hodoX_map.insert(pair<int,int>(11,20));
    PMT_to_hodoX_map.insert(pair<int,int>(12,9));
    PMT_to_hodoX_map.insert(pair<int,int>(13,10));
    PMT_to_hodoX_map.insert(pair<int,int>(14,11));
    PMT_to_hodoX_map.insert(pair<int,int>(15,1));
    PMT_to_hodoX_map.insert(pair<int,int>(16,30));
    PMT_to_hodoX_map.insert(pair<int,int>(17,23));
    PMT_to_hodoX_map.insert(pair<int,int>(18,22));
    PMT_to_hodoX_map.insert(pair<int,int>(19,21));
    PMT_to_hodoX_map.insert(pair<int,int>(20,8));
    PMT_to_hodoX_map.insert(pair<int,int>(21,7));
    PMT_to_hodoX_map.insert(pair<int,int>(22,6));
    PMT_to_hodoX_map.insert(pair<int,int>(23,2));
    PMT_to_hodoX_map.insert(pair<int,int>(24,31));
    PMT_to_hodoX_map.insert(pair<int,int>(25,24));
    PMT_to_hodoX_map.insert(pair<int,int>(26,25));
    PMT_to_hodoX_map.insert(pair<int,int>(27,26));
    PMT_to_hodoX_map.insert(pair<int,int>(28,27));
    PMT_to_hodoX_map.insert(pair<int,int>(29,5));
    PMT_to_hodoX_map.insert(pair<int,int>(30,4));
    PMT_to_hodoX_map.insert(pair<int,int>(31,3));

    // PMT Out - Hodo Y  [both 0->63]
    PMT_to_hodoY_map.insert(pair<int,int>(32,3));
    PMT_to_hodoY_map.insert(pair<int,int>(33,4));
    PMT_to_hodoY_map.insert(pair<int,int>(34,5));
    PMT_to_hodoY_map.insert(pair<int,int>(35,27));
    PMT_to_hodoY_map.insert(pair<int,int>(36,26));
    PMT_to_hodoY_map.insert(pair<int,int>(37,25));
    PMT_to_hodoY_map.insert(pair<int,int>(38,24));
    PMT_to_hodoY_map.insert(pair<int,int>(39,31));
    PMT_to_hodoY_map.insert(pair<int,int>(40,2));
    PMT_to_hodoY_map.insert(pair<int,int>(41,6));
    PMT_to_hodoY_map.insert(pair<int,int>(42,7));
    PMT_to_hodoY_map.insert(pair<int,int>(43,8));
    PMT_to_hodoY_map.insert(pair<int,int>(44,21));
    PMT_to_hodoY_map.insert(pair<int,int>(45,22));
    PMT_to_hodoY_map.insert(pair<int,int>(46,23));
    PMT_to_hodoY_map.insert(pair<int,int>(47,30));
    PMT_to_hodoY_map.insert(pair<int,int>(48,1));
    PMT_to_hodoY_map.insert(pair<int,int>(49,11));
    PMT_to_hodoY_map.insert(pair<int,int>(50,10));
    PMT_to_hodoY_map.insert(pair<int,int>(51,9));
    PMT_to_hodoY_map.insert(pair<int,int>(52,20));
    PMT_to_hodoY_map.insert(pair<int,int>(53,19));
    PMT_to_hodoY_map.insert(pair<int,int>(54,18));
    PMT_to_hodoY_map.insert(pair<int,int>(55,29));
    PMT_to_hodoY_map.insert(pair<int,int>(56,0));
    PMT_to_hodoY_map.insert(pair<int,int>(57,12));
    PMT_to_hodoY_map.insert(pair<int,int>(58,13));
    PMT_to_hodoY_map.insert(pair<int,int>(59,14));
    PMT_to_hodoY_map.insert(pair<int,int>(60,15));
    PMT_to_hodoY_map.insert(pair<int,int>(61,16));
    PMT_to_hodoY_map.insert(pair<int,int>(62,17));
    PMT_to_hodoY_map.insert(pair<int,int>(63,28));
}

//*******MAIN*******************************************************************
int main (int argc, char** argv)
{  
    cout<<"--------DUMPER: READ RAW DATA AND PRODUCE RECO TREE--------"<<endl;

    //-----this map tells how the MCPs will be order in the output tree. The names should match the cfg file----
    Fill_MCPList();   //look into the MCPMap.h class
    FillMaps();
  
    //--------Read Options--------------------------------
    CfgManager CFG(argv[1]);
    cout << CFG << endl;

    string inputFolder = CFG.GetOpt<string>("global", "inputDir");
    string outputFile = CFG.GetOpt<string>("global", "outputFile");
    string runType = CFG.GetOpt<string>("global", "runType");
    int nRuns = CFG.GetOpt<int>("global", "nRuns");
    int nCh = CFG.GetOpt<int>("global", "nChannels");
    int trigPos = CFG.GetOpt<int>("global", "trigPos");
    //    int trigPos2 = CFG.GetOpt<int>("global", "trigPos2");
    int trigPos2 = -1;



    std::string tag = "V00";
    std::string theBeamEnergy = Form("%.0f",50);

    //---------output tree----------------
    TFile* outROOT = TFile::Open(outputFile.c_str(), "recreate");  
    outROOT->cd();

    TProfile** wf_promed = new TProfile*[18];
    for(int iCh=0; iCh<18; ++iCh) 
        wf_promed[iCh] = new TProfile(Form("wf_promed_%d",iCh), "", 102400, 0., 1024.);

    TTree* outTree = new TTree("reco_tree", "reco_tree");
    outTree->SetDirectory(0);
    std::cout << " >>> SetOutTree HERE!!!!!!!!!!!!!! " << std::endl;
    SetOutTree(outTree);
    std::cout << " >>> SetOutTree done " << std::endl;

    int iRun=0;
    int start=0;
    //-------runs loop    
    while(iRun < nRuns) 
    {
        int run = CFG.GetOpt<int>("global", "runs", iRun);

        //-----Definitions
        vector<float> digiCh[18]; 
        vector<float> digiCh_dummy[18];
        float timeCF[18], timeCFcorr[18], timeCF30[18];
        float timeOT[18], timeStart[18], timeStop[18], ampMaxT[18];
        float timeStart_1000[18], timeStop_1000[18], timeStart_150[18], timeStop_150[18];
        float timeStart_200[18], timeStop_200[18], timeStart_500[18], timeStop_500[18], timeStart_300[18], timeStop_300[18];
        float intBase[18], intSignal[18], intSignalcorr[18], ampMax[18], ampMaxcorr[18];
        ///int fibreX[8], hodoYchannels[8];
        float tStart, tStop;

        //--reading wire chamber from other tree --
	//         TChain* positionTree = new TChain("outputTree");
	//         InitTree2(positionTree);

        //---Chain
        TChain* chain = new TChain("H4tree");
        InitTree(chain);

        // char command1[300];
        // sprintf(command1, "find  %s/%d/*/dqmPlotstotal.root > ntuples/listTemp_%d.txt", (inputFolder).c_str(), run, run);
        // system(command1);
        char command2[300];
	//        sprintf(command2, "find  %s/%d.root > ntuples/listTemp2_%d.txt", (inputFolder).c_str(), run, run);
        sprintf(command2, "find  %s/%d/*.root > ntuples/listTemp2_%d.txt", (inputFolder).c_str(), run, run);
        system(command2);

        // char list1[200];
        char list2[200];
        // sprintf (list1, "ntuples/listTemp_%d.txt", run);
        sprintf (list2, "ntuples/listTemp2_%d.txt", run);

        // ifstream rootList (list1);
        ifstream rootList2 (list2);

        // while (!rootList.eof() && !rootList2.eof())
	// {
        //     char iRun_tW[70];
        //     rootList >> iRun_tW;
        //     char iRun_str[70];
        //     rootList2 >> iRun_str;

        //     TChain* tTemp = new TChain("outputTree");
        //     tTemp->Add(iRun_tW);
        //     TChain* tTempH4 = new TChain("H4tree");
        //     tTempH4->Add(iRun_str);
	  
        //     if (tTemp->GetEntries() == tTempH4->GetEntries())
	//     {
        //         positionTree->Add(iRun_tW);	
        //         chain->Add(iRun_str);	
	//     }
        //     else
        //         cout<<"Bad spill found.. Skipped"<<endl;
        //     tTemp->Delete();
        //     tTempH4->Delete();
	// }

        while(!rootList2.eof())
	{
            char iRun_str[70];
            rootList2 >> iRun_str;
            
            chain->Add(iRun_str);	
	}

        // char command3[300];
        // sprintf(command3, "rm ntuples/listTemp_%d.txt", run);
        char command4[300];
        sprintf(command4, "rm ntuples/listTemp2_%d.txt", run);
      
        // system(command3);
        system(command4);
      

	TagHelper tagHelper(tag,theBeamEnergy);
	AlignmentOfficer alignOfficer(tagHelper.getAlignmentFileName());


        cout << "start reading run: " << run << endl;

        //-----Data loop--------------------------------------------------------
        for(int iEntry=0; iEntry<chain->GetEntries(); iEntry++)
        {
	    if(iEntry % 1000 == 0)
		cout << "read entry: " << iEntry << " / " << chain->GetEntriesFast() << endl;
            //-----Unpack data--------------------------------------------------
            for(int iCh=0; iCh<18; iCh++)
            {
                digiCh[iCh].clear();
                digiCh_dummy[iCh].clear();

            }
            //---Read the entry
            chain->GetEntry(iEntry);

	    unsigned int spill=spillNumber;
	    event=evtNumber;

	    if (spill!=spillNumber || event!=evtNumber) {
                cout<<"PROBLEM: non-coherent read"<<endl;
                continue;
	    }

	    //             hodoXpos = -1;
	    //             hodoYpos = -1;
	    
	    // 	    for(unsigned int iCh=0; iCh<nTdcChannels; iCh++)
	    // 	      {
	    // 		  tdc_front = tdcData[iCh];
	    // 	      }
	    

	    //fill HODOSMALLvalues
 	    //std::cout << " fill HODOSMALLvalues " << std::endl;
	    std::vector<float>  HODOSMALLvalues;
	    HODOSMALLvalues.clear();
 	    HODOSMALLvalues.resize(nHODOSMALLChannels, 0);
	    for(unsigned int iAdc=0; iAdc<nAdcChannels; ++iAdc){
	      //std::cout << "debug: ch " << iAdc << std::endl;
	      //small hodo for 2015 read out with adc board
	      if(adcBoard[iAdc] == 0x6010001){ 
		unsigned int ch = adcChannel[iAdc];
		if(ch < 2 || ch > 13) continue;
		if(ch < 6){ //2,3,4,5 are on y; 10,11,12,13 on x
		  HODOSMALLvalues.at(ch-2) = adcData[iAdc];
		}
		else if(ch > 9){
		  HODOSMALLvalues.at(ch-6) = adcData[iAdc];
		}
	      }
	    }
	    

	    //fillTDC
	    //std::cout << " fill TDC " << std::endl;
	    std::vector<float>   TDCreco;
 	    TDCreco.clear();
 	    TDCreco.resize(2,-999);
	    
	    std::vector<unsigned int> tdc_readings[4];
	    float tdc_recox = -999;
	    float tdc_recoy = -999;
	    
	    for(unsigned int iTdc = 0; iTdc<nTdcChannels; ++iTdc){
	      if(tdcBoard[iTdc] == 0x07020001 && tdcChannel[iTdc] < 4){
		  tdc_readings[tdcChannel[iTdc]].push_back((float)tdcData[iTdc]);
		}
	    }
	    if (tdc_readings[wcXl].size() != 0 && tdc_readings[wcXr].size() != 0){
	      float TXl = *std::min_element(tdc_readings[wcXl].begin(),tdc_readings[wcXl].begin()+tdc_readings[wcXl].size());
	      float TXr = *std::min_element(tdc_readings[wcXr].begin(),tdc_readings[wcXr].begin()+tdc_readings[wcXr].size());
	      float X = (TXr-TXl)*0.005; // = /40./5./10. //position in cm 0.2mm/ns with 25ps LSB TDC
	      tdc_recox = X;
	    }
	    if (tdc_readings[wcYd].size() != 0 && tdc_readings[wcYu].size() != 0){
	      float TYd = *std::min_element(tdc_readings[wcYd].begin(),tdc_readings[wcYd].begin()+tdc_readings[wcYd].size());
	      float TYu = *std::min_element(tdc_readings[wcYu].begin(),tdc_readings[wcYu].begin()+tdc_readings[wcYu].size());
	      float Y = (TYu-TYd)*0.005; // = /40./5./10. //position in cm 0.2mm/ns with 25ps LSB TDC
	      tdc_recoy = Y;
	    }
	    
	    nTDCHits[0] = tdc_readings[wcXl].size();
	    nTDCHits[1] = tdc_readings[wcXr].size();
	    nTDCHits[2] = tdc_readings[wcYd].size();
	    nTDCHits[3] = tdc_readings[wcYu].size();
	    
	    if(tdc_recox >- 999 && tdc_recoy >- 999){
	      TDCreco[0] = tdc_recox;
	      TDCreco[1] = tdc_recoy;
	    }


	    //fillFiber 
	    //std::cout << " fill fibers " << std::endl;
	    std::vector<int> fiberOrderA;
	    std::vector<int> fiberOrderB;

	    fiberOrderA.clear();
	    fiberOrderB.clear();

	    fiberOrderA.push_back(31);
	    fiberOrderA.push_back(29);
	    fiberOrderA.push_back(23);
	    fiberOrderA.push_back(21);
	    fiberOrderA.push_back(5);
	    fiberOrderA.push_back(7);
	    fiberOrderA.push_back(15);
	    fiberOrderA.push_back(13);
	    fiberOrderA.push_back(1);
	    fiberOrderA.push_back(3);
	    fiberOrderA.push_back(11);
	    fiberOrderA.push_back(9);
	    fiberOrderA.push_back(6);
	    fiberOrderA.push_back(8);
	    fiberOrderA.push_back(16);
	    fiberOrderA.push_back(14);
	    fiberOrderA.push_back(17);
	    fiberOrderA.push_back(27);
	    fiberOrderA.push_back(19);
	    fiberOrderA.push_back(25);
	    fiberOrderA.push_back(24);
	    fiberOrderA.push_back(22);
	    fiberOrderA.push_back(32);
	    fiberOrderA.push_back(30);
	    fiberOrderA.push_back(4);
	    fiberOrderA.push_back(2);
	    fiberOrderA.push_back(12);
	    fiberOrderA.push_back(10);
	    fiberOrderA.push_back(20);
	    fiberOrderA.push_back(18);
	    fiberOrderA.push_back(28);
	    fiberOrderA.push_back(26);

	    fiberOrderB.push_back(54);
	    fiberOrderB.push_back(64);
	    fiberOrderB.push_back(56);
	    fiberOrderB.push_back(62);
	    fiberOrderB.push_back(49);
	    fiberOrderB.push_back(51);
	    fiberOrderB.push_back(59);
	    fiberOrderB.push_back(57);
	    fiberOrderB.push_back(53);
	    fiberOrderB.push_back(55);
	    fiberOrderB.push_back(63);
	    fiberOrderB.push_back(61);
	    fiberOrderB.push_back(45);
	    fiberOrderB.push_back(47);
	    fiberOrderB.push_back(37);
	    fiberOrderB.push_back(39);
	    fiberOrderB.push_back(34);
	    fiberOrderB.push_back(42);
	    fiberOrderB.push_back(36);
	    fiberOrderB.push_back(44);
	    fiberOrderB.push_back(50);
	    fiberOrderB.push_back(52);
	    fiberOrderB.push_back(58);
	    fiberOrderB.push_back(60);
	    fiberOrderB.push_back(38);
	    fiberOrderB.push_back(48);
	    fiberOrderB.push_back(40);
	    fiberOrderB.push_back(46);
	    fiberOrderB.push_back(41);
	    fiberOrderB.push_back(43);
	    fiberOrderB.push_back(33);
	    fiberOrderB.push_back(35);

	    //fillHODO
	    //std::cout << " fill HODO " << std::endl;
	    std::vector<bool>    HODOX1;
	    std::vector<bool>    HODOX2;
	    std::vector<bool>    HODOY1;
	    std::vector<bool>    HODOY2;
	    HODOX1.clear();  HODOX1.resize(nFibersHodo,false);
	    HODOX2.clear();  HODOX2.resize(nFibersHodo,false);
	    HODOY1.clear();  HODOY1.resize(nFibersHodo,false);
	    HODOY2.clear();  HODOY2.resize(nFibersHodo,false);
	    std::vector<bool> *hodo;

	    for(unsigned int iPat=0; iPat<nPatterns; ++iPat){
	      if(patternBoard[iPat] == 0x08020001 || patternBoard[iPat] == 0x08020002){
		// here is where the hodoscope mapping is done
		if(patternBoard[iPat] == 0x08020001){
		  if(patternChannel[iPat] < 2) hodo = &HODOY2;
		  else hodo = &HODOX2;
		}
		else if(patternBoard[iPat] == 0x08020002){
		  if(patternChannel[iPat] < 2) hodo = &HODOY1;
		  else hodo = &HODOX1;
		}
		std::vector<int> *fiberorder = (bool)(patternChannel[iPat]&0b1) ? &fiberOrderB : &fiberOrderA;
		for(unsigned int j=0; j<32; j++){
		  bool thisfibon = (pattern[iPat]>>j)&0b1;
		  hodo->at(fiberorder->at(j)-1) = thisfibon;
		}
	      }
	    }
// 	    for(unsigned int iF=0; iF<HODOX2.size(); ++iF)
// 	      std::cout << "iF = " << iF << " HODOX2.at(iF) = " << HODOX2.at(iF) << std::endl;
	    

	    // hodo reconstruction 
	    std::vector<bool> hodoX1_values(HODOX1_CHANNELS, -1.);
	    std::vector<bool> hodoY1_values(HODOY1_CHANNELS, -1.);
	    assignValuesBool( hodoX1_values, HODOX1, 0. );
	    assignValuesBool( hodoY1_values, HODOY1, 0. );


	    std::vector<bool> hodoX2_values(HODOX2_CHANNELS, -1.);
	    std::vector<bool> hodoY2_values(HODOY2_CHANNELS, -1.);
	    assignValuesBool( hodoX2_values, HODOX2, 0 );
	    assignValuesBool( hodoY2_values, HODOY2, 0 );


	    std::vector<float> hodoSmallX_values(HODOSMALLX_CHANNELS, -1.);
	    std::vector<float> hodoSmallY_values(HODOSMALLY_CHANNELS, -1.);
	    assignValues( hodoSmallY_values, HODOSMALLvalues, 0 );
	    assignValues( hodoSmallX_values, HODOSMALLvalues, 4 );


	    // hodo cluster reconstruction
	    int clusterMaxFibres = 4;
	    doHodoReconstructionBool( hodoX1_values    , nClusters_hodoX1    , nFibres_hodoX1    , pos_hodoX1    , 0.5, clusterMaxFibres, 0. );
	    doHodoReconstructionBool( hodoY1_values    , nClusters_hodoY1    , nFibres_hodoY1    , pos_hodoY1    , 0.5, clusterMaxFibres, 0. );
	    doHodoReconstructionBool( hodoX2_values    , nClusters_hodoX2    , nFibres_hodoX2    , pos_hodoX2    , 0.5, clusterMaxFibres , 0.);
	    doHodoReconstructionBool( hodoY2_values    , nClusters_hodoY2    , nFibres_hodoY2    , pos_hodoY2    , 0.5, clusterMaxFibres, 0. );

	    std::vector<float> pedMeanX,pedMeanY, pedSigmaX, pedSigmaY,cutValuesX,cutValuesY;
	    //values obtained fitting pedestals from run 2778
	    pedMeanY.push_back(155.15);
	    pedMeanY.push_back(141.30);
	    pedMeanY.push_back(152.90);
	    pedMeanY.push_back(152.13);

	    pedMeanX.push_back(146.89);     
	    pedMeanX.push_back(139.89);
	    pedMeanX.push_back(151.73);
	    pedMeanX.push_back(53.27);

	    pedSigmaY.push_back(1.20);
	    pedSigmaY.push_back(1.25);
	    pedSigmaY.push_back(1.60);
	    pedSigmaY.push_back(1.20);

	    pedSigmaX.push_back(1.28);
	    pedSigmaX.push_back(1.32);
	    pedSigmaX.push_back(1.31);
	    pedSigmaX.push_back(0.83);

	    for(int i=0;i<pedMeanX.size();++i){
	      cutValuesX.push_back(pedMeanX[i]+5*pedSigmaX[i]);
	      cutValuesY.push_back(pedMeanY[i]+5*pedSigmaY[i]);
	    }
	    doHodoReconstructionMultipleCuts( hodoSmallX_values, nClusters_hodoSmallX, nFibres_hodoSmallX, pos_hodoSmallX, 1.0, 1, cutValuesX);
	    doHodoReconstructionMultipleCuts( hodoSmallY_values, nClusters_hodoSmallY, nFibres_hodoSmallY, pos_hodoSmallY, 1.0, 1, cutValuesY);

	    copyArray( nClusters_hodoX1, pos_hodoX1, pos_corr_hodoX1 );
	    copyArray( nClusters_hodoY1, pos_hodoY1, pos_corr_hodoY1 );
	    copyArray( nClusters_hodoX2, pos_hodoX2, pos_corr_hodoX2 );
	    copyArray( nClusters_hodoY2, pos_hodoY2, pos_corr_hodoY2 );
	    copyArray( nClusters_hodoSmallX, pos_hodoSmallX, pos_corr_hodoSmallX );
	    copyArray( nClusters_hodoSmallY, pos_hodoSmallY, pos_corr_hodoSmallY );

	    alignOfficer.fix("hodoX1", nClusters_hodoX1, pos_corr_hodoX1);
	    alignOfficer.fix("hodoY1", nClusters_hodoY1, pos_corr_hodoY1);
	    alignOfficer.fix("hodoX2", nClusters_hodoX2, pos_corr_hodoX2);
	    alignOfficer.fix("hodoY2", nClusters_hodoY2, pos_corr_hodoY2);

// 	    nTDCHits[0] = nTDCHits->at(0);
// 	    nTDCHits[1] = nTDCHits->at(1);
// 	    nTDCHits[2] = nTDCHits->at(2);
// 	    nTDCHits[3] = nTDCHits->at(3);

	    wc_x = TDCreco[0];
	    wc_y = TDCreco[1];

	    if( nRuns >= 170 ) wc_y = -wc_y;

	    wc_x_corr = wc_x + alignOfficer.getOffset("wc_x");
	    wc_y_corr = wc_y + alignOfficer.getOffset("wc_y");

 



	    int posOf2FibClustX1=0;
	    int nrOf2FibreClustersX1 = 0;
	    for( int i=0; i<nClusters_hodoX1; ++i ) {
	      if( nFibres_hodoX1[i]==2  ) {  
		++nrOf2FibreClustersX1;
		posOf2FibClustX1 = i ; } 
	    }
	    if( nrOf2FibreClustersX1 == 1){
	      pos_2FibClust_hodoX1 =   pos_hodoX1[ posOf2FibClustX1] ;
	    }else{
	      pos_2FibClust_hodoX1 =  -999 ;}

	    if(nClusters_hodoX1==1){
	      cluster_pos_hodoX1 = pos_hodoX1[0];
	    }else if(nrOf2FibreClustersX1==1){
	      cluster_pos_hodoX1 = pos_hodoX1[ posOf2FibClustX1];
	    }else{ cluster_pos_hodoX1 = -999;}


	    int posOf2FibClustX2=0;
	    int nrOf2FibreClustersX2 = 0;
	    for( int i=0; i<nClusters_hodoX2; ++i ) {
	      if( nFibres_hodoX2[i]==2  ) {  
		++nrOf2FibreClustersX2;
		posOf2FibClustX2 = i ; } 
	    }
	    if( nrOf2FibreClustersX2 == 1){
	      pos_2FibClust_hodoX2 =   pos_hodoX2[ posOf2FibClustX2] ;
	    }else{
	      pos_2FibClust_hodoX2 =  -999 ;}

	    if(nClusters_hodoX2==1){
	      cluster_pos_hodoX2 = pos_hodoX2[0];
	    }else if(nrOf2FibreClustersX2==1){
	      cluster_pos_hodoX2 = pos_hodoX2[ posOf2FibClustX2];
	    }else{ cluster_pos_hodoX2 = -999;}

	    int posOf2FibClustY1=0;
	    int nrOf2FibreClustersY1 = 0;
	    for( int i=0; i<nClusters_hodoY1; ++i ) {
	      if( nFibres_hodoY1[i]==2  ) {  
		++nrOf2FibreClustersY1;
		posOf2FibClustY1 = i ; } 
	    }
	    if( nrOf2FibreClustersY1 == 1){
	      pos_2FibClust_hodoY1 =   pos_hodoY1[ posOf2FibClustY1] ;
	    }else{
	      pos_2FibClust_hodoY1 =  -999 ;}
     
	    if(nClusters_hodoY1==1){
	      cluster_pos_hodoY1 = pos_hodoY1[0];
	    }else if(nrOf2FibreClustersY1==1){
	      cluster_pos_hodoY1 = pos_hodoY1[ posOf2FibClustY1];
	    }else{ cluster_pos_hodoY1 = -999;}
   

	    int posOf2FibClustY2=0;
	    int nrOf2FibreClustersY2 = 0;
	    for( int i=0; i<nClusters_hodoY2; ++i ) {
	      if( nFibres_hodoY2[i]==2  ) {  
		++nrOf2FibreClustersY2;
		posOf2FibClustY2 = i ; } 
	    }
	    if( nrOf2FibreClustersY2 == 1){
	      pos_2FibClust_hodoY2 =   pos_hodoY2[ posOf2FibClustY2] ;
	    }else{
	      pos_2FibClust_hodoY2 =  -999 ;}

	    if(nClusters_hodoY2==1){
	      cluster_pos_hodoY2 = pos_hodoY2[0];
	    }else if(nrOf2FibreClustersY2==1){
	      cluster_pos_hodoY2 = pos_hodoY2[ posOf2FibClustY2];
	    }else{ cluster_pos_hodoY2 = -999;}


	    pos_2FibClust_corr_hodoX1 = pos_2FibClust_hodoX1 + alignOfficer.getOffset("hodoX1");
	    pos_2FibClust_corr_hodoY1 = pos_2FibClust_hodoY1 + alignOfficer.getOffset("hodoY1");   
	    pos_2FibClust_corr_hodoX2 = pos_2FibClust_hodoX2 + alignOfficer.getOffset("hodoX2");   
	    pos_2FibClust_corr_hodoY2 = pos_2FibClust_hodoY2 + alignOfficer.getOffset("hodoY2");


	    cluster_pos_corr_hodoX1 = cluster_pos_hodoX1 + alignOfficer.getOffset("hodoX1");
	    cluster_pos_corr_hodoY1 = cluster_pos_hodoY1 + alignOfficer.getOffset("hodoY1");   
	    cluster_pos_corr_hodoX2 = cluster_pos_hodoX2 + alignOfficer.getOffset("hodoX2");   
	    cluster_pos_corr_hodoY2 = cluster_pos_hodoY2 + alignOfficer.getOffset("hodoY2");
	    // hodo reconstruction 


	    //---Read digitizer samples
	    // NB patch per leggere i primi 5 canali del secondo gruppo
	    //	for(unsigned int iSample=0; iSample<nDigiSamples; iSample++) {
	    for(unsigned int iSample=0; iSample<18432; iSample++) {
	      if (digiGroup[iSample]*9+digiChannel[iSample]==6 || digiGroup[iSample]*9+digiChannel[iSample]==7){
		//	    std::cout << " digiGroup[iSample]*9+digiChannel[iSample] = " << digiGroup[iSample]*9+digiChannel[iSample] << std::endl;
		//	    if( (digiGroup[iSample]*9+digiChannel[iSample]) >= 9)
		digiCh_dummy[(digiGroup[iSample]*9+digiChannel[iSample])].push_back(-digiSampleValue[iSample]);
	      }
	      else{
		//	    if( (digiGroup[iSample]*9+digiChannel[iSample]) >= 9)         
		digiCh_dummy[digiGroup[iSample]*9+digiChannel[iSample]].push_back(digiSampleValue[iSample]);
	      }
	    }
	    
	    //	std::cout << " fino a qui ok " << std::endl;
	    
	    for(int jCh=0; jCh<18; jCh++){
	      for(int nSamp=0; nSamp<digiCh_dummy[jCh].size(); ++nSamp){
		if(jCh < 5) digiCh[jCh].push_back(digiCh_dummy[jCh+9].at(nSamp));
		else digiCh[jCh].push_back(0.);
	      }
	    }
	


	    int triggerTime=100;                  //DON'T CHANGE THIS!!!!!
	    SubtractBaseline(5, 25, &digiCh[trigPos]);  //trigger baseline subtraction
	    triggerTime=int(TimeConstFrac(triggerTime, 400, &digiCh[trigPos], 1.)/0.2); //trigger
	    if(triggerTime<100 || triggerTime >800) continue;

	    //---loop over MPC's channels
	    for(int jCh=0; jCh<nCh; jCh++)
	    //	    for(int jCh=9; jCh<(9+nCh); jCh++)
            {
                string currentMCP = CFG.GetOpt<string>("global", "MCPs", jCh);
                int iCh = CFG.GetOpt<int>(currentMCP, "digiChannel");


		if(currentMCP.find("clock") != string::npos || currentMCP.find("TorGain1") != string::npos || currentMCP.find("TorGain2") != string::npos ) 
                { 

		  std::cout << " sono nel caso clock " << std::endl;
		  
		    SubtractBaseline(5, 25, &digiCh[iCh]);  
                    ampMax[iCh] = AmpMax(51, 1000, &digiCh[iCh]);
                    intBase[iCh] = ComputeIntegral(26, 50, &digiCh[iCh]);
                    intSignal[iCh] = ComputeIntegral(51, 1000, &digiCh[iCh]);
                    timeCF[iCh] = TimeConstFracAbs(51, 1000, &digiCh[iCh], 0.5, ampMax[iCh]);

                    TimeOverThreshold(51, 1000, &digiCh[iCh], -150., tStart, tStop);		  
                    timeStart_150[iCh]=tStart;
                    timeStop_150[iCh]=tStop;

                    TimeOverThreshold(51, 1000, &digiCh[iCh], -200., tStart, tStop);
                    timeStart_200[iCh]=tStart;
                    timeStop_200[iCh]=tStop;
		  
                    TimeOverThreshold(51, 1000, &digiCh[iCh], -300., tStart, tStop);
                    timeStart_300[iCh]=tStart;
                    timeStop_300[iCh]=tStop;

                    TimeOverThreshold(51, 1000, &digiCh[iCh], -500., tStart, tStop);
                    timeStart_500[iCh]=tStart;
                    timeStop_500[iCh]=tStop;

                    TimeOverThreshold(51, 1000, &digiCh[iCh], -1000., tStart, tStop);
                    timeStart_1000[iCh]=tStart;
                    timeStop_1000[iCh]=tStop;

                    timeOT[iCh] = TimeOverThreshold(51, 1000, &digiCh[iCh], -1000., tStart, tStop);
                    timeStart[iCh]=tStart;
                    timeStop[iCh]=tStop;

                    ampMaxcorr[iCh] = -1.*ampMax[iCh];
                    intSignalcorr[iCh] = -1.*intSignal[iCh];
                    timeCFcorr[iCh] = timeCF[iCh];
                }
		else 
                {
                    int ampMaxTimeTemp = TimeConstFrac(triggerTime-50, triggerTime+50, &digiCh[iCh], 1)/0.2; 
                    //time of max sample (window's coincidence:-50,50)
                    //window for charge calculation
                    int t1 = ampMaxTimeTemp-13;
                    int t2 = ampMaxTimeTemp+12;
                    ampMaxT[iCh]=ampMaxTimeTemp;
		
                    //subtract baseline immediately before pulse		
		    //                    if(iCh!=trigPos) 
		    //		    SubtractBaseline(t1-27, t1-7, &digiCh[iCh]);  
		    SubtractBaseline(25, 50, &digiCh[iCh]);  
                    intBase[iCh] = ComputeIntegral(50, 75, &digiCh[iCh]);

                    if(t1 > 50 && t1 < 1024 && t2 > 50 && t2 < 1024){
                        ampMax[iCh] = AmpMax(t1, t2, &digiCh[iCh]);
                        intSignal[iCh] = ComputeIntegral(t1, t2, &digiCh[iCh]);
			//std::cout<<ampMax[0]<<" "<<intSignal[0]<<std::endl;
			//			getchar();
                    }
                    else
                        ampMax[iCh] = AmpMax(47, 500, &digiCh[iCh]);
                    //---time OT
                    TimeOverThreshold(t1-10, t2+30, &digiCh[iCh], -150., tStart, tStop);
                    timeStart_150[iCh]=tStart;
                    timeStop_150[iCh]=tStop;

                    TimeOverThreshold(t1-10, t2+30, &digiCh[iCh], -200., tStart, tStop);
                    timeStart_200[iCh]=tStart;
                    timeStop_200[iCh]=tStop;
		  
                    TimeOverThreshold(t1-10, t2+30, &digiCh[iCh], -300., tStart, tStop);
                    timeStart_300[iCh]=tStart;
                    timeStop_300[iCh]=tStop;

                    TimeOverThreshold(t1-10, t2+30, &digiCh[iCh], -500., tStart, tStop);
                    timeStart_500[iCh]=tStart;
                    timeStop_500[iCh]=tStop;

                    TimeOverThreshold(t1-10, t2+30, &digiCh[iCh], -1000., tStart, tStop);
                    timeStart_1000[iCh]=tStart;
                    timeStop_1000[iCh]=tStop;

                    timeOT[iCh] = TimeOverThreshold(t1-10, t2+10, &digiCh[iCh], -1000., tStart, tStop);
                    timeStart[iCh]=tStart;
                    timeStop[iCh]=tStop;

                    timeCF[iCh] = TimeConstFracAbs(t1-10, t2+10, &digiCh[iCh], 0.5, ampMax[iCh]);
                    timeCF30[iCh] = TimeConstFracAbs(t1-10, t2+10, &digiCh[iCh], 0.3, ampMax[iCh]);

                    if(ampMax[iCh] < -3300.) 
                    {
                        ampMaxcorr[iCh] =
                            get_amp_max_from_time_OT(iCh, timeOT[iCh]*0.2, CFG.GetOpt<int>(currentMCP, "isPCON"), run);
                        intSignalcorr[iCh] =
                            get_charge_from_amp_max(iCh, ampMaxcorr[iCh], CFG.GetOpt<int>(currentMCP, "isPCON"), run);
                        timeCFcorr[iCh] =
                            get_time_CF_from_time_OT(iCh, timeOT[iCh]*0.2, CFG.GetOpt<int>(currentMCP, "isPCON"),
                                                     run, tStart*0.2)/0.2; 
                    }
                    else 
                    {
                        ampMaxcorr[iCh] = -1.*ampMax[iCh];
                        intSignalcorr[iCh] = -1.*intSignal[iCh];
                        timeCFcorr[iCh] = timeCF[iCh];
                    }
		}

                //---fill the MCP reco variables
                time_CF[MCPList.at(currentMCP)]   = timeCF[iCh]*0.2;
                time_CF_corr[MCPList.at(currentMCP)]   = timeCFcorr[iCh]*0.2;
                time_CF30[MCPList.at(currentMCP)]   = timeCF30[iCh]*0.2;
                time_OT[MCPList.at(currentMCP)]   = timeOT[iCh]*0.2;
                time_start[MCPList.at(currentMCP)]   = timeStart[iCh]*0.2;
                time_stop[MCPList.at(currentMCP)]   = timeStop[iCh]*0.2;
                time_start_150[MCPList.at(currentMCP)]   = timeStart_150[iCh]*0.2;
                time_stop_150[MCPList.at(currentMCP)]   = timeStop_150[iCh]*0.2;
                time_start_200[MCPList.at(currentMCP)]   = timeStart_200[iCh]*0.2;
                time_stop_200[MCPList.at(currentMCP)]   = timeStop_200[iCh]*0.2;
                time_start_300[MCPList.at(currentMCP)]   = timeStart_300[iCh]*0.2;
                time_stop_300[MCPList.at(currentMCP)]   = timeStop_300[iCh]*0.2;
                time_start_500[MCPList.at(currentMCP)]   = timeStart_500[iCh]*0.2;
                time_stop_500[MCPList.at(currentMCP)]   = timeStop_500[iCh]*0.2;
                time_start_1000[MCPList.at(currentMCP)]   = timeStart_1000[iCh]*0.2;
                time_stop_1000[MCPList.at(currentMCP)]   = timeStop_1000[iCh]*0.2;
                amp_max[MCPList.at(currentMCP)]   = -ampMax[iCh];
                amp_max_corr[MCPList.at(currentMCP)]   = ampMaxcorr[iCh];
                amp_max_time[MCPList.at(currentMCP)]   = ampMaxT[iCh]*0.2;
                charge[MCPList.at(currentMCP)]    = -intSignal[iCh];
                charge_corr[MCPList.at(currentMCP)]    = intSignalcorr[iCh];
                baseline[MCPList.at(currentMCP)]  = -intBase[iCh];

                isPCOn[MCPList.at(currentMCP)] = CFG.GetOpt<int>(currentMCP, "isPCON");
                HV[MCPList.at(currentMCP)] = CFG.GetOpt<float>(currentMCP, "HV", iRun);
                HV2[MCPList.at(currentMCP)] = CFG.GetOpt<float>(currentMCP, "HV2", iRun);
                isTrigger[MCPList.at(currentMCP)] = CFG.GetOpt<int>(currentMCP, "isTrigger");            
            }

            run_id = run;
            X0 = -1;
            if(runType == "X0")
                X0 = CFG.GetOpt<float>("global", "nX0", iRun);

            // positionTree->GetEntry(iEntry);
            // tdcX = (*TDCreco)[0];
            // tdcY = (*TDCreco)[1];
            // // event = evtNumber;

            // nhodoX1=0;
            // nhodoX2=0;
            // nhodoY1=0;
            // nhodoY2=0;

            // for (int i=0; i<64; i++)
            // {
            //     hodoX1[i] = (*HODOX1)[i];		 
            //     hodoX2[i] = (*HODOX2)[i];
            //     hodoY1[i] = (*HODOY1)[i];
            //     hodoY2[i] = (*HODOY2)[i];		      
            //     //cout<<(*HODOX1)[i]<<" "<<hodoX1[i]<<endl;	  //DEBUG    
            //     if (hodoX1[i]==true)   nhodoX1++;
            //     if (hodoX2[i]==true)   nhodoX2++;
            //     if (hodoY1[i]==true)   nhodoY1++;
            //     if (hodoY2[i]==true)   nhodoY2++;
            // }
            outTree->Fill();    
	}     
        //---Get ready for next run
	outTree->AutoSave();
        chain->Delete();
	// positionTree->Delete();
        ++iRun;
    }
    //-----close everything-----------------------------------------------------
    for(int iCh=0; iCh<nCh; iCh++) 
        wf_promed[iCh]->Write();

    outTree->Write();
    outROOT->Close();
    
//---------Done-----------------------------------------------------------------
}




void assignValues( std::vector<float> &target, std::vector<float> source, unsigned int startPos ) {

  for( unsigned i=0; i<target.size(); ++i ) 
    target[i] = source[startPos+i];

}


void assignValuesBool( std::vector<bool> &target, std::vector<bool> source, unsigned int startPos ) {

  for( unsigned i=0; i<target.size(); ++i ) 
    target[i] = source[startPos+i];

}

std::vector<HodoCluster*> getHodoClusters( std::vector<float> hodo, float fibreWidth, int nClusterMax, float Cut ) {

  std::vector<HodoCluster*> clusters;

  HodoCluster* currentCluster = new HodoCluster( hodo.size(), fibreWidth );

  for( unsigned i=0; i<hodo.size(); ++i ) {

    if( hodo[i] > Cut) { // hit

      if( currentCluster->getSize() < nClusterMax ) {

        currentCluster->addFibre( i );

      } else {

        clusters.push_back( currentCluster ); // store old one
        currentCluster = new HodoCluster( hodo.size(), fibreWidth );   // create a new one
        currentCluster->addFibre( i );        // get that fibre!

      }

    } else { // as soon as you find a hole
      
      if( currentCluster->getSize() > 0 ) {
     
        clusters.push_back( currentCluster ); // store old one
        currentCluster = new HodoCluster( hodo.size(), fibreWidth );   // create a new one

      }

    }


  } // for fibres


  if( currentCluster->getSize()>0 )
    clusters.push_back( currentCluster ); // store last cluster


  return clusters;

}

std::vector<HodoCluster*> getHodoClustersMultipleCuts( std::vector<float> hodo, float fibreWidth, int nClusterMax, std::vector<float> Cut ) {

  std::vector<HodoCluster*> clusters;

  HodoCluster* currentCluster = new HodoCluster( hodo.size(), fibreWidth );

  for( unsigned i=0; i<hodo.size(); ++i ) {

    if( hodo[i] > Cut[i]) { // hit

      if( currentCluster->getSize() < nClusterMax ) {

        currentCluster->addFibre( i );

      } else {

        clusters.push_back( currentCluster ); // store old one
        currentCluster = new HodoCluster( hodo.size(), fibreWidth );   // create a new one
        currentCluster->addFibre( i );        // get that fibre!

      }

    } else { // as soon as you find a hole
      
      if( currentCluster->getSize() > 0 ) {
     
        clusters.push_back( currentCluster ); // store old one
        currentCluster = new HodoCluster( hodo.size(), fibreWidth );   // create a new one

      }

    }


  } // for fibres


  if( currentCluster->getSize()>0 )
    clusters.push_back( currentCluster ); // store last cluster


  return clusters;

}




void doHodoReconstruction( std::vector<float> values, int &nClusters, int *nFibres, float *pos, float fibreWidth, int clusterMaxFibres, float Cut ) {

  std::vector<HodoCluster*> clusters = getHodoClusters( values, fibreWidth, clusterMaxFibres, Cut );

  nClusters = clusters.size();
  for( unsigned i=0; i<clusters.size(); ++i ) {
    nFibres[i] = clusters[i]->getSize();
    pos[i] = clusters[i]->getPosition();
  }

}

void doHodoReconstructionMultipleCuts( std::vector<float> values, int &nClusters, int *nFibres, float *pos, float fibreWidth, int clusterMaxFibres, std::vector<float> Cut ) {

  std::vector<HodoCluster*> clusters = getHodoClustersMultipleCuts( values, fibreWidth, clusterMaxFibres, Cut );

  nClusters = clusters.size();
  for( unsigned i=0; i<clusters.size(); ++i ) {
    nFibres[i] = clusters[i]->getSize();
    pos[i] = clusters[i]->getPosition();
  }

}


void copyArray( int n, float *source, float *target ) {

  for( unsigned i=0; i<n; ++i ) 
    target[i] = source[i];

}













std::vector<HodoCluster*> getHodoClustersBool( std::vector<bool> hodo, float fibreWidth, int nClusterMax, float Cut ) {

  std::vector<HodoCluster*> clusters;

  HodoCluster* currentCluster = new HodoCluster( hodo.size(), fibreWidth );

  for( unsigned i=0; i<hodo.size(); ++i ) {

    if( hodo[i] > Cut) { // hit

      if( currentCluster->getSize() < nClusterMax ) {

        currentCluster->addFibre( i );

      } else {

        clusters.push_back( currentCluster ); // store old one
        currentCluster = new HodoCluster( hodo.size(), fibreWidth );   // create a new one
        currentCluster->addFibre( i );        // get that fibre!

      }

    } else { // as soon as you find a hole
      
      if( currentCluster->getSize() > 0 ) {
     
        clusters.push_back( currentCluster ); // store old one
        currentCluster = new HodoCluster( hodo.size(), fibreWidth );   // create a new one

      }

    }


  } // for fibres


  if( currentCluster->getSize()>0 )
    clusters.push_back( currentCluster ); // store last cluster


  return clusters;

}


void doHodoReconstructionBool( std::vector<bool> values, int &nClusters, int *nFibres, float *pos, float fibreWidth, int clusterMaxFibres, float Cut ) {

  std::vector<HodoCluster*> clusters = getHodoClustersBool( values, fibreWidth, clusterMaxFibres, Cut );

  nClusters = clusters.size();
  for( unsigned i=0; i<clusters.size(); ++i ) {
    nFibres[i] = clusters[i]->getSize();
    pos[i] = clusters[i]->getPosition();
  }

}
