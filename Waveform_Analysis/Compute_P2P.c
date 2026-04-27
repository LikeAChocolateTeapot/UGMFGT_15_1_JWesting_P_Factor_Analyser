//
// Created by joewe on 20/04/2026.
// (P2P calc - finds peak to peak range of signals)
//

#include "Compute_P2P.h"
#include <float.h>   // gives DBL_MAX / DBL_MIN constants
#include "io.h"
#include "Power_Log_Extractor.h"


// ------------------------------------
// calculates peak-to-peak values
// basically max - min for each signal
// ------------------------------------
P2P_Result compute_p2p(const Power_Log *logs, int count) {

    P2P_Result result; // struct not init'd explicitly here (could be improved)

    // initailise extremes (start from wrst posible bounds)
    double maxA = -DBL_MAX, minA = DBL_MAX;
    double maxB = -DBL_MAX, minB = DBL_MAX;
    double maxC = -DBL_MAX, minC = DBL_MAX;
    double maxI = -DBL_MAX, minI = DBL_MAX;

    // loop through dataset
    for (int i = 0; i < count; i++) {

        // grab valus (local copies, just for readability)
        double a = logs[i].phaseA;
        double b = logs[i].phaseB;
        double c = logs[i].phaseC;
        double iL = logs[i].lineCurrent;

        // ---- Phase A ----
        if (a > maxA) maxA = a;
        if (a < minA) minA = a;

        // -- Phase B ----
        if (b > maxB) maxB = b;
        if (b < minB) minB = b;

        // ---- Phase C ----
        if (c > maxC) maxC = c;
        if (c < minC) minC = c;

        // ---- currnt ----
        if (iL > maxI) maxI = iL;
        if (iL < minI) minI = iL;
    }

    // final step: pek-to-peak = max - min
    result.p2p_phaseA = maxA - minA;
    result.p2p_phaseB = maxB - minB;
    result.p2p_phaseC = maxC - minC;
    result.p2p_current = maxI - minI;

    return result; // struct copied back to caller
}