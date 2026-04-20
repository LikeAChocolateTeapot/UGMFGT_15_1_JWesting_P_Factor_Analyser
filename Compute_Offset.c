#include "stdio.h"
#include "Compute_Offset.h"

Offset_Result compute_offset(const Power_Log *logs, int count) {

    Offset_Result result = {0};

    double sumA = 0.0;
    double sumB = 0.0;
    double sumC = 0.0;
    double sumI = 0.0;

    for (int i = 0; i < count; i++) {
        sumA += logs[i].phaseA; //printf("sumA: %f\n", sumA);
        sumB += logs[i].phaseB; //printf("sumB: %f\n", sumB);
        sumC += logs[i].phaseC; //printf("sumC: %f\n", sumC);
        sumI += logs[i].lineCurrent; //printf("sumI: %f\n", sumI);
    }

    result.dc_phaseA = sumA / count;
    result.dc_phaseB = sumB / count;
    result.dc_phaseC = sumC / count;
    result.dc_current = sumI / count;

    return result;
}