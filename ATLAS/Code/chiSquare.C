#include <iostream>
#include <string>
#include "TMath.h"
#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TLegend.h"
#include "fileHelper.h"
#include "TTree.h"
#include "string.h"
#include "THStack.h"
#include "TLatex.h"
#include <fstream>
using namespace std;

// float chisquareNBins(TH1F * data, TH1F * mc);
float chisquareNBins(TH1F * data, THStack * mc);
double getNDF(TH1F * data, THStack * mc);
float chisquareNBinsNormal(TH1F * data, TH1F * mc);
double getNDFnormal(TH1F * data, TH1F * mc);

void SetStyle();
// void PlotStack(TString path, TString varUnit, THStack * mc, TH1F * data, TLegend * legend);

int main(){
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
   
   
  // 
    TFile * file_zprime400  = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime400.mu_selected_/zprime400.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime500  = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime500.mu_selected_/zprime500.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime750  = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime750.mu_selected_/zprime750.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime1000 = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime1000.mu_selected_/zprime1000.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime1250 = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime1250.mu_selected_/zprime1250.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime1500 = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime1500.mu_selected_/zprime1500.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime1750 = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime1750.mu_selected_/zprime1750.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime2000 = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime2000.mu_selected_/zprime2000.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime2250 = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime2250.mu_selected_/zprime2250.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime2500 = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime2500.mu_selected_/zprime2500.mu_selected_SysJetMass_hist.root");
	TFile * file_zprime3000 = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zprime3000.mu_selected_/zprime3000.mu_selected_SysJetMass_hist.root");

	TH1F * h_zprime400 = (TH1F*)file_zprime400->Get("FullSysMass");
	TH1F * h_zprime500 = (TH1F*)file_zprime500->Get("FullSysMass");
	TH1F * h_zprime750 = (TH1F*)file_zprime750->Get("FullSysMass");
	TH1F * h_zprime1000 = (TH1F*)file_zprime1000->Get("FullSysMass");
	TH1F * h_zprime1250 = (TH1F*)file_zprime1250->Get("FullSysMass");
	TH1F * h_zprime1500 = (TH1F*)file_zprime1500->Get("FullSysMass");
	TH1F * h_zprime1750 = (TH1F*)file_zprime1750->Get("FullSysMass");
	TH1F * h_zprime2000 = (TH1F*)file_zprime2000->Get("FullSysMass");
	TH1F * h_zprime2250 = (TH1F*)file_zprime2250->Get("FullSysMass");
	TH1F * h_zprime2500 = (TH1F*)file_zprime2500->Get("FullSysMass");
	TH1F * h_zprime3000 = (TH1F*)file_zprime3000->Get("FullSysMass");
	
	// At this point, you want to first test the agreement between data and monte carlo.
	 // After that, you want to create a limit plot
	  // You should be able to do most of it on your own by now, but here are some usefull things:

	 // The function chisquareNBins(TH1F * data, TH1F * mc) returns the chi square value that characterizes the aggreement between a data histogram and a monte carlo histogramm
	       // It prints the degrees of freedom in this comparison, which might be useful information

	    //////////////////////////////////////////////////////////////////
	 // Do do: 1. quantify data-mc agreement
	//		  2. calculate limits to the cross section of Z' production
	 //
	             ////////////////////////////////////////////////////////////////////////////
	TFile * data = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/data.mu.2_selected_/data.mu.2_selected_SysJetMass_hist.root");
	TH1F * h_data = (TH1F*)data->Get("FullSysMass");
    
    THStack * hs_bkg = new THStack("hs_bkg", "");
    TFile * ttbar = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/ttbar.mu_selected_/ttbar.mu_selected_SysJetMass_hist.root");
    TH1F * h_ttbar = (TH1F*)ttbar->Get("FullSysMass");
    TFile * stop = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/singletop.mu_selected_/singletop.mu_selected_SysJetMass_hist.root");
    TH1F * h_stop = (TH1F*)stop->Get("FullSysMass");
    TFile * dboson = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/diboson.mu_selected_/diboson.mu_selected_SysJetMass_hist.root");
    TH1F * h_dboson = (TH1F*)dboson->Get("FullSysMass");
    TFile * zjets = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/zjets.mu_selected_/zjets.mu_selected_SysJetMass_hist.root");
    TH1F * h_zjets = (TH1F*)zjets->Get("FullSysMass");
    TFile * wjets = new TFile("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/root_plots/wjets.mu_selected_/wjets.mu_selected_SysJetMass_hist.root");
    TH1F * h_wjets = (TH1F*)wjets->Get("FullSysMass");
	
	h_ttbar->Scale(w_ttbar);
	h_stop->Scale(w_singletop);
	h_dboson->Scale(w_diboson);
	h_zjets->Scale(w_zjets);
	h_wjets->Scale(w_wjets);
	
    hs_bkg->Add(h_ttbar);
    hs_bkg->Add(h_stop);
    hs_bkg->Add(h_dboson);
    hs_bkg->Add(h_zjets);
    hs_bkg->Add(h_wjets);

	float discriminant_Chi2 = chisquareNBins(h_data, hs_bkg);
	unsigned int ndf = getNDF(h_data, hs_bkg);
	cout << "chi2:    " << discriminant_Chi2 << endl;
	cout << "NDF:    " << ndf << endl;
	cout << "p wert: " << TMath::Prob(discriminant_Chi2, ndf) << endl;
	//cout << "p value: " << discriminant_Chi2 << endl;



	// Once you finished calculating your limits, you want to plot them
	// Start with arrays of the mass, the expected cross section and the limits you calculated
	// The mass array has already be filled for you in order to remind you of the use of arrays
	float mass[11] = {400.,500.,750.,1000.,1250.,1500.,1750.,2000.,2250.,2500.,3000};
	// float expectedXsec[11] = {};
	// float limitXsec[11] = {};
	float scaleFactor[11] = {1.1, 0.82,0.2, 0.055, 0.019, 0.0083, 0.003, 0.0014, 6.7e-4, 3.5e-4, 1.2e-4};
	float scale_a[11] = {};

	// salvatores code snippet
	TH1F hist_array[11] = {*h_zprime400, *h_zprime500, *h_zprime750, *h_zprime1000,
												*h_zprime1250, *h_zprime1500, *h_zprime1750, *h_zprime2000,
												*h_zprime2250, *h_zprime2500, *h_zprime3000};
	TH1F *ptr = &hist_array[0]; // ptr zeigt auf nulltes Element des Arrays
	
	ofstream file;
	file.open("output_chi2.txt", ios_base::app);
	
	for (unsigned int i=0; i<11; i++) {
		float chi_squared = 0.0;
		unsigned int ndf = 0.0;
		double scaler = 0.0;

		do {
			TH1F *h_zprime_clone = (TH1F*)(ptr+i)->Clone();
			h_zprime_clone->Scale(scaleFactor[i] * scaler);
			
			TH1 * mc = (TH1*)hs_bkg->GetStack()->Last();
			
			TH1F *h_signal_plus_background = (TH1F*)mc->Clone();
			h_signal_plus_background->Add(h_zprime_clone);

			chi_squared = chisquareNBinsNormal(h_data, h_signal_plus_background);
			ndf = getNDFnormal(h_data, h_signal_plus_background);
			float p_value = TMath::Prob(chi_squared, ndf);
			if (p_value < 0.05) {
				cout << "scaler: " << scaler << " und p-value: " <<  p_value << endl;
				file << "scaler: " << scaler << " und p-value: " <<  p_value << endl;
				scale_a[i] = scaler;
				//h_zprime_clone->Reset("4j_el_nu_m");
				//h_signal_plus_background->Reset("4j_el_nu_m");
			}
			scaler += 0.1; // 0.01
			if(i==10) scaler = scaler + 1;
		}
		while (TMath::Prob(chi_squared, ndf) > 0.05);
	}
	file << "################################################################" << endl;
	file.close();
	float expectedXsec[11] = {1.1e2, 8.2e1, 2.0e1, 5.5, 1.9, 8.3e-1, 3.0e-1, 1.4e-1, 6.7e-2, 3.5e-2, 1.2e-2};
	float limitXsec[11] = {};

	file.open("output_chi2.txt", ios_base::app);
	for(unsigned int i = 0; i < 11; i++) {
		limitXsec[i] = scale_a[i]*expectedXsec[i];
		cout << "crosssection: " << limitXsec[i] << endl;
		file << "crosssection: " << limitXsec[i] << endl;
 	}
	// ende code snippet
	file << "################################################################" << endl;
	file << "chi2:    " << discriminant_Chi2 << endl;
	file << "NDF:    " << ndf << endl;
	file << "p wert: " << TMath::Prob(discriminant_Chi2, ndf) << endl;
	file << "################################################################" << endl;
	file.close();


	// Create a canvas
	SetStyle();
	TCanvas * c_limits = new TCanvas("c_limits", "canvas for limit plot", 1);
	// If you want to, use a logarithmic y axis 
  	c_limits->SetLogy();

	// Create a TGraph for the expected cross section
	TGraph * g_expected = new TGraph(11, mass, expectedXsec);
	g_expected->SetLineColor(kBlue);

	//Create a TGraph with you limits
	TGraph * g_limits = new TGraph(11, mass, limitXsec);
	
	//The TH1D is only to have axes to you plot
	TH1D * h_helper = new TH1D("h_helper", "just an empty helper histogram", 1, 400., 3000.);
	h_helper->SetMaximum(270);
	h_helper->GetXaxis()->SetTitle("m_{Z\'} [GeV]"); 
  	h_helper->GetYaxis()->SetTitle("#sigma_{Z'}#timesBR(Z'#rightarrow t#bar{t}) [pb]"); // don't forget the axis titles !
  	h_helper->Draw("p");

	// create a legend
	TLegend * l = new TLegend(0.35, 0.7, 0.9, 0.8, "");
  	l->SetFillColor(0);
  	l->SetBorderSize(0);
  	l->SetTextSize(0.04);
  	l->SetTextAlign(12);
  	l->AddEntry(g_expected, "Expected #sigma_{Z'}#timesBR(Z'#rightarrow t#bar{t})", "l");
  	l->AddEntry(g_limits, "Observed 95% CL upper limit (100 pb^{-1})", "l");
  	
  	g_expected->Draw("l SAME"); 
  	g_limits->Draw("l SAME");
  	l->Draw();
  	c_limits->SetLogy();
  	c_limits->Print("limits.pdf");
	
	return 0;

}
float chisquareNBinsNormal(TH1F * data, TH1F * mc){

	float chisquare_test = 0.0;
	
	int nbins = data->GetSize();
	int nbinsused = 0;
	for(int i = 1; i < nbins; i++){
		float n_data = data->GetBinContent(i);
		float n_mc = mc->GetBinContent(i);
		if(n_mc != 0.){
			chisquare_test = chisquare_test + (n_data-n_mc)*(n_data-n_mc)/n_mc;
			nbinsused++;
		}
	}


	// double ndf= double(nbinsused-1);

	// cout << "The number of degrees of freedom is " << ndf << endl;
	return chisquare_test;

}
double getNDFnormal(TH1F * data, TH1F * mc){

  int nbins = data->GetSize();
  int nbinsused = 0;
  for(int i = 1; i < nbins; i++){
	float n_mc = mc->GetBinContent(i);
    if(n_mc != 0.){
    	nbinsused++;
    }
  }
  double ndf= double(nbinsused-1);
  return ndf;
}

