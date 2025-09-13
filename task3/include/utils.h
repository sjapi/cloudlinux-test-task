#ifndef _UTILS_H
#define _UTILS_H

/*
 * rw-r--r-- (owner: read&write, group: read, others: read)
 */
#define FILE_MODE_RW_R__R__ 0644

int validate_input(int argc, char **argv);

int prog_exists(char *path);

int execute_prog1(char *prog);

int execute_pipeline_to_file(char *prog1, char *prog2, char *outfile);

void close_fds(int n, ...);

#endif
