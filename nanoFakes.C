#define nanoFakes_cxx
// The class definition in nanoFakes.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("nanoFakes.C")
// root> T->Process("nanoFakes.C","some options")
// root> T->Process("nanoFakes.C+")
//

#include "nanoFakes.h"
#include <TStyle.h>

int nentries = 0;
int maxentries = -1;
int counter = 0;

TFile* root_output;
TString filename;

bool ismc;
int channel;
float inputJetEt;
float leptonPtMin;
float leptonEtaMax;
float event_weight;
float l2tight_weight;
float deltaR;
float dxycut;

TLorentzVector tlv1;
TLorentzVector tlv2;

int jetIndex;

int nElectronsLooseLowPt = 0;
int nElectronsTightLowPt = 0;
int nElectronsLooseHighPt = 0;
int nElectronsTightHighPt = 0;
int nMuonsLooseLowPt = 0;
int nMuonsTightLowPt = 0;
int nMuonsLooseHighPt = 0;
int nMuonsTightHighPt = 0;

void nanoFakes::Begin(TTree * /*tree*/)
{

  filename = GetOption();

  if (!filename.Contains("Run2017"))
    {
      baseW = {fReader, "baseW"};
      Xsec = {fReader, "Xsec"};
      puWeight = {fReader, "puWeight"};
      Generator_weight = {fReader, "Generator_weight"};
    }

  root_output = new TFile("results/"+filename+".root", "recreate");

  TH1::SetDefaultSumw2();

   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

  //filename = GetOption();
  //ismc = (filename.Contains("Run2017")) ? false : true;

   for (int i=0; i<ncutFR; i++) {
     
     TString directory = scutFR[i];
     root_output -> cd();
     gDirectory -> mkdir(directory);
     root_output -> cd(directory);
   
     for (int j=0; j<njetet; j++) {
       
       TString muonsuffix = Form("_%.0fGeV", muonjetet[j]);
       TString elesuffix = Form("_%.0fGeV", elejetet[j]);
       
       //Histograms definition for all the variables considered
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
       
       h_Muon_loose_m2l[i][j] = new TH1D("h_Muon_loose_m2l" + muonsuffix, "", 1000, 0, 200);
       h_Muon_tight_m2l[i][j] = new TH1D("h_Muon_tight_m2l" + muonsuffix, "", 1000, 0, 200);
       h_Ele_loose_m2l [i][j] = new TH1D("h_Ele_loose_m2l"  + elesuffix,  "", 1000, 0, 200);
       h_Ele_tight_m2l [i][j] = new TH1D("h_Ele_tight_m2l"  + elesuffix,  "", 1000, 0, 200);
          
       // Define effective luminosity estimation histograms
       //------------------------------------------------------------------------
       h_Muon_loose_pt_m2l[i][j] = new TH2D("h_Muon_loose_pt_m2l" + muonsuffix, "", 200, 0, 200, nptbin, ptbins);
       h_Muon_tight_pt_m2l[i][j] = new TH2D("h_Muon_tight_pt_m2l" + muonsuffix, "", 200, 0, 200, nptbin, ptbins);
       h_Ele_loose_pt_m2l [i][j] = new TH2D("h_Ele_loose_pt_m2l"  + elesuffix,  "", 200, 0, 200, nptbin, ptbins);
       h_Ele_tight_pt_m2l [i][j] = new TH2D("h_Ele_tight_pt_m2l"  + elesuffix,  "", 200, 0, 200, nptbin, ptbins);
       
       //Initialize yields histograms
       h_Muon_loose_lowpt[i][j] = new TH1D("h_Muon_loose_lowpt" + muonsuffix, "", nptbin, ptbins);
       h_Muon_loose_lowpt_weighted[i][j] = new TH1D("h_Muon_loose_lowpt_weighted" + muonsuffix, "", nptbin, ptbins);
       h_Muon_loose_highpt[i][j] = new TH1D("h_Muon_loose_highpt" + muonsuffix, "", nptbin, ptbins);
       h_Muon_loose_highpt_weighted[i][j] = new TH1D("h_Muon_loose_highpt_weighted" + muonsuffix, "", nptbin, ptbins);
       h_Muon_tight_lowpt[i][j] = new TH1D("h_Muon_tight_lowpt" + muonsuffix, "", nptbin, ptbins);
       h_Muon_tight_lowpt_weighted[i][j] = new TH1D("h_Muon_tight_lowpt_weighted" + muonsuffix, "", nptbin, ptbins);
       h_Muon_tight_highpt[i][j] = new TH1D("h_Muon_tight_highpt" + muonsuffix, "", nptbin, ptbins);
       h_Muon_tight_highpt_weighted[i][j] = new TH1D("h_Muon_tight_highpt_weighted" + muonsuffix, "", nptbin, ptbins);
       
       h_Ele_loose_lowpt[i][j] = new TH1D("h_Ele_loose_lowpt" + muonsuffix, "", nptbin, ptbins);
       h_Ele_loose_lowpt_weighted[i][j] = new TH1D("h_Ele_loose_lowpt_weighted" + muonsuffix, "", nptbin, ptbins);
       h_Ele_loose_highpt[i][j] = new TH1D("h_Ele_loose_highpt" + muonsuffix, "", nptbin, ptbins);
       h_Ele_loose_highpt_weighted[i][j] = new TH1D("h_Ele_loose_highpt_weighted" + muonsuffix, "", nptbin, ptbins);
       h_Ele_tight_lowpt[i][j] = new TH1D("h_Ele_tight_lowpt" + muonsuffix, "", nptbin, ptbins);
       h_Ele_tight_lowpt_weighted[i][j] = new TH1D("h_Ele_tight_lowpt_weighted" + muonsuffix, "", nptbin, ptbins);
       h_Ele_tight_highpt[i][j] = new TH1D("h_Ele_tight_highpt" + muonsuffix, "", nptbin, ptbins);
       h_Ele_tight_highpt_weighted[i][j] = new TH1D("h_Ele_tight_highpt_weighted" + muonsuffix, "", nptbin, ptbins);
    
     }
   }

   for (int i=0; i<ncutPR; i++) {
     
     TString directory = scutPR[i];
     root_output -> cd();
     gDirectory -> mkdir(directory);
     root_output -> cd(directory);

     //Prompt rate histograms
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

void nanoFakes::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

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

  //printf("Entry number %lld \n", entry); 	 
  fReader.SetEntry(entry);  

  if(entry > maxentries && maxentries > -1) return 0;
  if(entry%100000 == 0) printf("Entry number %lld \n", entry); 	 
  nentries++;

  channel = (abs(Lepton_pdgId[0]) == 11) ? e : m;

  leptonPtMin  = (channel == e) ?  13 :  10;
  leptonEtaMax = (channel == e) ? 2.5 : 2.4;

  if (Lepton_pt[0] < leptonPtMin) return 0;
  if (fabs(Lepton_eta[0]) > leptonEtaMax) return 0;

  filename = GetOption();
  ismc = (filename.Contains("Run2017")) ? false : true;
  
  event_weight = 1.0;

  //Make Z candidate
  //------------------------------------------------------------------------  
  Zlepton1type = Loose;
  Zlepton2type = Loose;
  Zlepton1idisoW = 1.0;
  Zlepton2idisoW = 1.0;

  m2l = -999.0;

  if(*nLepton >= 2) {

    for(unsigned int iLep1 = 0; iLep1 < *nLepton; iLep1++) {
      
      if(Lepton_pt[iLep1] < 10.) continue;

      for(unsigned int iLep2 = 0; iLep2 < *nLepton; iLep2++) {
	
	if(Lepton_pt[iLep2] < 10.) continue;
	if(Lepton_pdgId[iLep1] + Lepton_pdgId[iLep2] != 0) continue;

	float mass1 = (abs(Lepton_pdgId[iLep1]) == 11) ? 0.000511 : 0.106;
	float mass2 = (abs(Lepton_pdgId[iLep2]) == 11) ? 0.000511 : 0.106;

	tlv1.SetPtEtaPhiM(Lepton_pt[iLep1], Lepton_eta[iLep1], Lepton_phi[iLep1], mass1);
	tlv2.SetPtEtaPhiM(Lepton_pt[iLep2], Lepton_eta[iLep2], Lepton_phi[iLep2], mass2);

	float inv_mass = (tlv1 + tlv2).M();

	if(m2l < 0 || fabs(inv_mass - 91.188) < fabs(m2l - 91.188)) {
	  
	  m2l = inv_mass;

	  dxycut = (Lepton_pt[iLep1] <= 20) ? 0.01 : 0.02;

	  //Is the first lepton tight?
	  if(abs(Lepton_pdgId[iLep1]) == 11 && Electron_mvaFall17Iso_WP80[Lepton_electronIdx[iLep1]] > 0.5 && (Electron_dz[Lepton_electronIdx[iLep1]] < 0.1) && (Electron_dxy[Lepton_electronIdx[iLep1]] < dxycut)) {
	    
	    Zlepton1type = Tight;
	    Zdecayflavour = 11;
	    if(ismc) Zlepton1idisoW = 1.0; //Temporary value until put in the trees

	  } else if(abs(Lepton_pdgId[iLep1]) == 13 && Lepton_isTightMuon_cut_Tight80x_HWWW[iLep1] > 0.5) {
	  
	    Zlepton1type = Tight;
	    Zdecayflavour = 13;
	    if(ismc) Zlepton1idisoW = 1.0; //Temporary value until put in the trees

	  }

	  dxycut = (Lepton_pt[iLep2] <= 20) ? 0.01 : 0.02;

	  //Is the second lepton tight?
	  if(abs(Lepton_pdgId[iLep2]) == 11 && Electron_mvaFall17Iso_WP80[Lepton_electronIdx[iLep2]] > 0.5 && (Electron_dz[Lepton_electronIdx[iLep1]] < 0.1) && (Electron_dxy[Lepton_electronIdx[iLep2]] < dxycut)) {
	    
	    Zlepton2type = Tight;
	    if(ismc) Zlepton2idisoW = 1.0; //Temporary value until put in the trees

	  } else if(abs(Lepton_pdgId[iLep2]) == 13 && Lepton_isTightMuon_cut_Tight80x_HWWW[iLep2] > 0.5) {
	  
	    Zlepton2type = Tight;
	    if(ismc) Zlepton2idisoW = 1.0; //Temporary value until put in the trees

	  }

	}

      }

    }

  }

  l2tight_weight = Zlepton1idisoW * Zlepton2idisoW;

  // Get the event weight
  //------------------------------------------------------------------------
  bool passTrigger = false;

  if (ismc) {
    
    //passTrigger = true;
    event_weight = (*baseW/1000.0) * (*puWeight) * (*Generator_weight);

    if(channel == m){
      
      (Lepton_pt[0] <= 20.) ? event_weight *= 2.903 : event_weight *= 65.944;
      
      if (Lepton_pt[0] <= 20. && *HLT_Mu8_TrkIsoVVL > 0.5) {
	
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 20. && *HLT_Mu17_TrkIsoVVL > 0.5) {
	
	passTrigger = true;
	
      }
      
    }

    if(channel == e){
      
      (Lepton_pt[0] <= 25.) ? event_weight *= 27.699 : event_weight *= 43.469;
      
      if (Lepton_pt[0] <= 25. && *HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
	
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
	
	passTrigger = true;
      }
      
    }

  } else {

    // Muons
    //------------------------------------------------------------------------
    if ((filename.Contains("DoubleMuon")) && channel == m) {
      
      if (Lepton_pt[0] <= 20. && *HLT_Mu8_TrkIsoVVL > 0.5) {
      
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 20. && *HLT_Mu17_TrkIsoVVL > 0.5) {

	passTrigger = true;
    
      }
    }
    
    // Electrons
    //------------------------------------------------------------------------
    if ((filename.Contains("SingleEle")) && channel == e) {
      
      if (Lepton_pt[0] <= 25. && *HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
	
	passTrigger = true;
	
	} else if (Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
	
	passTrigger = true;
      }
    }

  }

  //Fake rate calculation
  for (int i=0; i<njetet; i++) {
   
    bool passCuts = passTrigger;
    
    passCuts &= (*nLepton == 1);
    passCuts &= (*mtw1 < 20.);
    passCuts &= (*MET_pt < 20.);
 
    inputJetEt = (channel == e) ? elejetet[i] : muonjetet[i];

    TLorentzVector tlvLepton;
    tlvLepton.SetPtEtaPhiM(Lepton_pt[0], Lepton_eta[0], Lepton_phi[0], 0);
    
    jetIndex = 0;
    
    for (unsigned int j=0; j<*nCleanJet; j++) {
      
      if(CleanJet_pt[j] > 10.) {
	
	TLorentzVector tlvJet;
	tlvJet.SetPtEtaPhiM(CleanJet_pt[j], CleanJet_eta[j], CleanJet_phi[j], 0);
	deltaR = tlvJet.DeltaR(tlvLepton);
	
	if(deltaR > 1) jetIndex = j; break;
	
      }	
      
    }
    
    bool passJets = true;
    passJets &= (*nCleanJet >= 1); 
    passJets &= (CleanJet_pt[jetIndex] >= inputJetEt);
    
    //QCD region
    if (passJets && passCuts) {

      if (fabs(Zdecayflavour) == 11) {
	
	h_Ele_loose_m2l   [FR_00_QCD][i]->Fill(m2l, event_weight);
	h_Ele_loose_pt_m2l[FR_00_QCD][i]->Fill(m2l, tlv1.Pt(), event_weight);
      
	if (Zlepton1type == Tight && Zlepton2type == Tight) {
        
	  h_Ele_tight_m2l   [FR_00_QCD][i]->Fill(m2l, event_weight * l2tight_weight);
	  h_Ele_tight_pt_m2l[FR_00_QCD][i]->Fill(m2l, tlv1.Pt(), event_weight * l2tight_weight);
	}
      }
      else if (fabs(Zdecayflavour) == 13) {
      
	h_Muon_loose_m2l   [FR_00_QCD][i]->Fill(m2l, event_weight);
	h_Muon_loose_pt_m2l[FR_00_QCD][i]->Fill(m2l, tlv1.Pt(), event_weight);
      
	if (Zlepton1type == Tight && Zlepton2type == Tight) {
        
	  h_Muon_tight_m2l   [FR_00_QCD][i]->Fill(m2l, event_weight * l2tight_weight);
	  h_Muon_tight_pt_m2l[FR_00_QCD][i]->Fill(m2l, tlv1.Pt(), event_weight * l2tight_weight);
	}
      }

    }
    
    FillLevelHistograms(FR_00_QCD, i, passJets && passCuts);

    dxycut = (Lepton_pt[0] <= 20) ? 0.01 : 0.02;
    //Loose leptons counter
    if (passCuts && passJets && i == 3 && channel == m && Lepton_pt[0] <= 20. && *HLT_Mu8_TrkIsoVVL > 0.5) ++nMuonsLooseLowPt;
    if (passCuts && passJets && i == 3 && channel == m && Lepton_pt[0] > 20. && *HLT_Mu17_TrkIsoVVL > 0.5) ++nMuonsLooseHighPt;
    if (passCuts && passJets && i == 3 && channel == e && (Lepton_pt[0] <= 25. && *HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5)) ++nElectronsLooseLowPt;
    if (passCuts && passJets && i == 3 && channel == e && (Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5)) ++nElectronsLooseHighPt;

    //Tight leptons counter
    if (passCuts && passJets && i == 3 && channel == m && Lepton_pt[0] <= 20. && *HLT_Mu8_TrkIsoVVL > 0.5 && Lepton_isTightMuon_cut_Tight80x_HWWW[0] > 0.5) ++nMuonsTightLowPt;
    if (passCuts && passJets && i == 3 && channel == m && Lepton_pt[0] > 20. && *HLT_Mu17_TrkIsoVVL > 0.5 && Lepton_isTightMuon_cut_Tight80x_HWWW[0] > 0.5) ++nMuonsTightHighPt;
    if (passCuts && passJets && i == 3 && channel == e && Electron_mvaFall17Iso_WP80[Lepton_electronIdx[0]] > 0.5 && (Electron_dz[Lepton_electronIdx[0]] < 0.1) && (Electron_dxy[Lepton_electronIdx[0]] < dxycut) && (Lepton_pt[0] <= 25. && *HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5)) ++nElectronsTightLowPt;
    if (passCuts && passJets && i == 3 && channel == e && Electron_mvaFall17Iso_WP80[Lepton_electronIdx[0]] > 0.5 && (Electron_dz[Lepton_electronIdx[0]] < 0.1) && (Electron_dxy[Lepton_electronIdx[0]] < dxycut) && (Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5)) ++nElectronsTightLowPt;

    //Z Region
    passCuts = passTrigger;

    passCuts &= (*nLepton > 1);
    passCuts &= (*MET_pt < 20.);
    passCuts &= (m2l > 20.);

    if(passJets && passCuts) {
      
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

  //Prompt rate calculation
  bool passCuts = true;
  
  passCuts &= (76. < m2l && 106. > m2l);
  passCuts &= (*mtw1 < 20.);
  
  if (passCuts && filename.Contains("DY") && Zlepton1type == Tight) {

    float Zlep2pt  = Lepton_pt[1];
    float Zlep2eta = fabs(Lepton_eta[1]);
    
    if (fabs(Zdecayflavour) == 11) {
    
      h_Ele_loose_pt_eta_PR[PR_00] ->Fill(Zlep2pt, Zlep2eta, event_weight);
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

void nanoFakes::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void nanoFakes::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  printf("\n\n Writing histograms. This can take a while... \n \n");

  printf("============== MUONS ============== \n"); 
  printf("Number of muons loose, low pt: %d \n", nMuonsLooseLowPt);
  printf("Number of muons loose, high pt: %d \n", nMuonsLooseHighPt);
  printf("Number of muons tight, low pt: %d \n", nMuonsTightLowPt);
  printf("Number of muons tight, high pt: %d \n", nMuonsTightHighPt);

    printf("============== ELECTRONS ============== \n"); 
  printf("Number of electrons loose, low pt: %d \n", nElectronsLooseLowPt);
  printf("Number of electrons loose, high pt: %d \n", nElectronsLooseHighPt);
  printf("Number of electrons tight, low pt: %d \n", nElectronsTightLowPt);
  printf("Number of electrons tight, high pt: %d \n", nElectronsTightHighPt);

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

    h_Muon_loose_pt_eta_bin[icut][i]->Fill(Lepton_pt[0], lep1eta, event_weight);
    h_Muon_loose_pt_bin    [icut][i]->Fill(Lepton_pt[0],  event_weight);
    h_Muon_loose_eta_bin   [icut][i]->Fill(lep1eta, event_weight);

    if(Lepton_pt[0] <= 20. && *HLT_Mu8_TrkIsoVVL > 0.5) { //Low pt trigger
      h_Muon_loose_lowpt[icut][i]->Fill(Lepton_pt[0]); //Without weight
      h_Muon_loose_lowpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
    } else if(Lepton_pt[0] > 20. && *HLT_Mu17_TrkIsoVVL > 0.5) {
      h_Muon_loose_highpt[icut][i]->Fill(Lepton_pt[0]); //Without weight
      h_Muon_loose_highpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
    }

    if (Lepton_isTightMuon_cut_Tight80x_HWWW[0] > 0.5) {

      h_Muon_tight_pt_eta_bin[icut][i]->Fill(Lepton_pt[0], lep1eta, event_weight);
      h_Muon_tight_pt_bin [icut][i]->Fill(Lepton_pt[0],  event_weight);
      h_Muon_tight_eta_bin[icut][i]->Fill(lep1eta, event_weight);
    
      if(Lepton_pt[0] <= 20. && *HLT_Mu8_TrkIsoVVL > 0.5) { //Low pt trigger
	h_Muon_tight_lowpt[icut][i]->Fill(Lepton_pt[0]); //Without weight
	h_Muon_tight_lowpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
      } else if(Lepton_pt[0] > 20. && *HLT_Mu17_TrkIsoVVL > 0.5) {
	h_Muon_tight_highpt[icut][i]->Fill(Lepton_pt[0]); //Without weight
	h_Muon_tight_highpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
      }
      
    }
    
  } else if (channel == e) {
    
    h_Ele_loose_pt_eta_bin[icut][i]->Fill(Lepton_pt[0], lep1eta, event_weight);
    h_Ele_loose_pt_bin    [icut][i]->Fill(Lepton_pt[0],  event_weight);
    h_Ele_loose_eta_bin   [icut][i]->Fill(lep1eta, event_weight);
    
    dxycut = (Lepton_pt[0] <= 20) ? 0.01 : 0.02;

    if(Lepton_pt[0] <= 25. && *HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) { //Low pt trigger
      h_Ele_loose_lowpt[icut][i]->Fill(Lepton_pt[0]); //Without weight
      h_Ele_loose_lowpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
    } else if(Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
      h_Ele_loose_highpt[icut][i]->Fill(Lepton_pt[0]); //Without weight
      h_Ele_loose_highpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
    }

    if(Electron_mvaFall17Iso_WP80[Lepton_electronIdx[0]] > 0.5 && (Electron_dz[Lepton_electronIdx[0]] < 0.1) && (Electron_dxy[Lepton_electronIdx[0]] < dxycut)) {
      
      h_Ele_tight_pt_eta_bin[icut][i]->Fill(Lepton_pt[0], lep1eta, event_weight);
      h_Ele_tight_pt_bin [icut][i]->Fill(Lepton_pt[0],  event_weight);
      h_Ele_tight_eta_bin[icut][i]->Fill(lep1eta, event_weight);
     
      if(Lepton_pt[0] <= 25. && *HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) { //Low pt trigger
	h_Ele_tight_lowpt[icut][i]->Fill(Lepton_pt[0]); //Without weight
	h_Ele_tight_lowpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
      } else if(Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 > 0.5) {
	h_Ele_tight_highpt[icut][i]->Fill(Lepton_pt[0]); //Without weight
	h_Ele_tight_highpt_weighted[icut][i]->Fill(Lepton_pt[0], event_weight);
      }
 
    }

  }
    
}

/* 

[2018/07/16] Total luminosity = 41.530/fb
export PATH=$HOME/.local/bin:/afs/cern.ch/cms/lumi/brilconda-1.0.3/bin:$PATH

brilcalc lumi -b "STABLE BEAMS"               --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json               -u /pb               -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt  --hltpath "HLT_Mu8_TrkIsoVVL_v*"

#Summary: 
+-----------------------+-------+------+--------+-------------------+------------------+
| hltpath               | nfill | nrun | ncms   | totdelivered(/pb) | totrecorded(/pb) |
+-----------------------+-------+------+--------+-------------------+------------------+
| HLT_Mu8_TrkIsoVVL_v10 | 91    | 218  | 124448 | 2.092             | 1.831            |
| HLT_Mu8_TrkIsoVVL_v11 | 2     | 13   | 4469   | 0.065             | 0.062            |
| HLT_Mu8_TrkIsoVVL_v6  | 13    | 46   | 15947  | 0.148             | 0.143            |
| HLT_Mu8_TrkIsoVVL_v7  | 13    | 36   | 8349   | 0.080             | 0.074            |
| HLT_Mu8_TrkIsoVVL_v8  | 9     | 21   | 5909   | 0.119             | 0.109            |
| HLT_Mu8_TrkIsoVVL_v9  | 47    | 140  | 46316  | 0.733             | 0.684            |
+-----------------------+-------+------+--------+-------------------+------------------+
#Sum delivered : 3.237
#Sum recorded : 2.903


brilcalc lumi -b "STABLE BEAMS"               --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json               -u /pb               -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt  --hltpath "HLT_Mu17_TrkIsoVVL_v*" 

#Summary: 
+------------------------+-------+------+--------+-------------------+------------------+
| hltpath                | nfill | nrun | ncms   | totdelivered(/pb) | totrecorded(/pb) |
+------------------------+-------+------+--------+-------------------+------------------+
| HLT_Mu17_TrkIsoVVL_v10 | 91    | 218  | 124448 | 46.654            | 44.670           |
| HLT_Mu17_TrkIsoVVL_v11 | 2     | 13   | 4469   | 1.588             | 1.535            |
| HLT_Mu17_TrkIsoVVL_v5  | 2     | 3    | 1775   | 0.137             | 0.132            |
| HLT_Mu17_TrkIsoVVL_v6  | 11    | 43   | 14172  | 1.552             | 1.491            |
| HLT_Mu17_TrkIsoVVL_v7  | 13    | 36   | 8349   | 1.114             | 1.038            |
| HLT_Mu17_TrkIsoVVL_v8  | 9     | 21   | 5909   | 1.896             | 1.741            |
| HLT_Mu17_TrkIsoVVL_v9  | 47    | 140  | 46316  | 16.322            | 15.335           |
+------------------------+-------+------+--------+-------------------+------------------+
#Sum delivered : 69.263
#Sum recorded : 65.944

brilcalc lumi -b "STABLE BEAMS"               --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json               -u /pb               -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt  --hltpath "HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v*"

#Summary: 
+---------------------------------------------+-------+------+-------+-------------------+------------------+
| hltpath                                     | nfill | nrun | ncms  | totdelivered(/pb) | totrecorded(/pb) |
+---------------------------------------------+-------+------+-------+-------------------+------------------+
| HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v10 | 27    | 56   | 23305 | 0.277             | 0.268            |
| HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v11 | 18    | 47   | 19043 | 0.576             | 0.396            |
| HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v12 | 67    | 144  | 90816 | 1.567             | 1.506            |
| HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v13 | 6     | 27   | 14589 | 0.676             | 0.652            |
| HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v14 | 2     | 13   | 4469  | 0.197             | 0.192            |
| HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v8  | 9     | 21   | 5909  | 0.191             | 0.177            |
| HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v9  | 20    | 84   | 23011 | 0.851             | 0.783            |
+---------------------------------------------+-------+------+-------+-------------------+------------------+
#Sum delivered : 4.335
#Sum recorded : 3.973


brilcalc lumi -b "STABLE BEAMS"               --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json               -u /pb               -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt  --hltpath "HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v*"

#Summary: 
+----------------------------------------------+-------+------+-------+-------------------+------------------+
| hltpath                                      | nfill | nrun | ncms  | totdelivered(/pb) | totrecorded(/pb) |
+----------------------------------------------+-------+------+-------+-------------------+------------------+
| HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v10 | 9     | 21   | 5909  | 0.602             | 0.555            |
| HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v11 | 20    | 84   | 23011 | 2.288             | 2.091            |
| HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v12 | 27    | 56   | 23305 | 1.173             | 1.131            |
| HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v13 | 18    | 47   | 19043 | 4.148             | 3.858            |
| HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v14 | 67    | 144  | 90816 | 17.347            | 16.644           |
| HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v15 | 6     | 27   | 14589 | 2.745             | 2.637            |
| HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v16 | 2     | 13   | 4469  | 0.810             | 0.783            |
+----------------------------------------------+-------+------+-------+-------------------+------------------+
#Sum delivered : 29.114
#Sum recorded : 27.699


brilcalc lumi -b "STABLE BEAMS"               --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json               -u /pb               -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt  --hltpath "HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v*"

#Summary: 
+----------------------------------------------+-------+------+-------+-------------------+------------------+
| hltpath                                      | nfill | nrun | ncms  | totdelivered(/pb) | totrecorded(/pb) |
+----------------------------------------------+-------+------+-------+-------------------+------------------+
| HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v10 | 9     | 21   | 5909  | 1.070             | 0.994            |
| HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v11 | 20    | 84   | 23011 | 4.410             | 4.056            |
| HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v12 | 27    | 56   | 23305 | 4.573             | 4.407            |
| HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v13 | 18    | 47   | 19043 | 4.148             | 3.858            |
| HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v14 | 67    | 144  | 90816 | 21.239            | 20.408           |
| HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v15 | 6     | 27   | 14589 | 7.811             | 7.534            |
| HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v16 | 2     | 13   | 4469  | 2.279             | 2.211            |
+----------------------------------------------+-------+------+-------+-------------------+------------------+
#Sum delivered : 45.531
#Sum recorded : 43.469

*/
