#include "../interface/init_Reco_Tree.h"

void init()
{
}

void SetOutTree(TTree* outTree)
{
  //---standard analysis branches
  outTree->Branch("time_CF",&time_CF,"time_CF[10]/F");
  outTree->Branch("time_CF_corr",&time_CF_corr,"time_CF_corr[10]/F");
  outTree->Branch("time_OT",&time_OT,"time_OT[10]/F");
  outTree->Branch("time_Max",&time_Max,"time_Max[10]/F");
  outTree->Branch("amp_max",&amp_max,"amp_max[10]/F");
  outTree->Branch("amp_max_corr",&amp_max_corr,"amp_max_corr[10]/F");
  outTree->Branch("charge",&charge,"charge[10]/F"); 
  outTree->Branch("charge_corr",&charge_corr,"charge_corr[10]/F");
  outTree->Branch("baseline",&baseline,"baseline[10]/F");
  
  //---hodoscope branches       
  outTree->Branch("fibreX",&fibreX,"fibreX[8]/I");
  outTree->Branch("fibreY",&fibreY,"fibreY[8]/I");
  
  //---global branches    
  outTree->Branch("sci_front_adc",&sci_front_adc,"sci_front_adc/I");
  outTree->Branch("run_id",&run_id,"run_id/I");

  //---additional branches
  outTree->Branch("isPCOn",&isPCOn,"isPCOn[10]/I");
  outTree->Branch("HV",&HV,"HV[10]/I");
  outTree->Branch("isTrigger",&isTrigger,"isTrigger[10]/I");
  outTree->Branch("X0",&X0,"X0/F");

  outTree->Branch("tdcX",&tdcX,"tdcX/F");
  outTree->Branch("tdcY",&tdcY,"tdcY/F");
  //    outTree->Branch("MCPName"+nameMCP->at(Ch_1),&baseline_Ch1,"baseline_"+nameMCP->at(Ch_1)+"/F");          
}

   
void InitRecoTree(TTree* nt)
{
  nt->SetBranchAddress("time_CF", &time_CF, &b_time_CF);
  nt->SetBranchAddress("time_CF_corr", &time_CF_corr, &b_time_CF_corr);
  nt->SetBranchAddress("time_OT", &time_OT, &b_time_OT);
  nt->SetBranchAddress("time_Max", &time_Max, &b_time_Max);
  nt->SetBranchAddress("amp_max", &amp_max, &b_amp_max);
  nt->SetBranchAddress("amp_max_corr", &amp_max_corr, &b_amp_max_corr);
  nt->SetBranchAddress("charge", &charge, &b_charge);
  nt->SetBranchAddress("charge_corr", &charge_corr, &b_charge_corr);
  nt->SetBranchAddress("baseline", &baseline, &b_baseline);
  nt->SetBranchAddress("fibreX", &fibreX, &b_fibreX);
  nt->SetBranchAddress("fibreY", &fibreY, &b_fibreY);
  nt->SetBranchAddress("sci_front_adc", &sci_front_adc, &b_sci_front_adc);
  nt->SetBranchAddress("run_id", &run_id, &b_run_id);
  nt->SetBranchAddress("isPCOn", &isPCOn, &b_isPCOn);
  nt->SetBranchAddress("HV", &HV, &b_HV);
  nt->SetBranchAddress("isTrigger", &isTrigger, &b_isTrigger);
  nt->SetBranchAddress("X0", &X0, &b_X0);
  nt->SetBranchAddress("tdcX", &tdcX, &b_tdcX);
  nt->SetBranchAddress("tdcY", &tdcY, &b_tdcY);
}
