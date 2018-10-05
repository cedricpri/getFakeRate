//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
//
// root -l -b -q getYields.C
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void getYields() {

  TFile* data  = new TFile ("results/hadd_data.root", "read");
  TFile* wjets = new TFile ("results/hadd_wjets.root", "read");
  TFile* zjets = new TFile ("results/hadd_zjets.root", "read");

  //Muons
  //----------------------------------------------------------------------------

  //Muons loose
  TH1D* h_data_Muon_loose_lowpt  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_loose_lowpt_25GeV");
  TH1D* h_data_Muon_loose_lowpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_loose_lowpt_weighted_25GeV");
  TH1D* h_data_Muon_loose_hight  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_loose_highpt_25GeV");
  TH1D* h_data_Muon_loose_highpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_loose_highpt_weighted_25GeV");

  TH1D* h_wjets_Muon_loose_lowpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_loose_lowpt_25GeV");
  TH1D* h_wjets_Muon_loose_lowpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_loose_lowpt_weighted_25GeV");
  TH1D* h_wjets_Muon_loose_hight  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_loose_highpt_25GeV");
  TH1D* h_wjets_Muon_loose_highpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_loose_highpt_weighted_25GeV");

  TH1D* h_zjets_Muon_loose_lowpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_loose_lowpt_25GeV");
  TH1D* h_zjets_Muon_loose_lowpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_loose_lowpt_weighted_25GeV");
  TH1D* h_zjets_Muon_loose_hight  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_loose_highpt_25GeV");
  TH1D* h_zjets_Muon_loose_highpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_loose_highpt_weighted_25GeV");

  //Muons tight
  TH1D* h_data_Muon_tight_lowpt  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_tight_lowpt_25GeV");
  TH1D* h_data_Muon_tight_lowpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_tight_lowpt_weighted_25GeV");
  TH1D* h_data_Muon_tight_hight  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_tight_highpt_25GeV");
  TH1D* h_data_Muon_tight_highpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_tight_highpt_weighted_25GeV");

  TH1D* h_wjets_Muon_tight_lowpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_tight_lowpt_25GeV");
  TH1D* h_wjets_Muon_tight_lowpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_tight_lowpt_weighted_25GeV");
  TH1D* h_wjets_Muon_tight_hight  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_tight_highpt_25GeV");
  TH1D* h_wjets_Muon_tight_highpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_tight_highpt_weighted_25GeV");

  TH1D* h_zjets_Muon_tight_lowpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_tight_lowpt_25GeV");
  TH1D* h_zjets_Muon_tight_lowpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_tight_lowpt_weighted_25GeV");
  TH1D* h_zjets_Muon_tight_hight  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_tight_highpt_25GeV");
  TH1D* h_zjets_Muon_tight_highpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_tight_highpt_weighted_25GeV");

  //Electrons
  //----------------------------------------------------------------------------

  //Electrons loose
  TH1D* h_data_Ele_loose_lowpt  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_loose_lowpt_25GeV");
  TH1D* h_data_Ele_loose_lowpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_loose_lowpt_weighted_25GeV");
  TH1D* h_data_Ele_loose_hight  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_loose_highpt_25GeV");
  TH1D* h_data_Ele_loose_highpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_loose_highpt_weighted_25GeV");

  TH1D* h_wjets_Ele_loose_lowpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_loose_lowpt_25GeV");
  TH1D* h_wjets_Ele_loose_lowpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_loose_lowpt_weighted_25GeV");
  TH1D* h_wjets_Ele_loose_hight  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_loose_highpt_25GeV");
  TH1D* h_wjets_Ele_loose_highpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_loose_highpt_weighted_25GeV");

  TH1D* h_zjets_Ele_loose_lowpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_loose_lowpt_25GeV");
  TH1D* h_zjets_Ele_loose_lowpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_loose_lowpt_weighted_25GeV");
  TH1D* h_zjets_Ele_loose_hight  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_loose_highpt_25GeV");
  TH1D* h_zjets_Ele_loose_highpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_loose_highpt_weighted_25GeV");

  //Electrons tight
  TH1D* h_data_Ele_tight_lowpt  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_tight_lowpt_25GeV");
  TH1D* h_data_Ele_tight_lowpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_tight_lowpt_weighted_25GeV");
  TH1D* h_data_Ele_tight_hight  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_tight_highpt_25GeV");
  TH1D* h_data_Ele_tight_highpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_tight_highpt_weighted_25GeV");

  TH1D* h_wjets_Ele_tight_lowpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_tight_lowpt_25GeV");
  TH1D* h_wjets_Ele_tight_lowpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_tight_lowpt_weighted_25GeV");
  TH1D* h_wjets_Ele_tight_hight  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_tight_highpt_25GeV");
  TH1D* h_wjets_Ele_tight_highpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_tight_highpt_weighted_25GeV");

  TH1D* h_zjets_Ele_tight_lowpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_tight_lowpt_25GeV");
  TH1D* h_zjets_Ele_tight_lowpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_tight_lowpt_weighted_25GeV");
  TH1D* h_zjets_Ele_tight_hight  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_tight_highpt_25GeV");
  TH1D* h_zjets_Ele_tight_highpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_tight_highpt_weighted_25GeV");
  
  //Print low pt trigger table
  //----------------------------------------------------------------------------

  printf("\n \n ==========================================================================");
  printf("\n ================================ LOW PT ==================================");
  printf("\n ========================================================================== \n");
  printf("      * HLT_Mu8_TrkIsoVVL (2.90/pb) \n");
  printf("      * HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 (27.70/pb) \n");
  printf("========================================================================== \n");

  printf("                   Data with (w/o) weight               W+Jets                       Z+Jets \n");
  printf("Loose muons          %8.1f (%8.1f)            %8.1f (%8.1f)              %8.1f (%8.1f) \n", h_data_Muon_loose_lowpt->Integral(-1, -1), h_data_Muon_loose_lowpt_weighted->Integral(-1, -1), h_wjets_Muon_loose_lowpt->Integral(-1, -1), h_wjets_Muon_loose_lowpt_weighted->Integral(-1, -1), h_zjets_Muon_loose_lowpt->Integral(-1, -1), h_zjets_Muon_loose_lowpt_weighted->Integral(-1, -1));
  printf("Tight muons          %8.1f (%8.1f)            %8.1f (%8.1f)              %8.1f (%8.1f) \n", h_data_Muon_tight_lowpt->Integral(-1, -1), h_data_Muon_tight_lowpt_weighted->Integral(-1, -1), h_wjets_Muon_tight_lowpt->Integral(-1, -1), h_wjets_Muon_tight_lowpt_weighted->Integral(-1, -1), h_zjets_Muon_tight_lowpt->Integral(-1, -1), h_zjets_Muon_tight_lowpt_weighted->Integral(-1, -1));
  printf("Loose electrons      %8.1f (%8.1f)            %8.1f (%8.1f)              %8.1f (%8.1f) \n", h_data_Ele_loose_lowpt->Integral(-1, -1), h_data_Ele_loose_lowpt_weighted->Integral(-1, -1), h_wjets_Ele_loose_lowpt->Integral(-1, -1), h_wjets_Ele_loose_lowpt_weighted->Integral(-1, -1), h_zjets_Ele_loose_lowpt->Integral(-1, -1), h_zjets_Ele_loose_lowpt_weighted->Integral(-1, -1));
  printf("Tight electrons      %8.1f (%8.1f)            %8.1f (%8.1f)              %8.1f (%8.1f) \n", h_data_Ele_tight_lowpt->Integral(-1, -1), h_data_Ele_tight_lowpt_weighted->Integral(-1, -1), h_wjets_Ele_tight_lowpt->Integral(-1, -1), h_wjets_Ele_tight_lowpt_weighted->Integral(-1, -1), h_zjets_Ele_tight_lowpt->Integral(-1, -1), h_zjets_Ele_tight_lowpt_weighted->Integral(-1, -1));

  printf("\n");

  //Print high pt trigger table
  //----------------------------------------------------------------------------

  printf("\n \n ==========================================================================");
  printf("\n ================================ HIGH PT =================================");
  printf("\n ========================================================================== \n");
  printf("      * HLT_Mu17_TrkIsoVVL (65.94/pb) \n");
  printf("      * HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 (45.47/pb) \n");
  printf("========================================================================== \n");
  printf("                   Data with (w/o) weight              W+Jets                       Z+Jets \n");
  printf("Loose muons          %8.1f (%8.1f)           %8.1f (%8.1f)             %8.1f (%8.1f) \n", h_data_Muon_loose_lowpt->Integral(-1, -1), h_data_Muon_loose_lowpt_weighted->Integral(-1, -1), h_wjets_Muon_loose_lowpt->Integral(-1, -1), h_wjets_Muon_loose_lowpt_weighted->Integral(-1, -1), h_zjets_Muon_loose_lowpt->Integral(-1, -1), h_zjets_Muon_loose_lowpt_weighted->Integral(-1, -1));
  printf("Tight muons          %8.1f (%8.1f)           %8.1f (%8.1f)             %8.1f (%8.1f) \n", h_data_Muon_tight_lowpt->Integral(-1, -1), h_data_Muon_tight_lowpt_weighted->Integral(-1, -1), h_wjets_Muon_tight_lowpt->Integral(-1, -1), h_wjets_Muon_tight_lowpt_weighted->Integral(-1, -1), h_zjets_Muon_tight_lowpt->Integral(-1, -1), h_zjets_Muon_tight_lowpt_weighted->Integral(-1, -1));
  printf("Loose electrons      %8.1f (%8.1f)           %8.1f (%8.1f)             %8.1f (%8.1f) \n", h_data_Ele_loose_lowpt->Integral(-1, -1), h_data_Ele_loose_lowpt_weighted->Integral(-1, -1), h_wjets_Ele_loose_lowpt->Integral(-1, -1), h_wjets_Ele_loose_lowpt_weighted->Integral(-1, -1), h_zjets_Ele_loose_lowpt->Integral(-1, -1), h_zjets_Ele_loose_lowpt_weighted->Integral(-1, -1));
  printf("Tight electrons      %8.1f (%8.1f)           %8.1f (%8.1f)             %8.1f (%8.1f) \n", h_data_Ele_tight_lowpt->Integral(-1, -1), h_data_Ele_tight_lowpt_weighted->Integral(-1, -1), h_wjets_Ele_tight_lowpt->Integral(-1, -1), h_wjets_Ele_tight_lowpt_weighted->Integral(-1, -1), h_zjets_Ele_tight_lowpt->Integral(-1, -1), h_zjets_Ele_tight_lowpt_weighted->Integral(-1, -1));

  printf("\n \n");

}
