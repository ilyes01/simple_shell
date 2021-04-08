#include "simpleshell.h"

/**
 * is_builtin - function that search if it's builtin
 *
 * @arg: the name of the cmd
 *
 * Return: 1 if it's builtin, 0 otherwise
 **/

int is_builtin(char *arg)
{
	char *names[] = {"env", "exit", "help", NULL};
	int i = 0;

	while (names[i])
	{
		if (!_strcmp(names[i], arg))
		{
			return (1);
		}
		++i;
	}
	return (0);
}

/**
 * do_builtin - function that executes the cmd using builtins
 *
 * @data: the data struct
 * @node: the lav node to execute
 *
 * Return: -1 if error 0 otherwise
 **/

int	do_builtin(data_t *data, cmd_lst_t *node)
{
	char	*names[] = {"env", "exit", "help", NULL};
	int	i = 0;

	int	(*func_p[])(data_t *) = {bi_env, bi_exit, bi_help, NULL};

	while (names[i])
	{
		if (!_strcmp(names[i], node->av[0]))
		{
			return (func_p[i](data));
		}
		++i;
	}
	return (-1);
}

/**
 * do_execve - function that executes the cmd with execve
 * @data: the data structure
 * @node: the lav node to execute
 *
 * Return: 0
 **/
int	do_execve(data_t *data, cmd_lst_t *node)
{
	pid_t		c;
	int		status = 34;

	c = fork();
	wait(&status);
	if (c == 0)
	{
		execve(node->av[0], node->av, data->env);
		return (0);
	}
	node->exe = 1;
	return (0);
}

/**
 * execute - function that executes the cmds
 * @data: the data structure
 * @head: the head of llav linked list
 *
 * Return: -1 if error 0 otherwise
 **/
int	execute(data_t *data, cmd_lst_lst_t **head)
{
	cmd_lst_lst_t	*llav_node;
	cmd_lst_t	*node;

	llav_node = *head;
	while (llav_node)
	{
		node = llav_node->head;
		while (node)
		{
			if (!node->av[0])
				return (-1);
			if (_strchr(node->av[0], '/'))
			{
				if (!node->flag)
					do_execve(data, node);
				else if ((node->flag == '&' && node->prev && node->prev->exe == 1))
					do_execve(data, node);
				else if ((node->flag == '|' && node->prev && node->prev->exe == 0))
					do_execve(data, node);
			}
			else
			{
				if (do_builtin(data, node) == -1)
					return (-1);
			}
			node = node->next;
		}
		llav_node = llav_node->next;
	}
	return (0);
}
