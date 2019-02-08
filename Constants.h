#if !defined(MYLIB_CONSTANTS_H)
#define MYLIB_CONSTANTS_H 1

const double lumi_fb_Run2016BCD = 12.610;  // 2016B + 2016C + 2016D
const double lumi_fb_Run2016B   =  5.788;  // From run 272007 to run 275376
const double lumi_fb_2016_susy  =  9.983;  // run<276502
const double lumi_fb_2015       =  2.318;  // 2015C + 2015D35867.060
const double lumi_fb_Full2016   = 35.867;  // 2016B to 2016H
const double lumi_error_percent =  2.6;    // Preliminary

const int ELECTRON_FLAVOUR = 11;
const int MUON_FLAVOUR     = 13;
const int TAU_FLAVOUR      = 15;
const int Z_FLAVOUR        = 23;

const double BOTTOM_MASS   =   4.18;      // [GeV]
const double TOP_MASS      = 173.34;      // [GeV]
const double ELECTRON_MASS =   0.000511;  // [GeV]
const double MUON_MASS     =   0.106;     // [GeV]
const double TAU_MASS      =   1.777;     // [GeV]
const double Z_MASS        =  91.188;     // [GeV]
const double H_MASS        = 125.0;       // [GeV]

// Process colors
//------------------------------------------------------------------------------
const Color_t color_Prefit    = kBlue+1;
const Color_t color_Signal    = kRed;
const Color_t color_Fakes     = kGray+1;
const Color_t color_Data      = kBlack;
const Color_t color_WZTo3LNu  = kOrange-2;
const Color_t color_VZ        = kOrange+3;
const Color_t color_TTTo2L2Nu = kYellow;
const Color_t color_ST        = kYellow+3;
const Color_t color_WW        = kAzure-9;
const Color_t color_ZJets     = kGreen+2;
const Color_t color_ZJetsToTT = kGreen+3;
const Color_t color_WJets     = kGray+1;
const Color_t color_TTV       = kGreen-6;
const Color_t color_TTZ       = kOrange+2;
const Color_t color_HWW       = kAzure-7;
const Color_t color_Wg        = kBlue;
const Color_t color_WgStar    = kBlue+2;
const Color_t color_Zg        = kTeal;
const Color_t color_VVV       = kYellow-6;
const Color_t color_HZ        = kOrange+1;

// Branching ratios
//------------------------------------------------------------------------------
const double W2e     = 0.1075;
const double W2m     = 0.1057;
const double W2tau   = 0.1125;
const double Z2ll    = 0.033658;
const double WZ23lnu = 3 * Z2ll * (W2e + W2m + W2tau);
const double WW2lnu  = (W2e + W2m + W2tau) * (W2e + W2m + W2tau);

const int njetbin = 3;  // 0jet, 1jet, 2+jet, all

enum {roc_background, roc_signal, roc_none};

#endif
