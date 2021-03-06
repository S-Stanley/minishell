/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:24:51 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/08 22:43:21 by sserbin          ###   ########.fr       */
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

void	err_child(t_pid *pid, t_token *tmp)
{
	free_pid(pid);
	free_token_light(tmp);
	exit(127);
}

bool	create_all_files(char **line)
{
	unsigned int	i;
	int				fd;
	char			*file_n;

	i = 0;
	while (line[i])
	{
		if (ft_strcmp(line[i], "|") == 0)
			break ;
		file_n = line[i + 1];
		if ((!ft_strcmp(line[i], ">") || !ft_strcmp(line[i], ">>")) && file_n)
		{
			file_n = get_unq_copy(line[i + 1]);
			fd = open(file_n, O_RDWR | O_CREAT, 0777);
			if (fd == -1)
			{
				printf("%s\n", strerror(errno));
				return (false);
			}
			close(fd);
			free(file_n);
		}
		i++;
	}
	return (true);
}

bool	what_to_exec(t_token *lst, char ***env, t_history *history, char **cmd)
{
	if (count_len_matrice(lst->cmd) == 0)
		return (true);
	if (ft_strcmp(lst->cmd[0], "export") == 0 && lst->cmd[1])
		*env = export_something(env, cmd, lst);
	else if (ft_strcmp(lst->cmd[0], "unset") == 0)
	{
		*env = remove_item_env(lst->cmd, *env);
		if (lst->next)
			exec_cmd(lst->next, env, cmd);
	}
	else if (ft_strcmp(lst->cmd[0], "cd") == 0)
	{
		builtin_cd(lst->cmd[1], *env);
		if (lst->next)
			exec_cmd(lst->next, env, cmd);
	}
	else if (ft_strcmp(lst->cmd[0], "exit") == 0)
		builtin_exit(lst, env, history, cmd);
	else
		exec_cmd(lst, env, cmd);
	return (true);
}

bool	exec(char **cmd_line, char ***env, t_history *history)
{
	t_token	*lst;

	g_exit_status = 0;
	lst = NULL;
	lst = build_lst((char **)cmd_line, *env);
	if (!lst)
		return (false);
	if (g_exit_status != 130)
		what_to_exec(lst, env, history, cmd_line);
	free_token_light(lst);
	return (true);
}
