#include "syna.h"

#include "arguments.h"
#include "audio.h"

#include <stdio.h>

int syna(const struct Arguments* const arguments)
{
	// Do we have options file
	if (arguments->options_file)
		printf("Syna playing using settings from %s \n", arguments->options_file);
	// Read the options file here

	// Start the stream and check nothing failed
	if (startAudioStream() != 0)
		return 1;

	// Play while need to play
	while(1){};

	// End the stream, report failures
	return endAudioStream();
}
