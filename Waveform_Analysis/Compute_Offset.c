#include "stdio.h"
#include "Compute_Offset.h"
#include "io.h"
#include "Power_Log_Extractor.h"


// ------------------------------------
// computes DC offset for signals
// basically just average value over dataset
// ------------------------------------
Offset_Result compute_offset(const Power_Log *logs, int count) {

    Offset_Result result = {0}; // init all fields to 0 (safe start state)

    // running sums (used to calc mean later)
    double sumA = 0.0;
    double sumB = 0.0;
    double sumC = 0.0;
    double sumI = 0.0;

    // loop through all samples in array
    for (int i = 0; i < count; i++) {

        // logs[i] == *(logs + i) just hidden pointer math

        sumA += logs[i].phaseA;
        // printf("sumA: %f\n", sumA); // debug linew

        sumB += logs[i].phaseB;
        // printf("sumB: %f\n", sumB);

        sumC += logs[i].phaseC;
        // printf("sumC: %f\n", sumC);

        sumI += logs[i].lineCurrent;
        // printf("sumI: %f\n", sumI);
    }

    // average = sum / N samples
    // this gives DC offset estimate (mean bias of signal)
    result.dc_phaseA = sumA / count;
    result.dc_phaseB = sumB / count;
    result.dc_phaseC = sumC / count;
    result.dc_current = sumI / count;

    return result; // return struct by value (copy out)
}