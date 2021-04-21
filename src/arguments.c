#include "arguments.h"

#include "string_util.h"
#include "defines.h"

#include <stdio.h>

void parse_arguments(struct Arguments* arguments_out, int argc, char* argv[])
{
	// Initialize arguments to no flags state
	arguments_out->mode = 0;
	arguments_out->options_file = NULL;

	printf("Running command %s with %d arguments\n", argv[0], argc);

	// First arg is allways command used to run the program, so it can be skipped
	for (int i = 1; i < argc; ++i)
	{
		printf("Checking argument %d, it has value %s\n", i, argv[i]);
		if (compare_strings(argv[i], "-f") == 0 && i + 1 < argc)
		{
			arguments_out->options_file = argv[i+1];
			++i;
		}
		else if (compare_strings(argv[i], "-t"))
		{
			arguments_out->mode = 1;
		}
	}
}
