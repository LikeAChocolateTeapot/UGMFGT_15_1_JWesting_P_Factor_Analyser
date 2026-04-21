#include <math.h>
#include "Compute_RMS.h"
#include "Power_Log_Extractor.h"

/*
 * Computes RMS (Root Mean Square) value from an array of Power_Log samples.
 * Uses a function pointer to extract the required signal component.
 */
double compute_rms(const Power_Log *logs, size_t count, extract_fn extractor)
{
    // Safety checks
    if (!logs || count == 0 || !extractor)
        return 0.0;

    double sum_sq = 0.0;

    // Accumulate squared values
    for (size_t i = 0; i < count; i++)
    {
        double value = extractor(&logs[i]);
        sum_sq += value * value;
    }

    return sqrt(sum_sq / (double)count);
}

/*
 * Computes RMS percentage error relative to a nominal value.
 */
double rms_percent_error(double rms, double nominal)
{
    if (nominal == 0.0)
        return 0.0;

    return ((rms - nominal) / nominal) * 100.0;
}