/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 00:49:29 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/20 01:08:50 by sserbin          ###   ########.fr       */
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

typedef struct s_prompt	t_prompt;
typedef struct s_token	t_token;

/*
 *	Structure to hold all prompt info
 *	> line, given as an input
 *	> linked list of tokens (parsed commands)
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
	int		exit_status;
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
	t_token	*next;
};

/* Splits input by quotes  and whitespaces, returns allocated char[][], or NULL, if quote expression is wrong */
char	**ft_split_input(char *str);
/* takes splitted (not NULL) input and replaces variable names by it's values */
char	**ft_extend_vars(char **splitted, char **env);
/* takes replaced list of strings and separates characters < > >> << | */
char	**ft_extract_operators(char **extended);
/* extract_operators extending function */
char	**copy_n_extract(char **extended, int newtab_size);
/* extract_operators defining function */
int		get_operator(char *s);

char	*get_bash_var(char *var_to_find, char **env);
void	exec_cmd(t_token *lst, char **env, int *exit_status);
t_token	*add_token(t_token *lst, int in_fd, int out_fd, char **cmd);
void	free_token_list(t_token *lst);
void	parse_and_exec(char	**output, char **env, int *exit_status);
char	*get_full_path(char *cmd);
void	print_error(int code, char *value, int *exit_status);
int		ft_len_matrice(char **matrice);
char	*get_cmd_arr(char **cmd, int x, char *output, int *exit_status);
bool	is_builtin(char *str);
void	read_that_matrice(char **matrice);

#endif
