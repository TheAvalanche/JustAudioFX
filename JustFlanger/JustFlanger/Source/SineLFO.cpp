/*
  ==============================================================================

    SineLFO.cpp
    Created: 1 Aug 2022 6:31:54pm
    Author:  AleksandrKartishev

  ==============================================================================
*/
#define _USE_MATH_DEFINES

#include "SineLFO.h"
#include <cmath>

double SineLFO::getBipolarValue() {
    double bipolarSawValue = 2 * LFO::getCurrentModuloCounter() - 1;
    return sin(M_PI * bipolarSawValue);
}

double SineLFO::getUnipolarValue() {
    return LFO::getUnipolarValue();
}