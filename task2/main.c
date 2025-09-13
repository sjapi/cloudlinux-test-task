#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

static int dir_exists(const char *path)
{
	struct stat sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		return 1;
	}
	return 0;
}

static void print_tabs(unsigned int indent)
{
	for (unsigned int i = 0; i < indent; ++i)
	{
		printf("\t");
	}
}

static void list_dir(const char *path, unsigned int indent)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*name;
	char			full_path[PATH_MAX];

	dir = opendir(path);
	if (dir == NULL)
		return;
	while ((entry = readdir(dir)) != NULL)
	{
		name = entry->d_name;
		if (name != NULL && name[0] == '.')
			continue;
		print_tabs(indent);
		printf("%s\n", name);
		if (entry->d_type == DT_DIR)
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", path, name);
			list_dir(full_path, indent + 1);
		}
	}
	closedir(dir);
}

int main(int argc, char **argv)
{
	char	cwd[PATH_MAX];
	char	*target;

	if (argc == 1)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			fprintf(stderr, "Error: unable to get current working directory\n");
			return 1;
		}
		target = cwd;
	}
	else if (argc == 2)
	{
		target = argv[1];
		if (dir_exists(target) != 1)
		{
			fprintf(stderr, "Error: %s: no such directory\n", target);
			return 1;
		}
	}
	else
	{
		fprintf(stderr, "Error: extra arguments passed\n");
		return 1;
	}
	printf("%s\n", target);
	list_dir(target, 1);
	return 0;
}
