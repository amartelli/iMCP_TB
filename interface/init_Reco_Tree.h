#ifndef __init_Reco_Tree__
#define __init_Reco_Tree__

#include "TTree.h"
#include "TChain.h"
#include <vector>

// Declaration of leaf types 
extern int                    event;
extern float                 time_CF[8];
extern float                 time_CF_corr[8];
extern float                 time_CF30[8];
extern float                 time_OT[8];
extern float                 time_start[8];
extern float                 time_stop[8];
extern float                 time_start_1000[8];
extern float                 time_stop_1000[8];
extern float                 time_start_150[8];
extern float                 time_stop_150[8];
extern float                 time_start_200[8];
extern float                 time_stop_200[8];
extern float                 time_start_500[8];
extern float                 time_stop_500[8];
extern float                 time_start_300[8];
extern float                 time_stop_300[8];
extern float                 time_Max[8];
extern float                 amp_max[8];
extern float                 amp_max_corr[8];
extern float                 amp_max_time[8];
extern float                 charge[8];
extern float                 charge_corr[8];
extern float                 baseline[8];
extern int                   run_id;
extern int                   isPCOn[8];
extern int                   HV[8];
extern int                   HV2[8];
extern int                   isTrigger[8];
extern float                 X0;

extern int                   sci_front_adc;
extern int                   bgo_back_adc;

extern int           nClusters_hodoX1;
extern int           nFibres_hodoX1[64];
extern float         pos_hodoX1[64];
extern float         pos_corr_hodoX1[64];

extern int           nClusters_hodoY1;
extern int           nFibres_hodoY1[64];
extern float         pos_hodoY1[64];
extern float         pos_corr_hodoY1[64];

extern int           nClusters_hodoX2;
extern int           nFibres_hodoX2[64];
extern float         pos_hodoX2[64];
extern float         pos_corr_hodoX2[64];

extern int           nClusters_hodoY2;
extern int           nFibres_hodoY2[64];
extern float         pos_hodoY2[64];
extern float         pos_corr_hodoY2[64];

extern int           nClusters_hodoSmallX;
extern int           nFibres_hodoSmallX[4];
extern float         pos_hodoSmallX[4];
extern float         pos_corr_hodoSmallX[4];

extern int           nClusters_hodoSmallY;
extern int           nFibres_hodoSmallY[4];
extern float         pos_hodoSmallY[4];
extern float         pos_corr_hodoSmallY[4];


extern int           nTDCHits[4];
extern float         pos_2FibClust_hodoX1;
extern float         pos_2FibClust_corr_hodoX1;
extern float         pos_2FibClust_hodoY1;
extern float         pos_2FibClust_corr_hodoY1;
extern float         pos_2FibClust_hodoX2;
extern float         pos_2FibClust_corr_hodoX2;
extern float         pos_2FibClust_hodoY2;
extern float         pos_2FibClust_corr_hodoY2;
extern float         cluster_pos_hodoX1;
extern float         cluster_pos_corr_hodoX1;
extern float         cluster_pos_hodoX2;
extern float         cluster_pos_corr_hodoX2;
extern float         cluster_pos_hodoY1;
extern float         cluster_pos_corr_hodoY1;
extern float         cluster_pos_hodoY2;
extern float         cluster_pos_corr_hodoY2;
extern float         wc_x;
extern float         wc_y;
extern float         wc_x_corr;
extern float         wc_y_corr;

