#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils.h"

int main(int argc, char **argv)
{
	if (validate_input(argc, argv) != 0)
		return 1;
	if (execute_prog1(argv[1]) != 0)
		return 1;
	if (execute_pipeline_to_file(argv[2], argv[3], argv[4]) != 0)
		return 1;
	return 0;
}
