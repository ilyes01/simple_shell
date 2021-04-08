#ifndef SIMPLESHELL_H
#define SIMPLESHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 1024

#define INTERACTIVE 0
#define NONINTERACTIVE 1
#define FROMFILE 2

/**
  * struct cmd_lst_s - the list of logic op cutted cmd
  * @cmd: the logic op cutted cmd
  * @av: the whitespace cutted cmd
  * @exe: a boolean to know if this command was executed or not
  * @flag: the logical operator delimeter of this cmd
  * @next: the next elem in the ll
  * @prev: the previous elem in the ll
  **/

typedef struct			cmd_lst_s
{
	char			*cmd;
	char			**av;
	int			exe;
	char			flag;
	struct cmd_lst_s	*next;
	struct cmd_lst_s	*prev;
}				cmd_lst_t;

/**
  * struct cmd_lst_lst_s - the list of control op cutted list of cmd
  * @list: the former string
  * @head: the first elem of it' s cmd_lst_s ll
  * @next: the next elem in the ll
  **/

typedef struct	cmd_lst_lst_s
{
		char			*list;
		cmd_lst_t		*head;
		struct cmd_lst_lst_s	*next;
}					cmd_lst_lst_t;

int	add_cmd_lst(char *cmd, cmd_lst_t **head, char flag);
int	strsplit(cmd_lst_lst_t *llav, char *str);

/**
 * struct data_s - the data structure
 *
 * @env: environment
 * @mode: interactive, non interactive or from file
 * @bash: the argv[0]
 * @alias: the aliases
 * @line: the address of the getline line
 * @lines: index of the executed line
 * @llav_head: the head of the llav linked list
 */

typedef struct data_s
{
	char **env;
	char **alias;
	char **line;
	int mode;
	int lines;
	char *bash;
	cmd_lst_lst_t *llav_head;
} data_t;

/* MAIN */
int sh_start(data_t *data, int fd);
void stop_signal_handler(int signum);

/* BUILTINS */
int bi_env(data_t *data);
int bi_exit(data_t *data);
int bi_help(data_t *data);

/* EXECUTE */
int is_builtin(char *arg);
int do_builtin(data_t *data, cmd_lst_t *node);
int do_execve(data_t *data, cmd_lst_t *node);
int execute(data_t *data, cmd_lst_lst_t **head);

/* EXPANSION */
int expansion(data_t *data, cmd_lst_lst_t **head);
void expansion_path(char **arg, char *path_var);
char *parse_env_var(char *s, char **env);
char *expansion_alias(char *var, char **als);
void expansion_var_alias(char **av, data_t *data);

/* FREE_LISTS */
int free_av(char **av);
void free_cmd_lst(cmd_lst_t *node);
void free_cmd_lst_lst(cmd_lst_lst_t *llav);
int free_all(cmd_lst_lst_t **head);

/* PARSER */
int add_cmd_lst(char *cmd, cmd_lst_t **head, char flag);
int add_cmd_lst_lst(char *list, cmd_lst_lst_t **head);
int parse_logic_op(cmd_lst_lst_t **llav_head);
int parse_ctrl_op(char *input, cmd_lst_lst_t **head);
int parser(char *input, cmd_lst_lst_t **llav_head);

/* SH_GETLINE  */
int sh_getline(char **line, int fd);

/* UTIL_DATA */
data_t *sh_data_new(char **argv, char **env);
void *sh_data_delete(data_t *data);

/* UTIL_ENV */
char **sh_get_env(char **env);
void sh_delete_env(char **env);
char *sh_get_env_var(char *var, char **env);

/* UTIL_MEM */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* UTIL_STR */
int _puts(char *str);
int _strlen(char *str);
char *_strdup(char *str);
const char *_strchr(const char *s, char c);
char **strtoav(char *str, const char *delim);
int	_strcmp(char *s1, char *s2);
char *_strndup(char *str, int n);
char *str_concat(char *s1, char *s2);
char *c_concat(char *s, char c);

#endif /* SIMPLESHELL_H */
