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

std::string str_xglobal = "#it{x}_{global}";
std::string str_yglobal = "#it{y}_{global}";
std::string str_xlocal = "#it{x}_{local}";
std::string str_ylocal = "#it{y}_{local}";
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

std::vector<int> vz = {0, 10, 50, 100, 150, 250};
std::vector<TString> CT = {"(rC-rT)*10000"};
std::vector<TString> CCD = {"(rC+rCD)*10000"};
std::vector<TString> DCD = {"(rDC+rD)*10000"};
// std::vector<TString> DTD = {"(rDC+rD)*10000"};

std::string Var_CT = {"d#it{r}_{CT} (#mum)"};
std::string Var_CCD = {"d#it{r}_{CCD} (#mum)"};
std::string Var_DCD = {"d#it{r}_{DCD} (#mum)"};
// std::vector<std::string> vVar_DTD = {"d#it{r}_{DTD} (#mum)"};

std::vector<TString> Variable = {"dr"};
std::vector<TString> VariableBinning = {"600,-150,150"};

std::vector<TString> Cut = {"inTPC==0"};
std::vector<TString> CutName = {"inTPC"};

                              // 0    1    2         3             4         5
std::vector<TString> Axis = {"phi", "row","r", "phi/3.1415*18", "gx:gy", "lx:ly"};
std::vector<TString> AxisText{"phi", "row", "r", "sector", "gxy" ,"lxy"};
std::vector<std::string> AxisText_2{"#varphi (rad)", "row", "#it{r} cm", "sector"};
std::vector<TString> AxisBinning = {"360,-3.1415,3.1415", "152,0,152", "280,0,280", "18,0,18", "500,-250,250,500,-250,250", "200,-50,50,340,80,250"};
std::vector<std::string> vInput = {"inputSplinevs3D", "input3DSpline"};
std::vector<std::string> vStructure = {"Spline_vs_3D", "3D_for_Splines"};
std::vector<std::vector<std::string>> v2Daxis = {{str_xglobal, str_yglobal}, {str_xlocal, str_ylocal}};



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

  //Spline vs 3D Corr Comparison Source------------------------------------------------------------
  plotManager.AddInputDataFiles("inputSplinevs3D", {"/home/mhemmer/Documents/ServiceTask/Trees/CorrectionCompProfilesSplines_Average.root"});  // Comparison between Spline and 3D corr.
  plotManager.AddInputDataFiles("input3DSpline", {"/home/mhemmer/Documents/ServiceTask/Trees/CorrectionCompProfiles_Average.root"});  // Loads 3D Corr. instead of Splines, sanity check file!
  //----------------------------------------------------------------------------


  // save these settings to a file:
  plotManager.DumpInputDataFiles("/home/mhemmer/Documents/ServiceTask/Plotting/inputFiles.XML");
  // this way you can also modify this list of input files manually in the
  // xml file and then read it into your program via
  // plotManager.LoadInputDataFiles("/media/marvin/Samsung_T5/Analyse/OmegeAnalyseConfig.XML");

  // for instance the following will give you some nice default plots:
  std::vector<int16_t> goodColors = {kGray+3, kOrange+5, kViolet+5, kTeal+5, kPink+5, kAzure+5, kSpring+5};
  std::vector<int16_t> goodColorsRatio = {kGray+3, kOrange+5, kViolet+5, kTeal+5, kPink+5, kAzure+5, kSpring+5};
  std::vector<int16_t> goodColorsFill = {kGray+2, kOrange+6, kViolet+6, kTeal+6, kPink+6, kAzure+6, kSpring+6};
  std::vector<int16_t> goodColorsFillRatio = {kGray+2, kOrange+6, kViolet+6, kTeal+6, kPink+6, kAzure+6, kSpring+6};
  std::vector<int16_t> noMarker = {1, 1, 1, 1, 1, 1, 1};
  std::vector<int16_t> goodMarker = {kFullCircle, kOpenCircle, kOpenSquare, kOpenDiamond, kOpenCross};
  std::vector<int16_t> goodMarkerRatio = {kOpenCircle, kOpenSquare, kOpenDiamond, kOpenCross};
  std::vector<int16_t> goodFillStyle = {3004, 3005, 3005, 3005, 3005, 3005, 3005};


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

  // -------------------------------------------------------------------------
  for ( int i_var = 0; i_var < Variable.size(); i_var++)
  {
    for (int i_axis = 0; i_axis < Axis.size(); i_axis++)
    {
      for (int i = 0; i < vz.size()-1; i++)
      {
        for(int i_input = 0; i_input < vInput.size(); i_input++)
        {
          // TString for z slice cut
          TString z_cut = Form("gz<%i&&gz>%i&&" + Cut.at(0), vz.at(i+1), vz.at(i) );

          // TStrings for plotting (histo name and tree->Draw("THIS"))
          // 3D correction - Splines
          TString str_histo_CT = Form( TString(Variable.at(i_var) + "_" + AxisText.at(i_axis) + "_z_%i_%i_CT"),vz.at(i), vz.at(i+1) );
          TString str_mean_CT = Form( TString("mean_" + Variable.at(i_var) + "_" + AxisText.at(i_axis) + "_z_%i_%i_CT"),vz.at(i), vz.at(i+1) );

          // 3D correction + 3D distortion at corrected points
          TString str_histo_CCD = Form( TString(Variable.at(i_var) + "_" + AxisText.at(i_axis) + "_z_%i_%i_CCD"),vz.at(i), vz.at(i+1) );
          TString str_mean_CCD = Form( TString("mean_" + Variable.at(i_var) + "_" + AxisText.at(i_axis) + "_z_%i_%i_CCD"),vz.at(i), vz.at(i+1) );

          // 3D correction at distorted points + 3D distortion
          TString str_histo_DCD = Form( TString(Variable.at(i_var) + "_" + AxisText.at(i_axis) + "_z_%i_%i_DCD"),vz.at(i), vz.at(i+1) );
          TString str_mean_DCD = Form( TString("mean_" + Variable.at(i_var) + "_" + AxisText.at(i_axis) + "_z_%i_%i_DCD"),vz.at(i), vz.at(i+1) );
          if(i_axis < 4)
          {
            // CT
            //-----------------------------------------------------------------
            {
              Plot plot(str_histo_CT.Data(), "Spline_vs_3DCorr", "2d_squarelike");
              plot.SetFigureCategory(vStructure.at(i_input));
              plot[1].AddData(str_histo_CT.Data(), vInput.at(i_input), "").SetContours(255).SetOptions(colz);
              plot[1].AddData(str_mean_CT.Data(), vInput.at(i_input), "").SetColor(kTeal+5);
              plot[1]['X'].SetTitle(AxisText_2.at(i_axis));
              plot[1]['Y'].SetTitle(Var_CT);
              plot[1]['Z'].SetTitle("#it{counts}");
              plotManager.AddPlot(plot);
            }
            // CCD
            //-----------------------------------------------------------------
            {
              Plot plot(str_histo_CCD.Data(), "Spline_vs_3DCorr", "2d_squarelike");
              plot.SetFigureCategory(vStructure.at(i_input));
              plot[1].AddData(str_histo_CCD.Data(), vInput.at(i_input), "").SetContours(255).SetOptions(colz);
              plot[1].AddData(str_mean_CCD.Data(), vInput.at(i_input), "").SetColor(kTeal+5);
              plot[1]['X'].SetTitle(AxisText_2.at(i_axis));
              plot[1]['Y'].SetTitle(Var_CCD);
              plot[1]['Z'].SetTitle("#it{counts}");
              plotManager.AddPlot(plot);
            }
            // DCD
            //-----------------------------------------------------------------
            {
              Plot plot(str_histo_DCD.Data(), "Spline_vs_3DCorr", "2d_squarelike");
              plot.SetFigureCategory(vStructure.at(i_input));
              plot[1].AddData(str_histo_DCD.Data(), vInput.at(i_input), "").SetContours(255).SetOptions(colz);
              plot[1].AddData(str_mean_DCD.Data(), vInput.at(i_input), "").SetColor(kTeal+5);
              plot[1]['X'].SetTitle(AxisText_2.at(i_axis));
              plot[1]['Y'].SetTitle(Var_DCD);
              plot[1]['Z'].SetTitle("#it{counts}");
              plotManager.AddPlot(plot);
            }
          }
          else
          {
            // CT
            //-----------------------------------------------------------------
            {
              Plot plot(str_histo_CT.Data(), "Spline_vs_3DCorr", "2d_squarelike");
              plot.SetFigureCategory(vStructure.at(i_input));
              plot[1].AddData(str_mean_CT.Data(), vInput.at(i_input), "").SetContours(255).SetOptions(colz);
              plot[1]['X'].SetTitle(v2Daxis.at(i_axis - 4).at(0) );
              plot[1]['Y'].SetTitle(v2Daxis.at(i_axis - 4).at(1) );
              plot[1]['Z'].SetTitle(Var_CT);
              plotManager.AddPlot(plot);
            }
            // CCD
            //-----------------------------------------------------------------
            {
              Plot plot(str_histo_CCD.Data(), "Spline_vs_3DCorr", "2d_squarelike");
              plot.SetFigureCategory(vStructure.at(i_input));
              plot[1].AddData(str_mean_CCD.Data(), vInput.at(i_input), "").SetContours(255).SetOptions(colz);
              plot[1]['X'].SetTitle(v2Daxis.at(i_axis - 4).at(0) );
              plot[1]['Y'].SetTitle(v2Daxis.at(i_axis - 4).at(1) );
              plot[1]['Z'].SetTitle(Var_CCD).SetRange(-18,23);
              plotManager.AddPlot(plot);
            }
            // DCD
            //-----------------------------------------------------------------
            {
              Plot plot(str_histo_DCD.Data(), "Spline_vs_3DCorr", "2d_squarelike");
              plot.SetFigureCategory(vStructure.at(i_input));
              plot[1].AddData(str_mean_DCD.Data(), vInput.at(i_input), "").SetContours(255).SetOptions(colz);
              plot[1]['X'].SetTitle(v2Daxis.at(i_axis - 4).at(0) );
              plot[1]['Y'].SetTitle(v2Daxis.at(i_axis - 4).at(1) );
              plot[1]['Z'].SetTitle(Var_DCD).SetRange(-18,23);
              plotManager.AddPlot(plot);
            }
          }
        }
      } // end of loop over z
    } // end of loop over different axis
  } // end of loop over different variables
  //---------------------------------------------------------------------------
  // to save the plots to disk as pdf you first have to tell the manager where to put them
  plotManager.SetOutputDirectory("/home/mhemmer/Documents/ServiceTask/Pictures");
  // the manager will automatically create subfolders for the figure groups and categories
  // to generate all stored plots as pdf you can call
  plotManager.DumpPlots("/home/mhemmer/Documents/ServiceTask/Plotting/plotDefinitions.XML");
  // plotManager.CreatePlots("", "", { }, "pdf");

  return 0;
}
