#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "Compute_RMS.h"
#include "Compute_P2P.h"
#include "Compute_Offset.h"
#include "Power_Log_Extractor.h"
#include "clip_detection.h"

#define NOMINAL_VOLTAGE 230.0   // reference mains voltage (UK nominal supply)


int main(void)
{
    // filepath to CSV dataset
    const char filepath[64];
    printf("Please enter Power Log .csv filepath...\n");
    scanf("%s", filepath);
    //printf("%s", filepath);
    //"../power_quality_log.csv";

    int rowCount = 0; // will be set by load function via pointer (output parameter)

    // ---------- LOAD DATA ----------
    // loads CSV into heap-allocated array of Power_Log structs
    // returns pointer to first element, rowCount updated via &rowCount
    Power_Log *logs = load_power_log(filepath, &rowCount);

    // safety check: if file failed or malloc failed -> logs == NULL
    if (!logs) {
        return 1; // exit early (nothing to process)
    }


    // ---------- RAW DATA PRINT (DEBUG BLOCK - currently disabled) ----------
    /*
        This section was used during development to verify parsing.
        q is a pointer walker through contiguous heap memory.

        IMPORTANT: logs[i] == *(logs + i)
        but here pointer arithmetic is used manually.
    */
    /*
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

        q++; // advances pointer by sizeof(Power_Log)
    }
    */


    // ---------- RMS CALCULATIONS ----------
    // compute_rms uses function pointers to select which signal to process
    // avoids rewriting RMS logic for every signal type

    double rmsA = compute_rms(logs, rowCount, extract_phaseA);
    double rmsB = compute_rms(logs, rowCount, extract_phaseB);
    double rmsC = compute_rms(logs, rowCount, extract_phaseC);
    double rmsI = compute_rms(logs, rowCount, extract_current);

    // package results into struct for cleaner passing between functions
    RMS_Result rms = {rmsA, rmsB, rmsC, rmsI};


    // ---------- PEAK TO PEAK ----------
    // computes max-min range per signal across full dataset
    P2P_Result p2p = compute_p2p(logs, rowCount);


    // ---------- DC OFFSET ----------
    // calculates mean value (bias) of waveform
    Offset_Result offset = compute_offset(logs, rowCount);


    // ---------- CLIPPING DETECTION ----------
    // scans dataset and sets clip_flag inside each struct
    // modifies array in-place (important: logs is passed by pointer)
    apply_clipping_flags(logs, rowCount);


    // ---------- TOLERANCE CHECK ----------
    // checks if RMS values are within ±10% of nominal supply
    int A_ok = within_tolerance(rmsA, NOMINAL_VOLTAGE, 10.0);
    int B_ok = within_tolerance(rmsB, NOMINAL_VOLTAGE, 10.0);
    int C_ok = within_tolerance(rmsC, NOMINAL_VOLTAGE, 10.0);


    // ---------- OUTPUT REPORT GENERATION ----------
    // writes structured report to text file
    // includes RMS, P2P, offset, clipping summary, tolerance checks
    export_results(
        "Power_Log_Results.txt",
        rms,
        p2p,
        offset,
        logs,
        rowCount,
        A_ok,
        B_ok,
        C_ok
    );

    // convenience step: open report automatically
    // system() executes shell command
    system("notepad Power_Log_Results.txt");


    /*
    ---------- OLD DEBUG OUTPUT ----------

    This was originally used before export_results() existed.
    Kept for reference / validation of calculations.

    printf("\n=== RMS SUMMARY ===\n");

    printf("Phase A RMS: %.2f V (%.4f%%)\n",
           rmsA, rms_percent_error(rmsA, NOMINAL_VOLTAGE));

    printf("Phase B RMS: %.2f V (%.4f%%)\n",
           rmsB, rms_percent_error(rmsB, NOMINAL_VOLTAGE));

    printf("Phase C RMS: %.2f V (%.4f%%)\n\n",
           rmsC, rms_percent_error(rmsC, NOMINAL_VOLTAGE));


    printf("\n=== PEAK TO PEAK SUMMARY ===\n");
    printf("P2P Phase A: %f V\n", p2p.p2p_phaseA);
    printf("P2P Phase B: %f V\n", p2p.p2p_phaseB);
    printf("P2P Phase C: %f V\n", p2p.p2p_phaseC);
    printf("P2P Current : %f A\n", p2p.p2p_current);

    printf("\n=== DC OFFSET SUMMARY ===\n");
    printf("DC A: %f\n", offset.dc_phaseA);
    printf("DC B: %f\n", offset.dc_phaseB);
    printf("DC C: %f\n", offset.dc_phaseC);
    printf("DC I: %f\n", offset.dc_current);
    */


    // ---------- CLEANUP ----------
    // frees heap memory allocated inside load_power_log()
    // IMPORTANT: prevents memory leak (malloc without free = leak)
    free(logs);

    return 0; // successful execution
}