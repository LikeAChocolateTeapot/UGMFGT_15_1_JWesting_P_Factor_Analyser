//
// Created by joewe on 21/04/2026.
//

#include "clip_detection.h"
#include <math.h>

#define CLIP_LIMIT 324.9

static int is_clipping(double v)
{
    return fabs(v) >= CLIP_LIMIT;
}

void apply_clipping_flags(Power_Log *logs, int length)
{
    for (int i = 0; i < length; i++)
    {
        Power_Log *sample = &logs[i];

        sample->clip_flag =
            is_clipping(sample->phaseA) ||
            is_clipping(sample->phaseB) ||
            is_clipping(sample->phaseC);
    }
}