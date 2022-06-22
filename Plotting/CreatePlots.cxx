// Plotting Framework
//
// Copyright (C) 2019-2021  Mario Krüger
// Contact: mario.kruger@cern.ch
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "/home/mhemmer/PlottingFramework/inc/PlotManager.h"
#include "TString.h"
using namespace PlottingFramework;

std::string str_raxis = "#it{r} (cm)";
std::string str_draxis = "#it{dr}_{map}-#it{dr}_{spline} (#mum)";
std::string str_phiaxis = "#it{#varphi} (rad)";
std::string str_drphiaxis = "#it{dr#varphi}_{map}-#it{dr#varphi}_{spline} (#mum)";
std::string str_zaxis = "#it{z} (cm)";
std::string str_sc= "#it{#rho}_{sc} (C/cm^{3}/#it{#epsilon}_{0})";
std::string str_sector = "sector";
std::string str_row = "padrow";
std::string str_qpt = "q/#it{p}_{T} (ec/GeV)";
std::string str_dx = "#Deltax_{local} (cm)";
std::string str_dy = "#Deltay_{local} (cm)";
std::string str_dz = "#Deltaz_{local} (cm)";
std::string str_dsinphi = "#Deltasin(#varphi)";
std::string str_dtgl = "#Deltatg#lambda";
std::string str_dqpt = "#Deltaq/#it{p}_{T} (ec/GeV)";
std::string str_phi = "#it{#varphi} (rad)";
std::string str_NCluster = "#it{N}_{cluster}";


std::vector<int> vBinning = {500, 500, 400, 200, 200, 300, 18, 200, 180};
std::vector<float> vLow   = {-2.5, -1., -4, -0.6, -0.1, -1.5, 00, 000.0, -0.0};
std::vector<float> vHigh  = {+2.5, +4., +4, +0.6, +0.1, +1.5, 18, 200.0, 2.*M_PI};
std::vector<const char*> vTStr_2 = {"X", "Y", "Z", "SinPhi", "TanLam", "QPt", "Sector", "NCluster", "Phi"};
std::vector<std::string> vCuts = {"status>=0", "NCluster_Ref>=60&&status>=0", "Z_Ref>0&&status>=0", "Z_Ref<0&&status>=0"};
std::vector<const char*> vCutName_2 = {"Standard", "NClusterCut", "A-Side", "C-Side"};

std::vector<std::string> vStr_Axis = {str_dx, str_dy, str_dz, str_dsinphi, str_dtgl, str_dqpt};
std::vector<std::string> vCutName = {"Standard", "NClusterCut", "A-Side", "C-Side"};

std::vector<std::string> vOutFileName = {"inputTPC_Tracking_PiMi_Comp_AvgCorr", "inputTPC_Tracking_PiPl_Comp_AvgCorr", "inputTPC_Tracking_PiMi_Comp_NoCorr", "inputTPC_Tracking_PiPl_Comp_NoCorr", "inputTPC_Tracking_PiMi_Comp_ResidualDist", "inputTPC_Tracking_PiPl_Comp_ResidualDist", "inputTPC_Tracking_PiMi_Comp_3DCorr", "inputTPC_Tracking_PiPl_Comp_3DCorr"};
std::vector<std::string> vCategory = {"Boxgen/PiMi/AvgCorr", "Boxgen/PiPl/AvgCorr", "Boxgen/PiMi/NoCorr", "Boxgen/PiPl/NoCorr", "Boxgen/PiMi/ResidualDist", "Boxgen/PiPl/ResidualDist", "Boxgen/PiMi/3DCorr", "Boxgen/PiPl/3DCorr"}; 
std::vector<const char*> vLatexText = {"boxgen sim #pi^{-} // avg. correction", "boxgen sim #pi^{+} // avg. correction", "boxgen sim #pi^{-} // no correction", "boxgen sim #pi^{+} // no correction", "boxgen sim #pi^{-} // residual distortion", "boxgen sim #pi^{+} // residual distortion", "boxgen sim #pi^{-} // 3D correction", "boxgen sim #pi^{+} // 3D correction"};


// helper that creates some good looking plot tempaltes you can base your plots on
void DefinePlotTemplates(PlotManager& plotManager);

// ======= minimal working example ==========
// 0. source the ".plotrc" script in the main directory of the PlottingFramework repository (best put this also it in your .bashrc, .bash_profile, or similar)
// 1. copy directory containing this example to some place on your system (outside of the PlottingFramework repository)
// 2. generate files used in this example by running 'root -l generateMWE.C'
// 3. create build folder in this directory: 'mkdir build; cd build'
// 4. cmake ../
// 5. make
// 6. ./create
// 7. play around with the features described in README.md

