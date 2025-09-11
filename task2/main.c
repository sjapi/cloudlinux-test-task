#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

static void print_tabs(unsigned int indent)
{
	for (unsigned int i = 0; i < indent; ++i)
	{
		printf("\t");
	}
}

static void list_dir(const char *path, unsigned int indent)
{
	DIR		*dir;
	struct dirent	*entry;
	char		*name;
	char		full_path[1024];

	dir = opendir(path);
	if (dir == NULL)
		return;
	while ((entry = readdir(dir)) != NULL)
	{
		name = entry->d_name;
		if (name[0] == '.')
			continue;
		print_tabs(indent);
		printf("%s\n", name);
		snprintf(full_path, sizeof(full_path), "%s/%s", path, name);
		if (entry->d_type == DT_DIR)
		{
			list_dir(full_path, indent + 1);
		}
	}
	closedir(dir);
}

int main(int argc, char **argv)
{
	char	cwd[PATH_MAX];

	if (argc != 1)
	{
		fprintf(stderr, "Error: extra aguments passed\n");
		return 1;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		fprintf(stderr, "Error: unable to get current working directory\n");
		return 1;
	}
	printf("%s\n", cwd);
	list_dir(cwd, 1);
	(void)argv;
	return 0;
}
