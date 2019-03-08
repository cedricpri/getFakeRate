#define nanoFakes_cxx


#include "nanoFakes.h"
#include <TStyle.h>


// Data members
//------------------------------------------------------------------------------
string         option;
TString        filename;
TString        year;

TFile*         root_output;

bool           ismc;
int            channel;
float          inputJetEt;
float          leptonPtMin;
float          leptonEtaMax;
float          event_weight;
float          l2tight_weight;
float          deltaR;

TLorentzVector tlv1;
TLorentzVector tlv2;

int            jetIndex;
int            leptonIndex;

int            counter    = 0;
int            nentries   = 0;
int            maxentries = -1;


//------------------------------------------------------------------------------
// Begin
//------------------------------------------------------------------------------
void nanoFakes::Begin(TTree*)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  option = GetOption();

  printf("\n");

  printf("   option: %s\n", option.c_str());

  year     = option.substr(0,4);
  filename = option.erase(0,4);

  printf("     year: %s\n", year.Data());
  printf(" filename: %s\n", filename.Data());

  printf("\n");
  
  if (!filename.Contains("Run201")) {

    baseW            = {fReader, "baseW"};
    Xsec             = {fReader, "Xsec"};
    puWeight         = {fReader, "puWeight"};
    Generator_weight = {fReader, "Generator_weight"};
  }

  ismc = (filename.Contains("Run201")) ? false : true;

  root_output = new TFile("results/" + filename + ".root", "recreate");

  TH1::SetDefaultSumw2();


  // FR regions
  //----------------------------------------------------------------------------
  for (int i=0; i<ncutFR; i++) {
     
    TString directory = scutFR[i];

    root_output->cd();

    gDirectory->mkdir(directory);

    root_output->cd(directory);
   
    for (int j=0; j<njetet; j++) {
       
      TString muonsuffix = Form("_%.0fGeV", muonjetet[j]);
      TString elesuffix  = Form("_%.0fGeV", elejetet[j]);

       
      // Fake rate histograms
      //------------------------------------------------------------------------
      h_Muon_loose_pt_eta_bin[i][j] = new TH2D("h_Muon_loose_pt_eta_bin" + muonsuffix, "", nptbin, ptbins, netabin, etabins);
      h_Muon_tight_pt_eta_bin[i][j] = new TH2D("h_Muon_tight_pt_eta_bin" + muonsuffix, "", nptbin, ptbins, netabin, etabins);
      h_Ele_loose_pt_eta_bin [i][j] = new TH2D("h_Ele_loose_pt_eta_bin"  + elesuffix,  "", nptbin, ptbins, netabin, etabins);
      h_Ele_tight_pt_eta_bin [i][j] = new TH2D("h_Ele_tight_pt_eta_bin"  + elesuffix,  "", nptbin, ptbins, netabin, etabins);
       
      h_Muon_loose_pt_bin[i][j] = new TH1D("h_Muon_loose_pt_bin" + muonsuffix, "", nptbin, ptbins);
      h_Muon_tight_pt_bin[i][j] = new TH1D("h_Muon_tight_pt_bin" + muonsuffix, "", nptbin, ptbins);
      h_Ele_loose_pt_bin [i][j] = new TH1D("h_Ele_loose_pt_bin"  + elesuffix,  "", nptbin, ptbins);
      h_Ele_tight_pt_bin [i][j] = new TH1D("h_Ele_tight_pt_bin"  + elesuffix,  "", nptbin, ptbins);
       
      h_Muon_loose_eta_bin[i][j] = new TH1D("h_Muon_loose_eta_bin" + muonsuffix, "", netabin, etabins);
      h_Muon_tight_eta_bin[i][j] = new TH1D("h_Muon_tight_eta_bin" + muonsuffix, "", netabin, etabins);
      h_Ele_loose_eta_bin [i][j] = new TH1D("h_Ele_loose_eta_bin"  + elesuffix,  "", netabin, etabins);
      h_Ele_tight_eta_bin [i][j] = new TH1D("h_Ele_tight_eta_bin"  + elesuffix,  "", netabin, etabins);

      
      // Effective luminosity estimation histograms
      //------------------------------------------------------------------------
      h_Muon_loose_m2l[i][j] = new TH1D("h_Muon_loose_m2l" + muonsuffix, "", 1000, 0, 200);
      h_Muon_tight_m2l[i][j] = new TH1D("h_Muon_tight_m2l" + muonsuffix, "", 1000, 0, 200);
      h_Ele_loose_m2l [i][j] = new TH1D("h_Ele_loose_m2l"  + elesuffix,  "", 1000, 0, 200);
      h_Ele_tight_m2l [i][j] = new TH1D("h_Ele_tight_m2l"  + elesuffix,  "", 1000, 0, 200);
          
      h_Muon_loose_pt_m2l[i][j] = new TH2D("h_Muon_loose_pt_m2l" + muonsuffix, "", 200, 0, 200, nptbin, ptbins);
      h_Muon_tight_pt_m2l[i][j] = new TH2D("h_Muon_tight_pt_m2l" + muonsuffix, "", 200, 0, 200, nptbin, ptbins);
      h_Ele_loose_pt_m2l [i][j] = new TH2D("h_Ele_loose_pt_m2l"  + elesuffix,  "", 200, 0, 200, nptbin, ptbins);
      h_Ele_tight_pt_m2l [i][j] = new TH2D("h_Ele_tight_pt_m2l"  + elesuffix,  "", 200, 0, 200, nptbin, ptbins);


      // Yields histograms for getYields.C
      //------------------------------------------------------------------------
      h_Muon_loose_lowpt [i][j] = new TH1D("h_Muon_loose_lowpt"  + muonsuffix, "", nptbin, ptbins);
      h_Muon_loose_highpt[i][j] = new TH1D("h_Muon_loose_highpt" + muonsuffix, "", nptbin, ptbins);
      h_Muon_tight_lowpt [i][j] = new TH1D("h_Muon_tight_lowpt"  + muonsuffix, "", nptbin, ptbins);
      h_Muon_tight_highpt[i][j] = new TH1D("h_Muon_tight_highpt" + muonsuffix, "", nptbin, ptbins);
      
      h_Muon_loose_lowpt_weighted [i][j] = new TH1D("h_Muon_loose_lowpt_weighted"  + muonsuffix, "", nptbin, ptbins);
      h_Muon_loose_highpt_weighted[i][j] = new TH1D("h_Muon_loose_highpt_weighted" + muonsuffix, "", nptbin, ptbins);
      h_Muon_tight_lowpt_weighted [i][j] = new TH1D("h_Muon_tight_lowpt_weighted"  + muonsuffix, "", nptbin, ptbins);
      h_Muon_tight_highpt_weighted[i][j] = new TH1D("h_Muon_tight_highpt_weighted" + muonsuffix, "", nptbin, ptbins);
      
      h_Ele_loose_lowpt [i][j] = new TH1D("h_Ele_loose_lowpt"  + muonsuffix, "", nptbin, ptbins);
      h_Ele_loose_highpt[i][j] = new TH1D("h_Ele_loose_highpt" + muonsuffix, "", nptbin, ptbins);
      h_Ele_tight_lowpt [i][j] = new TH1D("h_Ele_tight_lowpt"  + muonsuffix, "", nptbin, ptbins);
      h_Ele_tight_highpt[i][j] = new TH1D("h_Ele_tight_highpt" + muonsuffix, "", nptbin, ptbins);
      
      h_Ele_loose_lowpt_weighted [i][j] = new TH1D("h_Ele_loose_lowpt_weighted"  + muonsuffix, "", nptbin, ptbins);
      h_Ele_loose_highpt_weighted[i][j] = new TH1D("h_Ele_loose_highpt_weighted" + muonsuffix, "", nptbin, ptbins);
      h_Ele_tight_lowpt_weighted [i][j] = new TH1D("h_Ele_tight_lowpt_weighted"  + muonsuffix, "", nptbin, ptbins);
      h_Ele_tight_highpt_weighted[i][j] = new TH1D("h_Ele_tight_highpt_weighted" + muonsuffix, "", nptbin, ptbins);
    }
  }


  // PR regions
  //----------------------------------------------------------------------------
  for (int i=0; i<ncutPR; i++) {
     
    TString directory = scutPR[i];

    root_output->cd();

    gDirectory->mkdir(directory);

    root_output->cd(directory);

    
    // Prompt rate histograms
    //--------------------------------------------------------------------------
    h_Muon_loose_pt_eta_PR[i] = new TH2D("h_Muon_loose_pt_eta_PR", "", nptbin, ptbins, netabin, etabins);
    h_Muon_tight_pt_eta_PR[i] = new TH2D("h_Muon_tight_pt_eta_PR", "", nptbin, ptbins, netabin, etabins);
    h_Ele_loose_pt_eta_PR[i]  = new TH2D("h_Ele_loose_pt_eta_PR",  "", nptbin, ptbins, netabin, etabins);
    h_Ele_tight_pt_eta_PR[i]  = new TH2D("h_Ele_tight_pt_eta_PR",  "", nptbin, ptbins, netabin, etabins);
     
    h_Muon_loose_pt_PR[i] = new TH1D("h_Muon_loose_pt_PR", "", nptbin, ptbins);
    h_Muon_tight_pt_PR[i] = new TH1D("h_Muon_tight_pt_PR", "", nptbin, ptbins);
    h_Ele_loose_pt_PR[i]  = new TH1D("h_Ele_loose_pt_PR",  "", nptbin, ptbins);
    h_Ele_tight_pt_PR[i]  = new TH1D("h_Ele_tight_pt_PR",  "", nptbin, ptbins);
     
    h_Muon_loose_eta_PR[i] = new TH1D("h_Muon_loose_eta_PR", "", netabin, etabins);
    h_Muon_tight_eta_PR[i] = new TH1D("h_Muon_tight_eta_PR", "", netabin, etabins);
    h_Ele_loose_eta_PR[i]  = new TH1D("h_Ele_loose_eta_PR",  "", netabin, etabins);
    h_Ele_tight_eta_PR[i]  = new TH1D("h_Ele_tight_eta_PR",  "", netabin, etabins);
   }
}


