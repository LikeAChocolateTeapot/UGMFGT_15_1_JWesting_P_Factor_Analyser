//
// Created by joewe on 20/04/2026.
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_IO_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_IO_H

typedef struct {
    double timestamp;
    double phaseA;
    double phaseB;
    double phaseC;
    double lineCurrent;
    double frequency;
    double powerFactor;
    double thd;
} Power_Log;

// Loads CSV into dynamically allocated array
// Returns pointer, and sets rowCount via pointer
Power_Log* load_power_log(const char *filepath, int *rowCount);

// helper to free
void free_power_log(Power_Log *logs);

#endif //UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_IO_H