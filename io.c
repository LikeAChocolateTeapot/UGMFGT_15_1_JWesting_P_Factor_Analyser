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
// Combines file opening, counting, allocation, and reading
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

// Frees allocated Power_Log array
void free_power_log(Power_Log *logs) {
    free(logs);
}