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
  TH1D* h_data_Muon_loose_highpt  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_loose_highpt_25GeV");
  TH1D* h_data_Muon_loose_highpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_loose_highpt_weighted_25GeV");

  TH1D* h_wjets_Muon_loose_lowpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_loose_lowpt_25GeV");
  TH1D* h_wjets_Muon_loose_lowpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_loose_lowpt_weighted_25GeV");
  TH1D* h_wjets_Muon_loose_highpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_loose_highpt_25GeV");
  TH1D* h_wjets_Muon_loose_highpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_loose_highpt_weighted_25GeV");

  TH1D* h_zjets_Muon_loose_lowpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_loose_lowpt_25GeV");
  TH1D* h_zjets_Muon_loose_lowpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_loose_lowpt_weighted_25GeV");
  TH1D* h_zjets_Muon_loose_highpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_loose_highpt_25GeV");
  TH1D* h_zjets_Muon_loose_highpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_loose_highpt_weighted_25GeV");

  //Muons tight
  TH1D* h_data_Muon_tight_lowpt  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_tight_lowpt_25GeV");
  TH1D* h_data_Muon_tight_lowpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_tight_lowpt_weighted_25GeV");
  TH1D* h_data_Muon_tight_highpt  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_tight_highpt_25GeV");
  TH1D* h_data_Muon_tight_highpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Muon_tight_highpt_weighted_25GeV");

  TH1D* h_wjets_Muon_tight_lowpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_tight_lowpt_25GeV");
  TH1D* h_wjets_Muon_tight_lowpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_tight_lowpt_weighted_25GeV");
  TH1D* h_wjets_Muon_tight_highpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_tight_highpt_25GeV");
  TH1D* h_wjets_Muon_tight_highpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Muon_tight_highpt_weighted_25GeV");

  TH1D* h_zjets_Muon_tight_lowpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_tight_lowpt_25GeV");
  TH1D* h_zjets_Muon_tight_lowpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_tight_lowpt_weighted_25GeV");
  TH1D* h_zjets_Muon_tight_highpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_tight_highpt_25GeV");
  TH1D* h_zjets_Muon_tight_highpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Muon_tight_highpt_weighted_25GeV");

  //Electrons
  //----------------------------------------------------------------------------

  //Electrons loose
  TH1D* h_data_Ele_loose_lowpt  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_loose_lowpt_25GeV");
  TH1D* h_data_Ele_loose_lowpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_loose_lowpt_weighted_25GeV");
  TH1D* h_data_Ele_loose_highpt  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_loose_highpt_25GeV");
  TH1D* h_data_Ele_loose_highpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_loose_highpt_weighted_25GeV");

  TH1D* h_wjets_Ele_loose_lowpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_loose_lowpt_25GeV");
  TH1D* h_wjets_Ele_loose_lowpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_loose_lowpt_weighted_25GeV");
  TH1D* h_wjets_Ele_loose_highpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_loose_highpt_25GeV");
  TH1D* h_wjets_Ele_loose_highpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_loose_highpt_weighted_25GeV");

  TH1D* h_zjets_Ele_loose_lowpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_loose_lowpt_25GeV");
  TH1D* h_zjets_Ele_loose_lowpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_loose_lowpt_weighted_25GeV");
  TH1D* h_zjets_Ele_loose_highpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_loose_highpt_25GeV");
  TH1D* h_zjets_Ele_loose_highpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_loose_highpt_weighted_25GeV");

  //Electrons tight
  TH1D* h_data_Ele_tight_lowpt  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_tight_lowpt_25GeV");
  TH1D* h_data_Ele_tight_lowpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_tight_lowpt_weighted_25GeV");
  TH1D* h_data_Ele_tight_highpt  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_tight_highpt_25GeV");
  TH1D* h_data_Ele_tight_highpt_weighted  = (TH1D*)data ->Get("FR/00_QCD/h_Ele_tight_highpt_weighted_25GeV");

  TH1D* h_wjets_Ele_tight_lowpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_tight_lowpt_25GeV");
  TH1D* h_wjets_Ele_tight_lowpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_tight_lowpt_weighted_25GeV");
  TH1D* h_wjets_Ele_tight_highpt  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_tight_highpt_25GeV");
  TH1D* h_wjets_Ele_tight_highpt_weighted  = (TH1D*)wjets ->Get("FR/00_QCD/h_Ele_tight_highpt_weighted_25GeV");

  TH1D* h_zjets_Ele_tight_lowpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_tight_lowpt_25GeV");
  TH1D* h_zjets_Ele_tight_lowpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_tight_lowpt_weighted_25GeV");
  TH1D* h_zjets_Ele_tight_highpt  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_tight_highpt_25GeV");
  TH1D* h_zjets_Ele_tight_highpt_weighted  = (TH1D*)zjets ->Get("FR/00_QCD/h_Ele_tight_highpt_weighted_25GeV");
  
  printf("\n \n ==========================================================================");
  printf("\n ================================ YIELDS ==================================");
  printf("\n ========================================================================== \n");
  printf("      * HLT_Mu8_TrkIsoVVL (2.90/pb) \n");
  printf("      * HLT_Mu17_TrkIsoVVL (65.94/pb) \n");
  printf("      * HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 (27.70/pb) \n");
  printf("      * HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 (45.47/pb) \n");
  printf("========================================================================== \n");

  printf("\n");

  printf("& & Data & \\multicolumn{3}{c|}{W+jets} & \\multicolumn{3}{c}{Z+jets} \\\\ \n");
  printf("& Trigger & & W/o weight & With & Ratio & W/o weight & With & Ratio \\\\ \n");
  printf("\\hline \n");

  printf("\\multirow{2}{*}{Loose muons}& low $p_T$ & %.0f & %.1f & %.1f & %.3f & %.1f & %.1f & %.3f \\\\ \n", h_data_Muon_loose_lowpt->Integral(-1, -1), h_wjets_Muon_loose_lowpt->Integral(-1, -1), h_wjets_Muon_loose_lowpt_weighted->Integral(-1, -1), (h_wjets_Muon_loose_lowpt_weighted->Integral(-1, -1)/h_wjets_Muon_loose_lowpt->Integral(-1, -1)), h_zjets_Muon_loose_lowpt->Integral(-1, -1), h_zjets_Muon_loose_lowpt_weighted->Integral(-1, -1), (h_zjets_Muon_loose_lowpt_weighted->Integral(-1, -1)/h_zjets_Muon_loose_lowpt->Integral(-1, -1)));
  printf("& high $p_T$ &  %.0f & %.1f & %.1f & %.3f & %.1f & %.1f & %.3f \\\\ \n", h_data_Muon_loose_highpt->Integral(-1, -1), h_wjets_Muon_loose_highpt->Integral(-1, -1), h_wjets_Muon_loose_highpt_weighted->Integral(-1, -1), (h_wjets_Muon_loose_highpt_weighted->Integral(-1, -1)/h_wjets_Muon_loose_highpt->Integral(-1, -1)), h_zjets_Muon_loose_highpt->Integral(-1, -1), h_zjets_Muon_loose_highpt_weighted->Integral(-1, -1), (h_zjets_Muon_loose_highpt_weighted->Integral(-1, -1)/h_zjets_Muon_loose_highpt->Integral(-1, -1)));
  printf("\\hline \n");

  printf("\\multirow{2}{*}{Tight muons}& low $p_T$ & %.0f & %.1f & %.1f & %.3f & %.1f & %.1f & %.3f \\\\ \n", h_data_Muon_tight_lowpt->Integral(-1, -1), h_wjets_Muon_tight_lowpt->Integral(-1, -1), h_wjets_Muon_tight_lowpt_weighted->Integral(-1, -1), (h_wjets_Muon_tight_lowpt_weighted->Integral(-1, -1)/h_wjets_Muon_tight_lowpt->Integral(-1, -1)), h_zjets_Muon_tight_lowpt->Integral(-1, -1), h_zjets_Muon_tight_lowpt_weighted->Integral(-1, -1), (h_zjets_Muon_tight_lowpt_weighted->Integral(-1, -1)/h_zjets_Muon_tight_lowpt->Integral(-1, -1)));
  printf("& high $p_T$ &  %.0f & %.1f & %.1f & %.3f & %.1f & %.1f & %.3f \\\\ \n", h_data_Muon_tight_highpt->Integral(-1, -1), h_wjets_Muon_tight_highpt->Integral(-1, -1), h_wjets_Muon_tight_highpt_weighted->Integral(-1, -1), (h_wjets_Muon_tight_highpt_weighted->Integral(-1, -1)/h_wjets_Muon_tight_highpt->Integral(-1, -1)), h_zjets_Muon_tight_highpt->Integral(-1, -1), h_zjets_Muon_tight_highpt_weighted->Integral(-1, -1), (h_zjets_Muon_tight_highpt_weighted->Integral(-1, -1)/h_zjets_Muon_tight_highpt->Integral(-1, -1)));
  printf("\\hline \n");

  printf("\\multirow{2}{*}{Loose Electrons}& low $p_T$ & %.0f & %.1f & %.1f & %.3f & %.1f & %.1f & %.3f \\\\ \n", h_data_Ele_loose_lowpt->Integral(-1, -1), h_wjets_Ele_loose_lowpt->Integral(-1, -1), h_wjets_Ele_loose_lowpt_weighted->Integral(-1, -1), (h_wjets_Ele_loose_lowpt_weighted->Integral(-1, -1)/h_wjets_Ele_loose_lowpt->Integral(-1, -1)), h_zjets_Ele_loose_lowpt->Integral(-1, -1), h_zjets_Ele_loose_lowpt_weighted->Integral(-1, -1), (h_zjets_Ele_loose_lowpt_weighted->Integral(-1, -1)/h_zjets_Ele_loose_lowpt->Integral(-1, -1)));
  printf("& high $p_T$ &  %.0f & %.1f & %.1f & %.3f & %.1f & %.1f & %.3f \\\\ \n", h_data_Ele_loose_highpt->Integral(-1, -1), h_wjets_Ele_loose_highpt->Integral(-1, -1), h_wjets_Ele_loose_highpt_weighted->Integral(-1, -1), (h_wjets_Ele_loose_highpt_weighted->Integral(-1, -1)/h_wjets_Ele_loose_highpt->Integral(-1, -1)), h_zjets_Ele_loose_highpt->Integral(-1, -1), h_zjets_Ele_loose_highpt_weighted->Integral(-1, -1), (h_zjets_Ele_loose_highpt_weighted->Integral(-1, -1)/h_zjets_Ele_loose_highpt->Integral(-1, -1)));
  printf("\\hline \n");

  printf("\\multirow{2}{*}{Tight electrons}& low $p_T$ & %.0f & %.1f & %.1f & %.3f & %.1f & %.1f & %.3f \\\\ \n", h_data_Ele_tight_lowpt->Integral(-1, -1), h_wjets_Ele_tight_lowpt->Integral(-1, -1), h_wjets_Ele_tight_lowpt_weighted->Integral(-1, -1), (h_wjets_Ele_tight_lowpt_weighted->Integral(-1, -1)/h_wjets_Ele_tight_lowpt->Integral(-1, -1)), h_zjets_Ele_tight_lowpt->Integral(-1, -1), h_zjets_Ele_tight_lowpt_weighted->Integral(-1, -1), (h_zjets_Ele_tight_lowpt_weighted->Integral(-1, -1)/h_zjets_Ele_tight_lowpt->Integral(-1, -1)));
  printf("& high $p_T$ &  %.0f & %.1f & %.1f & %.3f & %.1f & %.1f & %.3f \\\\ \n", h_data_Ele_tight_highpt->Integral(-1, -1), h_wjets_Ele_tight_highpt->Integral(-1, -1), h_wjets_Ele_tight_highpt_weighted->Integral(-1, -1), (h_wjets_Ele_tight_highpt_weighted->Integral(-1, -1)/h_wjets_Ele_tight_highpt->Integral(-1, -1)), h_zjets_Ele_tight_highpt->Integral(-1, -1), h_zjets_Ele_tight_highpt_weighted->Integral(-1, -1), (h_zjets_Ele_tight_highpt_weighted->Integral(-1, -1)/h_zjets_Ele_tight_highpt->Integral(-1, -1)));

  printf("\n \n");

}
