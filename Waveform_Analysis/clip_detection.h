//
// Created by joewe on 21/04/2026.
// (clip detection header - small module for flagging saturated samples)
//

#ifndef UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_CLIP_DETECTION_H
#define UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_CLIP_DETECTION_H


#include "io.h"   // needed for Power_Log struct (data model for each sample)


// ------------------------------------
// runs through log array and sets clip flags
// basically marks samples where signal hits limit
// ------------------------------------
void apply_clipping_flags(Power_Log *logs, int length);


#endif // UGMFGT_15_1_JWESTING_P_FACTOR_ANALYSER_CLIP_DETECTION_H