#include "audio.h"

#include <portaudio.h>
#include <stdio.h>

// type for data carried by the callback
struct UserData
{
	float right;
	float left;
};

// We need one global storage for that, better init it in start
static struct UserData userData;
// We need a stream that is shared between the calls to start and end
// Might be better to place it as parameter to them, but then I would
// need to include port audio elsewhere, or at least some type
// declarations. Also, depending on how this is allocated, might
// lead to memory leak if startAudioStream is called more than needed.
static PaStream* stream = NULL;

// Callback that actually plays the sound
int pa_stream_callback(
		const void* input, void* output, unsigned long frameCount,
		const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
		void* userData)
{
	(void) input; // This is output callback, we don't touch the input
	(void) timeInfo; // Don't really need to know about time
	(void) statusFlags; // Wonder if there are any interesting ones
	float* out = (float*) output; // Output is in floats

	// Cast userdata to format it actually is
	struct UserData* data = (struct UserData*) userData;

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

int startAudioStream()
{
	// Init user data
	userData.left = 0.0f;
	userData.right = 0.0f;

	// Init PortAudio
	PaError err = Pa_Initialize();
	if (err != paNoError)
	{
		printf("PaError in Initialize: %s \n", Pa_GetErrorText(err));
		return 1;
	}
	// Find audio capablities of the system
	int numDevices = Pa_GetDeviceCount();
	if (numDevices < 0)
	{
		printf("PaError: Pa_CountDevices returned 0x%x: %s \n", numDevices, Pa_GetErrorText(numDevices));
	}

	const PaDeviceInfo* deviceInfo;
	for (int i = 0; i < numDevices; i++)
	{
		deviceInfo = Pa_GetDeviceInfo(i);
		printf("Device %d: %s (i:%d/o:%d) \n", i, deviceInfo->name, deviceInfo->maxInputChannels, deviceInfo->maxOutputChannels);
		// Here would be tests to determine if device handles what we need it to handle,
		// but changes of default handling 2 channel CD audio output is too large to waste time and space
	}

	// Open a stream
	PaStream* stream = NULL;
	err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, 44100, paFramesPerBufferUnspecified, pa_stream_callback, &userData);
	if (err != paNoError)
	{
		printf("PaError in Open Stream: %s \n", Pa_GetErrorText(err));
		return 1;
	}
	// Start it
	err = Pa_StartStream(stream);
	if (err != paNoError)
	{
		printf("PaError in Start Stream: %s \n", Pa_GetErrorText(err));
		return 1;
	}
	return 0;
}

int endAudioStream()
{
	PaError err = Pa_StopStream(stream);
	if (err != paNoError)
	{
		printf("PaError in Stop Stream: %s \n", Pa_GetErrorText(err));
		return 1;
	}
	Pa_Terminate();
	return 0;
}
