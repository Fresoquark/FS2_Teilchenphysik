#include "Neutrino.h"
#include "TMinuit.h"
#include "TLorentzVector.h"
#include <iostream>

double metfit(double fitterPrintLevel, int ysol, double mW)
{

  //double Pxnu = 0.0;
  TMinuit* minu = new TMinuit(5);

  if (ysol == 1) minu->SetFCN(NeutrinoFit::delta1fcn);
  if (ysol == 2) minu->SetFCN(NeutrinoFit::delta2fcn);


  double arglist[20];
  int ierflg = 0;

  // Set print level.
  arglist[0] = fitterPrintLevel;
  minu->mnexcm("SET PRINT", arglist, 1, ierflg);
  // Set strategy. Possible values: 0, 1, 2
  arglist[0] =  2.0;
  minu->mnexcm("SET STRATEGY", arglist, 1, ierflg);
  arglist[0] =  1.0;
  minu->mnexcm("CALL FCN", arglist, 1, ierflg);

  // Calculate limits for the parameter:

  Double_t upper = 0.0;
  Double_t lower = 0.0;
  Double_t start = 0.0;

  if(NeutrinoFit::FullReco_Pxe < 0) {
    upper = - mW*mW/(4*NeutrinoFit::FullReco_Pxe) -0.01;
    lower = -9999.;
  }

  if(NeutrinoFit::FullReco_Pxe == 0) {
    upper =  9999.;
    lower = -9999.;
  }

  if(NeutrinoFit::FullReco_Pxe > 0) {
    upper = 9999.;
    lower = - mW*mW/(4*NeutrinoFit::FullReco_Pxe) +0.01;
  }

 if(NeutrinoFit::FullReco_MET_X > upper) start = upper -1;
 else if(NeutrinoFit::FullReco_MET_X < lower) start = lower + 1;
 else start = NeutrinoFit::FullReco_MET_X;


  // Set parameters:

  minu->mnparm(0, "Px", start, 0.001, lower, upper, ierflg);

  arglist[0] = .5;
  minu->mnexcm("SET ERR", arglist , 1, ierflg);

  arglist[0] = 0.0;
  minu->mnexcm("SET NOW", arglist , 1, ierflg);

  ierflg = 0;
  arglist[0] = 100;
  arglist[1] = 1.;
  minu->mnexcm("SIMPLEX", arglist, 2, ierflg);
  arglist[0] = 500;
  minu->mnexcm("MIGRAD", arglist, 1, ierflg);

  minu->mnmnos() ;

  double px_fit;
  double px_fit_error;

  int rtVal = minu->GetParameter(0, px_fit, px_fit_error);
  if (rtVal < 0)
    std::cerr << "Error with parameter." << std::endl;


  //Pxnu  = px_fit;

  if (fitterPrintLevel > 0) {
    std::cout<<"*******************************"<<std::endl;
    std::cout << "Fit Results: Px(nu) = " << px_fit
	      << " +- " << px_fit_error << std::endl;
    std::cout<<"*******************************"<<std::endl;
  }

  delete minu;
  return px_fit;
}


