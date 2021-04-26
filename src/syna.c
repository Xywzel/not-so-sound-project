#include "syna.h"

#include "arguments.h"

#include <stdio.h>
#include <portaudio.h>

struct UserData
{
	float right;
	float left;
};

static struct UserData userData;

int pa_stream_callback(
		const void *input, void *output, unsigned long frameCount,
		const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
		void *userData)
{
	(void) input; // This is output callback, we don't touch the input
	(void) timeInfo; // Don't really need to know about time
	(void) statusFlags; // Wonder if there are any interesting ones
	float *out = (float *)(output); // Output is in floats

	// Cast userdata to format it actually is
	struct UserData *data = (struct UserData*)userData;

	printf("New samples requested\n");

	// For each frame
	for(unsigned long i = 0; i < frameCount; ++i)
	{
		float left_sample = data->left;
		float right_sample = data->right;
		// Write left and right channel samples to the out
		*(out++) = left_sample;
		*(out++) = right_sample;
		// Prepare for next round
		data->left += 0.1f;
		data->right += 0.2f;
		if (data->left > 1.0f)
			data->left -= 2.0f;
		if (data->right > 1.0f)
			data->right -= 2.0f;
	}
	// Store state to userdata if needed
	// Return 0 for not having problems
	return 0;
}


int syna(const struct Arguments* const arguments)
{
	if (arguments->options_file)
		printf("Syna playing using settings from %s \n", arguments->options_file);
	// Read the options file here

	// Init PortAudio
	PaError err = Pa_Initialize();
	if (err != paNoError)
	{
		printf("PaError in Initialize: %s \n", Pa_GetErrorText(err));
		return 1;
	}
	// Find audio capablities of the system
	PaStream* stream = NULL;
	err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, 44100, paFramesPerBufferUnspecified, pa_stream_callback, &userData);
	if (err != paNoError)
	{
		printf("PaError in Open Stream: %s \n", Pa_GetErrorText(err));
		return 1;
	}

	err = Pa_StartStream(stream);
	if (err != paNoError)
	{
		printf("PaError in Start Stream: %s \n", Pa_GetErrorText(err));
		return 1;
	}

	while(1){};

	err = Pa_StopStream(stream);
	if (err != paNoError)
	{
		printf("PaError in Stop Stream: %s \n", Pa_GetErrorText(err));
		return 1;
	}

	Pa_Terminate();
	return 0;
}
