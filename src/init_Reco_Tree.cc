#include "../interface/init_Reco_Tree.h"

int event;
float                 time_CF[8];
float                 time_CF_corr[8];
float                 time_CF30[8];
float                 time_OT[8];
float                 time_start[8];
float                 time_stop[8];
float                 time_start_1000[8];
float                 time_stop_1000[8];
float                 time_start_150[8];
float                 time_stop_150[8];
float                 time_start_200[8];
float                 time_stop_200[8];
float                 time_start_500[8];
float                 time_stop_500[8];
float                 time_start_300[8];
float                 time_stop_300[8];
float                 time_Max[8];
float                 amp_max[8];
float                 amp_max_corr[8];
float                 amp_max_time[8];
float                 charge[8];
float                 charge_corr[8];
float                 baseline[8];
int                   sci_front_adc;
int                   bgo_back_adc;
int                   run_id;
int                   isPCOn[8];
int                   HV[8];
int                   HV2[8];
int                   isTrigger[8];
float                 X0;

int           nClusters_hodoX1;
int           nFibres_hodoX1[64];
float         pos_hodoX1[64]; 
float         pos_corr_hodoX1[64];

int           nClusters_hodoY1;
int           nFibres_hodoY1[64];
float         pos_hodoY1[64];  
float         pos_corr_hodoY1[64];

int           nClusters_hodoX2;
int           nFibres_hodoX2[64];
float         pos_hodoX2[64];  
float         pos_corr_hodoX2[64]; 

int           nClusters_hodoY2;
int           nFibres_hodoY2[64]; 
float         pos_hodoY2[64]; 
float         pos_corr_hodoY2[64]; 

int           nClusters_hodoSmallX;
int           nFibres_hodoSmallX[4];  
float         pos_hodoSmallX[4]; 
float         pos_corr_hodoSmallX[4];  

int           nClusters_hodoSmallY;
int           nFibres_hodoSmallY[4]; 
float         pos_hodoSmallY[4];  
float         pos_corr_hodoSmallY[4];  

int           nTDCHits[4];
float         pos_2FibClust_hodoX1;
float         pos_2FibClust_corr_hodoX1;

float         pos_2FibClust_hodoY1;
float         pos_2FibClust_corr_hodoY1;

float         pos_2FibClust_hodoX2;
float         pos_2FibClust_corr_hodoX2;

float         pos_2FibClust_hodoY2;
float         pos_2FibClust_corr_hodoY2;

float         cluster_pos_hodoX1;
float         cluster_pos_corr_hodoX1;
float         cluster_pos_hodoX2;
float         cluster_pos_corr_hodoX2;
float         cluster_pos_hodoY1;
float         cluster_pos_corr_hodoY1;
float         cluster_pos_hodoY2;
float         cluster_pos_corr_hodoY2;
float         wc_x;
float         wc_y;
float         wc_x_corr;
float         wc_y_corr;

// List of branches                     
TBranch        *b_event;
TBranch        *b_time_CF;   //! 
TBranch        *b_time_CF_corr;   //!   
TBranch        *b_time_CF30;   //! 
TBranch        *b_time_OT;   //!     
TBranch        *b_time_start;                                                                                                                         
TBranch        *b_time_stop;                                
TBranch        *b_time_start_1000; 
TBranch        *b_time_stop_1000;                                
TBranch        *b_time_start_150;                                                                                                                         
TBranch        *b_time_stop_150;                                
TBranch        *b_time_start_200;                                                                                                                         
TBranch        *b_time_stop_200;                                
TBranch        *b_time_start_500;                                                                                                                         
TBranch        *b_time_stop_500;
TBranch        *b_time_start_300;                                                                                                                         
TBranch        *b_time_stop_300;
TBranch        *b_time_Max;   //! 
TBranch        *b_amp_max;   //!    
TBranch        *b_amp_max_corr;   //!   
TBranch        *b_amp_max_time;   //!  
TBranch        *b_baseline;   //!   
TBranch        *b_charge;   //!    
TBranch        *b_charge_corr;   //!  
TBranch        *b_sci_front_adc;   //!
TBranch        *b_bgo_back_adc;   //! 
TBranch        *b_run_id;   //!   
TBranch        *b_isPCOn;   //! 
TBranch        *b_HV;   //!     
TBranch        *b_HV2;   //!     
TBranch        *b_isTrigger;
TBranch        *b_X0;

