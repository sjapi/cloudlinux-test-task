#include <unistd.h>
#include <string.h>
#include <stdarg.h>

int prog_exists(char *path)
{
	if (path == NULL)
		return 1;
	return (strlen(path) != 0 && access(path, F_OK | X_OK) == 0) ? 0 : 1;
}

void close_fds(int n, ...)
{
	va_list	args;
	int		fd;

	va_start(args, n);
	for (int i = 0; i < n; ++i)
	{
		fd = va_arg(args, int);
		if (fd >= 0)
			close(fd);
	}
	va_end(args);
}
