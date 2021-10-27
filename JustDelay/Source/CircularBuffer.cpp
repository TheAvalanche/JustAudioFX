#include "CircularBuffer.h"

void CircularBuffer::init(unsigned int _bufferLength) {
	// set write index to 0
	writeIndex = 0;
	// set buffer length
	bufferLength = _bufferLength;
	// create new buffer
	buffer.reset(new float[bufferLength]);
	// flush the buffer
	flush();
}

void CircularBuffer::flush() {
	memset(&buffer[0], 0, bufferLength * sizeof(float));
}

float CircularBuffer::read(unsigned int delaySamples) {
	// calculate read index as offset from write index
	int readIndex = writeIndex - delaySamples;
	// check and wrap backwards if the index is negative
	if (readIndex < 0) {
		// amount of wrap is negative readIndex + Length
		readIndex += bufferLength;
	}
	return buffer[readIndex];
}

void CircularBuffer::write(float input) {
	// write and increment index
	buffer[writeIndex] = input;
	writeIndex++;
	// wrap write index if exceeding buffer length
	if (writeIndex == bufferLength) {
		writeIndex = 0;
	}
}