int main(int argc, char *argv[])
{
  // the plot manager is the central entity that handles and creates your plots
  PlotManager plotManager;

  //Standard Source------------------------------------------------------------
  // plotManager.AddInputDataFiles("input50kHz", {"/media/marvin/Samsung_T5/Arbeiten/ServiceTask/FirstResult/spaceChargeDensityHist_average.root"});
  plotManager.AddInputDataFiles("input50kHz", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/Output.root"});
  //----------------------------------------------------------------------------
  plotManager.AddInputDataFiles("inputDistCorr50kHzRandomA", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/OutputRandom_A.root"});  // Random distortion object A side
  plotManager.AddInputDataFiles("inputDistCorr50kHzRandomC", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/OutputRandom_C.root"});  // Random distortion object C side
  //----------------------------------------------------------------------------
  plotManager.AddInputDataFiles("inputCorrectionComp50kHzRandom", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/CorrectionCompProfiles.root"});
  //----------------------------------------------------------------------------
  plotManager.AddInputDataFiles("inputCorrectionComp50kHzAverage", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/CorrectionCompProfiles_Average.root"});
  //----------------------------------------------------------------------------
  plotManager.AddInputDataFiles("inputTPC_Tracking_PiMi_Comp_AvgCorr", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/FirstResult/TPC_Tracking_PiMi_Comp_AvgCorr.root"});
  plotManager.AddInputDataFiles("inputTPC_Tracking_PiPl_Comp_AvgCorr", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/FirstResult/TPC_Tracking_PiPl_Comp_AvgCorr.root"});
  plotManager.AddInputDataFiles("inputTPC_Tracking_PiMi_Comp_NoCorr", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/FirstResult/TPC_Tracking_PiMi_Comp_NoCorr.root"});
  plotManager.AddInputDataFiles("inputTPC_Tracking_PiPl_Comp_NoCorr", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/FirstResult/TPC_Tracking_PiPl_Comp_NoCorr.root"});
  plotManager.AddInputDataFiles("inputTPC_Tracking_PiMi_Comp_ResidualDist", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/FirstResult/TPC_Tracking_PiMi_Comp_ResidualDist.root"});
  plotManager.AddInputDataFiles("inputTPC_Tracking_PiPl_Comp_ResidualDist", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/FirstResult/TPC_Tracking_PiPl_Comp_ResidualDist.root"});
  plotManager.AddInputDataFiles("inputTPC_Tracking_PiMi_Comp_3DCorr", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/FirstResult/TPC_Tracking_PiMi_Comp_3DCorr.root"});
  plotManager.AddInputDataFiles("inputTPC_Tracking_PiPl_Comp_3DCorr", {"/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/FirstResult/TPC_Tracking_PiPl_Comp_3DCorr.root"});
  //----------------------------------------------------------------------------

  // save these settings to a file:
  plotManager.DumpInputDataFiles("/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/Plotting/inputFiles.XML");
  // this way you can also modify this list of input files manually in the
  // xml file and then read it into your program via
  // plotManager.LoadInputDataFiles("/media/marvin/Samsung_T5/Analyse/OmegeAnalyseConfig.XML");


  // for the comparison of the tracking performace
  std::vector<const char*> vTStr = {"Y", "Z", "SinPhi", "TGL", "QPt", "Sector", "NCluster", "Phi"};


  // for instance the following will give you some nice default plots:
  vector<int16_t> goodColors = {kGray+3, kOrange+5, kViolet+5, kTeal+5, kPink+5, kAzure+5, kSpring+5};
  vector<int16_t> goodColorsRatio = {kGray+3, kOrange+5, kViolet+5, kTeal+5, kPink+5, kAzure+5, kSpring+5};
  vector<int16_t> goodColorsFill = {kGray+2, kOrange+6, kViolet+6, kTeal+6, kPink+6, kAzure+6, kSpring+6};
  vector<int16_t> goodColorsFillRatio = {kGray+2, kOrange+6, kViolet+6, kTeal+6, kPink+6, kAzure+6, kSpring+6};
  vector<int16_t> noMarker = {1, 1, 1, 1, 1, 1, 1};
  vector<int16_t> goodMarker = {kFullCircle, kOpenCircle, kOpenSquare, kOpenDiamond, kOpenCross};
  vector<int16_t> goodMarkerRatio = {kOpenCircle, kOpenSquare, kOpenDiamond, kOpenCross};

  vector<int16_t> goodFillStyle = {3004, 3005, 3005, 3005, 3005, 3005, 3005};


  { // -----------------------------------------------------------------------
    // template 1d
    Plot templatePlot("1d_nofraction_square", "TEMPLATES");
    templatePlot.SetDimensions(710, 710, true);
    templatePlot.SetTransparent();
    templatePlot[0]['X'].SetMaxDigits(3);
    templatePlot[0]['Y'].SetMaxDigits(3);
    templatePlot[0].SetDefaultLineColors(goodColors);
    templatePlot[0].SetDefaultMarkerColors(goodColors);
    templatePlot[0].SetDefaultFillColors(goodColorsFill);
    templatePlot[0].SetDefaultFillStyles({0});
    templatePlot[0].SetDefaultMarkerStyles(noMarker);
    templatePlot[0].SetDefaultLineStyles({kSolid});
    templatePlot[0].SetDefaultTextFont(43);
    templatePlot[0].SetDefaultTextSize(24);
    templatePlot[0].SetDefaultMarkerSize(0.);
    templatePlot[0].SetDefaultLineWidth(3.);
    templatePlot[0].SetTransparent();
    templatePlot[0].SetMargins(0.05, 0.14, 0.12, 0.05);                           // top, bottom, left, right
    templatePlot[0]['X'].SetTitleOffset(1.).SetTitleSize(34).SetOppositeTicks();
    templatePlot[0]['Y'].SetTitleOffset(1.2).SetTitleSize(34).SetOppositeTicks();
    templatePlot[1].SetPosition(0., 0., 1., 1.);
    //templatePlot[1].AddText(0.433, 0.98, "my Pad Title").SetTextColor(kRed);
    plotManager.AddPlotTemplate(templatePlot);
  } // -----------------------------------------------------------------------

  { // -----------------------------------------------------------------------
    // template 2d
    Plot templatePlot("2d_squarelike", "TEMPLATES");
    templatePlot.SetDimensions(1125, 1065, true);
    templatePlot.SetTransparent();
    templatePlot[0]['X'].SetMaxDigits(3);
    templatePlot[0]['Y'].SetMaxDigits(3);
    templatePlot[0]['Z'].SetMaxDigits(3);
    templatePlot[0].SetDefaultLineColors(goodColors);
    templatePlot[0].SetDefaultMarkerColors(goodColors);
    templatePlot[0].SetDefaultFillColors(goodColorsFill);
    templatePlot[0].SetDefaultFillStyles({0});
    templatePlot[0].SetDefaultMarkerStyles(noMarker);
    templatePlot[0].SetDefaultLineStyles({kSolid});
    templatePlot[0].SetDefaultTextFont(43);
    templatePlot[0].SetDefaultTextSize(24);
    templatePlot[0].SetDefaultMarkerSize(0.);
    templatePlot[0].SetDefaultLineWidth(3.);
    templatePlot[0].SetTransparent();
    // templatePlot[0].SetPalette(52);
    templatePlot[0].SetMargins(0.04, 0.12, 0.12, 0.18);                           // top, bottom, left, right
    templatePlot[0]['X'].SetTitleOffset(1.).SetTitleSize(34).SetOppositeTicks();
    templatePlot[0]['Y'].SetTitleOffset(1.2).SetTitleSize(34).SetOppositeTicks();
    templatePlot[0]['Z'].SetTitleOffset(1.2).SetTitleSize(34).SetOppositeTicks();
    templatePlot[1].SetPosition(0., 0., 1., 1.);
    //templatePlot[1].AddText(0.433, 0.98, "my Pad Title").SetTextColor(kRed);
    plotManager.AddPlotTemplate(templatePlot);
  } // -----------------------------------------------------------------------
  { // -----------------------------------------------------------------------
    // template 2d
    Plot templatePlot("2d_candle", "TEMPLATES");
    templatePlot.SetDimensions(1125, 1065, true);
    templatePlot.SetTransparent();
    templatePlot[0]['X'].SetMaxDigits(3);
    templatePlot[0]['Y'].SetMaxDigits(3);
    templatePlot[0]['Z'].SetMaxDigits(3);
    templatePlot[0].SetDefaultTextFont(43);
    templatePlot[0].SetDefaultTextSize(24);
    templatePlot[0].SetTransparent();
    templatePlot[0].SetDefaultCandleBoxRange(0.6827);                           // 1 sigma
    templatePlot[0].SetDefaultCandleWhiskerRange(0.9545);                       // 2 sigma
    templatePlot[0].SetMargins(0.04, 0.12, 0.12, 0.18);                         // top, bottom, left, right
    templatePlot[0]['X'].SetTitleOffset(1.).SetTitleSize(34).SetOppositeTicks();
    templatePlot[0]['Y'].SetTitleOffset(1.2).SetTitleSize(34).SetOppositeTicks();
    templatePlot[0]['Z'].SetTitleOffset(1.2).SetTitleSize(34).SetOppositeTicks();
    templatePlot[1].SetPosition(0., 0., 1., 1.);
    //templatePlot[1].AddText(0.433, 0.98, "my Pad Title").SetTextColor(kRed);
    plotManager.AddPlotTemplate(templatePlot);
  } // -----------------------------------------------------------------------
  { // -----------------------------------------------------------------------
    // template 1d ratio
    Plot templatePlot("2d_ALICE_Ratio", "TEMPLATES");
    templatePlot.SetDimensions(1575, 1785, true);
    templatePlot.SetTransparent();
    templatePlot[0]['X'].SetMaxDigits(3);
    templatePlot[0]['Y'].SetMaxDigits(3);
    templatePlot[1].SetDefaultLineColors(goodColors);
    templatePlot[1].SetDefaultMarkerColors(goodColors);
    templatePlot[1].SetDefaultFillColors(goodColorsFill);
    templatePlot[2].SetDefaultLineColors(goodColorsRatio);
    templatePlot[2].SetDefaultMarkerColors(goodColorsRatio);
    templatePlot[2].SetDefaultFillColors(goodColorsFillRatio);
    templatePlot[0].SetDefaultFillStyles({0});
    templatePlot[1].SetDefaultMarkerStyles(goodMarker);
    templatePlot[2].SetDefaultMarkerStyles(goodMarkerRatio);
    templatePlot[0].SetDefaultLineStyles({kSolid});
    templatePlot[1].SetDefaultDrawingOptionHist(points);
    templatePlot[2].SetDefaultDrawingOptionHist(points_endcaps);
    templatePlot[0].SetDefaultMarkerSize(1.5);
    templatePlot[0].SetDefaultLineWidth(3.);
    templatePlot[0].SetDefaultTextFont(43);
    templatePlot[0].SetDefaultTextSize(50);
    templatePlot[0].SetTransparent();
    templatePlot[0]['X'].SetTitleOffset(1.1).SetTitleSize(54).SetTitleFont(63).SetOppositeTicks();
    templatePlot[0]['Y'].SetTitleOffset(1.5).SetTitleSize(54).SetTitleFont(63).SetOppositeTicks();
    templatePlot[1].SetPosition(0., 0.20, 1., 1.);
    templatePlot[1].SetMargins(0.05, 0.0, 0.12, 0.14);
    templatePlot[1]['X'].SetTitleSize(0.).SetLabelSize(0.);
    templatePlot[1]['Y'].SetTitleOffset(1.5).SetTitleSize(54).SetTitleFont(63);
    templatePlot[2].SetPosition(0., 0., 1., 0.20);
    templatePlot[2].SetMargins(0.015, 0.32, 0.12, 0.14);
    templatePlot[2]['X'].SetTickLength(0.06).SetTitleSize(54).SetTitleFont(63).SetTitleOffset(1.0).SetOppositeTicks();
    templatePlot[2]['Y'].SetNumDivisions(305).SetTitleSize(54).SetTitleFont(63).SetTitleOffset(1.5).SetTitleCenter();
    plotManager.AddPlotTemplate(templatePlot);
  } // -----------------------------------------------------------------------

  //Space Charge Density------------------------------------------------------
  //--------------------------------------------------------------------------
  // A-Side SP density r,phi
  {
    // create the Plot object
    Plot plot("R_Phi_A", "SpaceCharge", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("scdensity_R_Phi", "input50kHz", "r #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Z'].SetTitle(str_sc);
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density r,z
  {
    // create the Plot object
    Plot plot("R_Z_A", "SpaceCharge", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("scdensity_R_Z", "input50kHz", "r z A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle(str_sc);
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density z,phi
  {
    // create the Plot object
    Plot plot("Z_Phi_A", "SpaceCharge", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("scdensity_Z_Phi", "input50kHz", "z #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Y'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle(str_sc);
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //Distorion in Z------------------------------------------------------------
  //--------------------------------------------------------------------------
  // A-Side SP density r,phi
  {
    // create the Plot object
    Plot plot("R_Phi_A", "DistorionZ", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("distZ_R_Phi", "input50kHz", "r #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Z'].SetTitle("#Delta z (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density r,z
  {
    // create the Plot object
    Plot plot("Z_Phi_A", "DistorionZ", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("distZ_Z_Phi", "input50kHz", "z #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Y'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#Delta z (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density z,phi
  {
    // create the Plot object
    Plot plot("Z_R_A", "DistorionZ", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("distZ_R_Z", "input50kHz", "r z A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#Delta z (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //Distorion in R------------------------------------------------------------
  //--------------------------------------------------------------------------
  // A-Side SP density r,phi
  {
    // create the Plot object
    Plot plot("R_Phi_A", "DistorionR", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("distR_R_Phi", "input50kHz", "r #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Z'].SetTitle("#Delta r (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density r,z
  {
    // create the Plot object
    Plot plot("Z_Phi_A", "DistorionR", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("distR_Z_Phi", "input50kHz", "z #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Y'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#Delta r (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density z,phi
  {
    // create the Plot object
    Plot plot("Z_R_A", "DistorionR", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("distR_R_Z", "input50kHz", "r z A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#Delta r (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //Distorion in R------------------------------------------------------------
  //--------------------------------------------------------------------------
  // A-Side SP density r,phi
  {
    // create the Plot object
    Plot plot("R_Phi_A", "DistorionRPhi", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("distRPhi_R_Phi", "input50kHz", "r #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Z'].SetTitle("#it{#Delta r#varphi} (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density r,z
  {
    // create the Plot object
    Plot plot("Z_Phi_A", "DistorionRPhi", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("distRPhi_Z_Phi", "input50kHz", "z #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Y'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{#Delta r#varphi} (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density z,phi
  {
    // create the Plot object
    Plot plot("Z_R_A", "DistorionRPhi", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("distRPhi_R_Z", "input50kHz", "r z A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{#Delta r#varphi} (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //Space Charge Density Random Map 0-----------------------------------------
  //--------------------------------------------------------------------------
  // A-Side SP density r,phi
  {
    // create the Plot object
    Plot plot("R_Phi_A", "SpaceCharge", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("scdensity_R_Phi", "inputDistCorr50kHzRandomA", "r #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Z'].SetTitle(str_sc);
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density r,z
  {
    // create the Plot object
    Plot plot("R_Z_A", "SpaceCharge", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("scdensity_R_Z", "inputDistCorr50kHzRandomA", "r z A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle(str_sc);
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density z,phi
  {
    // create the Plot object
    Plot plot("Z_Phi_A", "SpaceCharge", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("scdensity_Z_Phi", "inputDistCorr50kHzRandomA", "z #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Y'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle(str_sc);
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //Distorion in Z------------------------------------------------------------
  //--------------------------------------------------------------------------
  // A-Side SP density r,phi
  {
    // create the Plot object
    Plot plot("R_Phi_A", "DistorionZ", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("distZ_R_Phi", "inputDistCorr50kHzRandomA", "r #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Z'].SetTitle("#Delta z (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density r,z
  {
    // create the Plot object
    Plot plot("Z_Phi_A", "DistorionZ", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("distZ_Z_Phi", "inputDistCorr50kHzRandomA", "z #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Y'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#Delta z (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density z,phi
  {
    // create the Plot object
    Plot plot("Z_R_A", "DistorionZ", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("distZ_R_Z", "inputDistCorr50kHzRandomA", "r z A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#Delta z (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //Distorion in R------------------------------------------------------------
  //--------------------------------------------------------------------------
  // A-Side SP density r,phi
  {
    // create the Plot object
    Plot plot("R_Phi_A", "DistorionR", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("distR_R_Phi", "inputDistCorr50kHzRandomA", "r #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Z'].SetTitle("#Delta r (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density r,z
  {
    // create the Plot object
    Plot plot("Z_Phi_A", "DistorionR", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("distR_Z_Phi", "inputDistCorr50kHzRandomA", "z #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Y'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#Delta r (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density z,phi
  {
    // create the Plot object
    Plot plot("Z_R_A", "DistorionR", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("distR_R_Z", "inputDistCorr50kHzRandomA", "r z A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#Delta r (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //Distorion in R------------------------------------------------------------
  //--------------------------------------------------------------------------
  // A-Side SP density r,phi
  {
    // create the Plot object
    Plot plot("R_Phi_A", "DistorionRPhi", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("distRPhi_R_Phi", "inputDistCorr50kHzRandomA", "r #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Z'].SetTitle("#it{#Delta r#varphi} (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density r,z
  {
    // create the Plot object
    Plot plot("Z_Phi_A", "DistorionRPhi", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("distRPhi_Z_Phi", "inputDistCorr50kHzRandomA", "z #varphi A-Side").SetContours(255).SetOptions(colz);
    plot[1]['X'].SetRange(0.0, 2.*M_PI).SetTitle(str_phiaxis);
    plot[1]['Y'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{#Delta r#varphi} (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // A-Side SP density z,phi
  {
    // create the Plot object
    Plot plot("Z_R_A", "DistorionRPhi", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz_Random");
    plot[1].AddData("distRPhi_R_Z", "inputDistCorr50kHzRandomA", "r z A-Side").SetContours(255).SetOptions(colz);
    plot[1]['Y'].SetRange(82.5, 254.5).SetTitle(str_raxis);
    plot[1]['X'].SetRange(0., 249.525).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{#Delta r#varphi} (cm)");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------


  //--------------------------------------------------------------------------
  //-----------------------Correction ComparisonRandom------------------------
  //--------------------------------------------------------------------------
  std::vector<int> vz = {0, 10, 50, 100, 150, 250};

  for (int iz = 0; iz < vz.size()-1; iz++)
  {
    //--------------------------------------------------------------------------
    //------------------------------------dr------------------------------------
    //--------------------------------------------------------------------------

    // dr (phi)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("dr_phi_z_%i_%i", vz.at(iz), vz.at(iz+1) ), "ComparisonRandom", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("dr_phi_z_%i_%i", vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_dr_phi_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
      plot[1]['X'].SetRange(-M_PI, +M_PI).SetTitle(str_phiaxis);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // dr (sector)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("dr_sector_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonRandom", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("dr_sector_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_dr_sector_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
      plot[1]['X'].SetRange(0, 18).SetTitle(str_sector);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // dr (r)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("dr_r_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonRandom", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("dr_r_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_dr_r_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
      plot[1]['X'].SetRange(83, 246).SetTitle(str_raxis);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // dr (row)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("dr_row_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonRandom", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("dr_row_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_dr_row_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
      plot[1]['X'].SetRange(0, 152).SetTitle(str_row);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //----------------------------------drphi-----------------------------------
    //--------------------------------------------------------------------------

    // drphi (phi)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("drphi_phi_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonRandom", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("drphi_phi_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_drphi_phi_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
      plot[1]['X'].SetRange(-M_PI, +M_PI).SetTitle(str_phiaxis);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // drphi (sector)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("drphi_sector_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonRandom", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("drphi_sector_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_drphi_sector_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
      plot[1]['X'].SetRange(0, 18).SetTitle(str_sector);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // drphi (r)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("drphi_r_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonRandom", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("drphi_r_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_drphi_r_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
      plot[1]['X'].SetRange(83, 246).SetTitle(str_raxis);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // drphi (row)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("drphi_row_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonRandom", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("drphi_row_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_drphi_row_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
      plot[1]['X'].SetRange(0, 152).SetTitle(str_row);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //------------------------------------dr------------------------------------
    //--------------------------------------------------------------------------

    // dr (phi)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("dr_phi_z_%i_%i", vz.at(iz), vz.at(iz+1) ), "ComparisonAverage", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("dr_phi_z_%i_%i", vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_dr_phi_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
      plot[1]['X'].SetRange(-M_PI, +M_PI).SetTitle(str_phiaxis);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // dr (sector)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("dr_sector_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonAverage", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("dr_sector_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_dr_sector_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
      plot[1]['X'].SetRange(0, 18).SetTitle(str_sector);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // dr (r)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("dr_r_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonAverage", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("dr_r_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_dr_r_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
      plot[1]['X'].SetRange(83, 246).SetTitle(str_raxis);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // dr (row)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("dr_row_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonAverage", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("dr_row_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_dr_row_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
      plot[1]['X'].SetRange(0, 152).SetTitle(str_row);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //----------------------------------drphi-----------------------------------
    //--------------------------------------------------------------------------

    // drphi (phi)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("drphi_phi_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonAverage", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("drphi_phi_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_drphi_phi_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
      plot[1]['X'].SetRange(-M_PI, +M_PI).SetTitle(str_phiaxis);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // drphi (sector)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("drphi_sector_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonAverage", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("drphi_sector_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_drphi_sector_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
      plot[1]['X'].SetRange(0, 18).SetTitle(str_sector);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // drphi (r)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("drphi_r_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonAverage", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("drphi_r_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_drphi_r_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
      plot[1]['X'].SetRange(83, 246).SetTitle(str_raxis);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------

    // drphi (row)
    //--------------------------------------------------------------------------
    {
      // create the Plot object
      Plot plot(Form("drphi_row_z_%i_%i", vz.at(iz), vz.at(iz+1)), "ComparisonAverage", "2d_squarelike");
      // optionally you can also define figure categories (and subcategories) within a figure group
      plot.SetFigureCategory("50kHz");
      plot[1].AddData(Form("drphi_row_z_%i_%i",vz.at(iz), vz.at(iz+1) ), "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
      plot[1].AddData(Form("mean_drphi_row_z_%i_%i",vz.at(iz), vz.at(iz+1)), "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
      plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
      plot[1]['X'].SetRange(0, 152).SetTitle(str_row);
      plot[1]['Z'].SetTitle("#it{count}");
      plot[1].AddText(0.41, 0.194, Form("%i<#it{z}<%i", vz.at(iz), vz.at(iz+1) ) );
      plotManager.AddPlot(plot);
    }
    //--------------------------------------------------------------------------
  }

  // dr (z) A-side
  //--------------------------------------------------------------------------
  {
    // create the Plot object
    Plot plot("dr_z_A", "ComparisonRandom", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("dr_z_A", "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
    plot[1].AddData("mean_dr_z_A", "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
    plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
    plot[1]['X'].SetRange(0., 245).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{count}");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  // drphi (z) A-side
  //--------------------------------------------------------------------------
  {
    // create the Plot object
    Plot plot("drphi_z_A", "ComparisonRandom", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("drphi_z_A", "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
    plot[1].AddData("mean_drphi_z_A", "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
    plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
    plot[1]['X'].SetRange(0., 245).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{count}");

    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  // dr (z) C-side
  //--------------------------------------------------------------------------
  {
    // create the Plot object
    Plot plot("dr_z_C", "ComparisonRandom", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("dr_z_C", "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
    plot[1].AddData("mean_dr_z_C", "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
    plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
    plot[1]['X'].SetRange(-245., 0).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{count}");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  // drphi (z)C--side
  //--------------------------------------------------------------------------
  {
    // create the Plot object
    Plot plot("drphi_z_C", "ComparisonRandom", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("drphi_z_C", "inputCorrectionComp50kHzRandom", "").SetContours(255).SetOptions(colz);
    plot[1].AddData("mean_drphi_z_C", "inputCorrectionComp50kHzRandom", "").SetColor(kOrange+5);
    plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
    plot[1]['X'].SetRange(-245., 0).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{count}");

    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  //-AVERAGE-
  //--------------------------------------------------------------------------
  // dr (z) A-side
  //--------------------------------------------------------------------------
  {
    // create the Plot object
    Plot plot("dr_z_A", "ComparisonAverage", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("dr_z_A", "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
    plot[1].AddData("mean_dr_z_A", "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
    plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
    plot[1]['X'].SetRange(0., 245).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{count}");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  // drphi (z) A-side
  //--------------------------------------------------------------------------
  {
    // create the Plot object
    Plot plot("drphi_z_A", "ComparisonAverage", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("drphi_z_A", "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
    plot[1].AddData("mean_drphi_z_A", "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
    plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
    plot[1]['X'].SetRange(0., 245).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{count}");

    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  // dr (z) C-side
  //--------------------------------------------------------------------------
  {
    // create the Plot object
    Plot plot("dr_z_C", "ComparisonAverage", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("dr_z_C", "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
    plot[1].AddData("mean_dr_z_C", "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
    plot[1]['Y'].SetRange(-250, 250).SetTitle(str_draxis);
    plot[1]['X'].SetRange(-245., 0).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{count}");
    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------

  // drphi (z)C--side
  //--------------------------------------------------------------------------
  {
    // create the Plot object
    Plot plot("drphi_z_C", "ComparisonAverage", "2d_squarelike");
    // optionally you can also define figure categories (and subcategories) within a figure group
    plot.SetFigureCategory("50kHz");
    plot[1].AddData("drphi_z_C", "inputCorrectionComp50kHzAverage", "").SetContours(255).SetOptions(colz);
    plot[1].AddData("mean_drphi_z_C", "inputCorrectionComp50kHzAverage", "").SetColor(kOrange+5);
    plot[1]['Y'].SetRange(-200, 200).SetTitle(str_drphiaxis);
    plot[1]['X'].SetRange(-245., 0).SetTitle(str_zaxis);
    plot[1]['Z'].SetTitle("#it{count}");

    plotManager.AddPlot(plot);
  }
  //--------------------------------------------------------------------------
  for (int iFile = 0; iFile < vOutFileName.size(); iFile++) {
    for (int iCut = 0; iCut < vCuts.size(); iCut++) {
      for (int iTrackVar = 0; iTrackVar <= 5; iTrackVar++) {
        TString str_plot_2d_QPt = Form( "Diff%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(5), vCutName_2.at(iCut) );
        TString str_plot_mean_QPt = Form( "MeanDiff%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(5), vCutName_2.at(iCut) );
        TString str_plot_sigma_QPt = Form( "DiffSigma%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(5), vCutName_2.at(iCut) );
        TString str_plot_2d_Sector = Form( "Diff%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(6), vCutName_2.at(iCut) );
        TString str_plot_mean_Sector = Form( "MeanDiff%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(6), vCutName_2.at(iCut) );
        TString str_plot_sigma_Sector = Form( "DiffSigma%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(6), vCutName_2.at(iCut) );
        TString str_plot_2d_NCluster = Form( "Diff%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(7), vCutName_2.at(iCut) );
        TString str_plot_mean_NCluster = Form( "MeanDiff%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(7), vCutName_2.at(iCut) );
        TString str_plot_sigma_NCluster = Form( "DiffSigma%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(7), vCutName_2.at(iCut) );
        TString str_plot_2d_Phi = Form( "Diff%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(8), vCutName_2.at(iCut) );
        TString str_plot_mean_Phi = Form( "MeanDiff%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(8), vCutName_2.at(iCut) );
        TString str_plot_sigma_Phi = Form( "DiffSigma%s_%s_%s", vTStr_2.at(iTrackVar), vTStr_2.at(8), vCutName_2.at(iCut) );
        
        //--------------------------------------------------------------------------
        {
          // create the Plot object
          Plot plot(str_plot_2d_QPt.Data(), "ComparisonTracking", "2d_squarelike");
          // optionally you can also define figure categories (and subcategories) within a figure group
          plot.SetFigureCategory(vCategory.at(iFile));
          plot[1].AddData(str_plot_2d_QPt.Data(), vOutFileName.at(iFile), "").SetContours(255).SetOptions(colz);
          plot[1].AddData(str_plot_mean_QPt.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[1]['Y'].SetTitle(vStr_Axis.at(iTrackVar));
          plot[1]['X'].SetTitle(str_qpt).SetRange(-1.5, 0.5);
          plot[1]['Z'].SetTitle("#it{count}").SetLog();
          plot[1].AddText(0.2, 0.9, Form("%s // %s", vLatexText.at(iFile), vCutName_2.at(iCut) ) ) ;
          plotManager.AddPlot(plot);
        }
        //--------------------------------------------------------------------------
        {
          // create the Plot object
          Plot plot(str_plot_2d_QPt.Data(), "ComparisonTracking", "2d_ALICE_Ratio");
          // optionally you can also define figure categories (and subcategories) within a figure group
          plot.SetFigureCategory(vCategory.at(iFile) + "/Sigma");
          plot[1].AddData(str_plot_2d_QPt.Data(), vOutFileName.at(iFile), "").SetContours(255).SetOptions(colz);
          plot[1].AddData(str_plot_mean_QPt.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[2].AddData(str_plot_sigma_QPt.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[1]['Y'].SetTitle(vStr_Axis.at(iTrackVar));
          if(iTrackVar == 0)
          {
            plot[1].AddData("f1", vOutFileName.at(iFile), "").SetColor(kBlack);
            plot[1].AddData("f2", vOutFileName.at(iFile), "").SetColor(kBlack);
            plot[1]['Y'].SetRange(-0.5,0.5);
          }
          plot[1]['Z'].SetTitle("#it{count}").SetLog();
          plot[2]['Y'].SetTitle("#sigma");
          plot[2]['X'].SetTitle(str_qpt).SetRange(-1.5, 0.5);
          plot[1].AddText(0.2, 0.9, Form("%s // %s", vLatexText.at(iFile), vCutName_2.at(iCut) ) ) ;
          plotManager.AddPlot(plot);
        }
        //--------------------------------------------------------------------------
        {
          // create the Plot object
          Plot plot(str_plot_2d_Sector.Data(), "ComparisonTracking", "2d_squarelike");
          // optionally you can also define figure categories (and subcategories) within a figure group
          plot.SetFigureCategory(vCategory.at(iFile));
          plot[1].AddData(str_plot_2d_Sector.Data(), vOutFileName.at(iFile), "").SetContours(255).SetOptions(colz);
          plot[1].AddData(str_plot_mean_Sector.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[1]['Y'].SetTitle(vStr_Axis.at(iTrackVar));
          plot[1]['X'].SetTitle(str_sector);
          plot[1]['Z'].SetTitle("#it{count}").SetLog();
          plot[1].AddText(0.2, 0.9, Form("%s // %s", vLatexText.at(iFile), vCutName_2.at(iCut) ) ) ;
          plotManager.AddPlot(plot);
        }
        //--------------------------------------------------------------------------
        {
          // create the Plot object
          Plot plot(str_plot_2d_Sector.Data(), "ComparisonTracking", "2d_ALICE_Ratio");
          // optionally you can also define figure categories (and subcategories) within a figure group
          plot.SetFigureCategory(vCategory.at(iFile) + "/Sigma");
          plot[1].AddData(str_plot_2d_Sector.Data(), vOutFileName.at(iFile), "").SetContours(255).SetOptions(colz);
          plot[1].AddData(str_plot_mean_Sector.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[2].AddData(str_plot_sigma_Sector.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[1]['Y'].SetTitle(vStr_Axis.at(iTrackVar));
          if(iTrackVar == 0)
          {
            plot[1].AddData("f1", "inputTPC_Tracking_PiMi_Comp_NoCorr", "").SetColor(kBlack);
            plot[1].AddData("f2", "inputTPC_Tracking_PiMi_Comp_NoCorr", "").SetColor(kBlack);
            plot[1]['Y'].SetRange(-0.5,0.5);
          }
          plot[1]['Z'].SetTitle("#it{count}").SetLog();
          plot[2]['Y'].SetTitle("#sigma");
          plot[2]['X'].SetTitle(str_sector);
          plot[1].AddText(0.2, 0.9, Form("%s // %s", vLatexText.at(iFile), vCutName_2.at(iCut) ) ) ;
          plotManager.AddPlot(plot);
        }
        //--------------------------------------------------------------------------
        {
          // create the Plot object
          Plot plot(str_plot_2d_NCluster.Data(), "ComparisonTracking", "2d_squarelike");
          // optionally you can also define figure categories (and subcategories) within a figure group
          plot.SetFigureCategory(vCategory.at(iFile));
          plot[1].AddData(str_plot_2d_NCluster.Data(), vOutFileName.at(iFile), "").SetContours(255).SetOptions(colz);
          plot[1].AddData(str_plot_mean_NCluster.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[1]['Y'].SetTitle(vStr_Axis.at(iTrackVar));
          plot[1]['X'].SetTitle(str_NCluster);
          plot[1]['Z'].SetTitle("#it{count}").SetLog();
          plot[1].AddText(0.2, 0.9, Form("%s // %s", vLatexText.at(iFile), vCutName_2.at(iCut) ) ) ;
          plotManager.AddPlot(plot);
        }
        //--------------------------------------------------------------------------
        {
          // create the Plot object
          Plot plot(str_plot_2d_NCluster.Data(), "ComparisonTracking", "2d_ALICE_Ratio");
          // optionally you can also define figure categories (and subcategories) within a figure group
          plot.SetFigureCategory(vCategory.at(iFile) + "/Sigma");
          plot[1].AddData(str_plot_2d_NCluster.Data(), vOutFileName.at(iFile), "").SetContours(255).SetOptions(colz);
          plot[1].AddData(str_plot_mean_NCluster.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[2].AddData(str_plot_sigma_NCluster.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[1]['Y'].SetTitle(vStr_Axis.at(iTrackVar));
          if(iTrackVar == 0)
          {
            plot[1].AddData("f1", vOutFileName.at(iFile), "").SetColor(kBlack);
            plot[1].AddData("f2", vOutFileName.at(iFile), "").SetColor(kBlack);
            plot[1]['Y'].SetRange(-0.5,0.5);
          }
          plot[1]['Z'].SetTitle("#it{count}").SetLog();
          plot[2]['Y'].SetTitle("#sigma");
          plot[2]['X'].SetTitle(str_NCluster);
          plot[1].AddText(0.2, 0.9, Form("%s // %s", vLatexText.at(iFile), vCutName_2.at(iCut) ) ) ;
          plotManager.AddPlot(plot);
        }
        //--------------------------------------------------------------------------
        {
          // create the Plot object
          Plot plot(str_plot_2d_Phi.Data(), "ComparisonTracking", "2d_squarelike");
          // optionally you can also define figure categories (and subcategories) within a figure group
          plot.SetFigureCategory(vCategory.at(iFile));
          plot[1].AddData(str_plot_2d_Phi.Data(), vOutFileName.at(iFile), "").SetContours(255).SetOptions(colz);
          plot[1].AddData(str_plot_mean_Phi.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[1]['Y'].SetTitle(vStr_Axis.at(iTrackVar));
          plot[1]['X'].SetTitle(str_phi);
          plot[1]['Z'].SetTitle("#it{count}").SetLog();
          plot[1].AddText(0.2, 0.9, Form("%s // %s", vLatexText.at(iFile), vCutName_2.at(iCut) ) ) ;
          plotManager.AddPlot(plot);
        }
        //--------------------------------------------------------------------------
        {
          // create the Plot object
          Plot plot(str_plot_2d_Phi.Data(), "ComparisonTracking", "2d_candle");
          // optionally you can also define figure categories (and subcategories) within a figure group
          plot.SetFigureCategory(vCategory.at(iFile)+ "/Candle");
          plot[1].AddData(str_plot_2d_Phi.Data(), vOutFileName.at(iFile), "").SetOptions(candle7);
          if(iTrackVar == 0)
          {
            plot[1].AddData("f1", vOutFileName.at(iFile), "").SetColor(kBlack);
            plot[1].AddData("f2", vOutFileName.at(iFile), "").SetColor(kBlack);
            plot[1]['Y'].SetRange(-0.5,0.5);
          }
          plot[1]['Y'].SetTitle(vStr_Axis.at(iTrackVar));
          plot[1]['X'].SetTitle(str_phi);
          plot[1]['Z'].SetTitle("#it{count}").SetLog();
          plot[1].AddText(0.2, 0.9, Form("%s // %s", vLatexText.at(iFile), vCutName_2.at(iCut) ) ) ;
          plotManager.AddPlot(plot);
        }
        //--------------------------------------------------------------------------
        {
          // create the Plot object
          Plot plot(str_plot_2d_Phi.Data(), "ComparisonTracking", "2d_ALICE_Ratio");
          // optionally you can also define figure categories (and subcategories) within a figure group
          plot.SetFigureCategory(vCategory.at(iFile) + "/Sigma");
          plot[1].AddData(str_plot_2d_Phi.Data(), vOutFileName.at(iFile), "").SetContours(255).SetOptions(colz);
          plot[1].AddData(str_plot_mean_Phi.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[2].AddData(str_plot_sigma_Phi.Data(), vOutFileName.at(iFile), "").SetColor(kOrange+5);
          plot[1]['Y'].SetTitle(vStr_Axis.at(iTrackVar));
          if(iTrackVar == 0)
          {
            plot[1].AddData("f1", vOutFileName.at(iFile), "").SetColor(kBlack);
            plot[1].AddData("f2", vOutFileName.at(iFile), "").SetColor(kBlack);
            plot[1]['Y'].SetRange(-0.5,0.5);
          }
          plot[1]['Z'].SetTitle("#it{count}").SetLog();
          plot[2]['Y'].SetTitle("#sigma");
          plot[2]['X'].SetTitle(str_phi);
          plot[1].AddText(0.2, 0.9, Form("%s // %s", vLatexText.at(iFile), vCutName_2.at(iCut) ) ) ;
          plotManager.AddPlot(plot);
        }
      }
    }
  }
  // End of cut loop
  //----------------------------------------------------------------------------
  // to save the plots to disk as pdf you first have to tell the manager where to put them
  plotManager.SetOutputDirectory("/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/Plotting/Pictures");
  // the manager will automatically create subfolders for the figure groups and categories
  // to generate all stored plots as pdf you can call
  plotManager.DumpPlots("/media/mhemmer/Samsung_T5/Arbeiten/ServiceTask/Plotting/plotDefinitions.XML");
  // plotManager.CreatePlots("", "", { }, "pdf");

  return 0;
}
