#include "tests.h"

#include <stdio.h>

int tests(const struct Arguments* const arguments)
{
	printf("Running some tests, mode is %d ", arguments->mode);
	return 0;
}
