//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 23 15:59:15 2018 by ROOT version 6.10/09
// from TTree Events/Events
// found on file: /eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2017_nAOD_v1_Study2017/DATAl1loose2017/nanoLatino_DoubleMuon_Run2017C-31Mar2018-v1__part0.root
//////////////////////////////////////////////////////////

#ifndef nanoFakes_h
#define nanoFakes_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TLorentzVector.h>

// Headers needed by this particular selector

enum {
  e,
  m,
  l, 
  nchannel  // This line should be always last
};

const TString schannel[nchannel] = {
  "e",
  "m",
  "l",
};

const TString lchannel[nchannel] = {
  "e",
  "#mu",
  "l",
};

const int njetet = 7; 
const Double_t muonjetet[njetet] = {10, 15, 20, 25, 30, 35, 45}; 
const Double_t elejetet [njetet] = {10, 15, 20, 25, 30, 35, 45}; 

const int nptbin = 8;
const Double_t ptbins[nptbin+1] = {10, 15, 20, 25, 30, 35, 40, 45, 50};

const int netabin = 5;
const Double_t etabins[netabin+1] = {0, 0.5, 1.0, 1.5, 2.0, 2.5};

//Z candidate
int Zlepton1type;
int Zlepton2type;
float Zlepton1idisoW;
float Zlepton2idisoW;
int Zdecayflavour;
float m2l;

enum {Loose, Tight};

enum {
  FR_00_QCD,
  FR_01_Zpeak,
  ncutFR
};

const TString scutFR[ncutFR] = {
  "FR/00_QCD",
  "FR/01_Zpeak",
};

enum {
  PR_00,
  ncutPR
};

const TString scutPR[ncutPR] = {
  "PR/00",
};

