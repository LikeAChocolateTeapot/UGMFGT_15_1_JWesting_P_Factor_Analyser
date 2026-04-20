//
// Created by joewe on 20/04/2026.
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_OFFSET_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_OFFSET_H

#include "io.h"

// DC offset (mean value) per signal
typedef struct {
    double dc_phaseA;
    double dc_phaseB;
    double dc_phaseC;
    double dc_current;
} Offset_Result;

// Compute mean / DC offset
Offset_Result compute_offset(const Power_Log *logs, int count);

#endif //UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_COMPUTE_OFFSET_H