//------------------------------------------------------------------------------
// SlaveBegin
//------------------------------------------------------------------------------
void nanoFakes::SlaveBegin(TTree*)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
}


Bool_t nanoFakes::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetEntry(entry);  

  if (entry > maxentries && maxentries > -1) return 0;
  if (entry%20000 == 0) printf(" Entry number %lld \n", entry); 	 

  nentries++;
 
  channel = (abs(Lepton_pdgId[0]) == 11) ? e : m;

  leptonPtMin  = (channel == e) ?  13 :  10;  // [GeV]
  leptonEtaMax = (channel == e) ? 2.5 : 2.4;  // [GeV]

  if (Lepton_pt[0] < leptonPtMin) return 0;
  if (fabs(Lepton_eta[0]) > leptonEtaMax) return 0;

  event_weight = 1.0;


  // Make Z candidate
  //------------------------------------------------------------------------  
  Zlepton1type   = Loose;
  Zlepton2type   = Loose;
  Zlepton1idisoW = 1.0;
  Zlepton2idisoW = 1.0;

  m2l = -999.0;

  if (*nLepton >= 2) {

    for (unsigned int iLep1=0; iLep1<*nLepton; iLep1++) {
      
      if (Lepton_pt[iLep1] < 25.) continue;

      if ((abs(Lepton_pdgId[iLep1]) == 11 && Lepton_isTightElectron_mvaFall17Iso_WP90[iLep1] > 0.5) ||
	  (abs(Lepton_pdgId[iLep1]) == 13 && Lepton_isTightMuon_cut_Tight_HWWW[iLep1] > 0.5)) {

	Zlepton1type   = Tight;
	Zdecayflavour  = abs(Lepton_pdgId[iLep1]);
	Zlepton1idisoW = 1.0;  // Temporary value until put in the trees
      }

      for (unsigned int iLep2=iLep1+1; iLep2<*nLepton; iLep2++) {
	
	if (Lepton_pt[iLep2] < 10.) continue;

	if (Lepton_pdgId[iLep1] + Lepton_pdgId[iLep2] != 0) continue;

	float mass1 = (abs(Lepton_pdgId[iLep1]) == 11) ? 0.000511 : 0.106;
	float mass2 = (abs(Lepton_pdgId[iLep2]) == 11) ? 0.000511 : 0.106;

	tlv1.SetPtEtaPhiM(Lepton_pt[iLep1], Lepton_eta[iLep1], Lepton_phi[iLep1], mass1);
	tlv2.SetPtEtaPhiM(Lepton_pt[iLep2], Lepton_eta[iLep2], Lepton_phi[iLep2], mass2);

	float inv_mass = (tlv1 + tlv2).M();

	if (m2l < 0 || fabs(inv_mass - 91.188) < fabs(m2l - 91.188)) {
	  
	  m2l = inv_mass;

	  leptonIndex = iLep2;
	  
	  // Is the second lepton tight?
	  if ((abs(Lepton_pdgId[iLep2]) == 11 && Lepton_isTightElectron_mvaFall17Iso_WP90[iLep2] > 0.5) ||
	      (abs(Lepton_pdgId[iLep2]) == 13 && Lepton_isTightMuon_cut_Tight_HWWW[iLep2] > 0.5)) {
	    
	    Zlepton2type   = Tight;
	    Zlepton2idisoW = 1.0;  // Temporary value until put in the trees
	  }
	}
      }
    }
  }

  l2tight_weight = Zlepton1idisoW * Zlepton2idisoW;


  // Get the event weight
  //----------------------------------------------------------------------------
  bool passTrigger = false;

  if (ismc) {
    
    event_weight = (*baseW/1e3) * (*puWeight) * (*Generator_weight);

    if (channel == m) {
      
      (Lepton_pt[0] <= 20.) ? event_weight *= 2.903 : event_weight *= 65.944;  // Luminosity in fb-1 from brilcalc
      
      if (Lepton_pt[0] <= 20. && *HLT_Mu8_TrkIsoVVL > 0.5) {
	
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 20. && *HLT_Mu17_TrkIsoVVL > 0.5) {
	
	passTrigger = true;
      }
    }

    if (channel == e) {
      
      (Lepton_pt[0] <= 25.) ? event_weight *= 27.699 : event_weight *= 43.469;  // Luminosity in fb-1 from brilcalc
      
      if (Lepton_pt[0] <= 25. && *HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
	
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
	
	passTrigger = true;
      }
    }

  } else {

    if ((filename.Contains("DoubleMuon") or filename.Contains("SingleMuon")) && channel == m) {
      
      if (Lepton_pt[0] <= 20. && *HLT_Mu8_TrkIsoVVL > 0.5) {
      
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 20. && *HLT_Mu17_TrkIsoVVL > 0.5) {

	passTrigger = true;
      }
    }

    if ((filename.Contains("SingleEle") or filename.Contains("DoubleEG")) && channel == e) {
      
      if (Lepton_pt[0] <= 25. && *HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
	
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
	
	passTrigger = true;
      }
    }
  }


  // Away jet determination
  //----------------------------------------------------------------------------
  if (*nCleanJet > 0) {

    TLorentzVector tlvLepton;
  
    tlvLepton.SetPtEtaPhiM(Lepton_pt[0], Lepton_eta[0], Lepton_phi[0], 0);

    for (int i=0; i<njetet; i++) {
    
      jetIndex = -1;

      inputJetEt = (channel == e) ? elejetet[i] : muonjetet[i];
    
      for (unsigned int j=0; j<*nCleanJet; j++) {
      
	if (CleanJet_pt[j] < 10.) continue;
	if (abs(CleanJet_eta[j]) > 2.5) continue;
	
	TLorentzVector tlvJet;
	
	tlvJet.SetPtEtaPhiM(CleanJet_pt[j], CleanJet_eta[j], CleanJet_phi[j], 0);

	deltaR = tlvJet.DeltaR(tlvLepton);
	
	if (deltaR > 1) {

	  jetIndex = j;
	  
	  break;
	}	
      }

      bool passJets = (jetIndex != -1 && CleanJet_pt[jetIndex] >= inputJetEt);


      // QCD region
      //------------------------------------------------------------------------
      bool passCuts = passTrigger;

      passCuts &= (*nLepton == 1);
      passCuts &= (*mtw1 < 20.);
      passCuts &= (*PuppiMET_pt < 20.);

      FillLevelHistograms(FR_00_QCD, i, passJets && passCuts);


      // Z region
      //------------------------------------------------------------------------
      passCuts = passTrigger;

      passCuts &= (*nLepton > 1);
      passCuts &= (*PuppiMET_pt < 20.);
      passCuts &= (m2l > 20.);

      if (passJets && passCuts) {
	
	if (fabs(Zdecayflavour) == 11) {
	  
	  h_Ele_loose_m2l   [FR_01_Zpeak][i]->Fill(m2l, event_weight);
	  h_Ele_loose_pt_m2l[FR_01_Zpeak][i]->Fill(m2l, tlv1.Pt(), event_weight);
	  
	  if (Zlepton1type == Tight && Zlepton2type == Tight) {
	    
	    h_Ele_tight_m2l   [FR_01_Zpeak][i]->Fill(m2l, event_weight * l2tight_weight);
	    h_Ele_tight_pt_m2l[FR_01_Zpeak][i]->Fill(m2l, tlv1.Pt(), event_weight * l2tight_weight);
	  }
	}
	else if (fabs(Zdecayflavour) == 13) {
	  
	  h_Muon_loose_m2l   [FR_01_Zpeak][i]->Fill(m2l, event_weight);
	  h_Muon_loose_pt_m2l[FR_01_Zpeak][i]->Fill(m2l, tlv1.Pt(), event_weight);
	  
	  if (Zlepton1type == Tight && Zlepton2type == Tight) {
	    
	    h_Muon_tight_m2l   [FR_01_Zpeak][i]->Fill(m2l, event_weight * l2tight_weight);
	    h_Muon_tight_pt_m2l[FR_01_Zpeak][i]->Fill(m2l, tlv1.Pt(), event_weight * l2tight_weight);
	  }
	}
      }

      FillLevelHistograms(FR_01_Zpeak, i, passJets && passCuts);
    }
  }


  // Fill prompt rate histograms
  //----------------------------------------------------------------------------
  if ((76. < m2l && 106. > m2l) && filename.Contains("DY") && Zlepton1type == Tight) {

    float Zlep2pt  = Lepton_pt[leptonIndex];
    float Zlep2eta = fabs(Lepton_eta[leptonIndex]);
    
    if (fabs(Zdecayflavour) == 11) {
    
      h_Ele_loose_pt_eta_PR[PR_00]->Fill(Zlep2pt, Zlep2eta, event_weight);
      h_Ele_loose_pt_PR[PR_00]    ->Fill(Zlep2pt,  event_weight);
      h_Ele_loose_eta_PR[PR_00]   ->Fill(Zlep2eta, event_weight);
      
      if (Zlepton2type == Tight) {
      
	h_Ele_tight_pt_eta_PR[PR_00]->Fill(Zlep2pt, Zlep2eta, event_weight);
	h_Ele_tight_pt_PR[PR_00]    ->Fill(Zlep2pt,  event_weight);
	h_Ele_tight_eta_PR[PR_00]   ->Fill(Zlep2eta, event_weight);
      }
      
    } else if (fabs(Zdecayflavour) == 13) {
      
      h_Muon_loose_pt_eta_PR[PR_00]->Fill(Zlep2pt, Zlep2eta, event_weight);
      h_Muon_loose_pt_PR[PR_00]    ->Fill(Zlep2pt,  event_weight);
      h_Muon_loose_eta_PR[PR_00]   ->Fill(Zlep2eta, event_weight);
      
      if (Zlepton2type == Tight) {
	
	h_Muon_tight_pt_eta_PR[PR_00]->Fill(Zlep2pt, Zlep2eta, event_weight);
	h_Muon_tight_pt_PR[PR_00]    ->Fill(Zlep2pt,  event_weight);
	h_Muon_tight_eta_PR[PR_00]   ->Fill(Zlep2eta, event_weight);
      }
    }
  }

  return kTRUE;
}