class nanoFakes : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   void FillAnalysisHistograms(int icut,
			       int     i);

   void FillLevelHistograms   (int icut,
			       int     i,
			       bool    pass);

   // Fake rate histograms 
   //----------------------------------------------------------------------------
   TH2D* h_Muon_loose_pt_eta_bin[ncutFR][njetet];
   TH2D* h_Muon_tight_pt_eta_bin[ncutFR][njetet];
   TH2D* h_Ele_loose_pt_eta_bin [ncutFR][njetet];
   TH2D* h_Ele_tight_pt_eta_bin [ncutFR][njetet];

   TH1D* h_Muon_loose_pt_bin[ncutFR][njetet];
   TH1D* h_Muon_tight_pt_bin[ncutFR][njetet];
   TH1D* h_Ele_loose_pt_bin [ncutFR][njetet];
   TH1D* h_Ele_tight_pt_bin [ncutFR][njetet];

   TH1D* h_Muon_loose_eta_bin[ncutFR][njetet];
   TH1D* h_Muon_tight_eta_bin[ncutFR][njetet];
   TH1D* h_Ele_loose_eta_bin [ncutFR][njetet];
   TH1D* h_Ele_tight_eta_bin [ncutFR][njetet];

   TH1D* h_Muon_loose_m2l[ncutFR][njetet];
   TH1D* h_Muon_tight_m2l[ncutFR][njetet];
   TH1D* h_Ele_loose_m2l [ncutFR][njetet];
   TH1D* h_Ele_tight_m2l [ncutFR][njetet];

   // Declare effective luminosity estimation histograms
   //----------------------------------------------------------------------------
   TH2D* h_Muon_loose_pt_m2l[ncutFR][njetet];
   TH2D* h_Muon_tight_pt_m2l[ncutFR][njetet];
   TH2D* h_Ele_loose_pt_m2l [ncutFR][njetet];
   TH2D* h_Ele_tight_pt_m2l [ncutFR][njetet];

   // Prompt rate histograms
   //--------------------------------------------------------------------------
   TH2D* h_Muon_loose_pt_eta_PR[ncutPR];
   TH2D* h_Muon_tight_pt_eta_PR[ncutPR];
   TH2D* h_Ele_loose_pt_eta_PR[ncutPR];
   TH2D* h_Ele_tight_pt_eta_PR[ncutPR];

   TH1D* h_Muon_loose_pt_PR[ncutPR];
   TH1D* h_Muon_tight_pt_PR[ncutPR];
   TH1D* h_Ele_loose_pt_PR[ncutPR];
   TH1D* h_Ele_tight_pt_PR[ncutPR];

   TH1D* h_Muon_loose_eta_PR[ncutPR];
   TH1D* h_Muon_tight_eta_PR[ncutPR];
   TH1D* h_Ele_loose_eta_PR[ncutPR];
   TH1D* h_Ele_tight_eta_PR[ncutPR];

   // Readers to access the data (delete the ones you do not need).
   //#ifdef IS_MC
   TTreeReaderValue<Float_t> baseW;
   TTreeReaderValue<Float_t> Xsec;
   TTreeReaderValue<Float_t> puWeight;
   TTreeReaderValue<Float_t> Generator_weight;
   //#endif

   TTreeReaderValue<Bool_t> HLT_Mu8_TrkIsoVVL = {fReader, "HLT_Mu8_TrkIsoVVL"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL"};
   TTreeReaderValue<Bool_t> HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 = {fReader, "HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30"};
   TTreeReaderValue<Bool_t> HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 = {fReader, "HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30"};

   TTreeReaderValue<UInt_t> nLepton = {fReader, "nLepton"};
   TTreeReaderArray<Int_t> Lepton_pdgId = {fReader, "Lepton_pdgId"};
   TTreeReaderArray<Float_t> Lepton_pt = {fReader, "Lepton_pt"};
   TTreeReaderArray<Float_t> Lepton_eta = {fReader, "Lepton_eta"};
   TTreeReaderArray<Float_t> Lepton_phi = {fReader, "Lepton_phi"};
   TTreeReaderArray<Int_t> Lepton_electronIdx = {fReader, "Lepton_electronIdx"};

   TTreeReaderValue<UInt_t> nCleanJet = {fReader, "nCleanJet"};
   TTreeReaderArray<Float_t> CleanJet_pt = {fReader, "CleanJet_pt"};
   TTreeReaderArray<Float_t> CleanJet_eta = {fReader, "CleanJet_eta"};
   TTreeReaderArray<Float_t> CleanJet_phi = {fReader, "CleanJet_phi"};
   
   TTreeReaderValue<Float_t> mtw1 = {fReader, "mtw1"};
   TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
   TTreeReaderValue<Float_t> dphilep1jet1 = {fReader, "dphilep1jet1"};

   TTreeReaderArray<Int_t> Lepton_isTightElectron_mvaFall17noIso_WP80 = {fReader, "Lepton_isTightElectron_mvaFall17noIso_WP80"};
   TTreeReaderArray<Int_t> Lepton_isTightElectron_mvaFall17noIso = {fReader, "Lepton_isTightElectron_mvaFall17noIso"};
   TTreeReaderArray<Int_t> Lepton_isTightElectron_mvaFall17noIso_WP90 = {fReader, "Lepton_isTightElectron_mvaFall17noIso_WP90"};
   TTreeReaderArray<Int_t> Lepton_isTightElectron_mvaFall17Iso = {fReader, "Lepton_isTightElectron_mvaFall17Iso"};
   TTreeReaderArray<Int_t> Lepton_isTightElectron_mvaFall17noIso_WPL = {fReader, "Lepton_isTightElectron_mvaFall17noIso_WPL"};
   TTreeReaderArray<Int_t> Lepton_isTightElectron_mvaFall17Iso_WP90 = {fReader, "Lepton_isTightElectron_mvaFall17Iso_WP90"};
   TTreeReaderArray<Int_t> Lepton_isTightElectron_mvaFall17Iso_WPL = {fReader, "Lepton_isTightElectron_mvaFall17Iso_WPL"};
   TTreeReaderArray<Int_t> Lepton_isTightElectron_mvaFall17Iso_WP80 = {fReader, "Lepton_isTightElectron_mvaFall17Iso_WP80"};
   TTreeReaderArray<Int_t> Lepton_isTightMuon_cut_Medium80x = {fReader, "Lepton_isTightMuon_cut_Medium80x"};
   TTreeReaderArray<Int_t> Lepton_isTightMuon_cut_Tight80x_HWWW = {fReader, "Lepton_isTightMuon_cut_Tight80x_HWWW"};
   TTreeReaderArray<Int_t> Lepton_isTightMuon_cut_Tight80x = {fReader, "Lepton_isTightMuon_cut_Tight80x"};

   TTreeReaderArray<Float_t> Electron_mvaFall17Iso = {fReader, "Electron_mvaFall17Iso"};
   TTreeReaderArray<Float_t> Electron_mvaFall17noIso = {fReader, "Electron_mvaFall17noIso"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17Iso_WP80 = {fReader, "Electron_mvaFall17Iso_WP80"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17Iso_WP90 = {fReader, "Electron_mvaFall17Iso_WP90"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17Iso_WPL = {fReader, "Electron_mvaFall17Iso_WPL"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17noIso_WP80 = {fReader, "Electron_mvaFall17noIso_WP80"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17noIso_WP90 = {fReader, "Electron_mvaFall17noIso_WP90"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17noIso_WPL = {fReader, "Electron_mvaFall17noIso_WPL"};
   TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
   TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};

   nanoFakes(TTree * /*tree*/ =0) { }
   virtual ~nanoFakes() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(nanoFakes,0);

};

#endif

#ifdef nanoFakes_cxx
void nanoFakes::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t nanoFakes::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef nanoFakes_cxx