int pz_of_W(TLorentzVector lep, TLorentzVector* met, double* pz)
{
  // function for the reconstruction of the pz value of the W
  // using a W mass constrained
  // If the transverse mass of the W is bigger than the W mass itself
  // a fit changing the met is performed to ensure that the transverse
  // W mass is equal to the W mass

  const double MW = 80.4;
  int nsol = 0;
  //double pz[2]; // container for the two pz solutions;

  // filling the global variables neccessary for Minuit
  // lepton
  NeutrinoFit::FullReco_PTe = lep.Pt();
  NeutrinoFit::FullReco_Pxe = lep.Px();
  NeutrinoFit::FullReco_Pye = lep.Py();
  // met
  NeutrinoFit::FullReco_MET_X = met->Px();
  NeutrinoFit::FullReco_MET_Y = met->Py();

//   std::cout << "Debug: met_px = " << met->Px() << "; met_py = " << met->Py() << std::endl;
//   std::cout << "Debug: lep_px = " << lep.Px() << "; lep_py = " << lep.Py() << "; lep_pt = " << lep.Pt()<< std::endl;
  
  
  double MisET2 = met->Px()*met->Px() + met->Py()*met->Py();
  //transverse W-mass
  double mWT = sqrt(2*(lep.Pt()*sqrt(MisET2) - lep.Px()*met->Px() - lep.Py()*met->Py()));


  double PxNu_1 = 0;
  double PxNu_2 = 0;
  double PyNu_1 = 0.;
  double PyNu_2 = 0.;
  double PxNu = 0.;
  double PyNu = 0.;


  bool isComplex = false;

  //check, whether transverse W-mass is larger than pole-mass mW or not.
  if(mWT>MW){
    isComplex = true;

    // if mWT > mW correct PxNu and PyNu until mWT = MW
    PxNu_1 = metfit(-1,1,MW); //(Printlevel, y-solution, MW)
    PxNu_2 = metfit(-1,2,MW);


    PyNu_1 = ((MW*MW*NeutrinoFit::FullReco_Pye + 2*NeutrinoFit::FullReco_Pxe*NeutrinoFit::FullReco_Pye*PxNu_1)
	      -(MW*NeutrinoFit::FullReco_PTe)*(sqrt(MW*MW + 4*NeutrinoFit::FullReco_Pxe*PxNu_1)))
      /(2*NeutrinoFit::FullReco_Pxe*NeutrinoFit::FullReco_Pxe);
    PyNu_2 = ((MW*MW*NeutrinoFit::FullReco_Pye + 2*NeutrinoFit::FullReco_Pxe*NeutrinoFit::FullReco_Pye*PxNu_2)
	      +(MW*NeutrinoFit::FullReco_PTe)*(sqrt(MW*MW + 4*NeutrinoFit::FullReco_Pxe*PxNu_2)))
      /(2*NeutrinoFit::FullReco_Pxe*NeutrinoFit::FullReco_Pxe);


    //Calculate delta1 and delta2 from PxNu_1 and PxNu_2:

    double delta1 =  sqrt((PxNu_1 - NeutrinoFit::FullReco_MET_X)*(PxNu_1 - NeutrinoFit::FullReco_MET_X) +(PyNu_1 - NeutrinoFit::FullReco_MET_Y)*(PyNu_1 - NeutrinoFit::FullReco_MET_Y));

    double delta2 =  sqrt((PxNu_2 - NeutrinoFit::FullReco_MET_X)*(PxNu_2 - NeutrinoFit::FullReco_MET_X) +(PyNu_2 - NeutrinoFit::FullReco_MET_Y)*(PyNu_2 - NeutrinoFit::FullReco_MET_Y));


    //PxNu and PyNu(PxNu):
    if(delta1<delta2) {
	PxNu = PxNu_1;
	PyNu = PyNu_1;
    } else {
      PxNu = PxNu_2;
      PyNu = PyNu_2;
    }
  }

  double pz1,pz2;

  // z component of neutrino momentum ...
  if( !isComplex) {
    // ...for two real solutions (mWT < MW)

    double mu = (MW*MW)/2 + met->Px()*lep.Px() + met->Py()*lep.Py();
    double a = (mu*lep.Pz()) / (lep.E()*lep.E() - lep.Pz()*lep.Pz());
    double a2 = TMath::Power(a,2);
    double b = (TMath::Power(lep.E(),2.)*MisET2 - TMath::Power(mu,2.))/
      (TMath::Power(lep.E(),2) - TMath::Power(lep.Pz(),2));


    if(a2-b < 0) {
      //std::cout<<"Complex !!!"<<std::endl; // should not happen anymore!
      // Warning("pz_of_W",
      //         "Complex result should not happen anymore!!!");
      pz1 = a;
      pz2 = a;
      nsol = 1;
    } else {
      double root = sqrt(a2-b);
      pz1 = a + root;
      pz2 = a - root;
      nsol = 2;
    }


  } else {
    // ... for complex solutions (mWT > MW): PzNu_OLD and new correction (mWT = MW)

    double mu = (MW*MW)/2 + PxNu*lep.Px() + PyNu*lep.Py();
    double a = (mu*lep.Pz())/(lep.E()*lep.E() -
				    lep.Pz()*lep.Pz());
    double a2 = TMath::Power(a,2);
    double b = (TMath::Power(lep.E(),2.)*(PxNu*PxNu+PyNu*PyNu) - TMath::Power(mu,2.))/
      (TMath::Power(lep.E(),2) - TMath::Power(lep.Pz(),2));

    if (a2-b >= 0) {
      //double root = sqrt(a2-b);
      //std::cout<<"a+sqrt(a2-b) = "<<(a+root)<<" a-sqrt(a2-b) = "<<(a-root)<<std::endl;
    }

    pz1 = a;
    pz2 = a;
    nsol = 1;
  }

  // smaller pz solution is written to entry 0
  if (fabs(pz1) <= fabs(pz2) ) {
    pz[0] = pz1;
    pz[1] = pz2;
  } else {
    pz[0] = pz2;
    pz[1] = pz1;
  }

  // change values of met in case of complex solution
  if (isComplex) {
    met->SetPx(PxNu);
    met->SetPy(PyNu);
  }


  return nsol;
}


