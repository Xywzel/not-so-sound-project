#include "arguments.h"
#include "tests.h"
#include "syna.h"

int main(int argc, char *argv[])
{
	struct Arguments arguments;
	if(argc > 1)
	{
		parse_arguments(&arguments, argc, argv);
	}

	switch(arguments.mode)
	{
		case 0:
			return syna(&arguments);
		case 1:
			return tests(&arguments);
		default:
			return tests(&arguments);
	}
}
