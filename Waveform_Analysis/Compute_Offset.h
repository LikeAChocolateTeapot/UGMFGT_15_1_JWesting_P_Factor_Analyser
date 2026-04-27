//
// Created by joewe on 20/04/2026.
// (header for DC offset calc - basically mean value of signals)
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_OFFSET_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_OFFSET_H


#include "io.h"   // brings in Power_Log + Offset_Result structs


// ------------------------------------
// computes DC offset (average value)
// used to see if signal is biased away from 0
// ------------------------------------
Offset_Result compute_offset(const Power_Log *logs, int count);


#endif // UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_OFFSET_H