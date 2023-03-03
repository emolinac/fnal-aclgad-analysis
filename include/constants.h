#ifndef CONSTANTS_H
#define CONSTANTS_H

// NAMES
// Note: At the moment, you should include the path in the name of the file!
const char * input_fnal_tree      = "../input-files/converted_runs_46dB-att_6800mV.root";
const char * signaltonoise_output = "../output-files/signaltonoise.root";

// NUMERICAL CONSTANTS
const int nEvents = 5000;

const double t_base_init = -8.E-9;
const double t_base_end  = -6.E-9;

const double t_peak_init = -4.5E-9;
const double t_peak_end  = -4.0E-9;

#endif /* CONSTANTS_H */
