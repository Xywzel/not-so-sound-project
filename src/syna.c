#include "syna.h"

#include "arguments.h"

#include <stdio.h>

int syna(const struct Arguments* const arguments)
{
	printf("Syna playing something from %s", arguments->options_file);
	return 0;
}
