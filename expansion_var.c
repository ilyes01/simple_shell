#include "simpleshell.h"

/**
 * _isgraph - checks if it's a graphic character
 *
 * @c: the character to test
 *
 * Return: 1 if yes, 0 if no
 */

int _isgraph(char c)
{
	if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9')
			|| (c == '_'))
		return (1);
	return (0);
}

/**
 * _strncmp - compares string until n
 *
 * @s1: the first string
 * @s2: the second string
 * @n: the maximum lenght to search inside
 *
 * Return: 0 if it's equal, or other if no
 */

int _strncmp(char *s1, char *s2, int n)
{
	int i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

/**
 * parse_env_var - returns the value of the dirst encountered env variable
 *
 * @s: the string to look inside
 * @env: the environment variables
 *
 * Return: the value of the variable or NULL if it don't exists
 */

char	*parse_env_var(char *s, char **env)
{
	int len = 0, i = 0;
	char *name;
	char *content;

	if (s[i] == '$')
	{
		len += 1;
		while (s[len] && _isgraph(s[len]) && s[len] != '$')
			len++;
		name = _strndup(s + 1, len - 1);
		content = sh_get_env_var(name, env);
		free(name);
		if (!content)
			return (NULL);
		return (content);
	}
	return (NULL);
}

/**
 * expansion_alias - replace aliases in given arguments
 *
 * @var: the name of the variable to get
 * @als: the aliases variable
 *
 * Return: the value of the environment variable
 */

char *expansion_alias(char *var, char **als)
{
	int len = _strlen(var), i = 0;
	char *new = NULL;

	while (als && als[i])
	{
		if (_strncmp(als[i], var, len) == 0)
		{
			if (als[i][len] == '=' && als[i][len + 1])
			{
				new = _strdup(als[i] + len + 1);
				break;
			}
		}
		i++;
	}
	return (new);
}

/**
 * expansion_var_alias - expands the $X variables and replaces aliases
 *
 * @av: the arguments of our commands
 * @data: the data_t structure
 */

void expansion_var_alias(char **av, data_t *data)
{
	int i = 0, j;
	char *new = NULL, *content = NULL;
	char	*buf;

	while (av[i])
	{
		j = 0;
		new = expansion_alias(av[i], data->alias);
		if (new == NULL)
		{
			while (av[i][j])
			{
				if (av[i][j] == '$' && av[i][j + 1])
				{
					content = parse_env_var(av[i] + j, data->env);
					new = str_concat(new, content);
					j++;
					while (av[i][j] && _isgraph(av[i][j]))
						j++;
					j--;
				}
				else
					new = c_concat(new, av[i][j]);
				j++;
			}
		}
		buf = av[i];
		av[i] = _strdup(new);
		free(buf);
		free(new);
		new = NULL;
		i++;
	}
}
