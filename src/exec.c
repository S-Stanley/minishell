/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:24:51 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/30 19:23:53 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_splitter(void)
{
	char	**splitter;

	splitter = malloc(sizeof(char **) * 6);
	splitter[0] = "|";
	splitter[1] = "<";
	splitter[2] = "<<";
	splitter[3] = ">";
	splitter[4] = ">>";
	splitter[5] = 0;
	return (splitter);
}

char	**full_cmd(char **str)
{
	char	**to_return;
	char	**to_split;

	to_split = get_splitter();
	to_return = ft_matrice_split(str, to_split);
	free(to_split);
	if (to_return[0] == 0 || to_return[0][0] == 0)
	{
		free_that_matrice(to_return);
		return (NULL);
	}
	return (to_return);
}

void	read_lst(t_token *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			printf("%s ", lst->cmd[i]);
			i++;
		}
		printf("in %s out %s %d", lst->infile, lst->outfile, lst->is_builtin);
		printf("\n");
		lst = lst->next;
	}
}

bool	create_all_files(char **line)
{
	unsigned int	i;
	int				fd;

	i = 0;
	while (line[i])
	{
		if (ft_strcmp(line[i], "|") == 0)
			break ;
		if ((ft_strcmp(line[i], ">") == 0 || ft_strcmp(line[i], ">>") == 0)
			&& line[i + 1])
		{
			fd = open(line[i + 1], O_RDWR | O_CREAT, 0777);
			if (fd == -1)
			{
				printf("%s\n", strerror(errno));
				return (false);
			}
			close(fd);
		}
		i++;
	}
	return (true);
}

t_token	*build_lst(char **line, char **env)
{
	unsigned int	i;
	t_token			*lst;

	lst = NULL;
	i = 0;
	while (line[i])
	{
		create_all_files(&line[i]);
		lst = add_lst(lst, full_cmd(&line[i]), get_redirection(&line[i]), env);
		if (!lst)
			return (NULL);
		while (line[i] && ft_strcmp(line[i], "|") != 0)
			i++;
		while (ft_strcmp(line[i], "|") == 0)
			i++;
	}
	return (lst);
}

bool	what_to_exec(t_token *lst, char ***env, t_history *history)
{
	if (count_len_matrice(lst->cmd) == 0)
		return (true);
	if (ft_strcmp(lst->cmd[0], "export") == 0 && lst->cmd[1])
	{
		*env = update_env(lst->cmd, *env);
		exec_cmd(lst, env);
	}
	else if (ft_strcmp(lst->cmd[0], "unset") == 0)
	{
		*env = remove_item_env(lst->cmd, *env);
		if (lst->next)
			exec_cmd(lst->next, env);
	}
	else if (ft_strcmp(lst->cmd[0], "cd") == 0)
	{
		builtin_cd(lst->cmd[1], *env);
		if (lst->next)
			exec_cmd(lst->next, env);
	}
	else if (ft_strcmp(lst->cmd[0], "exit") == 0)
		builtin_exit(lst, env, history);
	else
		exec_cmd(lst, env);
	return (true);
}

t_token	*unquote_lst(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (lst)
	{
		lst->cmd = unquote(lst->cmd);
		lst = lst->next;
	}
	return (tmp);
}

bool	exec(char **cmd_line, char ***env, t_history *history)
{
	t_token	*lst;

	lst = NULL;
	lst = build_lst((char **)cmd_line, *env);
	if (!lst)
		return (false);
	lst = unquote_lst(lst);
	what_to_exec(lst, env, history);
	free_token_list(lst);
	return (true);
}
