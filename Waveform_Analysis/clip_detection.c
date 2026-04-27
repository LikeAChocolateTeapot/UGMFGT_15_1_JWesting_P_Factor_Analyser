//
// Created by joewe on 21/04/2026.
// (clip detection logic - flags samples hitting sensor limit)
//

#include "clip_detection.h"
#include <math.h>   // needed for fabs()


// hard limit from sensor spec (voltage clipping threshold)
#define CLIP_LIMIT 324.9


// ------------------------------------
// checks if a single value is clipping
// returns 1 if clipped, 0 if not
// ------------------------------------
static int is_clipping(double v)
{
    // fabs = absolute value (so negative spikes count too)
    return fabs(v) >= CLIP_LIMIT;
}


// ------------------------------------
// goes through whole array of logs
// and sets clip_flag per sample
// ------------------------------------
void apply_clipping_flags(Power_Log *logs, int length)
{
    for (int i = 0; i < length; i++)
    {
        // pointer to current struct in array
        // same as logs[i], just stored for readability
        Power_Log *sample = &logs[i];

        // check all 3 phases, if ANY exceed limit -> flagged
        sample->clip_flag =
            is_clipping(sample->phaseA) ||
            is_clipping(sample->phaseB) ||
            is_clipping(sample->phaseC);
    }
}