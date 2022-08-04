/*
  ==============================================================================

    SawLFO.cpp
    Created: 1 Aug 2022 6:32:20pm
    Author:  AleksandrKartishev

  ==============================================================================
*/

#include "SawLFO.h"
#include <cmath>

double SawLFO::getBipolarValue() {
    return 2 * LFO::getCurrentModuloCounter() - 1;
}

double SawLFO::getUnipolarValue() {
    return LFO::getCurrentModuloCounter();
}