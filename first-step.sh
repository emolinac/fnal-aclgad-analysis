#!/bin/bash

echo "____________________________________________________________________________________________________________________"
echo "   "
echo "   "
echo "This script executes root and shows you a 2D histogram with the shape of the signal to analyze."
echo "Copy the following command once root has opened:"
echo "pulse->Draw("channel[1]:time","","colz")"
echo "   "
echo "   "
echo "Check the histogram and by eye write the down the following quantities and the put them in the constants.h file:"
echo " * Start and end time of the base before the rising edge"
echo " * Start and end time of the peak of the signal"
echo " * Start and end time of the signal, i.e., width of the signal"
echo "   "
echo "   "
echo "NOTE : If there was to much interference in the measurements you will see the histogram with a lot of blue bins."
echo "       If that is the case guide yourself wih the yellow trace. "
echo "   "
echo "   "
echo "____________________________________________________________________________________________________________________"

root -l input-files/converted_runs_40dB-att_6800mV.root