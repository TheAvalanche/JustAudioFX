#include "CircularBuffer.h"

void CircularBuffer::init(unsigned int _bufferLength) {
	writeIndex = 0;
	bufferLength = _bufferLength;
	buffer.reset(new float[bufferLength]);
	flush();
}

void CircularBuffer::flush() {
	memset(&buffer[0], 0, bufferLength * sizeof(float));
}

float CircularBuffer::read(unsigned int delaySamples) {
	int readIndex = writeIndex - delaySamples;
	// check and wrap BACKWARDS if the index is negative
	if (readIndex < 0) {
		readIndex += bufferLength; // amount of wrap is -Read + Length
	}
	return buffer[readIndex];
}

void CircularBuffer::write(float input) {
	buffer[writeIndex] = input;
	writeIndex++;
	if (writeIndex == bufferLength) {
		writeIndex = 0;
	}
}