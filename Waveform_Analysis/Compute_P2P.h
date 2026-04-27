//
// Created by joewe on 20/04/2026.
// (header for peak-to-peak calculation module)
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_P2P_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_P2P_H


#include "io.h"   // needed for Power_Log+ P2P_Result structs


// ------------------------------------
// computes peak-to-peak values
// (max - min across hole dataset)
// ------------------------------------
P2P_Result compute_p2p(const Power_Log *logs, int count);


#endif // UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_P2P_H