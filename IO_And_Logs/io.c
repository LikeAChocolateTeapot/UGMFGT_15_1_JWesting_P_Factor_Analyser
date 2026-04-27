#include <stdio.h>   // Standrd input/output lib (FILE, fopen, fclose, fgets, printf, fprintf)
#include <stdlib.h>  // stdlib -> malloc, free, NULL etc
#include "io.h"      // custom header: defines structs like Power_Log, RMS_Result etc.


// ------------------------------------
// Opens file in read mode
// returns FILE pointter OR NULL if fail
// -----------------------------------------=
static FILE* open_file(const char *filepath) {

    // fopen returns pointer to FILE struct (stream obj handled by OS/runtime)
    FILE *fp = fopen(filepath, "r");  // "r" = read mode only

    // NULL means file didnt open (bad path / perms / missing file)
    if (!fp) {
        printf("could not open file\n"); // basic error msg (stderr would be better tbh)
    }

    return fp; // return pointer (caller must fclose later!!)
}


// ------------------------------------
// counts number of data rows in file
// assumes 1st line = header (skipped)
// ------------------------------------
static int count_rows(FILE *fp) {

    char line[512]; // temp buffer for each line (stack allocated)

    fgets(line, sizeof(line), fp); // skip header row (move file cursor forward)

    int count = 0; // row counter

    // fgets returns NULL when EOF reached
    while (fgets(line, sizeof(line), fp)) {
        count++; // increment for each valid row
    }

    return count; // total rows (excluding header)
}


// ------------------------------------
// allocates memory for Power_Log array (heap)
// returns pointer to first element OR NULL if fail
// ------------------------------------
static Power_Log* allocate_logs(int count) {

    // malloc reserves continuous block of memory for structs
    Power_Log *logs = malloc(count * sizeof(Power_Log));

    // NULL = allocation failed (no heap space left)
    if (!logs) {
        printf("memory allocation failed\n");
    }

    return logs; // pointer to first struct in array
}


// ------------------------------------
// parses single CSV line into struct
// uses pointer so we modify original memory directly
// ------------------------------------
static void parse_powerlog_line(char *line, Power_Log *p) {

    // CSV format:
    // timestamp,phaseA,phaseB,phaseC,lineCurrent,frequency,powerFactor,thd

    sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
           &p->timestamp,   // p is pointer -> use -> to access fields
           &p->phaseA,      // & gives address for sscanf to write into
           &p->phaseB,
           &p->phaseC,
           &p->lineCurrent,
           &p->frequency,
           &p->powerFactor,
           &p->thd);
}


// ------------------------------------
// reads file & fills allocated array
// assumes logs already malloc'd
// ------------------------------------
static void read_logs(FILE *fp, Power_Log *logs) {

    char line[512]; // buffer per row

    fgets(line, sizeof(line), fp); // skip header again

    Power_Log *p = logs; // pointer used to walk through array

    // loop until end of file
    while (fgets(line, sizeof(line), fp)) {

        parse_powerlog_line(line, p); // fill struct at current pointer pos

        p++; // move to next struct (pointer arithmetic: next block in heap)
    }
}


// ------------------------------------
// main loader function
// does:
// 1. open file
// 2. count rows
// 3. allocate mem
// 4. reopen file
// 5. parse data into memory
// ------------------------------------
Power_Log* load_power_log(const char *filepath, int *rowCount) {

    // -------- pass 1: count rows --------
    FILE *fp = open_file(filepath);

    if (!fp) return NULL; // fail fast if cant open

    int count = count_rows(fp); // consumes file stream

    fclose(fp); // IMPORTANT: release file handle

    // -------- allocate memory --------
    Power_Log *logs = allocate_logs(count);

    if (!logs) return NULL; // alloc fail safety

    // -------- pass 2: read data --------
    fp = open_file(filepath); // reopen file (cursor was used up earlier)

    if (!fp) {
        free(logs); // avoid mem leak
        return NULL;
    }

    read_logs(fp, logs); // fill array

    fclose(fp); // close file stream

    // output param -> write back to caller
    *rowCount = count; // dereference pointer to store value externally

    return logs; // return heap pointer (caller now owns it)
}

