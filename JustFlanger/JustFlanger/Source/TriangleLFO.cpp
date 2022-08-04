/*
  ==============================================================================

    TriangleLFO.cpp
    Created: 1 Aug 2022 6:32:36pm
    Author:  AleksandrKartishev

  ==============================================================================
*/

#include "TriangleLFO.h"
#include <cmath>

double TriangleLFO::getBipolarValue() {
	double bipolarSawValue = 2 * LFO::getCurrentModuloCounter() - 1;
	return 2 * fabs(bipolarSawValue) - 1;
}

double TriangleLFO::getUnipolarValue() {
    return LFO::getUnipolarValue();
}