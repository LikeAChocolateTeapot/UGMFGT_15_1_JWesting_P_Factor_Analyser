//
// Created by joewe on 09/

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTION_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTION_H

#include "Power_Log_StructDef.h"   // include the struct definition for Power_Log

// parse one CSV line into a Power_Log struct
static inline int parse_powerlog_line(const char *line, Power_Log *out)
{
    // use sscanf to extract 8 comma‑separated values
    return sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                  &out->timestamp,
                  &out->phaseA,
                  &out->phaseB,
                  &out->phaseC,
                  &out->lineCurrent,
                  &out->frequency,
                  &out->powerFactor,
                  &out->thd) == 8;
}

#endif //UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTION_H