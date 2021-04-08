#include "simpleshell.h"

/**
 * bi_help - the help builtin
 *
 * @data: the data_t struct
 *
 * Return: 0
 */

int bi_help(data_t *data)
{
	char *arg = data->llav_head->head->av[1];

	if (!arg)
	{
		_puts("exit [STATUS]\nenv\nhelp [COMMAND]\n");
		return (0);
	}

	if (!_strcmp(arg, "exit"))
	{
		_puts("exit: exit [STATUS]\n");
		_puts("\n\tTerminate the shell process. If STATUS is given it is");
		_puts("\n\tused as the exit status of the shell, otherwise the exit");
		_puts("\n\tstatus of the preceding command is used.\n");
	}
	else if (!_strcmp(arg, "env"))
	{
		_puts("env:\n\n\tPrints the current environment of the shell\n");
	}
	else if (!_strcmp(arg, "help"))
	{
		_puts("help: help [COMMAND]\n");
		_puts("\n\tPrints this command. If a COMMAND is given as parameter,");
		_puts("\n\tprints the usage and description of the builtin COMMAND.\n");
	}
	return (0);
}
