#include "simpleshell.h"

/**
 * sh_getline - getline
 * @line: the address where to store the line
 * @fd: the filde to read from
 *
  * Return: 1, -2 or EOF
 */

int sh_getline(char **line, int fd)
{
	int ret, pos = 0, buf_size = 1;
	char c;

	*line = malloc(sizeof(char) * 1);
	while ((ret = read(fd, &c, 1)) > 0)
	{
		*(*line + pos++) = (c == '\n') ? '\0' : c;
		if (*(*line + pos - 1) == '\0')
			return (1);
		if (pos >= buf_size)
		{
			*line = _realloc(*line, buf_size, buf_size + 1);
			buf_size++;
		}
	}
	return ((ret == 0) ? EOF : -2);
}
