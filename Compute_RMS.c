#include <stdio.h>
#include "Compute_RMS.h"
#include <math.h>

// Computes RMS (Root Mean Square) value from an array of Power_Log samples.
double compute_rms(const Power_Log *logs, size_t count, extract_fn extractor)
{
    // Validate inputs to prevent crashes or invalid calculations
    if (!logs || count == 0 || !extractor)
        return 0.0;

    double sum_sq = 0.0;

    // Loop through all samples in the dataset
    for (size_t i = 0; i < count; i++) {

        // Extract the desired value from the struct
        double v = extractor(&logs[i]);

        // Square the value and accumulate
        sum_sq += v * v;
    }

    // Divide by number of samples and take square root to get RMS
    return sqrt(sum_sq / count);
}

double get_phaseA(const Power_Log *entry) {
    printf("A called\n");
    return entry->phaseA;
}
double get_phaseB(const Power_Log *entry) {
    printf("B called\n");
    return entry->phaseB;
}
double get_phaseC(const Power_Log *entry) {
    printf("C called\n");
    return entry->phaseC;
}

double rms_percent_error(double rms, double nominal)
{
    if (nominal == 0.0) return 0.0;

    return ((rms - nominal) / nominal) * 100.0;
}