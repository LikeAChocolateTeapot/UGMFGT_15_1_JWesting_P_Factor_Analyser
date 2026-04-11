#include <stdio.h>
#include <stdlib.h>
#include "Power_Log_Extraction.h"
#include "Power_Log_StructDef.h"

int main(void) {

    // ---------- Count data rows in csv file -----------------------------------

    // open the file to count rows
    FILE *fp = fopen("C:/Users/joewe/OneDrive - UWE Bristol/Year 2.1/Programming for Engineers/Coursework - Power Factor Analyser/untitled/cmake-build-debug/power_quality_log.csv", "r");

    // check if the file opened correctly
    if (!fp) {
        printf("could not open file\n");
        return 1;
    }

    char line[512];

    // skip the header
    fgets(line, sizeof(line), fp);

    int rowCount = 0;

    // count each data row
    while (fgets(line, sizeof(line), fp)) {
        rowCount++;
    }

    // close the file after counting
    fclose(fp);

    // ---------- Allocate Memory ------------------------------------------------

    // allocate an array of Power_Log structs
    Power_Log *logs = malloc(rowCount * sizeof(Power_Log));

    // check if malloc failed
    if (!logs) {
        printf("memory allocation failed\n");
        return 1;
    }

    // ---------- Extract data using pointer arithmetic --------------------------

    // reopen the file to read data
    fp = fopen("C:/Users/joewe/OneDrive - UWE Bristol/Year 2.1/Programming for Engineers/Coursework - Power Factor Analyser/untitled/cmake-build-debug/power_quality_log.csv", "r");

    // skip the header again
    fgets(line, sizeof(line), fp);

    // point to the first struct in the array
    Power_Log *p = logs;

    // read each row into the array
    while (fgets(line, sizeof(line), fp)) {

        // parse the line into the struct pointed to by p
        if (parse_powerlog_line(line, p)) {

            // move the pointer to the next struct
            p++;
        }
    }

    fclose(fp);

    // ---------- Print data using pointer arithmetic ---------------------------


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

        q++;   // moving to the next struct
    }

    // ---------- Free memory ----------------------------------------------------

    free(logs);

    return 0;
}

