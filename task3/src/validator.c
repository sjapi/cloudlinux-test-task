#include <stdio.h>
#include <string.h>
#include <unistd.h>

int validate_input(int argc, char **argv)
{
	if (argc != 5)
	{
		fprintf(stderr, "Error: wrong arguments count, expected 4, got %d\n", argc - 1);
		return 1;
	}
	(void)argv;
	return 0;
}
