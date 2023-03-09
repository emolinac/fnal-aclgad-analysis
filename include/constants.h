#ifndef CONSTANTS_H
#define CONSTANTS_H

// NAMES
// Note: At the moment, you should include the path in the name of the file!
const char * input_fnal_tree = "../input-files/converted_runs_66dB-att_6800mV.root";
const char * analysis_output = "../output-files/plots-analysis.root";
const char * noiserms_output = "../output-files/noiserms.root";

// NUMERICAL CONSTANTS FOR SNR
const int nEvents = 5000;

// Specify the start and end time of the base before the rising edge
const double t_base_init = -8.E-9;
const double t_base_end  = -6.E-9;

// Specify the start and end time of the peak of the signal
const double t_peak_init = -4.3E-9;
const double t_peak_end  = -3.8E-9;

// NUMERICAL CONSTANTS FOR TR2080
const int profile_Nbins = 15;

// Specify the start and end time of the signal
const double t_signal_init = -5E-9;
const double t_signal_end  = -4.2E-9;

// Specify the start and end time of the fit to the signal
// The fit should be performed only in the rising edge up to the peak
const double t_signalfit_init = -4.8E-9;
const double t_signalfit_end  = -4.2E-9;

// NUMERICAL CONSTANTS FOR NOISE RMS
const double v_high =  0.02;
const double v_low  = -0.02;

#endif /* CONSTANTS_H */
