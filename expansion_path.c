#include "simpleshell.h"

/**
 * free_path - free the path
 *
 * @path: the path
 * @i: the index to be deleted
 */

void free_path(char **path, int i)
{
	while (path && path[i])
	{
		free(path[i]);
		i++;
	}
}

/**
 * expansion_path - search is the first argument is an executable in the PATH
 * @arg: the first argument
 * @path_var: the PATH environment variable
 */

void expansion_path(char **arg, char *path_var)
{
	char **path = NULL;
	int i = 0;
	char *bin_path = NULL, *tmp;
	struct stat stats;

	if (is_builtin(*arg))
		return;
	path = strtoav(path_var, ":");
	while (path && path[i])
	{
		tmp = _strdup(*arg);
		bin_path = NULL;
		if (path[i][_strlen(path[i]) - 1] != '/')
			path[i] = c_concat(path[i], '/');
		bin_path = str_concat(path[i], tmp);
		if (lstat(bin_path, &stats) == -1)
			free(bin_path);
		else
		{
			free_path(path, i + 1);
			free(path);
			if (stats.st_mode & S_IFREG)
			{
				if (stats.st_mode & S_IXUSR)
				{
					tmp = *arg;
					*arg = _strdup(bin_path);
					free(tmp);
				}
				free(bin_path);
				return;
			}
		}
		i++;
	}
	free(path);
}
