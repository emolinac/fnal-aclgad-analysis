#include <iostream>
#include <cmath>
#include "TROOT.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TTree.h"
#include "TProfile.h"
#include "constants.h"

int main(int argc, char* argv[])
{
    // Open the desired file
    TFile* fin = new TFile(input_fnal_tree,"READ");

    // Open the output file
    TFile* fout = new TFile(analysis_output,"RECREATE");
    gROOT->cd();

    // Obtain the fnal tree
    TTree* tree = (TTree*) fin->Get("pulse");

    // Create the TProfile
    TProfile* prof = new TProfile("prof","",profile_Nbins,t_signal_init,t_signal_end);

    // Create voltage histos
    TH1F* h_base = new TH1F("h_base","",100,-.2,.4);
    TH1F* h_peak = new TH1F("h_peak","",100,-.2,.4);

    // Fill the TProfile with the data of the pulse
    tree->Project("prof","channel[1]:time");

    // Fill the histos with the voltages of different time regions
    // Base region : just before rising edge
    tree->Project("h_base","channel[1]",Form("time>%E&&time<%E",t_base_init,t_base_end));
    
    // Peak region : peak of the pulse injected on the FNAL board
    tree->Project("h_peak","channel[1]",Form("time>%E&&time<%E",t_peak_init,t_peak_end));

    // Fit the TProfile with a landau
    TF1* fit_func = new TF1("fit_func","landau",t_signalfit_init,t_signalfit_end);
    prof->Fit(fit_func,"RSQ");
    
    // Calculate the amplitude
    double base_mean = h_base->GetMean();
    double peak_mean = h_peak->GetMean();
    double amplitude = peak_mean - base_mean;

    // Calculate the amplitude error
    double base_mean_error = h_base->GetMeanError();
    double peak_mean_error = h_peak->GetMeanError();
    double amplitude_error = sqrt(peak_mean_error*peak_mean_error + base_mean_error*base_mean_error);

    // Calculate the noise rms
    double noiserms       = h_base->GetStdDev();
    double noiserms_error = h_base->GetStdDevError();

    // Obtain the rise time from the fit
    double t0 = fit_func->GetX(base_mean + 0.2*amplitude,t_signalfit_init - 1.E-9,t_signalfit_end);
    double t1 = fit_func->GetX(base_mean + 0.8*amplitude,t_signalfit_init - 1.E-9,t_signalfit_end);
    
    double tr2080 = TMath::Abs(t1-t0);

    // NOTE : V will be converted to mV. s will be converted to ps.
    // Print the results
    std::cout<<"######################################################################################"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<" * Amp = "<<amplitude*1000.<<"+-"<<amplitude_error*1000.<<"mV"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"######################################################################################"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<" * NoiseRMS = "<<noiserms*1000.<<"+-"<<noiserms_error*1000.<<"mV"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"######################################################################################"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<" * SNR = "<<amplitude/noiserms<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"######################################################################################"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<" * tr2080 = "<<tr2080*pow(10,12)<<"ps"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"######################################################################################"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<" * tr/SNR = "<<tr2080*pow(10,12)/(amplitude/noiserms)<<"ps"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"######################################################################################"<<std::endl;

    // Write and close the file
    fout->cd();

    prof->Write("signal_fit");
    h_base->Write();
    h_peak->Write();

    fout->Close();

    return 0;
}