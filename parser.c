#include "simpleshell.h"

/**
  * add_cmd_lst - create a lav node and add it to the linked list
  * @cmd: the string of the node
  * @head: the address of the forst elem of lav ll
  * @flag: the logical operator delimiter
  *
  * Return: -1 if error 1 otherwise
  **/
int	add_cmd_lst(char *cmd, cmd_lst_t **head, char flag)
{
	cmd_lst_t	*node;
	cmd_lst_t	*buf = 0;

	node = (cmd_lst_t *)malloc(sizeof(cmd_lst_t));
	if (!node)
		return (-1);
	node->cmd = cmd;
	node->av = strtoav(cmd, " \t");
	node->exe = 0;
	node->flag = flag;
	node->next = NULL;
	buf = *head;
	if (buf)
	{
		while (buf->next)
			buf = buf->next;
		buf->next = node;
		node->prev = buf;
	}
	else
	{
		*head = node;
		node->prev = NULL;
	}
	return (1);
}

/**
  * add_cmd_lst_lst - create a llav node and add it to the linked list
  * @list: the string of the node
  * @head: the address of the forst elem of llav ll
  *
  * Return: -1 if error 1 otherwise
  **/
int	add_cmd_lst_lst(char *list, cmd_lst_lst_t **head)
{
	cmd_lst_lst_t	*node;
	cmd_lst_lst_t	*buf;

	node = (cmd_lst_lst_t *)malloc(sizeof(cmd_lst_lst_t));
	if (!node)
		return (-1);
	node->list = list;
	node->head = NULL;
	node->next = NULL;
	buf = *head;
	if (buf)
	{
		while (buf->next)
			buf = buf->next;
		buf->next = node;
	}
	else
		*head = node;
	return (1);
}

/**
  * parse_logic_op - cut the substrings at "&&" and "||"
  * @llav_head: the address of the forst elem of llav ll
  *
  * Return: -1 if error 1 otherwise
  **/
int	parse_logic_op(cmd_lst_lst_t **llav_head)
{
	cmd_lst_lst_t	*node;

	if (!llav_head)
		return (-1);
	node = *llav_head;
	while (node)
	{
		strsplit(node, node->list);
		node = node->next;
	}
	return (1);
}

/**
  * parse_ctrl_op - cut the string at ';'
  * @input: the input string
  * @head: the address of the forst elem of llav ll
  *
  * Return: -1 if error 1 otherwise
  **/
int	parse_ctrl_op(char *input, cmd_lst_lst_t **head)
{
	char	**lists;
	int	i = 0;

	lists = strtoav(input, ";\n");
	if (!lists)
		return (-1);
	while (lists[i])
	{
		add_cmd_lst_lst(lists[i], head);
		++i;
	}
	free(lists);
	return (1);
}

/**
  * parser - takes a string as input and output a llav linked list
  * @input: the input string
  * @llav_head: the address of the forst elem of llav ll
  *
  * Return: -1 if error 1 otherwise
  **/
int	parser(char *input, cmd_lst_lst_t **llav_head)
{
	cmd_lst_lst_t	*llav_node;
	cmd_lst_t	*node;

	if (!input)
		return (-1);
	if (parse_ctrl_op(input, llav_head) == -1)
		return (-1);
	if (parse_logic_op(llav_head) == -1)
		return (-1);
	llav_node = *llav_head;
	while (llav_node)
	{
		node = llav_node->head;
		while (node)
		{
			if (!node->av || !node->av[0])
			{
				free_all(llav_head);
				return (-1);
			}
			node = node->next;
		}
		llav_node = llav_node->next;
	}
	return (1);
}
