#pragma once
#include <memory>

/* 
	Performance optimized version of CircularBuffer (but CircularBuffer is easier to understand)
*/
class CircularBufferOptimized
{
public:

	void init(unsigned int _bufferLength);

	void flush();

	void write(float input);

	float read(unsigned int delaySamples);

private:
	std::unique_ptr<float[]> buffer = nullptr;
	unsigned int writeIndex = 0;
	unsigned int bufferLength = 1024;	// must be nearest power of 2
	unsigned int wrapMask = 1023;		// must be (bufferLength - 1)
};