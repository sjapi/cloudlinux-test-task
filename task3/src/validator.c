#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int prog_exists(char *path)
{
	return strlen(path) != 0 && access(path, F_OK | X_OK) == 0;
}

int validate_input(int argc, char **argv)
{
	if (argc != 5)
	{
		fprintf(stderr, "Error: wrong arguments count, expected 4, got %d\n", argc - 1);
		return 0;
	}
	for (int i = 1; i <= 3; ++i)
	{
		if (!prog_exists(argv[i]))
		{
			fprintf(stderr, "Error: file '%s' does not exist or not executable\n", argv[i]);
			return 1;
		}
	}
	return 0;
}
