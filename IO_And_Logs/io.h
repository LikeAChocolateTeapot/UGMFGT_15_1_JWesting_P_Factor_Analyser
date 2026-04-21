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

typedef struct {
    double rms_phaseA;
    double rms_phaseB;
    double rms_phaseC;
    double rms_current;
} RMS_Result;

typedef struct {
    double p2p_phaseA;
    double p2p_phaseB;
    double p2p_phaseC;
    double p2p_current;
} P2P_Result;

typedef struct {
    double dc_phaseA;
    double dc_phaseB;
    double dc_phaseC;
    double dc_current;
} Offset_Result;

// Loads CSV into dynamically allocated array
// Returns pointer, and sets rowCount via pointer
Power_Log* load_power_log(const char *filepath, int *rowCount);

// helper to free
void free_power_log(Power_Log *logs);

// NEW: export results report
int export_results(
    const char *filename,
    RMS_Result rms,
    P2P_Result p2p,
    Offset_Result offset
);

#endif //UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_IO_H