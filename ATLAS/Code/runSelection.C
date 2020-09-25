#include "mini.h"
#include "fileHelper.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argn, char *argv[]) {

  //if you want to run this script for several input files, it is useful to call the name of the file when executing this program
  if(argn==1){
    cout << "Please start runSelection.exe with added argument of file to be processed" << endl;
    return 1;
  }
  // path to the file to be studied + filename from argument called when executing file
  string inpath = string(argv[1]);
  TString filename = TString(inpath).ReplaceAll("/net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/", "");

  cout << "Processing " << filename << endl;

  // retrieve the tree from the file
  mini * tree = fileHelper::GetMiniTree(inpath);
  if (tree == 0) {
    cout << "ERROR tree is null pointer" << endl;
    return 1;
  }

  // check that the tree is not empty
 float nEntries = tree->GetEntries();
  cout << "INFO tree contains " << nEntries << " events" << endl;
  if (nEntries == 0) {
    cout << "ERROR tree contains zero events" << endl;
    return 1;
  }

  // create file to which the selection is going to be saved to
  TString outpath = "output_runSelection/" + filename;
  outpath.ReplaceAll(".root", "_selected.root");
  TFile * newFile = new TFile(outpath, "RECREATE");
  
  // make a copy of the tree to be saved after selection
  TTree * newTree = tree->CloneTree();
    
  // now loop over the events in the tree
  // counts for efficiencies
  int btagged; 
  
  float lep_n_counts(0);
  float lep_pt_counts(0);
  float lep_eta_counts(0);
  float jet_pt_counts(0);
  float b_tagged_counts(0);
  float met_et_counts(0);
  float jet_eta_counts(0);
  
  // normiert auf femtobarn
  // cross sections
  float ttbar_xsec = 252.82e-12;
  float singletop_xsec = 52.47e-12;
  float diboson_xsec = 29.41e-12;
  float z_jets_xsec = 2516.2e-12;
  float w_jets_xsec = 36214e-12;
  float zprime400_xsec = 1.1e-10;
  float zprime500_xsec = 8.2e-11;
  float zprime750_xsec = 2.0e-11;
  float zprime1000_xsec = 5.5e-12;
  float zprime1250_xsec = 1.9e-12;
  float zprime1500_xsec = 8.3e-13;
  float zprime1750_xsec = 3.0e-13;
  float zprime2000_xsec = 1.4e-13;
  float zprime2250_xsec = 6.7e-14;
  float zprime2500_xsec = 3.5e-14;
  float zprime3000_xsec = 1.2e-14;
  
  // events
  float ttbar_events = 7847944;
  float singletop_events = 1468942;
  float diboson_events = 922521;
  float z_jets_events = 37422926;
  float w_jets_events = 66536222;
  float zprime400_events = 100000;
  float zprime500_events = 100000;
  float zprime750_events = 100000;
  float zprime1000_events = 10000;
  float zprime1250_events = 10000;
  float zprime1500_events = 10000;
  float zprime1750_events = 10000;
  float zprime2000_events = 10000;
  float zprime2250_events = 100000;
  float zprime2500_events = 100000;
  float zprime3000_events = 100000;
  
  float lumi = 1e15; // inverse femtobarn
  
    // weights
  float w_ttbar      = lumi*ttbar_xsec      / ttbar_events;     
  float w_singletop  = lumi*singletop_xsec  / singletop_events; 
  float w_diboson    = lumi*diboson_xsec    / diboson_events;   
  float w_zjets      = lumi*z_jets_xsec     / z_jets_events;    
  float w_wjets      = lumi*w_jets_xsec     / w_jets_events;    
  float w_zprime400  = lumi*zprime400_xsec  / zprime400_events; 
  float w_zprime500  = lumi*zprime500_xsec  / zprime500_events; 
  float w_zprime750  = lumi*zprime750_xsec  / zprime750_events; 
  float w_zprime1000 = lumi*zprime1000_xsec / zprime1000_events;
  float w_zprime1250 = lumi*zprime1250_xsec / zprime1250_events;
  float w_zprime1500 = lumi*zprime1500_xsec / zprime1500_events;
  float w_zprime1750 = lumi*zprime1750_xsec / zprime1750_events;
  float w_zprime2000 = lumi*zprime2000_xsec / zprime2000_events;
  float w_zprime2250 = lumi*zprime2250_xsec / zprime2250_events;
  float w_zprime2500 = lumi*zprime2500_xsec / zprime2500_events;
  float w_zprime3000 = lumi*zprime3000_xsec / zprime3000_events;
  
  TBranch *btagged_n = newTree->Branch("btagged", &btagged, "btagged/I");
  
  for (unsigned int iEntry = 0; iEntry < nEntries; ++iEntry) {
	btagged = 0;
    // get entry no. iEntry and tell every 100000th event
    tree->GetEntry(iEntry);
    if ((iEntry+1)%100000 == 0) {
      cout << "INFO processing the " << iEntry+1 << "th event" << endl;
    }


//	cout << tree->lep_truthMatched[iEntry] << endl;
//	cout << tree->jet_pt[iEntry] << endl;
    //////////////////////////////////////////////////////
    // To do: Implement all required selection criteria //
    //////////////////////////////////////////////////////
	
    bool passCriteria = true;
//	int btag_count = 0;
	//unsigned int N_pt_jet = 0; // jets mit pt kleiner als grenze
	//int N_pt_lep = 0; // leptonen mit pt kleiner als grenze
	//int N_eta_lep = 0; // leptonen ausserhalb des bereichs
	int N_eta_jet = 0; // jets mit eta groesser als grenze
	
	
	
	// genau ein lepton
	if (tree->lep_n != 1) {
		continue;
	}
	lep_n_counts++;
	// lepton pt
//	for (unsigned int i = 0 ;i < tree->lep_n; i++){
//		if(tree->lep_pt[i] < 50000){
//			N_pt_lep++;
//		}
//	}
//
//	if (N_pt_lep > 0){
//		continue;
//	}
	if (tree->lep_pt[0] < 50000){
		continue;
	}
	lep_pt_counts++;
	// lepton eta
//	for (unsigned int i = 0 ;i < tree->lep_n; i++){
//		if(tree->lep_eta[i] < -1.4 || tree->lep_eta[i] > 1.4){
//			N_eta_lep++;
//		}
//	}
//	if (N_eta_lep > 0){
//		// passCriteria = false;
//		continue;
//	}
//	lep_eta_counts++;
	// fordere mehr als 3 jets
	if (tree->jet_n < 4){ //jan lukas: <= 4
		continue;
	}
	// jet pt
	unsigned int schwelle_jet_pt = 100000;
	// schwelle gibt hier die Energie jedes einzelnen Jets im Event an
	//for (unsigned int i = 0 ;i <= tree->jet_n; i++){
		// if(tree->jet_pt[i] > schwelle_jet_pt){ //jan lukas: < 100000
		// 	N_pt_jet++;
		// 	// continue;
		// }
	//	N_pt_jet += tree->jet_pt[i];
	//}
	//if (N_pt_jet < tree->jet_n * schwelle_jet_pt){
	//	continue;
	//}
	if (tree->jet_pt[0] < schwelle_jet_pt){
		continue;
	}
	jet_pt_counts++;
	// if b-tagged	
	for (unsigned int i = 0; i < tree->jet_n; i++){
		if(tree->jet_MV1[i] > 0.7892){
			btagged++;
		}
	}
	if (btagged <= 1){
		continue;
	}
	btagged_n->Fill();
	b_tagged_counts++;
	// missing transverse energy
	if (tree->met_et < 40000){
		continue;
	}
	met_et_counts++;
	// jet eta
	for (unsigned int i = 0 ;i <= tree->jet_n; i++){
		if(tree->jet_eta[i] < -2.4 || tree->jet_eta[i] > 2.4){
			N_eta_jet++;
		}
	}
	if (N_eta_jet > 0){
		passCriteria = false;
	}
	else {
		passCriteria = true;
		jet_eta_counts++;
	}
// 	passCriteria = true;
    // check all selection criteria and only save the event to the new
    // tree if all of them are true
    if (passCriteria) {
      newTree->Fill();
    }
  }
  cout << "jet eta counts" << jet_eta_counts << endl;
  cout << "nEntries:" << nEntries << endl;
  ofstream myfile;
  myfile.open("effizienzen.txt", ios_base::app);
  myfile << "Processed file    " << filename << endl;
  myfile << "lepton N effizienz  " << lep_n_counts/nEntries << endl;
  myfile << "lepton pt effizienz  " << lep_pt_counts/nEntries << endl;
  myfile << "lepton eta effizienz  " << lep_eta_counts/nEntries << endl;
  myfile << "jet pt effizienz  " << jet_pt_counts/nEntries << endl;
  myfile << "met et effizienz  " << met_et_counts/nEntries << endl;
  myfile << "btagging effizienz  " << b_tagged_counts/nEntries << endl;
  myfile << "jet eta effizienz   " << jet_eta_counts/nEntries << endl;
  myfile << "################################################################" << endl;
  myfile.close();
  // task 6.1 a.)
  float N_ttbar = lumi*ttbar_xsec * (jet_eta_counts/ttbar_events);
  float N_singletop = lumi*singletop_xsec * (jet_eta_counts/singletop_events);
  float N_diboson = lumi*diboson_xsec * (jet_eta_counts/diboson_events);
  float N_Z_jets = lumi*z_jets_xsec * (jet_eta_counts/z_jets_events);
  float N_W_jets = lumi*w_jets_xsec * (jet_eta_counts/w_jets_events);
  // task 6.1 b.)
  float N_total_bkg = N_ttbar + N_singletop + N_diboson + N_Z_jets + N_W_jets;
  
  ofstream ourfile;
  ourfile.open("expected_events.txt", ios_base::app);
  ourfile << "filename: " << filename << endl;
  ourfile << "Expected Nr ttbar Events  " << " " << N_ttbar << endl;       
  ourfile << "Expected Nr singletop Events  "<< " " << N_singletop << endl;     
  ourfile << "Expected Nr diboson Events  " << " " << N_diboson << endl;      
  ourfile << "Expected Nr z jets Events  " << " " << N_Z_jets << endl;      
  ourfile << "Expected Nr  w jets Events  " << " " << N_W_jets << endl;
  ourfile << "Expected Nr bkg Events  " << " " << N_total_bkg << ", nEvents after selection: " << jet_eta_counts << endl;
  // task 6.1 c.)
  ourfile << "Expected Nr zprime400_ Events  " << " " << lumi*zprime400_xsec   * (jet_eta_counts/zprime400_events) << endl;    
  ourfile << "Expected Nr zprime500_ Events  " << " " << lumi*zprime500_xsec   * (jet_eta_counts/zprime500_events) << endl;  
  ourfile << "Expected Nr zprime750_ Events  " << " " << lumi*zprime750_xsec   * (jet_eta_counts/zprime750_events) << endl;       
  ourfile << "Expected Nr zprime1000 Events  " << " " << lumi*zprime1000_xsec  * (jet_eta_counts/zprime1000_events) << endl;    
  ourfile << "Expected Nr zprime1250 Events  " << " " << lumi*zprime1250_xsec  * (jet_eta_counts/zprime1250_events) << endl;   
  ourfile << "Expected Nr zprime1500 Events  " << " " << lumi*zprime1500_xsec  * (jet_eta_counts/zprime1500_events) << endl;    
  ourfile << "Expected Nr zprime1750 Events  " << " " << lumi*zprime1750_xsec  * (jet_eta_counts/zprime1750_events) << endl;      
  ourfile << "Expected Nr zprime2000 Events  " << " " << lumi*zprime2000_xsec  * (jet_eta_counts/zprime2000_events) << endl;        
  ourfile << "Expected Nr zprime2250 Events  " << " " << lumi*zprime2250_xsec * (jet_eta_counts/zprime2250_events) << endl;       
  ourfile << "Expected Nr zprime2500 Events  " << " " << lumi*zprime2500_xsec * (jet_eta_counts/zprime2500_events) << endl;        
  ourfile << "Expected Nr zprime3000 Events  " << " " << lumi*zprime3000_xsec * (jet_eta_counts/zprime3000_events) << endl;       
  ourfile << "################################################################" << endl;
  ourfile.close();
  
  ofstream yourfile;
  yourfile.open("weights.txt", ios_base::app);
  yourfile << "filename :" << filename << endl;
  yourfile << "Weights for ttbar_events      " << " " << w_ttbar      << endl;
  yourfile << "Weights for singletop_events  " << " " << w_singletop  << endl;
  yourfile << "Weights for diboson_events    " << " " << w_diboson    << endl;
  yourfile << "Weights for z_jets_events     " << " " << w_zjets      << endl;
  yourfile << "Weights for w_jets_events     " << " " << w_wjets      << endl;
  yourfile << "Weights for zprime400_events  " << " " << w_zprime400  << endl;
  yourfile << "Weights for zprime500_events  " << " " << w_zprime500  << endl;
  yourfile << "Weights for zprime750_events  " << " " << w_zprime750  << endl;
  yourfile << "Weights for zprime1000_events " << " " << w_zprime1000 << endl;
  yourfile << "Weights for zprime1250_events " << " " << w_zprime1250 << endl;
  yourfile << "Weights for zprime1500_events " << " " << w_zprime1500 << endl;
  yourfile << "Weights for zprime1750_events " << " " << w_zprime1750 << endl;
  yourfile << "Weights for zprime2000_events " << " " << w_zprime2000 << endl;
  yourfile << "Weights for zprime2250_events " << " " << w_zprime2250 <<  endl;
  yourfile << "Weights for zprime2500_events " << " " << w_zprime2500 <<  endl;
  yourfile << "Weights for zprime3000_events " << " " << w_zprime3000 <<  endl;
  yourfile << "################################################################" << endl;
  yourfile.close();

  //cout << "Lep_pt counts" << newTree->GetEntries() << endl;
  // save new tree to file
  cout << "INFO saving new tree with " << newTree->GetEntries() << " entries" << endl;
  newFile->Write();
  gDirectory->Purge();
  newFile->Close();
  
  // end program happily
  delete newFile;
  return 0;
}
