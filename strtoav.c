#include "simpleshell.h"

/**
 * wrdcnt - counts the number to words in a string delimetered bu delim
 * @str: the string in which to count the words
 * @delim: the words delimeter
 *
 * Return: the number of words
 **/
int	wrdcnt(char *str, const char *delim)
{
	int		nb;

	if (!str)
		return (0);
	nb = 0;
	while (*str)
	{
		if (_strchr(delim, *str))
		{
			while (_strchr(delim, *str))
				++str;
		}
		else
		{
			++nb;
			while (*str && !_strchr(delim, *str))
				++str;
		}
	}
	return (nb);
}

/**
 * alloc_word - recursively allocate and fill a string with the next word\
 delimetered by ' '
 * @ri: the address of the pointer to the string
 * @str: the string in which to find the word
 * @len: the lenght of the word
 * @delim: the delimeter list
 *
 * Return: 0 if error, 1 otherwise
 **/
int	alloc_word(char **ri, char *str, int len, const char *delim)
{
	if (*str && !_strchr(delim, *str))
		alloc_word(ri, str + 1, len + 1, delim);
	else
	{
		*ri = malloc(len + 1);
		if (!*ri)
			return (0);
		(*ri)[len] = '\0';
		return (1);
	}
	(*ri)[len] = *str;
	return (1);
}

/**
 * strtoav - a function that splits a string into words
 * @str: the string in which to find the words
 * @delim: a list of character delimeters
 *
 * Return: a newly allocated list of words found in str
 **/
char	**strtoav(char *str, const char *delim)
{
	char	**r;
	int	wrdnb;
	int	i;

	if (!str || !*str)
		return (0);
	wrdnb = wrdcnt(str, delim);
	if (!wrdnb)
		return (0);
	r = (char **)malloc((wrdnb + 1) * sizeof(char *));
	if (!r)
		return (0);
	r[wrdnb] = 0;
	i = 0;
	while (*str)
	{
		while (*str && _strchr(delim, *str))
			++str;
		if (*str && !alloc_word(r + i, str, 0, delim))
		{
			while (i >= 0)
				free(r[i--]);
			free(r);
			return (0);
		}
		++i;
		while (*str && !_strchr(delim, *str))
			++str;
	}
	return (r);
}

