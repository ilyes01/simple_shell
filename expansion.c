#include "simpleshell.h"

/**
 * expansion - handles all expansions and replacement functions
 *
 * @data: the data_t structure
 * @head: the cmd_lst_lst head
 *
 * Return: an int
 */

int expansion(data_t *data, cmd_lst_lst_t **head)
{
	cmd_lst_lst_t   *llav_head = *head;
	cmd_lst_t *node;
	int i = 0, j = 0;
	char *path_var = NULL;

	while (llav_head)
	{
		node = (llav_head->head);
		j = 0;
		while (node)
		{
			if (!node->av[0])
				return (-1);
			path_var = sh_get_env_var("PATH", data->env);
			expansion_var_alias(node->av, data);
			if (_strchr(node->av[0], '.') == NULL)
				expansion_path(&node->av[0], path_var);
			if (path_var)
				free(path_var);
			node = node->next;
			++j;
		}
		llav_head = llav_head->next;
		++i;
	}
	return (0);
}

