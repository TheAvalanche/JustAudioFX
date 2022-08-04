#pragma once

class LFO
{
public:
	LFO(double sampleFrequency);
	virtual ~LFO() = default;

	void reset(double oscFrequency);

	virtual double getBipolarValue() = 0;

	virtual double getUnipolarValue() {
		return 0.5 * getBipolarValue() + 0.5;
	};

protected:
	double getCurrentModuloCounter();

private:
	double sampleFrequency;
	double oscFrequency = 1.0;
	double moduloCounter = 0.0;
	double phaseIncrement = 0.0;
};