//------------------------------------------------------------------------------
// SlaveTerminate
//------------------------------------------------------------------------------
void nanoFakes::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
}


//------------------------------------------------------------------------------
// Terminate
//------------------------------------------------------------------------------
void nanoFakes::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  printf("\n Writing histograms. This can take a while...\n\n");

  printf(" ============== MUONS ============== \n"); 
  printf(" Number of low  pt loose muons: %.0f \n", h_Muon_loose_lowpt [FR_00_QCD][3]->Integral());
  printf(" Number of high pt loose muons: %.0f \n", h_Muon_loose_highpt[FR_00_QCD][3]->Integral());
  printf(" Number of low  pt tight muons: %.0f \n", h_Muon_tight_lowpt [FR_00_QCD][3]->Integral());
  printf(" Number of high pt tight muons: %.0f \n", h_Muon_tight_highpt[FR_00_QCD][3]->Integral());

  printf("\n");

  printf(" ============== ELECTRONS ============== \n"); 
  printf(" Number of low  pt loose electrons: %.0f \n", h_Ele_loose_lowpt [FR_00_QCD][3]->Integral());
  printf(" Number of high pt loose electrons: %.0f \n", h_Ele_loose_highpt[FR_00_QCD][3]->Integral());
  printf(" Number of low  pt tight electrons: %.0f \n", h_Ele_tight_lowpt [FR_00_QCD][3]->Integral());
  printf(" Number of high pt tight electrons: %.0f \n", h_Ele_tight_highpt[FR_00_QCD][3]->Integral());

  printf("\n");

  root_output->Write("", TObject::kOverwrite);
  root_output->Close();
}