float chisquareNBins(TH1F * data, THStack * mc){

	float chisquare_test = 0.0;
	
	TH1 * last = (TH1*)mc->GetStack()->Last();
	
	int nbins = data->GetSize();
	int nbinsused = 0;
	for(int i = 1; i < nbins; i++){
		float n_data = data->GetBinContent(i);
		float n_mc = last->GetBinContent(i);
		if(n_mc != 0.){
			chisquare_test = chisquare_test + (n_data-n_mc)*(n_data-n_mc)/n_mc;
			nbinsused++;
		}
	}


	// double ndf= double(nbinsused-1);

	// cout << "The number of degrees of freedom is " << ndf << endl;
	return chisquare_test;

}

double getNDF(TH1F * data, THStack * mc){

	TH1 * last = (TH1*)mc->GetStack()->Last();

	int nbins = data->GetSize();
  int nbinsused = 0;
  for(int i = 1; i < nbins; i++){
		float n_mc = last->GetBinContent(i);
    if(n_mc != 0.){
    	nbinsused++;
    }
  }
  double ndf= double(nbinsused-1);
  return ndf;
}



// void PlotStack(TString filename, TString varUnit, THStack* mc, TH1F * data, TLegend * legend) {
//   SetStyle();
//   TCanvas * canv = new TCanvas("canv","Canvas for histogram",1);
//   canv->SetLeftMargin(.12);
//   canv->SetRightMargin(.1);
//   data->Draw("E1");
//   data->SetMinimum(0);
//   mc->Draw("hist SAME");
//   data->Draw("E1 SAME");
//   mc->SetTitle(";"+varUnit+";Events");
//   mc->GetYaxis()->SetTitleOffset(1);
//   data->Draw("E1 SAME");
//   legend->Draw();
//   canv->Print(filename);
//   delete canv;
// }

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
