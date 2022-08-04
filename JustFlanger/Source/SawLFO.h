/*
  ==============================================================================

    SawLFO.h
    Created: 1 Aug 2022 6:32:20pm
    Author:  AleksandrKartishev

  ==============================================================================
*/

#pragma once
#include "LFO.h"

class SawLFO : public LFO
{
public:
	SawLFO(double sampleFrequency) : LFO(sampleFrequency) {};

	double getBipolarValue() override;
	double getUnipolarValue() override;
};