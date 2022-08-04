/*
  ==============================================================================

    SineLFO.h
    Created: 1 Aug 2022 6:31:54pm
    Author:  AleksandrKartishev

  ==============================================================================
*/

#pragma once

#include "LFO.h"

class SineLFO : public LFO
{
public:
	SineLFO(double sampleFrequency) : LFO(sampleFrequency) {};

	double getBipolarValue() override;
	double getUnipolarValue() override;
};