/*
  ==============================================================================

    TriangleLFO.h
    Created: 1 Aug 2022 6:32:36pm
    Author:  AleksandrKartishev

  ==============================================================================
*/

#pragma once

#include "LFO.h"

class TriangleLFO : public LFO
{
public:
	TriangleLFO(double sampleFrequency) : LFO(sampleFrequency) {};

	double getBipolarValue() override;
	double getUnipolarValue() override;
};