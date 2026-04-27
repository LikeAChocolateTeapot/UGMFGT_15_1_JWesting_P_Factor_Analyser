//
// Created by joewe on 20/04/2026.
// (Power_Log extractor stuff - just small helper funcs really)
//

#include "Power_Log_Extractor.h"


// ------------------------------------
// these functions just pull out values
// from a Power_Log struct pointer
// nothing fancy, just readability helpers
// ------------------------------------


// get phase A voltage from sample
double extract_phaseA(const Power_Log *p)
{
    // p is pointer -> so we use -> to access struct member
    // basically "go to this memory address and grab phaseA"
    return p->phaseA;
}


// get phase B voltage
double extract_phaseB(const Power_Log *p)
{
    // same idea as above, just different field
    return p->phaseB;
}


// get phase C voltage
double extract_phaseC(const Power_Log *p)
{
    // again just reading struct data via pointer
    return p->phaseC;
}


// get current reading (line current)
double extract_current(const Power_Log *p)
{
    // pointer dereference via -> operator
    // returns current measurement from log entry
    return p->lineCurrent;
}