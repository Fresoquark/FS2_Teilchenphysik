#include <iostream>
#include <string>
#include "TMath.h"
#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TLegend.h"


using namespace std;

float chisquareNBins(TH1F * data, TH1F * mc);
double getNDF(TH1F * data, TH1F * mc);

void SetStyle();

int main(){

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

	TFile * file_data = new TFile("./plots/plots_data.mu_selected/data.mu_selected_hist.root");
	TFile * file_mc = new TFile("./chi_squared_data.root");

	TFile * file_zprime400 = new TFile("./plots/plots_zprime400.mu_selected/zprime400.mu_selected_hist.root");
	TFile * file_zprime500 = new TFile("./plots/plots_zprime500.mu_selected/zprime500.mu_selected_hist.root");
	TFile * file_zprime750 = new TFile("./plots/plots_zprime750.mu_selected/zprime750.mu_selected_hist.root");
	TFile * file_zprime1000 = new TFile("./plots/plots_zprime1000.mu_selected/zprime1000.mu_selected_hist.root");
	TFile * file_zprime1250 = new TFile("./plots/plots_zprime1250.mu_selected/zprime1250.mu_selected_hist.root");
	TFile * file_zprime1500 = new TFile("./plots/plots_zprime1500.mu_selected/zprime1500.mu_selected_hist.root");
	TFile * file_zprime1750 = new TFile("./plots/plots_zprime1750.mu_selected/zprime1750.mu_selected_hist.root");
	TFile * file_zprime2000 = new TFile("./plots/plots_zprime2000.mu_selected/zprime2000.mu_selected_hist.root");
	TFile * file_zprime2250 = new TFile("./plots/plots_zprime2250.mu_selected/zprime2250.mu_selected_hist.root");
	TFile * file_zprime2500 = new TFile("./plots/plots_zprime2500.mu_selected/zprime2500.mu_selected_hist.root");
	TFile * file_zprime3000 = new TFile("./plots/plots_zprime3000.mu_selected/zprime3000.mu_selected_hist.root");

	TH1F * h_data = (TH1F*)file_data->Get("4j_el_nu_m");
	TH1F * h_mc = (TH1F*)file_mc->Get("h_comb");

	TH1F * h_zprime400 = (TH1F*)file_zprime400->Get("4j_el_nu_m");
	TH1F * h_zprime500 = (TH1F*)file_zprime500->Get("4j_el_nu_m");
	TH1F * h_zprime750 = (TH1F*)file_zprime750->Get("4j_el_nu_m");
	TH1F * h_zprime1000 = (TH1F*)file_zprime1000->Get("4j_el_nu_m");
	TH1F * h_zprime1250 = (TH1F*)file_zprime1250->Get("4j_el_nu_m");
	TH1F * h_zprime1500 = (TH1F*)file_zprime1500->Get("4j_el_nu_m");
	TH1F * h_zprime1750 = (TH1F*)file_zprime1750->Get("4j_el_nu_m");
	TH1F * h_zprime2000 = (TH1F*)file_zprime2000->Get("4j_el_nu_m");
	TH1F * h_zprime2250 = (TH1F*)file_zprime2250->Get("4j_el_nu_m");
	TH1F * h_zprime2500 = (TH1F*)file_zprime2500->Get("4j_el_nu_m");
	TH1F * h_zprime3000 = (TH1F*)file_zprime3000->Get("4j_el_nu_m");

	// We assess if our data is background only compatible with the chi_squared goodness of fit
	float chi_squared = chisquareNBins(h_data, h_mc);
	unsigned int ndf = getNDF(h_data, h_mc);
	cout << "p wert: " << TMath::Prob(chi_squared, ndf) << endl;

	// Once you finished calculating your limits, you want to plot them
	// Start with arrays of the mass, the expected cross section and the limits you calculated
	// The mass array has already be filled for you in order to remind you of the use of arrays

	float mass[11] = {400.,500.,750.,1000.,1250.,1500.,1750.,2000.,2250.,2500.,3000};
	// Get cross sections of each zprime process in pb from infofile.txt.
	// These scale factors are already weighted by the lumi 1000/pb and the no. of events 100 000
	float scaleFactor[11] = {1.1, 0.82,0.2, 0.055, 0.019, 0.0083, 0.003, 0.0014, 6.7e-4, 3.5e-4, 1.2e-4};
	float scale_a[11] = {};

	TH1F hist_array[11] = {*h_zprime400, *h_zprime500, *h_zprime750, *h_zprime1000,
												*h_zprime1250, *h_zprime1500, *h_zprime1750, *h_zprime2000,
												*h_zprime2250, *h_zprime2500, *h_zprime3000};
	TH1F *ptr = &hist_array[0]; // ptr zeigt auf nulltes Element des Arrays

	for (unsigned int i=0; i<11; i++) {
		float chi_ed = 0.0;
		unsigned int ndf = 0.0;
		double scaler = 0.0;

		do {
			TH1F *h_zprime_clone = (TH1F*)(ptr+i)->Clone();
			h_zprime_clone->Scale(scaleFactor[i] * scaler);

			TH1F *h_signal_plus_background = (TH1F*)h_mc->Clone();
			h_signal_plus_background->Add(h_zprime_clone);

			chi_squared = chisquareNBins(h_data, h_signal_plus_background);
			ndf = getNDF(h_data, h_signal_plus_background);
			float p_value = TMath::Prob(chi_squared, ndf);
			if (p_value < 0.05) {
				cout << "scaler: " << scaler << " und p-value: " <<  p_value << endl;
				scale_a[i] = scaler;
				//h_zprime_clone->Reset("4j_el_nu_m");
				//h_signal_plus_background->Reset("4j_el_nu_m");
			}
			scaler += 0.1; // 0.01
			if(i==10) scaler = scaler + 1;
		}
		while (TMath::Prob(chi_squared, ndf) > 0.05);
	}

	float expectedXsec[11] = {1.1e2, 8.2e1, 2.0e1, 5.5, 1.9, 8.3e-1, 3.0e-1, 1.4e-1, 6.7e-2, 3.5e-2, 1.2e-2};
	float limitXsec[11] = {};

	for(unsigned int i = 0; i < 11; i++) {
    limitXsec[i] = scale_a[i]*expectedXsec[i];
    cout << "crosssection: " << limitXsec[i] << endl;
 	}

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
	h_helper->SetMaximum(300);
	h_helper->SetMinimum(0.01);
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
  	l->AddEntry(g_limits, "Observed 95% CL upper limit (1 fb^{-1})", "l");

  	g_expected->Draw("l SAME");
  	g_limits->Draw("l SAME");
  	l->Draw();
  	c_limits->SetLogy();
  	c_limits->Print("limits.pdf");

	return 0;

}


float chisquareNBins(TH1F * data, TH1F * mc){

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

	double ndf= double(nbinsused-1);

	//cout << "The number of degrees of freedom is " << ndf << endl;
  //      cout << "The Chi-Squared value is " << chisquare_test << endl;
	return chisquare_test;

}

double getNDF(TH1F * data, TH1F * mc){

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
