//
// Created by joewe on 20/04/2026.
//

#include "Compute_P2P.h"
#include <float.h>   // for DBL_MAX / DBL_MIN
#include "io.h"
#include "Power_Log_Extractor.h"

P2P_Result compute_p2p(const Power_Log *logs, int count) {

    P2P_Result result;

    // Initialise min/max properly
    double maxA = -DBL_MAX, minA = DBL_MAX;
    double maxB = -DBL_MAX, minB = DBL_MAX;
    double maxC = -DBL_MAX, minC = DBL_MAX;
    double maxI = -DBL_MAX, minI = DBL_MAX;

    // Loop through all samples
    for (int i = 0; i < count; i++) {

        double a = logs[i].phaseA;
        double b = logs[i].phaseB;
        double c = logs[i].phaseC;
        double iL = logs[i].lineCurrent;

        // Phase A
        if (a > maxA) maxA = a;
        if (a < minA) minA = a;

        // Phase B
        if (b > maxB) maxB = b;
        if (b < minB) minB = b;

        // Phase C
        if (c > maxC) maxC = c;
        if (c < minC) minC = c;

        // Current
        if (iL > maxI) maxI = iL;
        if (iL < minI) minI = iL;
    }

    // Peak-to-peak = max - min
    result.p2p_phaseA = maxA - minA;
    result.p2p_phaseB = maxB - minB;
    result.p2p_phaseC = maxC - minC;
    result.p2p_current = maxI - minI;

    return result;
}