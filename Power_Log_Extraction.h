//
// Created by joewe on 09/04/2026.
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTION_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTION_H

typedef struct {
    double timestamp;
    double phaseA;
    double phaseB;
    double phaseC;
    double lineCurrent;
    double frequency;
    double powerFactor;
    double thd;
} Power_Log;

#endif //UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTION_H