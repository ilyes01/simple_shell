#include "simpleshell.h"

/**
 * main - entry point of our shell
 * @argc: the number of arguments to main
 * @argv: the list of arguments
 * @env: the environement
 * Return: always 0
 */

int main(int argc, char **argv, char **env)
{
	data_t *data;
	int fd;

	data = sh_data_new(argv, env);
	if (argc > 1)
	{
		data->mode = FROMFILE;
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			_puts(data->bash);
			_puts(": 0: Can't open ");
			_puts(argv[1]);
			_puts("\n");
			sh_data_delete(data);
			return (127);
		}
		sh_start(data, fd);
	}
	else
	{
		if (isatty(STDIN_FILENO))
			data->mode = INTERACTIVE;
		else
			data->mode = NONINTERACTIVE;
		sh_start(data, STDIN_FILENO);
	}
	sh_data_delete(data);
	return (EXIT_SUCCESS);
}

/**
 * stop_signal_handler - the command to execute on Ctrl+C
 *
 * @signum: the value of the signal
 */

void stop_signal_handler(int signum)
{
	(void)signum;
	_puts("\n$ > ");
}

/**
 * sh_start - when the type of execution has been choosen, parses and executes
 * commands
 *
 * @data: the data_t structure
 * @fd: the file descriptor to read
 *
 * Return: EXIT_SUCCESS always because all errors should be treated
 */

int sh_start(data_t *data, int fd)
{
	cmd_lst_lst_t	*head = NULL;
	char		*line = NULL;
	int		ret = 0;

	if (data->mode == INTERACTIVE)
		_puts("$ > ");

	data->line = &line;
	signal(SIGINT, stop_signal_handler);
	while ((ret = sh_getline(&line, fd)) != EOF)
	{
		if (parser(line, &head) != -1)
		{
			data->llav_head = head;
			expansion(data, &head);
			execute(data, &head);
			free_all(&head);
		}
		data->lines++;
		free(line);
		if (data->mode == INTERACTIVE)
			_puts("$ > ");
	}
	if (line)
		free(line);
	if (data->mode == FROMFILE)
		close(fd);
	return (EXIT_SUCCESS);
}

