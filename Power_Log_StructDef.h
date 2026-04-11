#ifndef POWER_LOG_STRUCTDEF_H
#define POWER_LOG_STRUCTDEF_H

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

#endif