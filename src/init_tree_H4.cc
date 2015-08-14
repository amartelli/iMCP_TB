#include "../interface/init_tree_H4.h"
   
    // Declaration of leaf types
unsigned int          evtNumber;
unsigned int          evtTimeDist;
unsigned int          evtTimeStart;
//    unsigned int          evtTime;
//    unsigned int          boardTriggerBit;
//    unsigned int          triggerWord;
unsigned int          nAdcChannels;
unsigned int          adcBoard[100];   
unsigned int          adcChannel[100];   
unsigned int          adcData[100];   
unsigned int          nTdcChannels;
unsigned int          tdcBoard[10];   
unsigned int          tdcChannel[10];  
unsigned int          tdcData[10];  

unsigned int          nPatterns;
unsigned int          pattern[16];
unsigned int          patternBoard[16];
unsigned int          patternChannel[16];

unsigned int          nDigiSamples;
unsigned int          digiGroup[100000];   
unsigned int          digiChannel[100000];   
unsigned int          digiSampleIndex[100000];   
float                 digiSampleValue[100000];   

unsigned int spillNumber;

    // List of branches
TBranch        *b_evtNumber;   //!
TBranch        *b_evtTimeDist;   //!
TBranch        *b_evtTimeStart;   //!
//    TBranch        *b_evtTime;   //!
//    TBranch        *b_boardTriggerBit;   //!
//    TBranch        *b_triggerWord;   //!
TBranch        *b_nAdcChannels;   //!
TBranch        *b_adcBoard;   //!
TBranch        *b_adcChannel;   //!
TBranch        *b_adcData;   //!
TBranch        *b_nTdcChannels;   //!
TBranch        *b_tdcBoard;   //!
TBranch        *b_tdcChannel;   //!
TBranch        *b_tdcData;   //!

TBranch        *b_nPatterns;
TBranch        *b_pattern;
TBranch        *b_patternBoard;
TBranch        *b_patternChannel;

TBranch        *b_nDigiSamples;   //!
TBranch        *b_digiGroup;   //!
TBranch        *b_digiChannel;   //!
TBranch        *b_digiSampleIndex;   //!
TBranch        *b_digiSampleValue;   //!

TBranch  *b_spillNumber;
   

void InitTree(TChain* nt)
    {
      //      std::cout << " InitTree normal " << std::endl;

        nt->SetBranchAddress("evtNumber", &evtNumber, &b_evtNumber);
        nt->SetBranchAddress("evtTimeDist", &evtTimeDist, &b_evtTimeDist);
        nt->SetBranchAddress("evtTimeStart", &evtTimeStart, &b_evtTimeStart);
	//        nt->SetBranchAddress("evtTime", &evtTime, &b_evtTime);
	//        nt->SetBranchAddress("boardTriggerBit", &boardTriggerBit, &b_boardTriggerBit);
	//        nt->SetBranchAddress("triggerWord", &triggerWord, &b_triggerWord);
        nt->SetBranchAddress("nAdcChannels", &nAdcChannels, &b_nAdcChannels);
        nt->SetBranchAddress("adcBoard", adcBoard, &b_adcBoard);
        nt->SetBranchAddress("adcChannel", adcChannel, &b_adcChannel);
        nt->SetBranchAddress("adcData", adcData, &b_adcData);

        nt->SetBranchAddress("nTdcChannels", &nTdcChannels, &b_nTdcChannels);
        nt->SetBranchAddress("tdcBoard", tdcBoard, &b_tdcBoard);
        nt->SetBranchAddress("tdcChannel", tdcChannel, &b_tdcChannel);
        nt->SetBranchAddress("tdcData", tdcData, &b_tdcData);

	nt->SetBranchAddress("nPatterns", &nPatterns, &b_nPatterns);
	nt->SetBranchAddress("pattern", pattern, &b_pattern);
	nt->SetBranchAddress("patternBoard", &patternBoard, &b_patternBoard);
	nt->SetBranchAddress("patternChannel", &patternChannel, &b_patternChannel);

        nt->SetBranchAddress("nDigiSamples", &nDigiSamples, &b_nDigiSamples);
        nt->SetBranchAddress("digiGroup", digiGroup, &b_digiGroup);
        nt->SetBranchAddress("digiChannel", digiChannel, &b_digiChannel);
        nt->SetBranchAddress("digiSampleIndex", digiSampleIndex, &b_digiSampleIndex);
        nt->SetBranchAddress("digiSampleValue", digiSampleValue, &b_digiSampleValue);

        nt->SetBranchAddress("spillNumber", &spillNumber, &b_spillNumber);
    }

void InitTree2(TChain* nt2)
{
  //  std::cout << " InitTree2 " << std::endl;
//   nt2->SetBranchAddress("TDCreco", &TDCreco);//, &b_TDCreco); 
//   nt2->SetBranchAddress("HODOX1", &HODOX1); 
//   nt2->SetBranchAddress("HODOX2", &HODOX2); 
//   nt2->SetBranchAddress("HODOY1", &HODOY1); 
//   nt2->SetBranchAddress("HODOY2", &HODOY2); 
  nt2->SetBranchAddress("spillNumber", &spillNumber, &b_spillNumber); 
  nt2->SetBranchAddress("evtNumber", &evtNumber, &b_evtNumber);

}
