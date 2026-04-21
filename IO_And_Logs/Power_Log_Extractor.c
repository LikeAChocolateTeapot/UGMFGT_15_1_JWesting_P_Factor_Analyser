//
// Created by joewe on 20/04/2026.
//

#include "Power_Log_Extractor.h"

// Extract individual signals from a Power_Log sample

double extract_phaseA(const Power_Log *p)
{
    return p->phaseA;
}

double extract_phaseB(const Power_Log *p)
{
    return p->phaseB;
}

double extract_phaseC(const Power_Log *p)
{
    return p->phaseC;
}

double extract_current(const Power_Log *p)
{
    return p->lineCurrent;
}