// List of branches                 
extern TBranch        *b_event;
extern TBranch        *b_time_CF;   //!                                            
extern TBranch        *b_time_CF_corr;   //!                                   
extern TBranch        *b_time_CF30;   //!                                            
extern TBranch        *b_time_OT;   //!     
extern TBranch        *b_time_start;                       
extern TBranch        *b_time_stop;       
extern TBranch        *b_time_start_1000;                       
extern TBranch        *b_time_stop_1000;       
extern TBranch        *b_time_start_150;                       
extern TBranch        *b_time_stop_150;       
extern TBranch        *b_time_start_200;                       
extern TBranch        *b_time_stop_200;       
extern TBranch        *b_time_start_500;                       
extern TBranch        *b_time_stop_500;       
extern TBranch        *b_time_start_300;                       
extern TBranch        *b_time_stop_300;       
extern TBranch        *b_time_Max;   //!                                   
extern TBranch        *b_amp_max;   //!                                        
extern TBranch        *b_amp_max_corr;   //!                                                          
extern TBranch        *b_amp_max_time;   //!                                                          
extern TBranch        *b_baseline;   //!                                      
extern TBranch        *b_charge;   //!                                     
extern TBranch        *b_charge_corr;   //!                              
extern TBranch        *b_run_id;   //!                              
extern TBranch        *b_isPCOn;   //!  
extern TBranch        *b_HV;   //!     
extern TBranch        *b_HV2;   //!     
extern TBranch        *b_isTrigger;
extern TBranch        *b_X0;
extern TBranch *b_sci_front_adc;
extern TBranch *b_bgo_back_adc;

extern TBranch        *b_nClusters_hodoX1;   //!              
extern TBranch        *b_nFibres_hodoX1;   //!                
extern TBranch        *b_pos_hodoX1;   //!                    
extern TBranch        *b_pos_corr_hodoX1;   //!               
extern TBranch        *b_nClusters_hodoY1;   //!              
extern TBranch        *b_nFibres_hodoY1;   //!                
extern TBranch        *b_pos_hodoY1;   //!                    
extern TBranch        *b_pos_corr_hodoY1;   //!               
extern TBranch        *b_nClusters_hodoX2;   //!              
extern TBranch        *b_nFibres_hodoX2;   //!                
extern TBranch        *b_pos_hodoX2;   //!                    
extern TBranch        *b_pos_corr_hodoX2;   //!               
extern TBranch        *b_nClusters_hodoY2;   //!              
extern TBranch        *b_nFibres_hodoY2;   //!                
extern TBranch        *b_pos_hodoY2;   //!                    
extern TBranch        *b_pos_corr_hodoY2;   //!               
extern TBranch        *b_nClusters_hodoSmallX;   //!          
extern TBranch        *b_nFibres_hodoSmallX;   //!            
extern TBranch        *b_pos_hodoSmallX;   //!                
extern TBranch        *b_pos_corr_hodoSmallX;   //!           
extern TBranch        *b_nClusters_hodoSmallY;   //!          
extern TBranch        *b_nFibres_hodoSmallY;   //!            
extern TBranch        *b_pos_hodoSmallY;   //!                
extern TBranch        *b_pos_corr_hodoSmallY;   //!           

extern TBranch        *b_nTDCHits;   //!                      
extern TBranch        *b_pos_2FibClust_hodoX1;   //!          
extern TBranch        *b_pos_2FibClust_corr_hodoX1;   //!     
extern TBranch        *b_pos_2FibClust_hodoY1;   //!          
extern TBranch        *b_pos_2FibClust_corr_hodoY1;   //!     
extern TBranch        *b_pos_2FibClust_hodoX2;   //!          
extern TBranch        *b_pos_2FibClust_corr_hodoX2;   //!     
extern TBranch        *b_pos_2FibClust_hodoY2;   //!          
extern TBranch        *b_pos_2FibClust_corr_hodoY2;   //!     
extern TBranch        *b_cluster_pos_hodoX1;   //!            
extern TBranch        *b_cluster_pos_corr_hodoX1;   //!       
extern TBranch        *b_cluster_pos_hodoX2;   //!            
extern TBranch        *b_cluster_pos_corr_hodoX2;   //!       
extern TBranch        *b_cluster_pos_hodoY1;   //!            
extern TBranch        *b_cluster_pos_corr_hodoY1;   //!       
extern TBranch        *b_cluster_pos_hodoY2;   //!            
extern TBranch        *b_cluster_pos_corr_hodoY2;   //!       
extern TBranch        *b_wc_x;   //!    
extern TBranch        *b_wc_y;   //! 
extern TBranch        *b_wc_x_corr;   //!   
extern TBranch        *b_wc_y_corr;   //! 



void InitRecoTree(TTree* nt);

void init();

void SetOutTree(TTree* outTree);

#endif