//------------------------------------------------------------------------------
// FillLevelHistograms
//------------------------------------------------------------------------------
void nanoFakes::FillLevelHistograms(int icut, int i, bool pass)
{
  if (!pass) return;

  FillAnalysisHistograms(icut, i);
}


//------------------------------------------------------------------------------   
// FillanalysisHistograms
//------------------------------------------------------------------------------                 
void nanoFakes::FillAnalysisHistograms(int icut, int i)
{
  float lep1eta = fabs(Lepton_eta[0]);

  if (channel == m) {


    // Loose muons
    //--------------------------------------------------------------------------
    h_Muon_loose_pt_eta_bin[icut][i]->Fill(Lepton_pt[0], lep1eta, event_weight);
    h_Muon_loose_pt_bin    [icut][i]->Fill(Lepton_pt[0],  event_weight);
    h_Muon_loose_eta_bin   [icut][i]->Fill(lep1eta, event_weight);

    if (Lepton_pt[0] <= 20.)
      {
	h_Muon_loose_lowpt         [icut][i]->Fill(Lepton_pt[0]);
	h_Muon_loose_lowpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
      }
    else
      {
	h_Muon_loose_highpt         [icut][i]->Fill(Lepton_pt[0]);
	h_Muon_loose_highpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
      }


    // Tight muons
    //--------------------------------------------------------------------------
    if (Lepton_isTightMuon_cut_Tight_HWWW[0] > 0.5) {

      h_Muon_tight_pt_eta_bin[icut][i]->Fill(Lepton_pt[0], lep1eta, event_weight);
      h_Muon_tight_pt_bin    [icut][i]->Fill(Lepton_pt[0],  event_weight);
      h_Muon_tight_eta_bin   [icut][i]->Fill(lep1eta, event_weight);
    
      if (Lepton_pt[0] <= 20.)
	{
	  h_Muon_tight_lowpt         [icut][i]->Fill(Lepton_pt[0]);
	  h_Muon_tight_lowpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
	}
      else
	{
	  h_Muon_tight_highpt         [icut][i]->Fill(Lepton_pt[0]);
	  h_Muon_tight_highpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
	}
    }
    
  } else if (channel == e) {

    
    // Loose electrons
    //--------------------------------------------------------------------------
    h_Ele_loose_pt_eta_bin[icut][i]->Fill(Lepton_pt[0], lep1eta, event_weight);
    h_Ele_loose_pt_bin    [icut][i]->Fill(Lepton_pt[0],  event_weight);
    h_Ele_loose_eta_bin   [icut][i]->Fill(lep1eta, event_weight);
    
    if (Lepton_pt[0] <= 25.)
      {
	h_Ele_loose_lowpt         [icut][i]->Fill(Lepton_pt[0]);
	h_Ele_loose_lowpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
      }
    else
      {
	h_Ele_loose_highpt         [icut][i]->Fill(Lepton_pt[0]);
	h_Ele_loose_highpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
      }


    // Tight electrons
    //--------------------------------------------------------------------------
    if (Lepton_isTightElectron_mvaFall17Iso_WP90[0] > 0.5) {
      
      h_Ele_tight_pt_eta_bin[icut][i]->Fill(Lepton_pt[0], lep1eta, event_weight);
      h_Ele_tight_pt_bin    [icut][i]->Fill(Lepton_pt[0],  event_weight);
      h_Ele_tight_eta_bin   [icut][i]->Fill(lep1eta, event_weight);
     
      if(Lepton_pt[0] <= 25.)
	{
	  h_Ele_tight_lowpt         [icut][i]->Fill(Lepton_pt[0]);
	  h_Ele_tight_lowpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
	}
      else
	{
	  h_Ele_tight_highpt         [icut][i]->Fill(Lepton_pt[0]);
	  h_Ele_tight_highpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
	}
    }
  }
}
