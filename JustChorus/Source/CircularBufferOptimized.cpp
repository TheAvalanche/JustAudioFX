#include "CircularBufferOptimized.h"

void CircularBufferOptimized::init(unsigned int _bufferLength) {
	// set write index to 0
	writeIndex = 0;
	// find nearest power of 2 for buffer length, thus we will be able to use wrap mask for wrapping
	bufferLength = pow(2, ceil(log(_bufferLength) / log(2)));
	// set wrap mask as (bufferLength - 1) for wrapping
	wrapMask = bufferLength - 1;
	// create new buffer
	buffer.reset(new float[bufferLength]);
	// flush buffer
	flush();
}

void CircularBufferOptimized::flush() {
	memset(&buffer[0], 0, bufferLength * sizeof(float));
}

float CircularBufferOptimized::read(unsigned int delaySamples) {
	// calculate read index as offset from write index
	int readIndex = writeIndex - delaySamples;
	// check and wrap backwards if the index is negative
	readIndex &= wrapMask;

	return buffer[readIndex];
}

void CircularBufferOptimized::write(float input) {
	// write and increment index
	buffer[writeIndex++] = input;
	// wrap write index if exceeding buffer length
	writeIndex &= wrapMask;
}