TBranch        *b_nClusters_hodoX1;   //!             
TBranch        *b_nFibres_hodoX1;   //!               
TBranch        *b_pos_hodoX1;   //!                   
TBranch        *b_pos_corr_hodoX1;   //!              
TBranch        *b_nClusters_hodoY1;   //!             
TBranch        *b_nFibres_hodoY1;   //!               
TBranch        *b_pos_hodoY1;   //!                   
TBranch        *b_pos_corr_hodoY1;   //!              
TBranch        *b_nClusters_hodoX2;   //!             
TBranch        *b_nFibres_hodoX2;   //!               
TBranch        *b_pos_hodoX2;   //!                   
TBranch        *b_pos_corr_hodoX2;   //!              
TBranch        *b_nClusters_hodoY2;   //!             
TBranch        *b_nFibres_hodoY2;   //!               
TBranch        *b_pos_hodoY2;   //!                   
TBranch        *b_pos_corr_hodoY2;   //!              
TBranch        *b_nClusters_hodoSmallX;   //!         
TBranch        *b_nFibres_hodoSmallX;   //!           
TBranch        *b_pos_hodoSmallX;   //!               
TBranch        *b_pos_corr_hodoSmallX;   //!          
TBranch        *b_nClusters_hodoSmallY;   //!         
TBranch        *b_nFibres_hodoSmallY;   //!           
TBranch        *b_pos_hodoSmallY;   //!               
TBranch        *b_pos_corr_hodoSmallY;   //!          

TBranch        *b_nTDCHits;   //!                     
TBranch        *b_pos_2FibClust_hodoX1;   //!         
TBranch        *b_pos_2FibClust_corr_hodoX1;   //!    
TBranch        *b_pos_2FibClust_hodoY1;   //!         
TBranch        *b_pos_2FibClust_corr_hodoY1;   //!    
TBranch        *b_pos_2FibClust_hodoX2;   //!         
TBranch        *b_pos_2FibClust_corr_hodoX2;   //!    
TBranch        *b_pos_2FibClust_hodoY2;   //!         
TBranch        *b_pos_2FibClust_corr_hodoY2;   //!    
TBranch        *b_cluster_pos_hodoX1;   //!           
TBranch        *b_cluster_pos_corr_hodoX1;   //!      
TBranch        *b_cluster_pos_hodoX2;   //!           
TBranch        *b_cluster_pos_corr_hodoX2;   //!      
TBranch        *b_cluster_pos_hodoY1;   //!           
TBranch        *b_cluster_pos_corr_hodoY1;   //!      
TBranch        *b_cluster_pos_hodoY2;   //!           
TBranch        *b_cluster_pos_corr_hodoY2;   //!      
TBranch        *b_wc_x;   //!                         
TBranch        *b_wc_y;   //!                         
TBranch        *b_wc_x_corr;   //!                    
TBranch        *b_wc_y_corr;   //!                    

void init()
{
}

