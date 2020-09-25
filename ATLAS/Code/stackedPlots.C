#include "fileHelper.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "string.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"

using namespace std;

void SetStyle();
void PlotStack(TString path, TString varUnit, THStack * mc, TH1F * data, TLegend * legend);

int main() {
  //float ttbar_xsec = 252.82e-13;
  //float singletop_xsec = 52.47e-13;
  //float diboson_xsec = 29.41e-13;
  //float z_jets_xsec = 2516.2e-13;
  //float w_jets_xsec = 36214e-13;
  //
  //// events
  //float ttbar_events = 7847944;
  //float singletop_events = 1468942;
  //float diboson_events = 922521;
  //float z_jets_events = 37422926;
  //float w_jets_events = 66536222;
  //
  //float lumi = 1e15; // inverse femtobarn
  
  double intlumi = 100;

  int n_ttbar = 7847944;
  double xsec_ttbar = 252.82;

  int n_singletop = 1468942;
  double xsec_singletop = 52.47;

  int n_diboson = 922521;
  double xsec_diboson = 29.41;

  int n_zjets = 37422926;
  double xsec_zjets = 2516.2;

  int n_wjets = 66536222;
  double xsec_wjets = 36214;  

    // weights
  float w_ttbar      = intlumi*xsec_ttbar      / n_ttbar;     
  float w_singletop  = intlumi*xsec_singletop  / n_singletop; 
  float w_diboson    = intlumi*xsec_diboson    / n_diboson;   
  float w_zjets      = intlumi*xsec_zjets      / n_zjets;    
  float w_wjets      = intlumi*xsec_wjets      / n_wjets;    
    
    
  
  //float w_ttbar      = lumi*ttbar_xsec      / ttbar_events;     
  //float w_singletop  = lumi*singletop_xsec  / singletop_events; 
  //float w_diboson    = lumi*diboson_xsec    / diboson_events;   
  //float w_zjets      = lumi*z_jets_xsec     / z_jets_events;    
  //float w_wjets      = lumi*w_jets_xsec     / w_jets_events;
  
  ////////////////////////////////////////////////////////////////////////////////
  // This file can guide you through the process of combining monte carlo and data
  ///////////////////////////////////////////////////////////////////////////////

  // Let's say you want to have all the relevant plots in one file, this is how you create it
  TFile * analysis = new TFile("analysis.root", "RECREATE");

  // now you have to get the histograms you want to use. If you have saved them in another file beforehand, you can get them this way:
  // TFile * file_histogram1 = new TFile("name_of_file_where_you_saved_histogram1.root");
  // TH1F * h_histogram1 = (TH1F*)file_histogram1->Get("name_of_variable");
  
  //This is for the Mass of the Full System used as the Discriminant 
  
  TFile * data_disc = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_SysJetMass_hist.root");
  TH1F * h_data_mass = (TH1F*)data_disc->Get("FullSysMass");
  THStack * hs_FullMass = new THStack("hs_FullMass", "");
  TFile * tt_mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_SysJetMass_hist.root");
  TH1F * h_tt_disc = (TH1F*)tt_mass->Get("FullSysMass");
  TFile * st_mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_SysJetMass_hist.root");
  TH1F * h_st_disc = (TH1F*)st_mass->Get("FullSysMass");
  TFile * db_mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_SysJetMass_hist.root");
  TH1F * h_db_disc = (TH1F*)db_mass->Get("FullSysMass");
  TFile * zj_mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_SysJetMass_hist.root");
  TH1F * h_zj_disc = (TH1F*)zj_mass->Get("FullSysMass");
  TFile * wj_mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_SysJetMass_hist.root");
  TH1F * h_wj_disc = (TH1F*)wj_mass->Get("FullSysMass");
  
  h_tt_disc->Scale(w_ttbar);
  h_st_disc->Scale(w_singletop);
  h_db_disc->Scale(w_diboson);
  h_zj_disc->Scale(w_zjets);
  h_wj_disc->Scale(w_wjets);
  
  hs_FullMass->Add(h_tt_disc);
  hs_FullMass->Add(h_st_disc);
  hs_FullMass->Add(h_db_disc);
  hs_FullMass->Add(h_zj_disc);
  hs_FullMass->Add(h_wj_disc);
  
  // This is for the pseudorapidity of the Full System
  TFile * data_fulleta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_FullSysEta_hist.root");
  TH1F * h_data_fulleta = (TH1F*)data_fulleta->Get("FullSysEta");
  THStack * hs_fulleta = new THStack("hs_fulleta", "");
  TFile * tt_fulleta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_FullSysEta_hist.root");
  TH1F * h_tt_fulleta = (TH1F*)tt_fulleta->Get("FullSysEta");
  TFile * st_fulleta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_FullSysEta_hist.root");
  TH1F * h_st_fulleta = (TH1F*)st_fulleta->Get("FullSysEta");
  TFile * db_fulleta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_FullSysEta_hist.root");
  TH1F * h_db_fulleta = (TH1F*)db_fulleta->Get("FullSysEta");
  TFile * zj_fulleta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_FullSysEta_hist.root");
  TH1F * h_zj_fulleta = (TH1F*)zj_fulleta->Get("FullSysEta");
  TFile * wj_fulleta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_FullSysEta_hist.root");
  TH1F * h_wj_fulleta = (TH1F*)wj_fulleta->Get("FullSysEta");
  
  h_tt_fulleta->Scale(w_ttbar);
  h_st_fulleta->Scale(w_singletop);
  h_db_fulleta->Scale(w_diboson);
  h_zj_fulleta->Scale(w_zjets);
  h_wj_fulleta->Scale(w_wjets);
  
  hs_fulleta->Add(h_tt_fulleta);
  hs_fulleta->Add(h_st_fulleta);
  hs_fulleta->Add(h_db_fulleta);
  hs_fulleta->Add(h_zj_fulleta);
  hs_fulleta->Add(h_wj_fulleta);
  
  //This is for Delta Phi
  TFile * data_deltaphi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_DeltaPhi_hist.root");
  TH1F * h_data_deltaphi = (TH1F*)data_deltaphi->Get("DeltaPhi");
  THStack * hs_deltaphi = new THStack("hs_deltaphi", "");
  TFile * tt_deltaphi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_DeltaPhi_hist.root");
  TH1F * h_tt_deltaphi = (TH1F*)tt_deltaphi->Get("DeltaPhi");
  TFile * st_deltaphi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_DeltaPhi_hist.root");
  TH1F * h_st_deltaphi = (TH1F*)st_deltaphi->Get("DeltaPhi");
  TFile * db_deltaphi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_DeltaPhi_hist.root");
  TH1F * h_db_deltaphi = (TH1F*)db_deltaphi->Get("DeltaPhi");
  TFile * zj_deltaphi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_DeltaPhi_hist.root");
  TH1F * h_zj_deltaphi = (TH1F*)zj_deltaphi->Get("DeltaPhi");
  TFile * wj_deltaphi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_DeltaPhi_hist.root");
  TH1F * h_wj_deltaphi = (TH1F*)wj_deltaphi->Get("DeltaPhi");
  
  h_tt_deltaphi->Scale(w_ttbar);
  h_st_deltaphi->Scale(w_singletop);
  h_db_deltaphi->Scale(w_diboson);
  h_zj_deltaphi->Scale(w_zjets);
  h_wj_deltaphi->Scale(w_wjets);
  
  hs_deltaphi->Add(h_tt_deltaphi);
  hs_deltaphi->Add(h_st_deltaphi);
  hs_deltaphi->Add(h_db_deltaphi);
  hs_deltaphi->Add(h_zj_deltaphi);
  hs_deltaphi->Add(h_wj_deltaphi);
  
  //This is for the btagged jet 
  TFile * data_btagged = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_btagged_hist.root");
  TH1F * h_data_btagged = (TH1F*)data_btagged->Get("btagged");
  THStack * hs_btagged = new THStack("hs_btagged", "");
  TFile * tt_btagged = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_btagged_hist.root");
  TH1F * h_tt_btagged = (TH1F*)tt_btagged->Get("btagged");
  TFile * st_btagged = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_btagged_hist.root");
  TH1F * h_st_btagged = (TH1F*)st_btagged->Get("btagged");
  TFile * db_btagged = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_btagged_hist.root");
  TH1F * h_db_btagged = (TH1F*)db_btagged->Get("btagged");
  TFile * zj_btagged = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_btagged_hist.root");
  TH1F * h_zj_btagged = (TH1F*)zj_btagged->Get("btagged");
  TFile * wj_btagged = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_btagged_hist.root");
  TH1F * h_wj_btagged = (TH1F*)wj_btagged->Get("btagged");
  
  h_tt_btagged->Scale(w_ttbar);
  h_st_btagged->Scale(w_singletop);
  h_db_btagged->Scale(w_diboson);
  h_zj_btagged->Scale(w_zjets);
  h_wj_btagged->Scale(w_wjets);
  
  hs_btagged->Add(h_tt_btagged);
  hs_btagged->Add(h_st_btagged);
  hs_btagged->Add(h_db_btagged);
  hs_btagged->Add(h_zj_btagged);
  hs_btagged->Add(h_wj_btagged);
  //This is for lepton pt
  TFile * data_lep_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_lep_pt_hist.root");
  TH1F * h_data_lep_pt = (TH1F*)data_lep_pt->Get("lep_pt");
  THStack * hs_lep_pt = new THStack("hs_lep_pt", "");
  TFile * tt_lep_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_lep_pt_hist.root");
  TH1F * h_tt_lep_pt = (TH1F*)tt_lep_pt->Get("lep_pt");
  TFile * st_lep_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_lep_pt_hist.root");
  TH1F * h_st_lep_pt = (TH1F*)st_lep_pt->Get("lep_pt");
  TFile * db_lep_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_lep_pt_hist.root");
  TH1F * h_db_lep_pt = (TH1F*)db_lep_pt->Get("lep_pt");
  TFile * zj_lep_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_lep_pt_hist.root");
  TH1F * h_zj_lep_pt = (TH1F*)zj_lep_pt->Get("lep_pt");
  TFile * wj_lep_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_lep_pt_hist.root");
  TH1F * h_wj_lep_pt = (TH1F*)wj_lep_pt->Get("lep_pt");
  
  h_tt_lep_pt->Scale(w_ttbar);
  h_st_lep_pt->Scale(w_singletop);
  h_db_lep_pt->Scale(w_diboson);
  h_zj_lep_pt->Scale(w_zjets);
  h_wj_lep_pt->Scale(w_wjets);
  
  hs_lep_pt->Add(h_tt_lep_pt);
  hs_lep_pt->Add(h_st_lep_pt);
  hs_lep_pt->Add(h_db_lep_pt);
  hs_lep_pt->Add(h_zj_lep_pt);
  hs_lep_pt->Add(h_wj_lep_pt);
  //This is for lepton eta
  TFile * data_lep_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_lep_eta_hist.root");
  TH1F * h_data_lep_eta = (TH1F*)data_lep_eta->Get("lep_eta");
  THStack * hs_lep_eta = new THStack("hs_lep_eta", "");
  TFile * tt_lep_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_lep_eta_hist.root");
  TH1F * h_tt_lep_eta = (TH1F*)tt_lep_eta->Get("lep_eta");
  TFile * st_lep_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_lep_eta_hist.root");
  TH1F * h_st_lep_eta = (TH1F*)st_lep_eta->Get("lep_eta");
  TFile * db_lep_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_lep_eta_hist.root");
  TH1F * h_db_lep_eta = (TH1F*)db_lep_eta->Get("lep_eta");
  TFile * zj_lep_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_lep_eta_hist.root");
  TH1F * h_zj_lep_eta = (TH1F*)zj_lep_eta->Get("lep_eta");
  TFile * wj_lep_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_lep_eta_hist.root");
  TH1F * h_wj_lep_eta = (TH1F*)wj_lep_eta->Get("lep_eta");
   
  h_tt_lep_eta->Scale(w_ttbar);
  h_st_lep_eta->Scale(w_singletop);
  h_db_lep_eta->Scale(w_diboson);
  h_zj_lep_eta->Scale(w_zjets);
  h_wj_lep_eta->Scale(w_wjets); 
   
  hs_lep_eta->Add(h_tt_lep_eta);
  hs_lep_eta->Add(h_st_lep_eta);
  hs_lep_eta->Add(h_db_lep_eta);
  hs_lep_eta->Add(h_zj_lep_eta);
  hs_lep_eta->Add(h_wj_lep_eta);
  //This is for lepton phi
  TFile * data_lep_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_lep_phi_hist.root");
  TH1F * h_data_lep_phi = (TH1F*)data_lep_phi->Get("lep_phi");
  THStack * hs_lep_phi = new THStack("hs_lep_phi", "");
  TFile * tt_lep_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_lep_phi_hist.root");
  TH1F * h_tt_lep_phi = (TH1F*)tt_lep_phi->Get("lep_phi");
  TFile * st_lep_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_lep_phi_hist.root");
  TH1F * h_st_lep_phi = (TH1F*)st_lep_phi->Get("lep_phi");
  TFile * db_lep_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_lep_phi_hist.root");
  TH1F * h_db_lep_phi = (TH1F*)db_lep_phi->Get("lep_phi");
  TFile * zj_lep_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_lep_phi_hist.root");
  TH1F * h_zj_lep_phi = (TH1F*)zj_lep_phi->Get("lep_phi");
  TFile * wj_lep_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_lep_phi_hist.root");
  TH1F * h_wj_lep_phi = (TH1F*)wj_lep_phi->Get("lep_phi");
   
  h_tt_lep_phi->Scale(w_ttbar);
  h_st_lep_phi->Scale(w_singletop);
  h_db_lep_phi->Scale(w_diboson);
  h_zj_lep_phi->Scale(w_zjets);
  h_wj_lep_phi->Scale(w_wjets); 
     
  hs_lep_phi->Add(h_tt_lep_phi);
  hs_lep_phi->Add(h_st_lep_phi);
  hs_lep_phi->Add(h_db_lep_phi);
  hs_lep_phi->Add(h_zj_lep_phi);
  hs_lep_phi->Add(h_wj_lep_phi);
  //This is for lepton Energy
  TFile * data_lep_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_lep_E_hist.root");
  TH1F * h_data_lep_E = (TH1F*)data_lep_E->Get("lep_E");
  THStack * hs_lep_E = new THStack("hs_lep_E", "");
  TFile * tt_lep_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_lep_E_hist.root");
  TH1F * h_tt_lep_E = (TH1F*)tt_lep_E->Get("lep_E");
  TFile * st_lep_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_lep_E_hist.root");
  TH1F * h_st_lep_E = (TH1F*)st_lep_E->Get("lep_E");
  TFile * db_lep_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_lep_E_hist.root");
  TH1F * h_db_lep_E = (TH1F*)db_lep_E->Get("lep_E");
  TFile * zj_lep_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_lep_E_hist.root");
  TH1F * h_zj_lep_E = (TH1F*)zj_lep_E->Get("lep_E");
  TFile * wj_lep_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_lep_E_hist.root");
  TH1F * h_wj_lep_E = (TH1F*)wj_lep_E->Get("lep_E");
     
  h_tt_lep_E->Scale(w_ttbar);
  h_st_lep_E->Scale(w_singletop);
  h_db_lep_E->Scale(w_diboson);
  h_zj_lep_E->Scale(w_zjets);
  h_wj_lep_E->Scale(w_wjets);   
     
  hs_lep_E->Add(h_tt_lep_E);
  hs_lep_E->Add(h_st_lep_E);
  hs_lep_E->Add(h_db_lep_E);
  hs_lep_E->Add(h_zj_lep_E);
  hs_lep_E->Add(h_wj_lep_E);
  //This is for Missing transverse Energy
  TFile * data_met_et = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_met_et_hist.root");
  TH1F * h_data_met_et = (TH1F*)data_met_et->Get("met_et");
  THStack * hs_met_et = new THStack("hs_met_et", "");
  TFile * tt_met_et = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_met_et_hist.root");
  TH1F * h_tt_met_et = (TH1F*)tt_met_et->Get("met_et");
  TFile * st_met_et = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_met_et_hist.root");
  TH1F * h_st_met_et = (TH1F*)st_met_et->Get("met_et");
  TFile * db_met_et = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_met_et_hist.root");
  TH1F * h_db_met_et = (TH1F*)db_met_et->Get("met_et");
  TFile * zj_met_et = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_met_et_hist.root");
  TH1F * h_zj_met_et = (TH1F*)zj_met_et->Get("met_et");
  TFile * wj_met_et = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_met_et_hist.root");
  TH1F * h_wj_met_et = (TH1F*)wj_met_et->Get("met_et");
      
  h_tt_met_et->Scale(w_ttbar);
  h_st_met_et->Scale(w_singletop);
  h_db_met_et->Scale(w_diboson);
  h_zj_met_et->Scale(w_zjets);
  h_wj_met_et->Scale(w_wjets);    
      
  hs_met_et->Add(h_tt_met_et);
  hs_met_et->Add(h_st_met_et);
  hs_met_et->Add(h_db_met_et);
  hs_met_et->Add(h_zj_met_et);
  hs_met_et->Add(h_wj_met_et);
  //This is for Number of jets
  TFile * data_jet_n = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_jet_n_hist.root");
  TH1F * h_data_jet_n = (TH1F*)data_jet_n->Get("jet_n");
  THStack * hs_jet_n = new THStack("hs_jet_n", "");
  TFile * tt_jet_n = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_jet_n_hist.root");
  TH1F * h_tt_jet_n = (TH1F*)tt_jet_n->Get("jet_n");
  TFile * st_jet_n = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_jet_n_hist.root");
  TH1F * h_st_jet_n = (TH1F*)st_jet_n->Get("jet_n");
  TFile * db_jet_n = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_jet_n_hist.root");
  TH1F * h_db_jet_n = (TH1F*)db_jet_n->Get("jet_n");
  TFile * zj_jet_n = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_jet_n_hist.root");
  TH1F * h_zj_jet_n = (TH1F*)zj_jet_n->Get("jet_n");
  TFile * wj_jet_n = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_jet_n_hist.root");
  TH1F * h_wj_jet_n = (TH1F*)wj_jet_n->Get("jet_n");
 
  h_tt_jet_n->Scale(w_ttbar);
  h_st_jet_n->Scale(w_singletop);
  h_db_jet_n->Scale(w_diboson);
  h_zj_jet_n->Scale(w_zjets);
  h_wj_jet_n->Scale(w_wjets);
 
  hs_jet_n->Add(h_tt_jet_n);
  hs_jet_n->Add(h_st_jet_n);
  hs_jet_n->Add(h_db_jet_n);
  hs_jet_n->Add(h_zj_jet_n);
  hs_jet_n->Add(h_wj_jet_n);
  //This is for the pseudorapidity of the jets
  TFile * data_jet_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_jet_eta_hist.root");
  TH1F * h_data_jet_eta = (TH1F*)data_jet_eta->Get("jet_eta");
  THStack * hs_jet_eta = new THStack("hs_jet_eta", "");
  TFile * tt_jet_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_jet_eta_hist.root");
  TH1F * h_tt_jet_eta = (TH1F*)tt_jet_eta->Get("jet_eta");
  TFile * st_jet_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_jet_eta_hist.root");
  TH1F * h_st_jet_eta = (TH1F*)st_jet_eta->Get("jet_eta");
  TFile * db_jet_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_jet_eta_hist.root");
  TH1F * h_db_jet_eta = (TH1F*)db_jet_eta->Get("jet_eta");
  TFile * zj_jet_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_jet_eta_hist.root");
  TH1F * h_zj_jet_eta = (TH1F*)zj_jet_eta->Get("jet_eta");
  TFile * wj_jet_eta = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_jet_eta_hist.root");
  TH1F * h_wj_jet_eta = (TH1F*)wj_jet_eta->Get("jet_eta");
  
  h_tt_jet_eta->Scale(w_ttbar);
  h_st_jet_eta->Scale(w_singletop);
  h_db_jet_eta->Scale(w_diboson);
  h_zj_jet_eta->Scale(w_zjets);
  h_wj_jet_eta->Scale(w_wjets);
  
  hs_jet_eta->Add(h_tt_jet_eta);
  hs_jet_eta->Add(h_st_jet_eta);
  hs_jet_eta->Add(h_db_jet_eta);
  hs_jet_eta->Add(h_zj_jet_eta);
  hs_jet_eta->Add(h_wj_jet_eta);
  //This is for the pt of the jets
  TFile * data_jet_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_jet_pt_hist.root");
  TH1F * h_data_jet_pt = (TH1F*)data_jet_pt->Get("jet_pt");
  THStack * hs_jet_pt = new THStack("hs_jet_pt", "");
  TFile * tt_jet_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_jet_pt_hist.root");
  TH1F * h_tt_jet_pt = (TH1F*)tt_jet_pt->Get("jet_pt");
  TFile * st_jet_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_jet_pt_hist.root");
  TH1F * h_st_jet_pt = (TH1F*)st_jet_pt->Get("jet_pt");
  TFile * db_jet_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_jet_pt_hist.root");
  TH1F * h_db_jet_pt = (TH1F*)db_jet_pt->Get("jet_pt");
  TFile * zj_jet_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_jet_pt_hist.root");
  TH1F * h_zj_jet_pt = (TH1F*)zj_jet_pt->Get("jet_pt");
  TFile * wj_jet_pt = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_jet_pt_hist.root");
  TH1F * h_wj_jet_pt = (TH1F*)wj_jet_pt->Get("jet_pt");
     
  h_tt_jet_pt->Scale(w_ttbar);
  h_st_jet_pt->Scale(w_singletop);
  h_db_jet_pt->Scale(w_diboson);
  h_zj_jet_pt->Scale(w_zjets);
  h_wj_jet_pt->Scale(w_wjets);   
     
  hs_jet_pt->Add(h_tt_jet_pt);
  hs_jet_pt->Add(h_st_jet_pt);
  hs_jet_pt->Add(h_db_jet_pt);
  hs_jet_pt->Add(h_zj_jet_pt);
  hs_jet_pt->Add(h_wj_jet_pt);
  //This is for the angle phi of the jets
  TFile * data_jet_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_jet_phi_hist.root");
  TH1F * h_data_jet_phi = (TH1F*)data_jet_phi->Get("jet_phi");
  THStack * hs_jet_phi = new THStack("hs_jet_phi", "");
  TFile * tt_jet_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_jet_phi_hist.root");
  TH1F * h_tt_jet_phi = (TH1F*)tt_jet_phi->Get("jet_phi");
  TFile * st_jet_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_jet_phi_hist.root");
  TH1F * h_st_jet_phi = (TH1F*)st_jet_phi->Get("jet_phi");
  TFile * db_jet_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_jet_phi_hist.root");
  TH1F * h_db_jet_phi = (TH1F*)db_jet_phi->Get("jet_phi");
  TFile * zj_jet_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_jet_phi_hist.root");
  TH1F * h_zj_jet_phi = (TH1F*)zj_jet_phi->Get("jet_phi");
  TFile * wj_jet_phi = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_jet_phi_hist.root");
  TH1F * h_wj_jet_phi = (TH1F*)wj_jet_phi->Get("jet_phi");
    
  h_tt_jet_phi->Scale(w_ttbar);
  h_st_jet_phi->Scale(w_singletop);
  h_db_jet_phi->Scale(w_diboson);
  h_zj_jet_phi->Scale(w_zjets);
  h_wj_jet_phi->Scale(w_wjets);  
    
  hs_jet_phi->Add(h_tt_jet_phi);
  hs_jet_phi->Add(h_st_jet_phi);
  hs_jet_phi->Add(h_db_jet_phi);
  hs_jet_phi->Add(h_zj_jet_phi);
  hs_jet_phi->Add(h_wj_jet_phi);
  
  //This is for the Energy of the jets
  TFile * data_jet_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_jet_E_hist.root");
  TH1F * h_data_jet_E = (TH1F*)data_jet_E->Get("jet_E");
  THStack * hs_jet_E = new THStack("hs_jet_E", "");
  TFile * tt_jet_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_jet_E_hist.root");
  TH1F * h_tt_jet_E = (TH1F*)tt_jet_E->Get("jet_E");
  TFile * st_jet_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_jet_E_hist.root");
  TH1F * h_st_jet_E = (TH1F*)st_jet_E->Get("jet_E");
  TFile * db_jet_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_jet_E_hist.root");
  TH1F * h_db_jet_E = (TH1F*)db_jet_E->Get("jet_E");
  TFile * zj_jet_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_jet_E_hist.root");
  TH1F * h_zj_jet_E = (TH1F*)zj_jet_E->Get("jet_E");
  TFile * wj_jet_E = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_jet_E_hist.root");
  TH1F * h_wj_jet_E = (TH1F*)wj_jet_E->Get("jet_E");
     
  h_tt_jet_E->Scale(w_ttbar);
  h_st_jet_E->Scale(w_singletop);
  h_db_jet_E->Scale(w_diboson);
  h_zj_jet_E->Scale(w_zjets);
  h_wj_jet_E->Scale(w_wjets);
  
  hs_jet_E->Add(h_tt_jet_E);
  hs_jet_E->Add(h_st_jet_E);
  hs_jet_E->Add(h_db_jet_E);
  hs_jet_E->Add(h_zj_jet_E);
  hs_jet_E->Add(h_wj_jet_E);
  
  //3JetMass und alle good Jets Dinger funzen nicht
  TFile * file_3jetmass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_InvJetMass_hist.root");
  TH1F * h_data_3mass = (TH1F*)file_3jetmass->Get("InvJetMass");
  THStack * hs_3mass = new THStack("hs_3mass", "");
  TFile * tt_3mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_InvJetMass_hist.root");
  TH1F * h_tt_3mass = (TH1F*)tt_3mass->Get("InvJetMass");
  TFile * st_3mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_InvJetMass_hist.root");
  TH1F * h_st_3mass = (TH1F*)st_3mass->Get("InvJetMass");
  TFile * db_3mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_InvJetMass_hist.root");
  TH1F * h_db_3mass = (TH1F*)db_3mass->Get("InvJetMass");
  TFile * zj_3mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_InvJetMass_hist.root");
  TH1F * h_zj_3mass = (TH1F*)zj_3mass->Get("InvJetMass");
  TFile * wj_3mass = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_InvJetMass_hist.root");
  TH1F * h_wj_3mass = (TH1F*)wj_3mass->Get("InvJetMass");
     
  h_tt_3mass->Scale(w_ttbar);
  h_st_3mass->Scale(w_singletop);
  h_db_3mass->Scale(w_diboson);
  h_zj_3mass->Scale(w_zjets);
  h_wj_3mass->Scale(w_wjets);
  
  hs_3mass->Add(h_tt_3mass);
  hs_3mass->Add(h_st_3mass);
  hs_3mass->Add(h_db_3mass);
  hs_3mass->Add(h_zj_3mass);
  hs_3mass->Add(h_wj_3mass);
  
  // now good jets
  // jet eta
  TFile * data_jet_eta_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_jet_eta_good_hist.root");
  TH1F * h_data_jet_eta_good = (TH1F*)data_jet_eta_good->Get("jet_eta_good");
  THStack * hs_jet_eta_good = new THStack("hs_jet_eta_good", "");
  TFile * tt_jet_eta_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_jet_eta_good_hist.root");
  TH1F *h_tt_jet_eta_good = (TH1F*)tt_jet_eta_good->Get("jet_eta_good");
  TFile * st_jet_eta_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_jet_eta_good_hist.root");
  TH1F *h_st_jet_eta_good = (TH1F*)st_jet_eta_good->Get("jet_eta_good");
  TFile * db_jet_eta_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_jet_eta_good_hist.root");
  TH1F *h_db_jet_eta_good = (TH1F*)db_jet_eta_good->Get("jet_eta_good");
  TFile * zj_jet_eta_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_jet_eta_good_hist.root");
  TH1F *h_zj_jet_eta_good = (TH1F*)zj_jet_eta_good->Get("jet_eta_good");
  TFile * wj_jet_eta_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_jet_eta_good_hist.root");
  TH1F *h_wj_jet_eta_good = (TH1F*)wj_jet_eta_good->Get("jet_eta_good");
  
  h_tt_jet_eta_good->Scale(w_ttbar);
  h_st_jet_eta_good->Scale(w_singletop);
  h_db_jet_eta_good->Scale(w_diboson);
  h_zj_jet_eta_good->Scale(w_zjets);
  h_wj_jet_eta_good->Scale(w_wjets);
  
  hs_jet_eta_good->Add(h_tt_jet_eta_good);
  hs_jet_eta_good->Add(h_st_jet_eta_good);
  hs_jet_eta_good->Add(h_db_jet_eta_good);
  hs_jet_eta_good->Add(h_zj_jet_eta_good);
  hs_jet_eta_good->Add(h_wj_jet_eta_good);
  // jet E
  TFile * data_jet_E_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_jet_E_good_hist.root");
  TH1F * h_data_jet_E_good = (TH1F*)data_jet_E_good->Get("jet_E_good");
  THStack * hs_jet_E_good = new THStack("hs_jet_E_good", "");
  TFile * tt_jet_E_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_jet_E_good_hist.root");
  TH1F *h_tt_jet_E_good = (TH1F*)tt_jet_E_good->Get("jet_E_good");
  TFile * st_jet_E_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_jet_E_good_hist.root");
  TH1F *h_st_jet_E_good = (TH1F*)st_jet_E_good->Get("jet_E_good");
  TFile * db_jet_E_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_jet_E_good_hist.root");
  TH1F *h_db_jet_E_good = (TH1F*)db_jet_E_good->Get("jet_E_good");
  TFile * zj_jet_E_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_jet_E_good_hist.root");
  TH1F *h_zj_jet_E_good = (TH1F*)zj_jet_E_good->Get("jet_E_good");
  TFile * wj_jet_E_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_jet_E_good_hist.root");
  TH1F *h_wj_jet_E_good = (TH1F*)wj_jet_E_good->Get("jet_E_good");
  
  h_tt_jet_E_good->Scale(w_ttbar);
  h_st_jet_E_good->Scale(w_singletop);
  h_db_jet_E_good->Scale(w_diboson);
  h_zj_jet_E_good->Scale(w_zjets);
  h_wj_jet_E_good->Scale(w_wjets);
  
  hs_jet_E_good->Add(h_tt_jet_E_good);
  hs_jet_E_good->Add(h_st_jet_E_good);
  hs_jet_E_good->Add(h_db_jet_E_good);
  hs_jet_E_good->Add(h_zj_jet_E_good);
  hs_jet_E_good->Add(h_wj_jet_E_good);
  // jet phi
  TFile * data_jet_phi_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_jet_phi_good_hist.root");
  TH1F * h_data_jet_phi_good = (TH1F*)data_jet_phi_good->Get("jet_phi_good");
  THStack * hs_jet_phi_good = new THStack("hs_jet_phi_good", "");
  TFile * tt_jet_phi_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_jet_phi_good_hist.root");
  TH1F *h_tt_jet_phi_good = (TH1F*)tt_jet_phi_good->Get("jet_phi_good");
  TFile * st_jet_phi_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_jet_phi_good_hist.root");
  TH1F *h_st_jet_phi_good = (TH1F*)st_jet_phi_good->Get("jet_phi_good");
  TFile * db_jet_phi_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_jet_phi_good_hist.root");
  TH1F *h_db_jet_phi_good = (TH1F*)db_jet_phi_good->Get("jet_phi_good");
  TFile * zj_jet_phi_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_jet_phi_good_hist.root");
  TH1F *h_zj_jet_phi_good = (TH1F*)zj_jet_phi_good->Get("jet_phi_good");
  TFile * wj_jet_phi_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_jet_phi_good_hist.root");
  TH1F *h_wj_jet_phi_good = (TH1F*)wj_jet_phi_good->Get("jet_phi_good");
  
  h_tt_jet_phi_good->Scale(w_ttbar);
  h_st_jet_phi_good->Scale(w_singletop);
  h_db_jet_phi_good->Scale(w_diboson);
  h_zj_jet_phi_good->Scale(w_zjets);
  h_wj_jet_phi_good->Scale(w_wjets);
  
  hs_jet_phi_good->Add(h_tt_jet_phi_good);
  hs_jet_phi_good->Add(h_st_jet_phi_good);
  hs_jet_phi_good->Add(h_db_jet_phi_good);
  hs_jet_phi_good->Add(h_zj_jet_phi_good);
  hs_jet_phi_good->Add(h_wj_jet_phi_good);
  // jet pt
  TFile * data_jet_pt_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_jet_pt_good_hist.root");
  TH1F * h_data_jet_pt_good = (TH1F*)data_jet_pt_good->Get("jet_pt_good");
  THStack * hs_jet_pt_good = new THStack("hs_jet_pt_good", "");
  TFile * tt_jet_pt_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_jet_pt_good_hist.root");
  TH1F *h_tt_jet_pt_good = (TH1F*)tt_jet_pt_good->Get("jet_pt_good");
  TFile * st_jet_pt_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_jet_pt_good_hist.root");
  TH1F *h_st_jet_pt_good = (TH1F*)st_jet_pt_good->Get("jet_pt_good");
  TFile * db_jet_pt_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_jet_pt_good_hist.root");
  TH1F *h_db_jet_pt_good = (TH1F*)db_jet_pt_good->Get("jet_pt_good");
  TFile * zj_jet_pt_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_jet_pt_good_hist.root");
  TH1F *h_zj_jet_pt_good = (TH1F*)zj_jet_pt_good->Get("jet_pt_good");
  TFile * wj_jet_pt_good = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_jet_pt_good_hist.root");
  TH1F *h_wj_jet_pt_good = (TH1F*)wj_jet_pt_good->Get("jet_pt_good");
  
  h_tt_jet_pt_good->Scale(w_ttbar);
  h_st_jet_pt_good->Scale(w_singletop);
  h_db_jet_pt_good->Scale(w_diboson);
  h_zj_jet_pt_good->Scale(w_zjets);
  h_wj_jet_pt_good->Scale(w_wjets);
  
  hs_jet_pt_good->Add(h_tt_jet_pt_good);
  hs_jet_pt_good->Add(h_st_jet_pt_good);
  hs_jet_pt_good->Add(h_db_jet_pt_good);
  hs_jet_pt_good->Add(h_zj_jet_pt_good);
  hs_jet_pt_good->Add(h_wj_jet_pt_good);
  //If you want to scale the histogram, use Scale(float factor)
  //If you want to adjust the bin width, use Rebin(int number_of_bins_to_be_merged)

  //You should set a different fill color for each process using SetFillColor(Color_t fcolor); examples for fcolor are kRed, kGreen, kYellow etc. 
  //You can also add integer like kRed+2 to change the shade

  //You might also want to change the line color using e.g. SetLineColor(kBlack)
  
  
  
  
  
  //You should add a legend to be able to distinguish the different processes
  TLegend *leg = new TLegend(0.7,0.6,0.85,0.9);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->AddEntry(h_data_jet_pt_good,"data", "p");
  leg->AddEntry(h_tt_jet_pt_good,"ttbar", "f");
  leg->AddEntry(h_st_jet_pt_good,"singletop", "f");
  leg->AddEntry(h_db_jet_pt_good,"diboson", "f");
  leg->AddEntry(h_zj_jet_pt_good,"w jets", "f");
  leg->AddEntry(h_wj_jet_pt_good,"z jets", "f");
  //To plot several MC histograms, use THStack. At this point you should be able to figure out its use by looking it up online. 
  //For further analysis, you should however combine them to a new TH1F
   
   
   
   
   
   
   
   
   
   
   
    
  //For histograms of data, you can use the following commands to change the attributes of the histobramm
  // 3jetmass system
  h_data_3mass->SetLineWidth(0);
  h_data_3mass->SetLineColor(kBlack);
  h_data_3mass->SetMarkerStyle(7);
  h_data_3mass->SetMarkerSize(1);
  h_data_3mass->SetMarkerColor(kBlack);
  h_tt_3mass->SetFillColor(kPink-3);
  h_st_3mass->SetFillColor(kAzure+1);
  h_db_3mass->SetFillColor(kMagenta);
  h_zj_3mass->SetFillColor(kPink-8);
  h_wj_3mass->SetFillColor(kCyan);
  // eta good
  h_data_jet_eta_good->SetLineWidth(0);
  h_data_jet_eta_good->SetLineColor(kBlack);
  h_data_jet_eta_good->SetMarkerStyle(7);
  h_data_jet_eta_good->SetMarkerSize(1);
  h_data_jet_eta_good->SetMarkerColor(kBlack);
  h_tt_jet_eta_good->SetFillColor(kPink-3);
  h_st_jet_eta_good->SetFillColor(kAzure+1);
  h_db_jet_eta_good->SetFillColor(kMagenta);
  h_zj_jet_eta_good->SetFillColor(kPink-8);
  h_wj_jet_eta_good->SetFillColor(kCyan);
  // pt good
  h_data_jet_pt_good->SetLineWidth(0);
  h_data_jet_pt_good->SetLineColor(kBlack);
  h_data_jet_pt_good->SetMarkerStyle(7);
  h_data_jet_pt_good->SetMarkerSize(1);
  h_data_jet_pt_good->SetMarkerColor(kBlack);
  h_tt_jet_pt_good->SetFillColor(kPink-3);
  h_st_jet_pt_good->SetFillColor(kAzure+1);
  h_db_jet_pt_good->SetFillColor(kMagenta);
  h_zj_jet_pt_good->SetFillColor(kPink-8);
  h_wj_jet_pt_good->SetFillColor(kCyan);
  // phi good
  h_data_jet_phi_good->SetLineWidth(0);
  h_data_jet_phi_good->SetLineColor(kBlack);
  h_data_jet_phi_good->SetMarkerStyle(7);
  h_data_jet_phi_good->SetMarkerSize(1);
  h_data_jet_phi_good->SetMarkerColor(kBlack);
  h_tt_jet_phi_good->SetFillColor(kPink-3);
  h_st_jet_phi_good->SetFillColor(kAzure+1);
  h_db_jet_phi_good->SetFillColor(kMagenta);
  h_zj_jet_phi_good->SetFillColor(kPink-8);
  h_wj_jet_phi_good->SetFillColor(kCyan);
  // E good
  h_data_jet_E_good->SetLineWidth(0);
  h_data_jet_E_good->SetLineColor(kBlack);
  h_data_jet_E_good->SetMarkerStyle(7);
  h_data_jet_E_good->SetMarkerSize(1);
  h_data_jet_E_good->SetMarkerColor(kBlack);
  h_tt_jet_E_good->SetFillColor(kPink-3);
  h_st_jet_E_good->SetFillColor(kAzure+1);
  h_db_jet_E_good->SetFillColor(kMagenta);
  h_zj_jet_E_good->SetFillColor(kPink-8);
  h_wj_jet_E_good->SetFillColor(kCyan);
  
  h_data_mass->SetLineWidth(0);
  h_data_mass->SetLineColor(kBlack);
  h_data_mass->SetMarkerStyle(7);
  h_data_mass->SetMarkerSize(1);
  h_data_mass->SetMarkerColor(kBlack);
  h_tt_disc->SetFillColor(kPink-3);
  h_st_disc->SetFillColor(kAzure+1);
  h_db_disc->SetFillColor(kMagenta);
  h_zj_disc->SetFillColor(kPink-8);
  h_wj_disc->SetFillColor(kCyan);
  
  h_data_fulleta->SetLineWidth(0);
  h_data_fulleta->SetLineColor(kBlack);
  h_data_fulleta->SetMarkerStyle(7);
  h_data_fulleta->SetMarkerSize(1);
  h_data_fulleta->SetMarkerColor(kBlack);
  h_tt_fulleta->SetFillColor(kPink-3);
  h_st_fulleta->SetFillColor(kAzure+1);
  h_db_fulleta->SetFillColor(kMagenta);
  h_zj_fulleta->SetFillColor(kPink-8);
  h_wj_fulleta->SetFillColor(kCyan);
  
  h_data_deltaphi->SetLineWidth(0);
  h_data_deltaphi->SetLineColor(kBlack);
  h_data_deltaphi->SetMarkerStyle(7);
  h_data_deltaphi->SetMarkerSize(1);
  h_data_deltaphi->SetMarkerColor(kBlack);
  h_tt_deltaphi->SetFillColor(kPink-3);
  h_st_deltaphi->SetFillColor(kAzure+1);
  h_db_deltaphi->SetFillColor(kMagenta);
  h_zj_deltaphi->SetFillColor(kPink-8);
  h_wj_deltaphi->SetFillColor(kCyan);

  h_data_btagged->SetLineWidth(0);
  h_data_btagged->SetLineColor(kBlack);
  h_data_btagged->SetMarkerStyle(7);
  h_data_btagged->SetMarkerSize(1);
  h_data_btagged->SetMarkerColor(kBlack);
  h_tt_btagged->SetFillColor(kPink-3);
  h_st_btagged->SetFillColor(kAzure+1);
  h_db_btagged->SetFillColor(kMagenta);
  h_zj_btagged->SetFillColor(kPink-8);
  h_wj_btagged->SetFillColor(kCyan);
  
  h_data_lep_pt->SetLineWidth(0);
  h_data_lep_pt->SetLineColor(kBlack);
  h_data_lep_pt->SetMarkerStyle(7);
  h_data_lep_pt->SetMarkerSize(1);
  h_data_lep_pt->SetMarkerColor(kBlack);
  h_tt_lep_pt->SetFillColor(kPink-3);
  h_st_lep_pt->SetFillColor(kAzure+1);
  h_db_lep_pt->SetFillColor(kMagenta);
  h_zj_lep_pt->SetFillColor(kPink-8);
  h_wj_lep_pt->SetFillColor(kCyan);
   
  h_data_lep_eta->SetLineWidth(0);
  h_data_lep_eta->SetLineColor(kBlack);
  h_data_lep_eta->SetMarkerStyle(7);
  h_data_lep_eta->SetMarkerSize(1);
  h_data_lep_eta->SetMarkerColor(kBlack);
  h_tt_lep_eta->SetFillColor(kPink-3);
  h_st_lep_eta->SetFillColor(kAzure+1);
  h_db_lep_eta->SetFillColor(kMagenta);
  h_zj_lep_eta->SetFillColor(kPink-8);
  h_wj_lep_eta->SetFillColor(kCyan);
 
  h_data_lep_phi->SetLineWidth(0);
  h_data_lep_phi->SetLineColor(kBlack);
  h_data_lep_phi->SetMarkerStyle(7);
  h_data_lep_phi->SetMarkerSize(1);
  h_data_lep_phi->SetMarkerColor(kBlack);
  h_tt_lep_phi->SetFillColor(kPink-3);
  h_st_lep_phi->SetFillColor(kAzure+1);
  h_db_lep_phi->SetFillColor(kMagenta);
  h_zj_lep_phi->SetFillColor(kPink-8);
  h_wj_lep_phi->SetFillColor(kCyan);
 
  h_data_lep_E->SetLineWidth(0);
  h_data_lep_E->SetLineColor(kBlack);
  h_data_lep_E->SetMarkerStyle(7);
  h_data_lep_E->SetMarkerSize(1);
  h_data_lep_E->SetMarkerColor(kBlack);
  h_tt_lep_E->SetFillColor(kPink-3);
  h_st_lep_E->SetFillColor(kAzure+1);
  h_db_lep_E->SetFillColor(kMagenta);
  h_zj_lep_E->SetFillColor(kPink-8);
  h_wj_lep_E->SetFillColor(kCyan);
 
  h_data_met_et->SetLineWidth(0);
  h_data_met_et->SetLineColor(kBlack);
  h_data_met_et->SetMarkerStyle(7);
  h_data_met_et->SetMarkerSize(1);
  h_data_met_et->SetMarkerColor(kBlack);
  h_tt_met_et->SetFillColor(kPink-3);
  h_st_met_et->SetFillColor(kAzure+1);
  h_db_met_et->SetFillColor(kMagenta);
  h_zj_met_et->SetFillColor(kPink-8);
  h_wj_met_et->SetFillColor(kCyan); 
  
  h_data_jet_n->SetLineWidth(0);
  h_data_jet_n->SetLineColor(kBlack);
  h_data_jet_n->SetMarkerStyle(7);
  h_data_jet_n->SetMarkerSize(1);
  h_data_jet_n->SetMarkerColor(kBlack);
  h_tt_jet_n->SetFillColor(kPink-3);
  h_st_jet_n->SetFillColor(kAzure+1);
  h_db_jet_n->SetFillColor(kMagenta);
  h_zj_jet_n->SetFillColor(kPink-8);
  h_wj_jet_n->SetFillColor(kCyan); 

  h_data_jet_eta->SetLineWidth(0);
  h_data_jet_eta->SetLineColor(kBlack);
  h_data_jet_eta->SetMarkerStyle(7);
  h_data_jet_eta->SetMarkerSize(1);
  h_data_jet_eta->SetMarkerColor(kBlack);
  h_tt_jet_eta->SetFillColor(kPink-3);
  h_st_jet_eta->SetFillColor(kAzure+1);
  h_db_jet_eta->SetFillColor(kMagenta);
  h_zj_jet_eta->SetFillColor(kPink-8);
  h_wj_jet_eta->SetFillColor(kCyan); 
  
  h_data_jet_pt->SetLineWidth(0);
  h_data_jet_pt->SetLineColor(kBlack);
  h_data_jet_pt->SetMarkerStyle(7);
  h_data_jet_pt->SetMarkerSize(1);
  h_data_jet_pt->SetMarkerColor(kBlack);
  h_tt_jet_pt->SetFillColor(kPink-3);
  h_st_jet_pt->SetFillColor(kAzure+1);
  h_db_jet_pt->SetFillColor(kMagenta);
  h_zj_jet_pt->SetFillColor(kPink-8);
  h_wj_jet_pt->SetFillColor(kCyan); 
  
  h_data_jet_phi->SetLineWidth(0);
  h_data_jet_phi->SetLineColor(kBlack);
  h_data_jet_phi->SetMarkerStyle(7);
  h_data_jet_phi->SetMarkerSize(1);
  h_data_jet_phi->SetMarkerColor(kBlack);
  h_tt_jet_phi->SetFillColor(kPink-3);
  h_st_jet_phi->SetFillColor(kAzure+1);
  h_db_jet_phi->SetFillColor(kMagenta);
  h_zj_jet_phi->SetFillColor(kPink-8);
  h_wj_jet_phi->SetFillColor(kCyan); 
     
  h_data_jet_E->SetLineWidth(0);
  h_data_jet_E->SetLineColor(kBlack);
  h_data_jet_E->SetMarkerStyle(7);
  h_data_jet_E->SetMarkerSize(1);
  h_data_jet_E->SetMarkerColor(kBlack);
  h_tt_jet_E->SetFillColor(kPink-3);
  h_st_jet_E->SetFillColor(kAzure+1);
  h_db_jet_E->SetFillColor(kMagenta);
  h_zj_jet_E->SetFillColor(kPink-8);
  h_wj_jet_E->SetFillColor(kCyan);    
  
  //For plotting data and stacked MC, you can use the function PlotStack at the end of this file 
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_disc.pdf", " ", hs_FullMass, h_data_mass, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_fulleta.pdf", " ", hs_fulleta, h_data_fulleta, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_deltaphi.pdf", " ", hs_deltaphi, h_data_deltaphi, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_btagged.pdf", " ", hs_btagged, h_data_btagged, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_lep_pt.pdf", " ", hs_lep_pt, h_data_lep_pt, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_lep_eta.pdf", " ", hs_lep_eta, h_data_lep_eta, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_lep_phi.pdf", " ", hs_lep_phi, h_data_lep_phi, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_lep_E.pdf", " ", hs_lep_E, h_data_lep_E, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_met_et.pdf", " ", hs_met_et, h_data_met_et, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_jet_n.pdf", " ", hs_jet_n, h_data_jet_n, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_jet_eta.pdf", " ", hs_jet_eta, h_data_jet_eta, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_jet_pt.pdf", " ", hs_jet_pt, h_data_jet_pt, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_jet_phi.pdf", " ", hs_jet_phi, h_data_jet_phi, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_jet_E.pdf", " ", hs_jet_E, h_data_jet_E, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_3JetSys.pdf", " ", hs_3mass, h_data_3mass, leg);
  // jet good
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_jet_E_good.pdf", " ", hs_jet_E_good, h_data_jet_E_good, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_jet_eta_good.pdf", " ", hs_jet_eta_good, h_data_jet_eta_good, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_jet_pt_good.pdf", " ", hs_jet_pt_good, h_data_jet_pt_good, leg);
  PlotStack("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/stacked_plots/stacked_jet_phi_good.pdf", " ", hs_jet_phi_good, h_data_jet_phi_good, leg);

  analysis->cd();
  //For all objects you want to write to the analysis file, call Write(), e.gl
  // h_histogram1->Write();
  h_tt_3mass->Write();
  h_st_3mass->Write();
  h_db_3mass->Write();
  h_zj_3mass->Write();
  h_wj_3mass->Write();
  // eta good
  h_tt_jet_eta_good->Write();
  h_st_jet_eta_good->Write();
  h_db_jet_eta_good->Write();
  h_zj_jet_eta_good->Write();
  h_wj_jet_eta_good->Write();
  // pt good
  h_tt_jet_pt_good->Write();
  h_st_jet_pt_good->Write();
  h_db_jet_pt_good->Write();
  h_zj_jet_pt_good->Write();
  h_wj_jet_pt_good->Write();
  // E good
  h_tt_jet_E_good->Write();
  h_st_jet_E_good->Write();
  h_db_jet_E_good->Write();
  h_zj_jet_E_good->Write();
  h_wj_jet_E_good->Write();
  // phi good
  h_tt_jet_phi_good->Write();
  h_st_jet_phi_good->Write();
  h_db_jet_phi_good->Write();
  h_zj_jet_phi_good->Write();
  h_wj_jet_phi_good->Write();
  //
  h_tt_disc->Write();
  h_st_disc->Write();
  h_db_disc->Write();
  h_zj_disc->Write();
  h_wj_disc->Write();
  
  h_tt_fulleta->Write();
  h_st_fulleta->Write();
  h_db_fulleta->Write();
  h_zj_fulleta->Write();
  h_wj_fulleta->Write();
 
 
  h_tt_deltaphi->Write();
  h_st_deltaphi->Write();
  h_db_deltaphi->Write();
  h_zj_deltaphi->Write();
  h_wj_deltaphi->Write();
  
  h_tt_btagged->Write();
  h_st_btagged->Write();
  h_db_btagged->Write();
  h_zj_btagged->Write();
  h_wj_btagged->Write();
  
  h_tt_lep_pt->Write();
  h_st_lep_pt->Write();
  h_db_lep_pt->Write();
  h_zj_lep_pt->Write();
  h_wj_lep_pt->Write();

  h_tt_lep_eta->Write();
  h_st_lep_eta->Write();
  h_db_lep_eta->Write();
  h_zj_lep_eta->Write();
  h_wj_lep_eta->Write();

  h_tt_lep_phi->Write();
  h_st_lep_phi->Write();
  h_db_lep_phi->Write();
  h_zj_lep_phi->Write();
  h_wj_lep_phi->Write();

  h_tt_lep_E->Write();
  h_st_lep_E->Write();
  h_db_lep_E->Write();
  h_zj_lep_E->Write();
  h_wj_lep_E->Write();

  h_tt_met_et->Write();
  h_st_met_et->Write();
  h_db_met_et->Write();
  h_zj_met_et->Write();
  h_wj_met_et->Write();

  h_tt_jet_n->Write();
  h_st_jet_n->Write();
  h_db_jet_n->Write();
  h_zj_jet_n->Write();
  h_wj_jet_n->Write();

  h_tt_jet_eta->Write();
  h_st_jet_eta->Write();
  h_db_jet_eta->Write();
  h_zj_jet_eta->Write();
  h_wj_jet_eta->Write();

  h_tt_jet_pt->Write();
  h_st_jet_pt->Write();
  h_db_jet_pt->Write();
  h_zj_jet_pt->Write();
  h_wj_jet_pt->Write();
  
  h_tt_jet_phi->Write();
  h_st_jet_phi->Write();
  h_db_jet_phi->Write();
  h_zj_jet_phi->Write();
  h_wj_jet_phi->Write();  
  
  h_tt_jet_E->Write();
  h_st_jet_E->Write();
  h_db_jet_E->Write();
  h_zj_jet_E->Write();
  h_wj_jet_E->Write();
  

  //End the programm properly by deleting all dynamic instances
  // file_histogram1->Close();
  // eta good
  tt_jet_eta_good->Close();
  st_jet_eta_good->Close();
  db_jet_eta_good->Close();
  zj_jet_eta_good->Close();
  wj_jet_eta_good->Close();
  // pt good
  tt_jet_pt_good->Close();
  st_jet_pt_good->Close();
  db_jet_pt_good->Close();
  zj_jet_pt_good->Close();
  wj_jet_pt_good->Close();
  // E good
  tt_jet_E_good->Close();
  st_jet_E_good->Close();
  db_jet_E_good->Close();
  zj_jet_E_good->Close();
  wj_jet_E_good->Close();
  // phi good
  tt_jet_phi_good->Close();
  st_jet_phi_good->Close();
  db_jet_phi_good->Close();
  zj_jet_phi_good->Close();
  wj_jet_phi_good->Close();
  //
  tt_3mass->Close();	
  st_3mass->Close();
  db_3mass->Close();
  zj_3mass->Close();
  wj_3mass->Close();
  
  tt_mass->Close();
  st_mass->Close();
  db_mass->Close();
  zj_mass->Close();
  wj_mass->Close();
  
  tt_fulleta->Close();
  st_fulleta->Close();
  db_fulleta->Close();
  zj_fulleta->Close();
  wj_fulleta->Close();
  
  
  tt_deltaphi->Close();
  st_deltaphi->Close();
  db_deltaphi->Close();
  zj_deltaphi->Close();
  wj_deltaphi->Close();
  
  tt_btagged->Close();
  st_btagged->Close();
  db_btagged->Close();
  zj_btagged->Close();
  wj_btagged->Close();
  
  tt_lep_pt->Close();
  st_lep_pt->Close();
  db_lep_pt->Close();
  zj_lep_pt->Close();
  wj_lep_pt->Close();
  
  tt_lep_eta->Close();
  st_lep_eta->Close();
  db_lep_eta->Close();
  zj_lep_eta->Close();
  wj_lep_eta->Close();
  
  tt_lep_phi->Close();
  st_lep_phi->Close();
  db_lep_phi->Close();
  zj_lep_phi->Close();
  wj_lep_phi->Close();
  
  tt_lep_E->Close();
  st_lep_E->Close();
  db_lep_E->Close();
  zj_lep_E->Close();
  wj_lep_E->Close();
   
  tt_met_et->Close();
  st_met_et->Close();
  db_met_et->Close();
  zj_met_et->Close();
  wj_met_et->Close(); 
 
  tt_jet_n->Close();
  st_jet_n->Close();
  db_jet_n->Close();
  zj_jet_n->Close();
  wj_jet_n->Close(); 
 
  tt_jet_eta->Close();
  st_jet_eta->Close();
  db_jet_eta->Close();
  zj_jet_eta->Close();
  wj_jet_eta->Close(); 
  
  tt_jet_pt->Close();
  st_jet_pt->Close();
  db_jet_pt->Close();
  zj_jet_pt->Close();
  wj_jet_pt->Close(); 
  
  tt_jet_phi->Close();
  st_jet_phi->Close();
  db_jet_phi->Close();
  zj_jet_phi->Close();
  wj_jet_phi->Close(); 

  tt_jet_E->Close();
  st_jet_E->Close();
  db_jet_E->Close();
  zj_jet_E->Close();
  wj_jet_E->Close();   
  

    
   
  // delete file_histogram1;
  // eta good
  delete tt_jet_eta_good;
  delete st_jet_eta_good;
  delete db_jet_eta_good;
  delete zj_jet_eta_good;
  delete wj_jet_eta_good;
  // pt good
  delete tt_jet_pt_good;
  delete st_jet_pt_good;
  delete db_jet_pt_good;
  delete zj_jet_pt_good;
  delete wj_jet_pt_good;
   // E good
  delete tt_jet_E_good;
  delete st_jet_E_good;
  delete db_jet_E_good;
  delete zj_jet_E_good;
  delete wj_jet_E_good;
   // phi good
  delete tt_jet_phi_good;
  delete st_jet_phi_good;
  delete db_jet_phi_good;
  delete zj_jet_phi_good;
  delete wj_jet_phi_good;
  //
  
  delete tt_3mass;	
  delete st_3mass;
  delete db_3mass;
  delete zj_3mass;
  delete wj_3mass;


  delete tt_mass;
  delete st_mass;
  delete db_mass;
  delete zj_mass;
  delete wj_mass;
  
  
  delete leg;
  
  
  delete tt_fulleta;
  delete st_fulleta;
  delete db_fulleta;
  delete zj_fulleta;
  delete wj_fulleta;
  
  
  delete tt_deltaphi;
  delete st_deltaphi;
  delete db_deltaphi;
  delete zj_deltaphi;
  delete wj_deltaphi;
  
  delete tt_btagged;
  delete st_btagged;
  delete db_btagged;
  delete zj_btagged;
  delete wj_btagged;
  
  delete tt_lep_pt;
  delete st_lep_pt;
  delete db_lep_pt;
  delete zj_lep_pt;
  delete wj_lep_pt;
  
  delete tt_lep_eta;
  delete st_lep_eta;
  delete db_lep_eta;
  delete zj_lep_eta;
  delete wj_lep_eta;
  
  delete tt_lep_phi;
  delete st_lep_phi;
  delete db_lep_phi;
  delete zj_lep_phi;
  delete wj_lep_phi;
      
  delete tt_lep_E;
  delete st_lep_E;
  delete db_lep_E;
  delete zj_lep_E;
  delete wj_lep_E;
  
  delete tt_met_et;
  delete st_met_et;
  delete db_met_et;
  delete zj_met_et;
  delete wj_met_et;  
  
  delete tt_jet_n;
  delete st_jet_n;
  delete db_jet_n;
  delete zj_jet_n;
  delete wj_jet_n;  
  
  
  delete tt_jet_eta;
  delete st_jet_eta;
  delete db_jet_eta;
  delete zj_jet_eta;
  delete wj_jet_eta;  
 
 
  delete tt_jet_pt;
  delete st_jet_pt;
  delete db_jet_pt;
  delete zj_jet_pt;
  delete wj_jet_pt;  

  delete tt_jet_phi;
  delete st_jet_phi;
  delete db_jet_phi;
  delete zj_jet_phi;
  delete wj_jet_phi;  

  delete tt_jet_E;
  delete st_jet_E;
  delete db_jet_E;
  delete zj_jet_E;
  delete wj_jet_E;   


    
  analysis->Close();



  return 0;
}

void SetStyle() {
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetTitleXOffset(1.3);
  gStyle->SetTitleYOffset(1.3);
  gStyle->SetTextSize(0.05);
  gStyle->SetLabelSize(0.05,"x");
  gStyle->SetTitleSize(0.05,"x");
  gStyle->SetLabelSize(0.05,"y");
  gStyle->SetTitleSize(0.05,"y");
  gStyle->SetLabelSize(0.05,"z");
  gStyle->SetTitleSize(0.05,"z");
  gStyle->SetHistLineWidth(1);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
}


void PlotStack(TString filename, TString varUnit, THStack* mc, TH1F * data, TLegend * legend) {
  SetStyle();
  TCanvas * canv = new TCanvas("canv","Canvas for histogram",1);
  canv->SetLeftMargin(.12);
  canv->SetRightMargin(.1);
  data->Draw("E1");
  data->SetMinimum(0);
  mc->Draw("hist SAME");
  data->Draw("E1 SAME");
  mc->SetTitle(";"+varUnit+";Events");
  mc->GetYaxis()->SetTitleOffset(1);
  data->Draw("E1 SAME");
  legend->Draw();
  canv->Print(filename);
  delete canv;
}






