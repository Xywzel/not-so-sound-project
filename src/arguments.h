#pragma once

/* Arguments
 * Structure for storing read commandline arguments
 */

struct Arguments
{
	char* options_file;
	int mode;
};

/* parseArguments
 * Parses standard format c commandline arguments into Arguments struct
 * input:
 * - argumentsOut, pointer to target struct to be filled, space must be reserved
 * - argc, number of entries in the argv
 * - argv, array of pointer to null termined c strings
 */

void parse_arguments(struct Arguments* arguments_out, int argc, char* argv[]);
