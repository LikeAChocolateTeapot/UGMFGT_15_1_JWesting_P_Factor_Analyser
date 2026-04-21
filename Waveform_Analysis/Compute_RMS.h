#ifndef COMPUTE_RMS_H
#define COMPUTE_RMS_H

#include <stddef.h>
#include "io.h"

// Function pointer type for selecting signal component
typedef double (*extract_fn)(const Power_Log *entry);

// RMS computation
double compute_rms(const Power_Log *logs, size_t count, extract_fn extractor);

// RMS error vs nominal value
double rms_percent_error(double rms, double nominal);

#endif