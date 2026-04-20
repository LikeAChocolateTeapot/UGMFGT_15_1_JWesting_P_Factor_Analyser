//
// Created by joewe on 20/04/2026.
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_P2P_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_P2P_H

#include "io.h"

// Computes peak-to-peak values for each phase
// Uses array of Power_Log samples
typedef struct {
    double p2p_phaseA;
    double p2p_phaseB;
    double p2p_phaseC;
    double p2p_current;
} P2P_Result;

// Main function
P2P_Result compute_p2p(const Power_Log *logs, int count);

#endif //UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_P2P_H