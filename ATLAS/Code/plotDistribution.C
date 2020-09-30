#include "fileHelper.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "string.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TLorentzVector.h"
#include "TLegend.h"
#include "physicsHelper.h"
#include "math.h"


using namespace std;
int n_bins = 12;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// These functions might be useful. They can be found at the end of this script and don't have to be but can be altered. //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetStyle();
// Should be called before plotting to get a decent looking plot

TH1F * InitHist(TString varName,TString varUnit, int numberBins, float minBin, float maxBin, bool isData); 
// Helps you initialize a histogram so that it already ha the correct labels when plotted.
// varName is the variable name in the tuple or the name you pick for a derived physical variable. You should stick to it for the rest of the analysis. (e.g. lep_eta)
// 

void PlotHist(TString filename, TH1F * hist);
// Creates a file in with path name (e.g. "text.pdf") and plots histogram in it

 
//void AddABranch(TTree* tree){
//	unsigned int btag_count; 
//	TBranch* btagged = tree->AddBranch(&tree);
//	for (int entry = 0; entry < tree->GetEntries(); ++entry){
//		tree->GetEntry();
//	    //Number of btagged jets 
//    for (unsigned int i = 0; i < tree->jet_n; i++){
//		if(tree->jet_MV1[i] > 0.7892){
//			btag_count++;
//		}
//	}
//	btagged->Fill();
//}
//}


