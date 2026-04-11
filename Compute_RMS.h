#ifndef COMPUTE_RMS_H
#define COMPUTE_RMS_H

#include <stddef.h>
#include "power_log_structdef.h"

// Function pointer type
typedef double (*extract_fn)(const Power_Log *entry);

// RMS computation
double compute_rms(const Power_Log *logs, size_t count, extract_fn extractor);

// Extractors
double get_phaseA(const Power_Log *entry);
double get_phaseB(const Power_Log *entry);
double get_phaseC(const Power_Log *entry);

double rms_percent_error(double rms, double nominal);

#endif