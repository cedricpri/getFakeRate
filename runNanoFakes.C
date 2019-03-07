//------------------------------------------------------------------------------
//
//      Target: Produce fake and prompt rates
//     Authors: Jonatan Piedra, Cedric Prieels
// Last update: March 7th, 2019
//
//------------------------------------------------------------------------------
TString path_mc   = "";
TString path_data = "";


std::string to_string(int i)
{
  std::stringstream ss;
  ss << i;
  return ss.str();
}


void runNanoFakes(TString year = "2017", TString filename = "NONE")
{
  if (year == "2016")
    {
      path_mc   = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Summer16_94X_nAODv3_Full2016v2/MCl1loose2016__MCCorr2016/";
      path_data = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2016_94X_nAODv3_Full2016v2/DATAl1loose2016/";
    }
  else if (year == "2017")
    {
      path_mc   = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Fall2017_nAOD_v1_Full2017v2/MCl1loose2017v2__MCCorr2017__btagPerEvent/";
      path_data = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2017_nAOD_v1_Full2017v2/DATAl1loose2017v2__DATACorr2017/";
    }
  else if (year == "2018")
    {
      path_mc   = "";  // Not yet available
      path_data = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2018_102X_nAODv4_14Sep_Full2018/DATAl1loose2018__fakeSel/";
    }
  else
    {
      printf(" The year should be either 2016, 2017 or 2018\n");
      return;
    }

  if (filename.EqualTo("NONE"))
    {
      printf("\n Examples\n\n");
      printf(" root -l -b -q \'runNanoFakes.C(\"%s\", \"nanoLatino_DoubleMuon_Run2017C-31Mar2018-v1__part0\")\'\n", year.Data());
      printf(" root -l -b -q \'runNanoFakes.C(\"%s\", \"nanoLatino_SingleElectron_Run2017C-31Mar2018-v1__part0\")\'\n", year.Data());
      printf(" root -l -b -q \'runNanoFakes.C(\"%s\", \"nanoLatino_WJetsToLNu-LO__part0\")\'\n", year.Data());
      printf(" root -l -b -q \'runNanoFakes.C(\"%s\", \"nanoLatino_DYJetsToLL_M-50__part0\")\'\n", year.Data());
      printf("\n");

      return;
    }
  
  TString path = (filename.Contains("Run201")) ? path_data : path_mc;

  TChain* mychain = new TChain("Events", "Events");

  mychain->Add(path + filename + ".root");

//printf("\n Executing mychain->Process(\"/afs/cern.ch/user/c/cprieels/work/public/Fakes/CMSSW_10_1_0/src/getFakeRate/nanoFakes.C+\")...\n\n");
  printf("\n Executing mychain->Process(\"nanoFakes.C+\")...\n\n");

  TString option = year + filename;

//mychain->Process("/afs/cern.ch/user/c/cprieels/work/public/Fakes/CMSSW_10_1_0/src/getFakeRate/nanoFakes.C+", option);
  mychain->Process("nanoFakes.C+", option);
  
  return;
}
