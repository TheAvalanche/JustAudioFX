#pragma once
#include <memory>

class CircularBuffer
{
public:

	void init(unsigned int _bufferLength);

	void flush();

	void write(float input);

	float read(unsigned int delaySamples);

private:
	std::unique_ptr<float[]> buffer = nullptr;
	unsigned int writeIndex = 0;
	unsigned int bufferLength = 1024;
};