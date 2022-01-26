/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 00:49:29 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/26 21:13:38 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

# define ARR_L 1
# define ARR_R 2
# define D_A_L 3
# define D_A_R 4
# define PIPE 5
# define COMMAND_NOT_FOUND	0

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>

static int						g_exit_status = 0;

typedef struct s_prompt	t_prompt;
typedef struct s_token	t_token;
// extern int				g_exit_status;

/*
 *	Structure to hold all prompt info
 *	> line, given as an input
 *	> linked list of tokenes (parsed commands)
 *	> amount of tokens
 *	> array of strings representing environment variables
 *	> pointer to currently executing command
 */

struct s_prompt
{
	char	*line;
	t_list	*first_token;
	int		token_len;
	char	**env;
	t_token	*current;
};

/*
 *	Structure to hold command token
 *	> array of strings representing the executable name, arguments, etc, like argv
 *	> name of executable
 *	> Bool value is builtin or not
 *	> input file descriptor
 *	> output file descriptor
 *	> pointer to the next token
 */

struct s_token
{
	char	**cmd;
	char	*exec_name;
	bool	is_builtin;
	int		in_fd;
	int		out_fd;
	char	*infile;
	char	*outfile;
	t_token	*next;
};

typedef struct s_pid {
	pid_t			pid;
	int				status;
	struct s_pid	*next;
}	t_pid;

typedef struct s_history {
	char				*str;
	struct s_history	*next;
}	t_history;

/* Splits input by quotes  and whitespaces, returns allocated char[][],
	or NULL, if quote expression is wrong */
char		**ft_split_input(char *str);
/* takes splitted (not NULL) input and replaces variable names by it's values */
char		**ft_extend_vars(char **splitted, char **env);
/* takes replaced list of strings and separates characters < > >> << | */
char		**ft_extract_operators(char **extended, char **env);
/* extract_operators extending function */
char		**copy_n_extract(char **extended, int newtab_size, char **env);
/* extract_operators defining function */
int			get_operator(char *s);
/* checks for arrow and pipe misuse */
int			check_input(char *command_line);

char		*get_bash_var(char *var_to_find, char **env);
void		exec_cmd(t_token *lst, char ***env);
t_token		*add_token(t_token *lst, int in_fd, int out_fd, char **cmd);
void		free_token_list(t_token *lst);
char		*get_full_path(char *cmd);
void		print_error(int code, char *value);
int			ft_len_matrice(char **matrice);
char		*get_cmd_arr(char **cmd, int x, char *output);
bool		is_builtin(char *str);
void		read_that_matrice(char **matrice);
bool		exec(char **cmd_line, char ***env, t_history *history);
char		**ft_matrice_split(char **matrice, char **splitter);
int			find_index_matrice(char **matrice, char **to_find);
int			count_len_matrice(char **matrice);
char		**get_redirection(char **str);
char		*read_from_stdin(char *next_cmd_line);
t_token		*build_lst(char **line);
t_token		*add_lst(t_token *lst, char **cmd, char **redirections);
bool		builtin_cd(char *path, char **env);
int			find_index(const char *str, char c);
char		*get_prompt(void);
void		builtin_pwd(void);
void		exec_buildint(t_token *lst, char ***env);
char		**get_env(char **env);
char		**update_env(char **cmd, char **env);
char		**remove_item_env(char **cmd, char **env);
void		read_export(char **env);
void		read_env(char **env);
bool		builtin_exit(t_token *lst, char ***env, t_history *history);
bool		builtin_echo(char **cmd);
t_history	*add_cmd_line(t_history *cmd, char *to_add);
void		free_history(t_history *history);
t_pid		*add_pid(t_pid *pid, pid_t new_pid);
void		wait_all_pid(t_pid *pid);
void		free_pid(t_pid *pid);
void		set_status(int status);
bool		string_is_separator(char *str, char *separators);

#endif
