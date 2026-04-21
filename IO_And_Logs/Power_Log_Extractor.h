//
// Created by joewe on 20/04/2026.
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTOR_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTOR_H

#include "io.h"

// Signal extraction helpers
double extract_phaseA(const Power_Log *p);
double extract_phaseB(const Power_Log *p);
double extract_phaseC(const Power_Log *p);
double extract_current(const Power_Log *p);

#endif //UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTOR_H