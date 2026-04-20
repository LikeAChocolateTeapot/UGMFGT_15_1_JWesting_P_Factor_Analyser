#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "Compute_RMS.h"

#define NOMINAL_VOLTAGE 230.0

int main(void)
{
       const char *filepath =
          "C:/Users/joewe/OneDrive - UWE Bristol/Year 2.1/Programming for Engineers/"
          "Coursework - Power Factor Analyser/untitled/cmake-build-debug/power_quality_log.csv";

       int rowCount = 0;

       // Load data from CSV
       Power_Log *logs = load_power_log(filepath, &rowCount);

       // Check if loading failed
       if (!logs) {
              return 1;
       }

    // ---------- Print raw data ----------
    Power_Log *q = logs;

    for (int i = 0; i < rowCount; i++) {
        printf("%f, %f, %f, %f, %f, %f, %f, %f\n",
               q->timestamp,
               q->phaseA,
               q->phaseB,
               q->phaseC,
               q->lineCurrent,
               q->frequency,
               q->powerFactor,
               q->thd);

        q++;
    }

    // ---------- RMS calculations ----------
    double rmsA = compute_rms(logs, rowCount, get_phaseA);
    double rmsB = compute_rms(logs, rowCount, get_phaseB);
    double rmsC = compute_rms(logs, rowCount, get_phaseC);

    // ---------- Output ----------
    printf("\n=== RMS SUMMARY ===\n");

    printf("Phase A RMS: %.2f V (%.4f%%)\n",
           rmsA, rms_percent_error(rmsA, NOMINAL_VOLTAGE));

    printf("Phase B RMS: %.2f V (%.4f%%)\n",
           rmsB, rms_percent_error(rmsB, NOMINAL_VOLTAGE));

    printf("Phase C RMS: %.2f V (%.4f%%)\n",
           rmsC, rms_percent_error(rmsC, NOMINAL_VOLTAGE));

    // ---------- Cleanup ----------
    free(logs);

    return 0;
}