#ifndef COMPUTE_RMS_H
#define COMPUTE_RMS_H


#include <stddef.h>   // size_t definition (for array sizes, indexing etc.
#include "io.h"       // brings in Power_Log strct def


// ------------------------------------
// function pointer type
// used so we can "plug in" different signal extractors
// (phaseA, phaseB, current, etc.)
// ------------------------------------
typedef double (*extract_fn)(const Power_Log *entry);


// ------------------------------------
// RMS callculation function
// uses function pointer to select signal dynamically
// ------------------------------------
double compute_rms(const Power_Log *logs, size_t count, extract_fn extractor);


// ------------------------------------
// compares RMS against nominal value
// returns percentage error (+/-)
// ------------------------------------
double rms_percent_error(double rms, double nominal);


#endif