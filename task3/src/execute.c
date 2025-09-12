#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "task3.h"

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
		fprintf(stderr, "Error: execl() failed");
		_exit(1);
	}
	else if (pid > 0)
	{
		return pid;
	}
	else
	{
		fprintf(stderr, "Error: fork() failed");
		return -1;
	}
}

int execute_prog1(char *prog)
{
	pid_t	pid;
	int		status;

	pid = fork_and_exec(prog, STDIN_FILENO, STDOUT_FILENO, -1);
	waitpid(pid, &status, 0);
	return format_status(status);
}

int execute_pipeline_to_file(char *prog1, char *prog2, char *outfile)
{
	int		pipefd[2];
	int		out_fd;
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (pipe(pipefd) < 0)
	{
		fprintf(stderr, "Error: pipe() failed");
		return 1;
	}
	out_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC);
	if (out_fd == -1)
	{
		fprintf(stderr, "Error: open() failed");
		return 1;
	}
	pid1 = fork_and_exec(prog1, STDIN_FILENO, pipefd[1], pipefd[0]);
	pid2 = fork_and_exec(prog2, pipefd[0], out_fd, pipefd[1]);
	close(pipefd[0]);
	close(pipefd[1]);
	close(out_fd);
	if (pid1 < 0 || pid2 < 0)
		return 1;
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return format_status(status1) && format_status(status2) ? 0 : 1;
}
