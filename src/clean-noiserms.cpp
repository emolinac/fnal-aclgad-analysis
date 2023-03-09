#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include "TROOT.h"
#include "constants.h"

int main(int argc, char* argv[])
{
    // Open the desired file
    TFile* fin = new TFile(input_fnal_tree,"READ");

    // Open the output file
    TFile* fout = new TFile(noiserms_output,"RECREATE");
    gROOT->cd();

    // Obtain the fnal tree
    TTree* tree = (TTree*) fin->Get("pulse");

    // Create voltage histo
    TH1F* h_base  = new TH1F("h_base","",100,v_low,v_high);
    TH1F* h_clean = new TH1F("h_clean","",100,v_low,v_high);

    // Fill the histo with the voltage of the base region and obtain deviation quantities
    tree->Project("h_base","channel[1]",Form("time>%E&&time<%E",t_base_init,t_base_end));
    double noiserms       = h_base->GetStdDev();
    double noiserms_error = h_base->GetStdDevError();

    // Fit the noise with a gaussian
    TF1* fit_func = new TF1("fit_func","gaus",v_low,v_high);
    h_base->Fit(fit_func,"RSQ");

    // Obtain the voltage cuts
    double sigma = fit_func->GetParameter(2);
    double mu    = fit_func->GetParameter(1);

    double vcut_neg = mu - 2*sigma;
    double vcut_pos = mu + 2*sigma;

    // Fill the histo with the voltage applying the cuts and obtain deviation quantities
    tree->Project("h_clean","channel[1]",Form("time>%E&&time<%E&&channel[1]>%f&&channel[1]<%f",t_base_init,t_base_end,vcut_neg,vcut_pos));
    double clean_noiserms       = h_clean->GetStdDev();
    double clean_noiserms_error = h_clean->GetStdDevError();
    
    std::cout<<"######################################################################################"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<" * NoiseRMS       = "<<noiserms*1000.<<"+-"<<noiserms_error*1000.<<"mV"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"######################################################################################"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<" * Clean NoiseRMS = "<<clean_noiserms*1000.<<"+-"<<clean_noiserms_error*1000.<<"mV"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"######################################################################################"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<" There was a "<<TMath::Abs(1.-clean_noiserms/noiserms)*100.<<" percent improvement of the noise RMS."<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"######################################################################################"<<std::endl;
    
    // Write and close the file
    fout->cd();
    h_base->Write("noiserms_fit");
    h_clean->Write("clean_noise");

    fout->Close();

    return 0;
}