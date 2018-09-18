//------------------------------------------------------------------------------
//
//      Target: Check nanoLatino trees
//     Authors: Jonatan Piedra, Cedric Prieels
// Last update: August 2nd, 2018
//
//------------------------------------------------------------------------------
TString path_mc = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Fall2017_nAOD_v1_Study2017/MCl1loose2017__baseW__hadd/";
TString path_data = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2017_nAOD_v1_Study2017/DATAl1loose2017__hadd/";


void runNanoFakes(TString filename = "NONE")
{
  if (filename.EqualTo("NONE"))
    {
      printf("\n Examples\n\n");
      printf(" root -l -b -q \'runNanoFakes.C(\"DoubleMuon_Run2017C-31Mar2018-v1__part0\")\'\n");
      printf(" root -l -b -q \'runNanoFakes.C(\"DoubleEG_Run2017C-31Mar2018-v1__part0\")\'\n");
      printf(" root -l -b -q \'runNanoFakes.C(\"WJetsToLNu-LO__part0\")\'\n");
      printf(" root -l -b -q \'runNanoFakes.C(\"DYJetsToLL_M-50__part0\")\'\n");
      printf("\n");
      
      return;
    }
  
  TString path = (filename.Contains("Run2017")) ? path_data : path_mc;

  TChain* mychain = new TChain("Events", "Events");
  mychain->Add(path + filename + ".root");

  printf("\nExecuting mychain->Process(\"nanoFakes.C+\")...\n\n");

  mychain->Process("nanoFakes.C+", filename);

  return;
}