void SetOutTree(TTree* outTree)
{
  //---standard analysis branches
  outTree->Branch("event",&event,"event/I");
  outTree->Branch("time_CF",&time_CF,"time_CF[8]/F");
  outTree->Branch("time_CF_corr",&time_CF_corr,"time_CF_corr[8]/F");
  outTree->Branch("time_CF30",&time_CF30,"time_CF30[8]/F");
  outTree->Branch("time_OT",&time_OT,"time_OT[8]/F");
  outTree->Branch("time_start",&time_start,"time_start[8]/F");
  outTree->Branch("time_stop",&time_stop,"time_stop[8]/F");
  outTree->Branch("time_start_1000",&time_start_1000,"time_start_1000[8]/F");
  outTree->Branch("time_stop_1000",&time_stop_1000,"time_stop_1000[8]/F");
  outTree->Branch("time_start_150",&time_start_150,"time_start_150[8]/F");
  outTree->Branch("time_stop_150",&time_stop_150,"time_stop_150[8]/F");
  outTree->Branch("time_start_200",&time_start_200,"time_start_200[8]/F");
  outTree->Branch("time_stop_200",&time_stop_200,"time_stop_200[8]/F");
  outTree->Branch("time_start_500",&time_start_500,"time_start_500[8]/F");
  outTree->Branch("time_stop_500",&time_stop_500,"time_stop_500[8]/F");
  outTree->Branch("time_start_300",&time_start_300,"time_start_300[8]/F");
  outTree->Branch("time_stop_300",&time_stop_300,"time_stop_300[8]/F");
  outTree->Branch("time_Max",&time_Max,"time_Max[8]/F");
  outTree->Branch("amp_max",&amp_max,"amp_max[8]/F");
  outTree->Branch("amp_max_corr",&amp_max_corr,"amp_max_corr[8]/F");
  outTree->Branch("amp_max_time",&amp_max_time,"amp_max_time[8]/F");
  outTree->Branch("charge",&charge,"charge[8]/F"); 
  outTree->Branch("charge_corr",&charge_corr,"charge_corr[8]/F");
  outTree->Branch("baseline",&baseline,"baseline[8]/F");

  //---global branches    
  outTree->Branch("sci_front_adc",&sci_front_adc,"sci_front_adc/I");
  outTree->Branch("bgo_back_adc",&bgo_back_adc,"bgo_back_adc/I");
  outTree->Branch("run_id",&run_id,"run_id/I");

  //---additional branches
  outTree->Branch("isPCOn",&isPCOn,"isPCOn[8]/I");
  outTree->Branch("HV",&HV,"HV[8]/I");
  outTree->Branch("HV2",&HV2,"HV2[8]/I");
  outTree->Branch("isTrigger",&isTrigger,"isTrigger[8]/I");
  outTree->Branch("X0",&X0,"X0/F");

  // hodo
  outTree->Branch( "nClusters_hodoX1", &nClusters_hodoX1, "nClusters_hodoX1/I" );
  outTree->Branch( "nFibres_hodoX1", nFibres_hodoX1, "nFibres_hodoX1[nClusters_hodoX1]/I" );
  outTree->Branch( "pos_hodoX1", pos_hodoX1, "pos_hodoX1[nClusters_hodoX1]/F" );
  outTree->Branch( "pos_corr_hodoX1", pos_corr_hodoX1, "pos_corr_hodoX1[nClusters_hodoX1]/F" );

  outTree->Branch( "nClusters_hodoY1", &nClusters_hodoY1, "nClusters_hodoY1/I" );
  outTree->Branch( "nFibres_hodoY1", nFibres_hodoY1, "nFibres_hodoY1[nClusters_hodoY1]/I" );
  outTree->Branch( "pos_hodoY1", pos_hodoY1, "pos_hodoY1[nClusters_hodoY1]/F" );
  outTree->Branch( "pos_corr_hodoY1", pos_corr_hodoY1, "pos_corr_hodoY1[nClusters_hodoY1]/F" );

  outTree->Branch( "nClusters_hodoX2", &nClusters_hodoX2, "nClusters_hodoX2/I" );
  outTree->Branch( "nFibres_hodoX2", nFibres_hodoX2, "nFibres_hodoX2[nClusters_hodoX2]/I" );
  outTree->Branch( "pos_hodoX2", pos_hodoX2, "pos_hodoX2[nClusters_hodoX2]/F" );
  outTree->Branch( "pos_corr_hodoX2", pos_corr_hodoX2, "pos_corr_hodoX2[nClusters_hodoX2]/F" );

  outTree->Branch( "nClusters_hodoY2", &nClusters_hodoY2, "nClusters_hodoY2/I" );
  outTree->Branch( "nFibres_hodoY2", nFibres_hodoY2, "nFibres_hodoY2[nClusters_hodoY2]/I" );
  outTree->Branch( "pos_hodoY2", pos_hodoY2, "pos_hodoY2[nClusters_hodoY2]/F" );
  outTree->Branch( "pos_corr_hodoY2", pos_corr_hodoY2, "pos_corr_hodoY2[nClusters_hodoY2]/F" );

  outTree->Branch( "nClusters_hodoSmallX", &nClusters_hodoSmallX, "nClusters_hodoSmallX/I" );
  outTree->Branch( "nFibres_hodoSmallX", nFibres_hodoSmallX, "nFibres_hodoSmallX[nClusters_hodoSmallX]/I" );
  outTree->Branch( "pos_hodoSmallX", pos_hodoSmallX, "pos_hodoSmallX[nClusters_hodoSmallX]/F" );
  outTree->Branch( "pos_corr_hodoSmallX", pos_corr_hodoSmallX, "pos_corr_hodoSmallX[nClusters_hodoSmallX]/F" );

  outTree->Branch( "nClusters_hodoSmallY", &nClusters_hodoSmallY, "nClusters_hodoSmallY/I" );
  outTree->Branch( "nFibres_hodoSmallY", nFibres_hodoSmallY, "nFibres_hodoSmallY[nClusters_hodoSmallY]/I" );
  outTree->Branch( "pos_hodoSmallY", pos_hodoSmallY, "pos_hodoSmallY[nClusters_hodoSmallY]/F" );
  outTree->Branch( "pos_corr_hodoSmallY", pos_corr_hodoSmallY, "pos_corr_hodoSmallY[nClusters_hodoSmallY]/F" );

  outTree->Branch( "nTDCHits", &nTDCHits, "nTDCHits[4]/I" );
  outTree->Branch( "pos_2FibClust_hodoX1", &pos_2FibClust_hodoX1, "pos_2FibClust_hodoX1/F" );
  outTree->Branch( "pos_2FibClust_corr_hodoX1", &pos_2FibClust_corr_hodoX1, "pos_2FibClust_corr_hodoX1/F" );

  outTree->Branch( "pos_2FibClust_hodoY1", &pos_2FibClust_hodoY1, "pos_2FibClust_hodoY1/F" );
  outTree->Branch( "pos_2FibClust_corr_hodoY1", &pos_2FibClust_corr_hodoY1, "pos_2FibClust_corr_hodoY1/F" );
  outTree->Branch( "pos_2FibClust_hodoX2", &pos_2FibClust_hodoX2, "pos_2FibClust_hodoX2/F" );
  outTree->Branch( "pos_2FibClust_corr_hodoX2", &pos_2FibClust_corr_hodoX2, "pos_2FibClust_corr_hodoX2/F" );

  outTree->Branch( "pos_2FibClust_hodoY2", &pos_2FibClust_hodoY2, "pos_2FibClust_hodoY2/F" );
  outTree->Branch( "pos_2FibClust_corr_hodoY2", &pos_2FibClust_corr_hodoY2, "pos_2FibClust_corr_hodoY2/F" );
  outTree->Branch( "cluster_pos_hodoX1", &cluster_pos_hodoX1, "cluster_pos_hodoX1/F" );
  outTree->Branch( "cluster_pos_corr_hodoX1", &cluster_pos_corr_hodoX1, "cluster_pos_corr_hodoX1/F" );
  outTree->Branch( "cluster_pos_hodoX2", &cluster_pos_hodoX2, "cluster_pos_hodoX2/F" );
  outTree->Branch( "cluster_pos_corr_hodoX2", &cluster_pos_corr_hodoX2, "cluster_pos_corr_hodoX2/F" );

  outTree->Branch( "cluster_pos_hodoY1", &cluster_pos_hodoY1, "cluster_pos_hodoY1/F" );
  outTree->Branch( "cluster_pos_corr_hodoY1", &cluster_pos_corr_hodoY1, "cluster_pos_corr_hodoY1/F" );
  outTree->Branch( "cluster_pos_hodoY2", &cluster_pos_hodoY2, "cluster_pos_hodoY2/F" );
  outTree->Branch( "cluster_pos_corr_hodoY2", &cluster_pos_corr_hodoY2, "cluster_pos_corr_hodoY2/F" );


  outTree->Branch( "wc_x", &wc_x, "wc_x/F");
  outTree->Branch( "wc_y", &wc_y, "wc_y/F");
  outTree->Branch( "wc_x_corr", &wc_x_corr, "wc_x_corr/F");
  outTree->Branch( "wc_y_corr", &wc_y_corr, "wc_y_corr/F");

}

   
void InitRecoTree(TTree* nt)
{
  nt->SetBranchAddress("event", &event, &b_event);
  nt->SetBranchAddress("time_CF", &time_CF, &b_time_CF);
  nt->SetBranchAddress("time_CF_corr", &time_CF_corr, &b_time_CF_corr);
  nt->SetBranchAddress("time_CF30", &time_CF30, &b_time_CF30);
  nt->SetBranchAddress("time_OT", &time_OT, &b_time_OT);
  nt->SetBranchAddress("time_start", &time_start, &b_time_start);
  nt->SetBranchAddress("time_stop", &time_stop, &b_time_stop);
  nt->SetBranchAddress("time_start_1000", &time_start_1000, &b_time_start_1000);
  nt->SetBranchAddress("time_stop_1000", &time_stop_1000, &b_time_stop_1000);
  nt->SetBranchAddress("time_start_150", &time_start_150, &b_time_start_150);
  nt->SetBranchAddress("time_stop_150", &time_stop_150, &b_time_stop_150);
  nt->SetBranchAddress("time_start_200", &time_start_200, &b_time_start_200);
  nt->SetBranchAddress("time_stop_200", &time_stop_200, &b_time_stop_200);
  nt->SetBranchAddress("time_start_500", &time_start_500, &b_time_start_500);
  nt->SetBranchAddress("time_stop_500", &time_stop_500, &b_time_stop_500);
  nt->SetBranchAddress("time_start_300", &time_start_300, &b_time_start_300);
  nt->SetBranchAddress("time_stop_300", &time_stop_300, &b_time_stop_300);
  nt->SetBranchAddress("time_Max", &time_Max, &b_time_Max);
  nt->SetBranchAddress("amp_max", &amp_max, &b_amp_max);
  nt->SetBranchAddress("amp_max_corr", &amp_max_corr, &b_amp_max_corr);
  nt->SetBranchAddress("amp_max_time", &amp_max_time, &b_amp_max_time);
  nt->SetBranchAddress("charge", &charge, &b_charge);
  nt->SetBranchAddress("charge_corr", &charge_corr, &b_charge_corr);
  nt->SetBranchAddress("baseline", &baseline, &b_baseline);
  nt->SetBranchAddress("run_id", &run_id, &b_run_id);
  nt->SetBranchAddress("isPCOn", &isPCOn, &b_isPCOn);
  nt->SetBranchAddress("HV", &HV, &b_HV);
  nt->SetBranchAddress("HV2", &HV2, &b_HV2);
  nt->SetBranchAddress("isTrigger", &isTrigger, &b_isTrigger);
  nt->SetBranchAddress("X0", &X0, &b_X0);
  nt->SetBranchAddress("sci_front_adc", &sci_front_adc, &b_sci_front_adc);
  nt->SetBranchAddress("bgo_back_adc", &bgo_back_adc, &b_bgo_back_adc);

  nt->SetBranchAddress("nClusters_hodoX1", &nClusters_hodoX1, &b_nClusters_hodoX1);
  nt->SetBranchAddress("nFibres_hodoX1", nFibres_hodoX1, &b_nFibres_hodoX1);
  nt->SetBranchAddress("pos_hodoX1", pos_hodoX1, &b_pos_hodoX1);
  nt->SetBranchAddress("pos_corr_hodoX1", pos_corr_hodoX1, &b_pos_corr_hodoX1);
  nt->SetBranchAddress("nClusters_hodoY1", &nClusters_hodoY1, &b_nClusters_hodoY1);
  nt->SetBranchAddress("nFibres_hodoY1", nFibres_hodoY1, &b_nFibres_hodoY1);
  nt->SetBranchAddress("pos_hodoY1", pos_hodoY1, &b_pos_hodoY1);
  nt->SetBranchAddress("pos_corr_hodoY1", pos_corr_hodoY1, &b_pos_corr_hodoY1);
  nt->SetBranchAddress("nClusters_hodoX2", &nClusters_hodoX2, &b_nClusters_hodoX2);
  nt->SetBranchAddress("nFibres_hodoX2", nFibres_hodoX2, &b_nFibres_hodoX2);
  nt->SetBranchAddress("pos_hodoX2", pos_hodoX2, &b_pos_hodoX2);
  nt->SetBranchAddress("pos_corr_hodoX2", pos_corr_hodoX2, &b_pos_corr_hodoX2);
  nt->SetBranchAddress("nClusters_hodoY2", &nClusters_hodoY2, &b_nClusters_hodoY2);
  nt->SetBranchAddress("nFibres_hodoY2", nFibres_hodoY2, &b_nFibres_hodoY2);
  nt->SetBranchAddress("pos_hodoY2", pos_hodoY2, &b_pos_hodoY2);
  nt->SetBranchAddress("pos_corr_hodoY2", pos_corr_hodoY2, &b_pos_corr_hodoY2);
  nt->SetBranchAddress("nClusters_hodoSmallX", &nClusters_hodoSmallX, &b_nClusters_hodoSmallX);
  nt->SetBranchAddress("nFibres_hodoSmallX", nFibres_hodoSmallX, &b_nFibres_hodoSmallX);
  nt->SetBranchAddress("pos_hodoSmallX", pos_hodoSmallX, &b_pos_hodoSmallX);
  nt->SetBranchAddress("pos_corr_hodoSmallX", pos_corr_hodoSmallX, &b_pos_corr_hodoSmallX);
  nt->SetBranchAddress("nClusters_hodoSmallY", &nClusters_hodoSmallY, &b_nClusters_hodoSmallY);
  nt->SetBranchAddress("nFibres_hodoSmallY", nFibres_hodoSmallY, &b_nFibres_hodoSmallY);
  nt->SetBranchAddress("pos_hodoSmallY", pos_hodoSmallY, &b_pos_hodoSmallY);
  nt->SetBranchAddress("pos_corr_hodoSmallY", pos_corr_hodoSmallY, &b_pos_corr_hodoSmallY);

  nt->SetBranchAddress("nTDCHits", &nTDCHits, &b_nTDCHits);
  nt->SetBranchAddress("pos_2FibClust_hodoX1", &pos_2FibClust_hodoX1, &b_pos_2FibClust_hodoX1);
  nt->SetBranchAddress("pos_2FibClust_corr_hodoX1", &pos_2FibClust_corr_hodoX1, &b_pos_2FibClust_corr_hodoX1);
  nt->SetBranchAddress("pos_2FibClust_hodoY1", &pos_2FibClust_hodoY1, &b_pos_2FibClust_hodoY1);
  nt->SetBranchAddress("pos_2FibClust_corr_hodoY1", &pos_2FibClust_corr_hodoY1, &b_pos_2FibClust_corr_hodoY1);
  nt->SetBranchAddress("pos_2FibClust_hodoX2", &pos_2FibClust_hodoX2, &b_pos_2FibClust_hodoX2);
  nt->SetBranchAddress("pos_2FibClust_corr_hodoX2", &pos_2FibClust_corr_hodoX2, &b_pos_2FibClust_corr_hodoX2);
  nt->SetBranchAddress("pos_2FibClust_hodoY2", &pos_2FibClust_hodoY2, &b_pos_2FibClust_hodoY2);
  nt->SetBranchAddress("pos_2FibClust_corr_hodoY2", &pos_2FibClust_corr_hodoY2, &b_pos_2FibClust_corr_hodoY2);
  nt->SetBranchAddress("cluster_pos_hodoX1", &cluster_pos_hodoX1, &b_cluster_pos_hodoX1);
  nt->SetBranchAddress("cluster_pos_corr_hodoX1", &cluster_pos_corr_hodoX1, &b_cluster_pos_corr_hodoX1);
  nt->SetBranchAddress("cluster_pos_hodoX2", &cluster_pos_hodoX2, &b_cluster_pos_hodoX2);
  nt->SetBranchAddress("cluster_pos_corr_hodoX2", &cluster_pos_corr_hodoX2, &b_cluster_pos_corr_hodoX2);
  nt->SetBranchAddress("cluster_pos_hodoY1", &cluster_pos_hodoY1, &b_cluster_pos_hodoY1);
  nt->SetBranchAddress("cluster_pos_corr_hodoY1", &cluster_pos_corr_hodoY1, &b_cluster_pos_corr_hodoY1);
  nt->SetBranchAddress("cluster_pos_hodoY2", &cluster_pos_hodoY2, &b_cluster_pos_hodoY2);
  nt->SetBranchAddress("cluster_pos_corr_hodoY2", &cluster_pos_corr_hodoY2, &b_cluster_pos_corr_hodoY2);
  nt->SetBranchAddress("wc_x", &wc_x, &b_wc_x);
  nt->SetBranchAddress("wc_y", &wc_y, &b_wc_y);
  nt->SetBranchAddress("wc_x_corr", &wc_x_corr, &b_wc_x_corr);
  nt->SetBranchAddress("wc_y_corr", &wc_y_corr, &b_wc_y_corr);

}
