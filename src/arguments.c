#include "arguments.h"

#include "string_util.h"

void parse_arguments(struct Arguments* arguments_out, int argc, char* argv[])
{
	// First arg is allways command used to run the program, so it can be skipped
	for (int i = 1; i < argc; ++i)
	{
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
