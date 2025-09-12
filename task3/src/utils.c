#include <unistd.h>
#include <stdarg.h>

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
