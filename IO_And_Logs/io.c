#include <stdio.h>
#include <stdlib.h>
#include "io.h"
// Opens a file in read mode
// Returns FILE pointer, or NULL if opening fails
static FILE* open_file(const char *filepath) {
    FILE *fp = fopen(filepath, "r");

    if (!fp) {
        printf("could not open file\n");
    }

    return fp;
}

// Counts number of data rows in the file
// Assumes first line is a header and skips it
static int count_rows(FILE *fp) {
    char line[512];

    fgets(line, sizeof(line), fp); // skip header row

    int count = 0;

    // Count remaining lines
    while (fgets(line, sizeof(line), fp)) {
        count++;
    }

    return count;
}

// Allocates memory for Power_Log array
// Returns pointer to allocated memory or NULL on failure
static Power_Log* allocate_logs(int count) {
    Power_Log *logs = malloc(count * sizeof(Power_Log));

    if (!logs) {
        printf("memory allocation failed\n");
    }

    return logs;
}

// Parses one CSV line into a Power_Log struct
static void parse_powerlog_line(char *line, Power_Log *p) {

    // CSV format: timestamp,phaseA,phaseB,phaseC,lineCurrent,frequency,powerFactor,thd

    sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
           &p->timestamp,
           &p->phaseA,
           &p->phaseB,
           &p->phaseC,
           &p->lineCurrent,
           &p->frequency,
           &p->powerFactor,
           &p->thd);
}

// Reads CSV data and fills Power_Log array
// Assumes memory is already allocated
static void read_logs(FILE *fp, Power_Log *logs) {
    char line[512];

    fgets(line, sizeof(line), fp); // skip header row

    Power_Log *p = logs;

    // Parse each line into struct
    while (fgets(line, sizeof(line), fp)) {
        parse_powerlog_line(line, p);
        p++; // move to next struct
    }
}

// Main function to load CSV data into memory
// Does file opening, counting, allocation, and reading
Power_Log* load_power_log(const char *filepath, int *rowCount) {

    // First pass: open file and count rows
    FILE *fp = open_file(filepath);
    if (!fp) return NULL;

    int count = count_rows(fp);
    fclose(fp);

    // Allocate memory for all rows
    Power_Log *logs = allocate_logs(count);
    if (!logs) return NULL;

    // Second pass: reopen file and read data
    fp = open_file(filepath);
    if (!fp) {
        free(logs); // avoid memory leak
        return NULL;
    }

    read_logs(fp, logs);
    fclose(fp);

    // Output the number of rows to caller
    *rowCount = count;

    return logs;
}

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
    FILE *fp = fopen(filename, "w");

    if (!fp) {
        printf("Failed to open output file\n");
        return 0;
    }

    fprintf(fp, "=== Power Analysis Report ===\n\n");

    /* ---------------- RMS ---------------- */
    fprintf(fp, "--- RMS Values ---\n");
    fprintf(fp, "Phase A RMS: %f\n", rms.rms_phaseA);
    fprintf(fp, "Phase B RMS: %f\n", rms.rms_phaseB);
    fprintf(fp, "Phase C RMS: %f\n", rms.rms_phaseC);
    fprintf(fp, "Current RMS : %f\n\n", rms.rms_current);

    /* ---------------- P2P ---------------- */
    fprintf(fp, "--- Peak-to-Peak ---\n");
    fprintf(fp, "Phase A P2P: %f\n", p2p.p2p_phaseA);
    fprintf(fp, "Phase B P2P: %f\n", p2p.p2p_phaseB);
    fprintf(fp, "Phase C P2P: %f\n", p2p.p2p_phaseC);
    fprintf(fp, "Current P2P: %f\n\n", p2p.p2p_current);

    /* ---------------- OFFSET ---------------- */
    fprintf(fp, "--- DC Offset ---\n");
    fprintf(fp, "Phase A Offset: %f\n", offset.dc_phaseA);
    fprintf(fp, "Phase B Offset: %f\n", offset.dc_phaseB);
    fprintf(fp, "Phase C Offset: %f\n", offset.dc_phaseC);
    fprintf(fp, "Current Offset: %f\n\n", offset.dc_current);

    /* ---------------- CLIPPING ---------------- */
    fprintf(fp, "--- Clip Detection ---\n");

    int clipped_count = 0;

    for (int i = 0; i < rowCount; i++)
    {
        if (logs[i].clip_flag)
            clipped_count++;
    }

    fprintf(fp, "Sensor limit: |V| >= 324.9 V\n\n");
    fprintf(fp,
        "Clip Detection Summary - %d entries at sensor limit.\n\n",
        clipped_count
    );

    if (clipped_count == 0)
    {
        fprintf(fp, "No clipping detected.\n\n");
    }
    else
    {
        for (int i = 0; i < rowCount; i++)
        {
            if (logs[i].clip_flag)
            {
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

    /* ---------------- TOLERANCE ---------------- */
    fprintf(fp, "--- Voltage Tolerance Check (±10%% of 230V) ---\n");

    double lower = 230.0 * 0.9;
    double upper = 230.0 * 1.1;

    fprintf(fp, "Acceptable Range: %.1f V - %.1f V\n\n", lower, upper);

    fprintf(fp, "Phase A: %.2f V -> %s\n",
            rms.rms_phaseA,
            A_ok ? "OK (within tolerance)" : "OUT OF RANGE");

    fprintf(fp, "Phase B: %.2f V -> %s\n",
            rms.rms_phaseB,
            B_ok ? "OK (within tolerance)" : "OUT OF RANGE");

    fprintf(fp, "Phase C: %.2f V -> %s\n\n",
            rms.rms_phaseC,
            C_ok ? "OK (within tolerance)" : "OUT OF RANGE");

    /* ---------------- END ---------------- */
    fprintf(fp, "=== End of Report ===\n");

    fclose(fp);

    printf("Results exported successfully.\n");

    return 1;
}

// Frees allocated Power_Log array
void free_power_log(Power_Log *logs) {
    free(logs);
}