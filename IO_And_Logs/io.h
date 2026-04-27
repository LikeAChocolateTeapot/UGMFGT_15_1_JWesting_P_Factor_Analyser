//
// Created by joewe on 20/04/2026.
// (io.h - header for file IO + data structs)
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_IO_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_IO_H


// ------------------------------------
// main data struct for each CSV row
// basically 1 sample per of power system data
// ------------------------------------
typedef struct {

    double timestamp;     // time stamp from logger (seconds probably)

    double phaseA;        // voltage of phase A
    double phaseB;        // voltage phase B
    double phaseC;        // voltage phase C

    double lineCurrent;   // current reading (line current)

    double frequency;     // system freq (should be ~50Hz in UK)

    double powerFactor;   // PF value (0-1 usually but sometimes messy data)

    double thd;           // total harmonic distortion %

    int clip_flag;        // 0 = normal, 1 = clipping detected
                          // (sensor hitting limit basically)

} Power_Log;



// ------------------------------------
// RMS results (root mean square values)
// used for voltage/current magnitude calc
// ------------------------------------
typedef struct {

    double rms_phaseA;
    double rms_phaseB;
    double rms_phaseC;

    double rms_current;

} RMS_Result;



// ------------------------------------
// peak-to-peak values
// max - min basically
// ------------------------------------
typedef struct {

    double p2p_phaseA;
    double p2p_phaseB;
    double p2p_phaseC;

    double p2p_current;

} P2P_Result;



// ------------------------------------
// DC offset values
// shows signal bias away from zero
// ------------------------------------
typedef struct {

    double dc_phaseA;
    double dc_phaseB;
    double dc_phaseC;

    double dc_current;

} Offset_Result;

// ------------------------------
// loads CSV into heap array
// returns pointer to array (MUST free later)
// rowCount is output param (pointer used to return value)
// ------------------------------------
Power_Log* load_power_log(const char *filepath, int *rowCount);

// frees allocated memory for logs
// important or you'll leak heap memory
void free_power_log(Power_Log *logs);

// ------------------------
// exports full report to text file
// returns 1 if ok, 0 if fail
// (bit messy function but works)
// -----------------------------------------
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
);


#endif // UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_IO_H