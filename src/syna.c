#include "syna.h"

#include "arguments.h"

#include <stdio.h>

int syna(const struct Arguments* const arguments)
{
	if (arguments->options_file)
		printf("Syna playing using settings from %s", arguments->options_file);
	// Read the options file here

	// Find audio capablities of the system
	

	return 0;
}
