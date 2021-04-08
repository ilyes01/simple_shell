#include "simpleshell.h"

/**
 * sh_get_env - duplicates the environment from env variable
 *
 * @env: the env variable
 *
 * Return: pointer on char ** array of variables
 */

char **sh_get_env(char **env)
{
	int i = 0;
	char **new_env;

	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;

	while (env[i])
	{
		new_env[i] = _strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/**
 * sh_delete_env - deletes the env array
 *
 * @env: the env array
 */

void sh_delete_env(char **env)
{
	int i = 0;

	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
}

/**
 * sh_get_env_var - get the environment variable
 *
 * @var: the name of the variable to get
 * @env: the environment variable
 *
 * Return: the value of the environment variable
 */

char *sh_get_env_var(char *var, char **env)
{
	int i = 0, j;
	char *val = NULL;

	while (env[i])
	{
		j = 0;
		while (env[i][j] == var[j] && var[j])
			j++;
		if (env[i][j] == '=' && var[j] == '\0')
		{
			val = _strdup(env[i] + j + 1);
			break;
		}
		i++;
	}
	return (val);
}
