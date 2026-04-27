//
// Created by joewe on 20/04/2026.
// (header for Power_Log signal extraction helpers)
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTOR_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTOR_H


#include "io.h"   // brings in Power_Log struct + related defs


// ------------------------------------
// simple helper funcs to grab signals
// from a Power_Log struct pointer
// (just makes main code cleaner tbh)
// ------------------------------------


// extract phase A voltage
double extract_phaseA(const Power_Log *p);

// extract phase B voltage
double extract_phaseB(const Power_Log *p);

// extract phase C voltage
double extract_phaseC(const Power_Log *p);

// extract line current value
double extract_current(const Power_Log *p);


#endif // UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTOR_H