#include "simpleshell.h"

/**
 * _atoi - converts a string into an integer
 * @s: the string to be converted
 *
 * Return: the value of the int
 */

int _atoi(char *s)
{
	int i = 0, sign = 0, res = 0;

	while (s[i] && (!(s[i] >= '0') || !(s[i] <= '9')))
	{
		if (s[i] == '-')
			sign++;
		i++;
	}
	sign = (sign % 2) ? -1 : 1;
	while (s[i] && ((s[i] >= '0') && (s[i] <= '9')))
		res = res * 10 + (s[i++] - '0') * sign;
	return (res);
}


/**
 * bi_exit - exit builtin
 *
 * @data: the data_t structure
 *
 * Return: 0
 */

int bi_exit(data_t *data)
{
	int status = 0, i = 0;
	char *av1 = data->llav_head->head->av[1];

	if (av1)
	{
		while (av1[i])
		{
			if (av1[i] < '0' || av1[i] > '9')
				return (2);
			i++;
		}
		status = _atoi(data->llav_head->head->av[1]);
	}

	free_all(&data->llav_head);
	free(*data->line);
	sh_data_delete(data);

	exit(status);
	return (0);
}
