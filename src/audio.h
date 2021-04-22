#pragma once

#include <portaudio.h>

struct StreamInfo
{
	int inputChannelCount;
	int outputChannelCount;
	double sampleRate;
	// How many frames of samples is expected
	// to be written to buffer per call to the
	// callback. If 0, then the portAudio will
	// set it for each call to best match underlying
	// implementation.
	unsigned long framesPerBuffer;
}


void openStream(StreamInfo* streamInfo);
