#include "simpleshell.h"

/**
 * _strncpy - copy n char of a source string to dest
 *@src: the source string
 *@dest: the destination string
 * @n: the number of elements to copy
 *
 *Return: pointer to the dest string
 **/
char	*_strncpy(char *dest, char *src, int n)
{
	int	i = 0;

	if (!dest || !src)
		return (dest);
	while (i < n)
	{
		dest[i] = *src;
		if (*src)
			++src;
		++i;
	}
	return (dest);
}

/**
  * stralloc - creates a new lav node and add it
  * @str: the pointer to the string to copy
  * @i: the size of the new string
  * @flag: the delimeter
  * @llav: the head of llav ll
  *
  * Return: -1 if error 1 otherwise
  **/
int	stralloc(char *str, int i, char flag, cmd_lst_lst_t *llav)
{
	char	*buf;

	buf = (char *)malloc(i + 1);
	if (!buf)
		return (-1);
	buf = _strncpy(buf, str, i);
	buf[i] = '\0';
	add_cmd_lst(buf, &llav->head, flag);
	return (1);
}

/**
  * free_r - frees r if error
  * @size: the current size of r
  * @r: a list of strings
  **/
void	free_r(size_t size, char **r)
{
	while (size > 0)
		free(r[--size]);
	free(r);
}

/**
 * strsplit - a function that splits a string at the logical \
 operator "||" and "&&"
 * @s: the string in which to find the words
 * @llav: the head of the llav ll
 *
 * Return: 0 if error, 1 otherwise
 **/
int	strsplit(cmd_lst_lst_t *llav, char *s)
{
	int	i = 0;
	size_t	size = 1;
	char	flag = 0;

	if (!s || !*s)
		return (0);
	while (s[i])
	{
		if ((s[i] == '|' && s[i + 1] == '|') || (s[i] == '&' && s[i + 1] == '&'))
		{
			if (stralloc(s, i, flag, llav) == 1)
			{
				flag = (s[i] == '|') ? '|' : '&';
				++size;
				s += i + 2;
				i = -1;
			}
			else
				return (0);
		}
		++i;
	}
	if (stralloc(s, i, flag, llav) == -1)
		return (0);
	return (1);
}

