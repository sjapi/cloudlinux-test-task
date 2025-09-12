#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "utils.h"

static int format_status(int status)
{
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	return 1;
}

static pid_t fork_and_exec(char *prog, int input_fd, int output_fd, int close_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		if (close_fd >= 0)
		{
			close(close_fd);
		}
		execl(prog, prog, NULL);
		fprintf(stderr, "Error: execl() failed\n");
		_exit(1);
	}
	else if (pid > 0)
	{
		return pid;
	}
	else
	{
		fprintf(stderr, "Error: fork() failed\n");
		return -1;
	}
}

int execute_prog1(char *prog)
{
	pid_t	pid;
	int		status;

	pid = fork_and_exec(prog, STDIN_FILENO, STDOUT_FILENO, -1);
	if (pid < 0)
		return 1;
	waitpid(pid, &status, 0);
	return format_status(status);
}

int execute_pipeline_to_file(char *prog1, char *prog2, char *outfile)
{
	int		out_fd;
	int		pipefd[2];
	pid_t	pid1, pid2;
	int		status1, status2;

	out_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, FILE_MODE_RW_R__R__);
	if (out_fd == -1)
	{
		fprintf(stderr, "Error: open() failed\n");
		return 1;
	}
	if (pipe(pipefd) == -1)
	{
		close(out_fd);
		fprintf(stderr, "Error: pipe() failed\n");
		return 1;
	}
	pid1 = fork_and_exec(prog1, STDIN_FILENO, pipefd[1], pipefd[0]);
	if (pid1 == -1)
	{
		close_fds(3, pipefd[0], pipefd[1], out_fd);
		return 1;
	}
	pid2 = fork_and_exec(prog2, pipefd[0], out_fd, pipefd[1]);
	if (pid2 == -1)
	{
		close_fds(3, pipefd[0], pipefd[1], out_fd);
		kill(pid1, SIGTERM);
		waitpid(pid1, NULL, 0);
		return 1;
	}
	close_fds(3, pipefd[0], pipefd[1], out_fd);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (format_status(status1) == 0 && format_status(status2) == 0) ? 0 : 1;
}
