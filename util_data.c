#include "simpleshell.h"

/**
 * sh_data_new - initialize new data_t structure
 *
 * @argv: the arguments
 * @env: the environment
 *
 * Return: pointer to the new data_t structure
 */

data_t *sh_data_new(char **argv, char **env)
{
	data_t *new = NULL;

	if (argv)
	{
		new = malloc(sizeof(data_t));
		if (new)
		{
			new->env = sh_get_env(env);
			new->alias = NULL;
			new->lines = 0;
			new->bash = _strdup(argv[0]);
			new->llav_head = NULL;
		}
	}
	return (new);
}

/**
 * sh_data_delete - deletes the data_t structure
 *
 * @data: the data_t variable
 *
 * Return: NULL always (call if needed)
 */

void *sh_data_delete(data_t *data)
{
	if (data)
	{
		if (data->env)
			sh_delete_env(data->env);
		if (data->bash)
			free(data->bash);
		free(data);
	}
	return (NULL);
}
