#include <stdio.h>
#include "Power_Log_Extraction.h"
#include "Power_Log_StructDef.h"

int main(void) {
    // open the CSV file
    FILE *fp = fopen("C:/Users/joewe/OneDrive - UWE Bristol/Year 2.1/Programming for Engineers/Coursework - Power Factor Analyser/untitled/cmake-build-debug/power_quality_log.csv", "r");

    // error logging for open failure
    if (!fp) {
        printf("could not open file\n");
        return 1;
    }

    // buffer for reading lines
    char line[512];

    // skip the header row
    fgets(line, sizeof(line), fp);

    // struct to hold parsed data
    Power_Log row;

    // read each remaining line
    while (fgets(line, sizeof(line), fp)) {

        // parse the CSV line into the struct
        if (parse_powerlog_line(line, &row)) {

            // print all fields in the struct
            printf("%f, %f, %f, %f, %f, %f, %f, %f\n",
        row.timestamp,
        row.phaseA,
        row.phaseB,
        row.phaseC,
        row.lineCurrent,
        row.frequency,
        row.powerFactor,
        row.thd);
        }
    }

    // close the file
    fclose(fp);
    return 0;
}