int main(int argn, char *argv[]) {
  
  //if you want to run this script for several input files, it is useful to call the name of the file when executing this program
  if(argn==1){
    cout << "Please start plotDistribution.exe with added argument of file to be processed" << endl;
    return 1;
  }

  // path to the file to be studied, e.g.
  string path = string(argv[1]);
  string inpath = string(argv[1]);
  TString filename = TString(inpath).ReplaceAll("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/", "");
  cout << filename << "was muss man hier aendern?" << endl;
  // is the file a data file or not? setting this variable now might be useful
  bool isdata = false;

  // retrieve the tree from the file
  mini * tree = fileHelper::GetMiniTree(path);
  if (tree == 0) {
    cout << "ERROR tree is null pointer" << endl;
    return 1;
  }

  // check that the tree is not empty
  int nEntries = tree->GetEntries();
  cout << "INFO tree contains " << nEntries << " events" << endl;
  if (nEntries == 0) {
    cout << "ERROR tree contains zero events" << endl;
    return 1;
  }
  
  //////////////////////////////////////////////////////////////////////////////
  // To do: initialize histograms to be made
  // example:
  //lepton plots
  TH1F * h_lep_pt = InitHist("lep_pt","p_{T}(l) [MeV]",n_bins,0,200.e3,isdata);
  TH1F * h_lep_eta = InitHist("lep_eta","lep_{eta} ",n_bins,-3,3,isdata);
  TH1F * h_lep_phi = InitHist("lep_phi","lep_{phi} ",n_bins,-M_PI,M_PI,isdata);
  TH1F * h_lep_E = InitHist("lep_E","lep_{E} [MeV]",n_bins,0,700.e3,isdata);
  
  //jet plots
  TH1F * h_jet_eta = InitHist("jet_eta","jet_{eta} ",n_bins,-3,3,isdata);
  TH1F * h_jet_pt = InitHist("jet_pt","jet_{pt} [MeV]",n_bins,30,200.e3,isdata);
  TH1F * h_jet_phi = InitHist("jet_phi","jet_{phi} ",n_bins,-M_PI,M_PI,isdata);
  TH1F * h_jet_E = InitHist("jet_E","jet_{E} [MeV]",n_bins,0,640.e3,isdata);

  //number of jets
  TH1F * h_jet_n = InitHist("jet_n","jet_{n} ",5,2,7,isdata);

  //magnitude missing transverse momtum
  TH1F * h_met_et = InitHist("met_et","E_{T}^{miss} [MeV]",n_bins,39.e3,150.e3,isdata);
  
  //Btagged jets 
  TH1F * h_btagged = InitHist("btagged","Btagged Jets",3,2,5,isdata);

	// good histograms
  TH1F * h_jet_eta_good = InitHist("jet_eta_good","jet_{eta} good",n_bins,-3,3,isdata);
  TH1F * h_jet_pt_good = InitHist("jet_pt_good","jet_{pt} good [MeV]",n_bins,30,200.e3,isdata);
  TH1F * h_jet_phi_good = InitHist("jet_phi_good","Jet_{phi} for good jets",n_bins,-M_PI,M_PI,isdata);
  TH1F * h_jet_E_good = InitHist("jet_E_good","Jet_{E} for good jets [MeV]",n_bins,0,640.e3,isdata);
  //////////////////////////////////////////////////////////////////////////////////
  // additional discriminants
  TH1F * h_DeltaPhi = InitHist("DeltaPhi","Delta Phi(lepton, E_{T}^{miss}) ",n_bins,-0.1,1.1*M_PI,isdata);
  TH1F * h_3JetSystemMass = InitHist("InvJetMass","inv. mass of 3 jet system [MeV]",n_bins, 0, 1000.e3,isdata);
  TH1F * h_FullSysMass = InitHist("FullSysMass","inv. mass of system [MeV]",n_bins, 0, 1600.e3,isdata);
  TH1F * h_FullSysEta = InitHist("FullSysEta","Eta (4jets, lep)",n_bins, -3, 3,isdata);
  // now loop over the events in the tree
  for (int iEntry = 0; iEntry < nEntries; ++iEntry) {

    // get entry no. iEntry and tell every 100th event
    tree->GetEntry(iEntry);
    if ((iEntry+1)%10000 == 0) {
      cout << "INFO processing the " << iEntry+1 << "th event" << endl;
    }
    // For Monte Carlo, each event has to have a scale factor. 
    // The scale factors necessary can be found separately in the samples, but they have also been combined in the variable scaleFactor_COMBINED.
    float w = 1.;
    // if (filename.CompareTo("ttbar.el_selected.root") == 0){
	// 	w = w_ttbar;
	// 	cout << filename << " worked!" << endl;
	// }
	// else if (filename.CompareTo("ttbar.mu.2_selected.root") == 0){
	// 	w = w_ttbar;
	// 	cout << filename << " worked!" << endl;
	// }
	// else if (filename.CompareTo("singletop.el_selected.root") == 0){
	// 	w = w_singletop;
	// 	cout << filename << " worked!" << endl;
	// }
	// else if (filename.CompareTo("singletop.mu.2_selected.root") == 0){
	// 	w = w_singletop;
	// 	cout << filename << " worked!" << endl;
	// }
	// else if (filename.CompareTo("diboson.el_selected.root") == 0){
	// 	w = w_diboson;
	// 	cout << filename << " worked!" << endl;
	// }
	// else if (filename.CompareTo("diboson.mu.2_selected.root") == 0){
	// 	w = w_diboson;
	// 	cout << filename << " worked!" << endl;
	// }
	// else if (filename.CompareTo("wjets.el_selected.root") == 0){
	// 	w = w_wjets;
	// 	cout << filename << " worked!" << endl;
	// }
	// else if (filename.CompareTo("wjets.mu.2_selected.root") == 0){
	// 	w = w_wjets;
	// 	cout << filename << " worked!" << endl;
	// }
	// else if (filename.CompareTo("zjets.el_selected.root") == 0){
	// 	w = w_zjets;
	// 	cout << filename << " worked!" << endl;
	// }
	// else if (filename.CompareTo("zjets.mu.2_selected.root") == 0){
	// 	w = w_zjets;
	// 	cout << filename << " worked!" << endl;
	// }
	// else {
	// 	w = 1.;
	// 	cout << filename << "is lame !!!!!!!!!11!11!" << endl;
	// }
	
    if (!isdata) // if (!isdata)
      w = tree->scaleFactor_COMBINED;
    else
		w = 1.;
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // Get variable or calculate it (s. instructions)
    float lep_pt = tree->lep_pt[0];
    float lep_E = tree->lep_E[0];
    float lep_phi = tree->lep_phi[0];
    float lep_eta = tree->lep_eta[0];
    
    float jet_eta = tree->jet_eta[0];
	float jet_pt = tree->jet_pt[0];
	float jet_phi = tree->jet_phi[0];
	float jet_E = tree->jet_E[0];
	
	unsigned int jet_n = tree->jet_n;
	
	unsigned int met_et = tree->met_et;
	
	int btagged = tree->btagged;
	
	// additional discriminants
	// delta phi(E_T, lep)
	float DeltaPhi_1 = abs(tree->met_phi - tree->lep_phi[0]);
	float DeltaPhi_2 = abs(2*M_PI - abs(tree->met_phi - tree->lep_phi[0]));
	
	// 3 jet system
	TLorentzVector baseVec = TLorentzVector();
	for (unsigned int i = 0; i < 3; i++){
		TLorentzVector Jet = TLorentzVector();
		Jet.SetPtEtaPhiE(tree->jet_pt[i], tree->jet_eta[i], tree->jet_phi[i], tree->jet_E[i]);
		baseVec += Jet;
	}
	
	float InvJetMass = baseVec.M();
	
	// whole system
	TLorentzVector * SysVec = new TLorentzVector();
	TLorentzVector * lepton = new TLorentzVector();
	for (unsigned int i = 0; i < 4; i++){
		TLorentzVector * Jet = new TLorentzVector();
		Jet->SetPtEtaPhiE(tree->jet_pt[i], tree->jet_eta[i], tree->jet_phi[i], tree->jet_E[i]);
		*SysVec += *Jet;
	}
	// lepton TLV
	lepton->SetPtEtaPhiE(lep_pt, lep_eta, lep_phi, lep_E);
	// met et TLV of neutrino
	TLorentzVector * MET_ET = new TLorentzVector();
	MET_ET->SetPxPyPzE(met_et*cos(tree->met_phi), met_et*sin(tree->met_phi), 0., met_et);
	// Neutrino TLV
	TLorentzVector * Neut = new TLorentzVector();
	Neut = physicsHelper::Neutrino(*MET_ET, *lepton);
	*SysVec += *lepton;
	*SysVec += *Neut;
	float SysJetMass = SysVec->M();
	float FullSysEta = SysVec->Eta();
	
    ///////////////////////////////////////////////////////////////////////////////////////////  
    // fill histograms
    h_lep_pt->Fill(lep_pt, w);
    h_lep_eta->Fill(lep_eta, w);
    h_lep_phi->Fill(lep_phi, w);
    h_lep_E->Fill(lep_E, w);
    
    h_jet_eta->Fill(jet_eta, w);
	h_jet_pt->Fill(jet_pt, w);
	h_jet_phi->Fill(jet_phi, w);
	h_jet_E->Fill(jet_E, w);
	
	h_jet_n->Fill(jet_n, w);
	
	h_met_et->Fill(met_et,w);

    h_btagged->Fill(btagged,w);
    ///////////////////////////////////////////////////////////////////////////////////////////

	// fill hist for all good jets
	for (unsigned int i = 0; i < tree->jet_n; i++){
		h_jet_eta_good->Fill(tree->jet_eta[i], w);
		h_jet_pt_good->Fill(tree->jet_pt[i], w);
		h_jet_phi_good->Fill(tree->jet_phi[i], w);
		h_jet_E_good->Fill(tree->jet_E[i], w);
	}
	
	if (DeltaPhi_1 > DeltaPhi_2){
		h_DeltaPhi->Fill(DeltaPhi_2, w);
	}
	else{
		h_DeltaPhi->Fill(DeltaPhi_1, w);
	}
	h_3JetSystemMass->Fill(InvJetMass, w);
	h_FullSysMass->Fill(SysJetMass, w);
	h_FullSysEta->Fill(FullSysEta, w);


  }

  SetStyle();

  ///////////////////////////////////////////////////////////////////////////////////////////
  //To do: Use PlotHist to plot
	TString str = argv[1];
    str.ReplaceAll(".root", "_");
    str.ReplaceAll("output_runSelection/", "root_plots/");
    TString str2 = str; 
    str2.ReplaceAll("root_plots","");
    str2.ReplaceAll("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte//","");
  
	PlotHist(str + "/" + str2 +"lep_pt.pdf", h_lep_pt);
	PlotHist(str + "/" + str2 +"lep_eta.pdf", h_lep_eta);
	PlotHist(str + "/" + str2 +"lep_phi.pdf", h_lep_phi);
	PlotHist(str + "/" + str2 +"lep_E.pdf", h_lep_E);

	PlotHist(str + "/" + str2 +"jet_eta.pdf", h_jet_eta);
	PlotHist(str + "/" + str2 +"jet_pt.pdf", h_jet_pt);
	PlotHist(str + "/" + str2 +"jet_phi.pdf", h_jet_phi);
	PlotHist(str + "/" + str2 +"jet_E.pdf", h_jet_E);

	PlotHist(str + "/" + str2 +"jet_eta_good.pdf", h_jet_eta_good);
	PlotHist(str + "/" + str2 +"jet_pt_good.pdf", h_jet_pt_good);
	PlotHist(str + "/" + str2 +"jet_phi_good.pdf", h_jet_phi_good);
	PlotHist(str + "/" + str2 +"jet_E_good.pdf", h_jet_E_good);

	PlotHist(str + "/" + str2 +"jet_n.pdf", h_jet_n);
	
	PlotHist(str + "/" + str2 + "met_et.pdf",h_met_et);
	
	PlotHist(str + "/" + str2 + "btagged.pdf",h_btagged);
	// additional discriminants: plotting
	PlotHist(str + "/" + str2 + "DeltaPhi.pdf", h_DeltaPhi);
	PlotHist(str + "/" + str2 + "InvJetMass.pdf", h_3JetSystemMass);
	PlotHist(str + "/" + str2 + "SysJetMass.pdf", h_FullSysMass);
	PlotHist(str + "/" + str2 + "FullSysEta.pdf", h_FullSysEta);

  /////////////////////////////////////////////////////////////////////////////////////////////
  //You can now use fileHelper::SaveNewHist to save histograms
	fileHelper::TSaveNewHist(str + "/" + str2 +"lep_pt.root", h_lep_pt, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"lep_eta.root", h_lep_eta, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"lep_phi.root", h_lep_phi, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"lep_E.root", h_lep_E, true);
	
	
	fileHelper::TSaveNewHist(str + "/" + str2 +"jet_eta.root", h_jet_eta, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"jet_pt.root", h_jet_pt, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"jet_phi.root", h_jet_phi, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"jet_E.root", h_jet_E, true);

	fileHelper::TSaveNewHist(str + "/" + str2 +"jet_n.root", h_jet_n, true);

	fileHelper::TSaveNewHist(str + "/" + str2 +"met_et.root",h_met_et, true);
	
	fileHelper::TSaveNewHist(str + "/" + str2 +"btagged.root",h_btagged, true);
	
	// good hist save
	fileHelper::TSaveNewHist(str + "/" + str2 +"jet_eta_good.root", h_jet_eta_good, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"jet_pt_good.root", h_jet_pt_good, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"jet_phi_good.root", h_jet_phi_good, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"jet_E_good.root", h_jet_E_good, true);
	
	fileHelper::TSaveNewHist(str + "/" + str2 +"DeltaPhi.root", h_DeltaPhi, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"InvJetMass.root", h_3JetSystemMass, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"SysJetMass.root", h_FullSysMass, true);
	fileHelper::TSaveNewHist(str + "/" + str2 +"FullSysEta.root", h_FullSysEta, true);
  // To end the program properly, delete all dynamic instances
  delete h_lep_pt;
  delete h_lep_eta;
  delete h_lep_phi;
  delete h_lep_E;
  
  delete h_jet_eta;
  delete h_jet_pt;
  delete h_jet_phi;
  delete h_jet_E;
  
  delete h_jet_n;
  
  delete h_met_et;
  
  delete h_btagged;
  
  delete h_jet_eta_good;
  delete h_jet_pt_good;
  delete h_jet_phi_good;
  delete h_jet_E_good;
  delete h_DeltaPhi;
  delete h_3JetSystemMass;
  delete h_FullSysMass;
  delete h_FullSysEta;
  
  delete tree;
  return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////
////// Functions that can but do not have to be uses: ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////



TH1F * InitHist(TString varName,TString varUnit, int numberBins, float minBin, float maxBin, bool isData){
  TH1F *hist = new TH1F(varName,varName,numberBins,minBin,maxBin);
  hist->SetTitle(";"+varUnit+";Events");
  hist->GetYaxis()->SetTitleOffset(1.3);
  hist->Sumw2(false);
  if(isData){
    hist->Sumw2(true);
  }
  return hist;
}


void PlotHist(TString filename, TH1F * hist){
	TCanvas * canv = new TCanvas("canv","Canvas for histogram",1);
  hist->Draw("hist");
  canv->Print(filename);
  cout << "INFO: " << filename << " has been created" << endl;
  delete canv;
}

void Plot2Hist(TString filename, TString varUnit, TH1F * hist1, TH1F * hist2) {
  TCanvas * canv = new TCanvas("canv","Canvas for histograms",1);
  canv->SetLeftMargin(.12);
  canv->SetRightMargin(.1);
  
  hist1->Draw("HIST");

  hist1->SetTitle(";"+varUnit+";Events");
  hist1->GetYaxis()->SetTitleOffset(1);

  hist2->Draw("HIST SAME");

  TLegend * l = new TLegend(0.5, 0.75, 0.86, 0.9, "");
  l->SetFillColor(0);
  l->SetBorderSize(1);
  l->SetTextSize(0.04);
  l->SetTextAlign(12);
  l->AddEntry(hist1, "Add description", "l");
  l->AddEntry(hist2, "Add description here", "l");
  l->Draw();

  ///////////////////////////////////////////
  // Histograms can be normalized to unit area by calling 
  // hist->Scale(1./hist->Integral()) before plotting
  // In case you decide to do that, you can use the following lines to label your plots
  ////////////////////////////////////////////////////////////////////////////////////////
  //TLatex * t = new TLatex(0.93,0.55,"#bf{Normalized to unit area}");
  //t->SetTextAngle(90);
  //t->SetNDC();
  //t->SetTextSize(.04);
  //t->DrawClone();

  canv->Print(filename);
  cout << "INFO: " << filename << " has been created" << endl;
  delete canv;
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
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1.2);
  gStyle->SetHistLineWidth(2);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
}


