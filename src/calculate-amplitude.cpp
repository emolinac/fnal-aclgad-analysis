#include <iostream>
#include <cmath>
#include "TROOT.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TTree.h"
#include "constants.h"

int main(int argc , char* argv[])
{
    // Open the desired file
    TFile* fin = new TFile(input_fnal_tree,"READ");

    // Open the output file
    TFile* fout = new TFile(amplitude_output,"RECREATE");
    gROOT->cd();

    // Obtain the fnal tree
    TTree* tree = (TTree*) fin->Get("pulse");

    // Declare voltage histos
    TH1F* h_base = new TH1F("h_base","",100,-.2,.4);
    TH1F* h_peak = new TH1F("h_peak","",100,-.2,.4);

    // Fill the histos with the voltages of different time regions
    // Base region : just before rising edge
    tree->Project("h_base","channel[1]",Form("time>%E&&time<%E",t_base_init,t_base_end));
    
    // Peak region : peak of the pulse injected on the FNAL board
    tree->Project("h_peak","channel[1]",Form("time>%E&&time<%E",t_peak_init,t_peak_end));
    
    // Calculate the amplitude
    double base_mean = h_base->GetMean();
    double peak_mean = h_peak->GetMean();
    double amplitude = peak_mean - base_mean;

    // Calculate the amplitude error
    double base_mean_error = h_base->GetMeanError();
    double peak_mean_error = h_peak->GetMeanError();
    double amplitude_error = sqrt(peak_mean_error*peak_mean_error + base_mean_error*base_mean_error);

    // Save the histos
    fout->cd();
    h_base->Write();
    h_peak->Write();

    // Close files
    fin->Close();
    fout->Close();

    // Print the results
    std::cout<<"######################################################################################"<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"The amplitude of the pulse is "<<amplitude<<"+-"<<amplitude_error<<std::endl;
    std::cout<<"                                                                                      "<<std::endl;
    std::cout<<"######################################################################################"<<std::endl;

    return 0;
}
