#include "LFO.h"
#include <cmath>

LFO::LFO(double _sampleFrequency) {
	sampleFrequency = _sampleFrequency;
}

void LFO::reset(double _oscFrequency) {
	oscFrequency = _oscFrequency;
	phaseIncrement = oscFrequency / sampleFrequency;
	moduloCounter = 0;
}

double LFO::getCurrentModuloCounter() {
	moduloCounter += phaseIncrement;
	if (phaseIncrement > 0 && moduloCounter >= 1.0) {
		moduloCounter = 0;
	}

	return moduloCounter;
}