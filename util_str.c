#include "simpleshell.h"

/**
 * _strlen - calculates the length of a string
 * @str: the string
 *
 * Return: length of the string, or 0 is string is NULL or empty
 */
int _strlen(char *str)
{
	int len = 0;

	if (str)
		while (str[len])
			len++;
	return (len);
}

/**
 * _puts - writes a string on the POSIX stdout
 * @str: the string to write
 *
 * Return: length of str on success, 0 if nothing has been written, -1 on error
 */
int _puts(char *str)
{
	return (write(STDOUT_FILENO, str, _strlen(str)));
}

/**
 * _strdup - allocates a new space in memory which contains
 * a copy of the string given as a parameter
 * @str: the string to duplicate
 *
 * Return: a pointer to the new string, or NULL if str = NULL or fail
 */
char *_strdup(char *str)
{
	char *new_str;
	int i = 0;

	if (str == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * _strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/**
 * _strchr - a function that locates a character in a string
 * @s: the string to search in
 * @c: the char to search
 *
 * Return: 0 if error or no match else the pointer to the matching char in s
 *
 **/
const char	*_strchr(const char *s, char c)
{
	if (!s)
		return (0);
	if (c == 0)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (s);
		++s;
	}
	return (0);
}

/**
 * _strcmp - compare two strings
 * @s1: one string to compare
 * @s2: second string to compare
 *
 * Return: 0 if same char diff if not
 **/

int	_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i] || !s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	return (s2[i] ? -s2[i] : 0);
}