// ------------------------------------
// exports results to text file
// ------------------------------------
int export_results(
    const char *filename,
    RMS_Result rms,
    P2P_Result p2p,
    Offset_Result offset,
    Power_Log *logs,
    int rowCount,
    int A_ok,
    int B_ok,
    int C_ok
) {

    FILE *fp = fopen(filename, "w"); // write mode (overwrites file)

    if (!fp) {
        printf("Failed to open output file\n");
        return 0;
    }

    fprintf(fp, "=== Power Analysis Report ===\n\n");

    // -------- RMS section --------
    fprintf(fp, "--- RMS Values ---\n");
    fprintf(fp, "Phase A RMS: %f\n", rms.rms_phaseA);
    fprintf(fp, "Phase B RMS: %f\n", rms.rms_phaseB);
    fprintf(fp, "Phase C RMS: %f\n", rms.rms_phaseC);
    fprintf(fp, "Current RMS : %f\n\n", rms.rms_current);

    // -------- P2P section --------
    fprintf(fp, "--- Peak-to-Peak ---\n");
    fprintf(fp, "Phase A P2P: %f\n", p2p.p2p_phaseA);
    fprintf(fp, "Phase B P2P: %f\n", p2p.p2p_phaseB);
    fprintf(fp, "Phase C P2P: %f\n", p2p.p2p_phaseC);
    fprintf(fp, "Current P2P: %f\n\n", p2p.p2p_current);

    // -------- offset section --------
    fprintf(fp, "--- DC Offset ---\n");
    fprintf(fp, "Phase A Offset: %f\n", offset.dc_phaseA);
    fprintf(fp, "Phase B Offset: %f\n", offset.dc_phaseB);
    fprintf(fp, "Phase C Offset: %f\n", offset.dc_phaseC);
    fprintf(fp, "Current Offset: %f\n\n", offset.dc_current);

    // -------- clipping detect --------
    fprintf(fp, "--- Clip Detection ---\n");

    int clipped_count = 0; // local counter

    for (int i = 0; i < rowCount; i++) {

        // logs[i] == *(logs + i) pointer math hidden by array syntax
        if (logs[i].clip_flag)
            clipped_count++;
    }

    fprintf(fp, "Sensor limit: |V| >= 324.9 V\n\n");

    fprintf(fp,
        "Clip Detection Summary - %d entries at limit.\n\n",
        clipped_count
    );

    if (clipped_count == 0) {
        fprintf(fp, "No clipping detected.\n\n");
    } else {

        for (int i = 0; i < rowCount; i++) {
            if (logs[i].clip_flag) {

                fprintf(fp,
                    "t=%.3f s | Va=%.2f V | Vb=%.2f V | Vc=%.2f V\n",
                    logs[i].timestamp,
                    logs[i].phaseA,
                    logs[i].phaseB,
                    logs[i].phaseC
                );
            }
        }

        fprintf(fp, "\n");
    }

    // -------- tolerance check --------
    fprintf(fp, "--- Voltage Tolerance Check (±10%% of 230V) ---\n");

    double lower = 230.0 * 0.9;
    double upper = 230.0 * 1.1;

    fprintf(fp, "Range: %.1f V - %.1f V\n\n", lower, upper);

    fprintf(fp, "Phase A: %.2f V -> %s\n",
            rms.rms_phaseA,
            A_ok ? "OK (within tolerance)" : "OUT OF RANGE");

    fprintf(fp, "Phase B: %.2f V -> %s\n",
            rms.rms_phaseB,
            B_ok ? "OK (within tolerance)" : "OUT OF RANGE");

    fprintf(fp, "Phase C: %.2f V -> %s\n\n",
            rms.rms_phaseC,
            C_ok ? "OK (within tolerance)" : "OUT OF RANGE");

    // -------- end --------
    fprintf(fp, "=== End of Report ===\n");

    fclose(fp); // flush + close file

    printf("Results exported successfully.\n");

    return 1; // success
}
// ------------------------------------
// frees heap memory allocated for logs
// MUST match malloc in load_power_log
// ------------------------------------
void free_power_log(Power_Log *logs) {
    free(logs); // release heap block
}