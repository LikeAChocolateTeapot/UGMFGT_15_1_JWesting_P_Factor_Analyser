#include <math.h>
#include "Compute_RMS.h"
#include "Power_Log_Extractor.h"


/*
 * computes RMS (Root Mean Square)
 * basically energy of signal,,
 * uses  function pointer so we can reuse for diff signals
 */
double compute_rms(const Power_Log *logs, size_t count, extract_fn extractor)
{
    // quick safety checks (avoid segfaults / bad calls)
    if (!logs || count == 0 || !extractor)
        return 0.0;

    double sum_sq = 0.0; // running sum of squared values

    // loop through samples
    for (size_t i = 0; i < count; i++)
    {
        // extractor is function pointer:
        // it decides WHICH signal we are reading (phaseA, current, etc.)
        double value = extractor(&logs[i]);

        sum_sq += value * value; // square it and accumulate
    }

    // RMS = sqrt(mean of squares)
    return sqrt(sum_sq / (double)count);
}


/*
 * RMS percentage error vs nominal value
 * tells how far off measured RMS is
 */
double rms_percent_error(double rms, double nominal)
{
    // avoid divide-by-zero crash
    if (nominal == 0.0)
        return 0.0;

    return ((rms - nominal) / nominal) * 100.0;
}


/*
 * simple tolerance checker
 * returns 1 if within range, else 0
 */
int within_tolerance(double value, double nominal, double percent)
{
    // compute bounds around nominal
    double lower = nominal * (1.0 - percent / 100.0);
    double upper = nominal * (1.0 + percent / 100.0);

    // check if value sits inside acceptable band
    return (value >= lower && value <= upper);
}