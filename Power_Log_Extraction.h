//
// Created by joewe on 09/04/2026.
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTION_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTION_H

#include "Power_Log_StructDef.h"

int parse_powerlog_line(const char *line, Power_Log *out);

#endif //UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_POWER_LOG_EXTRACTION_H