#include "simpleshell.h"

/**
 * str_concat - concatenates two strings
 *
 * @s1: the first string
 * @s2: the second string
 *
 * Return: a pointer to the new string, or NULL on failure
 */

char *str_concat(char *s1, char *s2)
{
	char *str;
	int i = 0, j = 0;

	if (s1 == NULL && s2 != NULL)
		return (s2);
	if (s2 == NULL && s1 != NULL)
		return (s1);
	str = malloc(sizeof(char) * (_strlen(s1) + _strlen(s2) + 1));
	if (!str)
		return (NULL);
	if (s1 != NULL && s2 != NULL)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		while (s2[j])
		{
			str[i + j] = s2[j];
			j++;
		}
		free(s1);
		free(s2);
	}
	str[i + j] = '\0';
	return (str);
}

/**
 * c_concat - concatenates a char to a string
 *
 * @s: the string
 * @c: the char
 *
 * Return: a pointer to the new string, or NULL on failure
 */

char *c_concat(char *s, char c)
{
	char *str;
	int i = 0;

	str = malloc(sizeof(char) * (_strlen(s) + 2));
	if (!str)
		return (NULL);
	if (s)
	{
		while (s[i])
		{
			str[i] = s[i];
			i++;
		}
		free(s);
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

/**
 * _strndup - allocates a new space in memory which contains
 * a copy of the string given as a parameter until n length
 *
 * @str: the string to duplicate
 * @n: the max length
 *
 * Return: a pointer to the new string, or NULL if str = NULL or fail
 */

char *_strndup(char *str, int n)
{
	char *new_str;
	int	i = 0;

	if (str == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (NULL);
	while (str[i] && i < n)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
