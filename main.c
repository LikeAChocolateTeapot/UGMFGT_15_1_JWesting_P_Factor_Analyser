#include <stdio.h>
#include <stdlib.h>

#include "Power_Log_Extraction.h"
#include "Power_Log_StructDef.h"
#include "Compute_RMS.h"

#define NOMINAL_VOLTAGE 230.0

int main(void)
{
    const char *filepath =
        "C:/Users/joewe/OneDrive - UWE Bristol/Year 2.1/Programming for Engineers/"
        "Coursework - Power Factor Analyser/untitled/cmake-build-debug/power_quality_log.csv";

    // ---------- Open file ----------
    FILE *fp = fopen(filepath, "r");

    if (!fp) {
        printf("could not open file\n");
        return 1;
    }

    char line[512];

    // ---------- Count rows ----------
    fgets(line, sizeof(line), fp); // skip header

    int rowCount = 0;

    while (fgets(line, sizeof(line), fp)) {
        rowCount++;
    }

    fclose(fp);

    // ---------- Allocate memory ----------
    Power_Log *logs = malloc(rowCount * sizeof(Power_Log));

    if (!logs) {
        printf("memory allocation failed\n");
        return 1;
    }

    // ---------- Read data ----------
    fp = fopen(filepath, "r");

    if (!fp) {
        printf("could not reopen file\n");
        free(logs);
        return 1;
    }

    fgets(line, sizeof(line), fp); // skip header

    Power_Log *p = logs;

    while (fgets(line, sizeof(line), fp)) {

        parse_powerlog_line(line, p);

        p++;   // original pointer-style loop
    }

    fclose(fp);

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