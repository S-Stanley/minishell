/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 00:49:29 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/16 00:49:32 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
#define MINISHELL

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

// Commented imports needed `cause of my IDE 
//# include <libft.h>
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_prompt t_prompt;
typedef struct s_token t_token;

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
	t_list	*tokens;
	int		tokens_l;
	char	**envs;
	t_token	*current;
};

/*
 *	Structure to hold command token
 *	> array of strings representing the executable name,
 *		arguments, etc
 *	> input file descriptor
 *	> output file descriptor
 */

struct s_token
{
	char	**cmd;
	int		in_fd;
	int		out_fd;
};

#endif
