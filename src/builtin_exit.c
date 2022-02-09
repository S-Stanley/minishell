/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:51:26 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/10 00:30:59 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_and_free(int exit_code, t_token *lst,
	char ***env, t_history *history)
{
	free_that_matrice(*env);
	free(lst->cmd[1]);
	free_token_list(lst);
	free_history(history);
	if (exit_code == 0)
		close_fds();
	exit(exit_code);
}

int	get_value_i_exit(t_token *lst)
{
	int	i;

	i = 0;
	if (lst->cmd[1][i] == '-')
		i++;
	return (i);
}

bool	check_if_alphanum(t_token *lst, char ***env, t_history *history)
{
	int		i;
	char	*value_err;
	char	*value_err2;

	if (count_len_matrice(lst->cmd) > 2)
	{
		print_error(1, lst->exec_name);
		return (false);
	}
	i = get_value_i_exit(lst);
	while (lst->cmd[1][i])
	{
		if (lst->cmd[1][i] < '0' || lst->cmd[1][i] > '9')
		{
			value_err = ft_strjoin(lst->exec_name, ":");
			value_err2 = ft_strjoin(value_err, lst->cmd[1]);
			print_error(2, lst->exec_name);
			free(value_err2);
			free(value_err);
			exit_and_free(255, lst, env, history);
		}
		i++;
	}
	return (true);
}

bool	builtin_exit(t_token *lst, char ***env, t_history *history, char **cmd)
{
	int	exit_code;

	rl_clear_history();
	free_that_matrice(cmd);
	free(lst->exec_name);
	if (count_len_matrice(lst->cmd) == 1)
		exit_and_free(0, lst, env, history);
	if (!check_if_alphanum(lst, env, history))
		return (false);
	exit_code = ft_atoi(lst->cmd[1]);
	if (exit_code > 255)
		exit_and_free(exit_code - 256, lst, env, history);
	if (exit_code > (255 * 2))
		exit_and_free(exit_code % 256, lst, env, history);
	if (exit_code < 0)
		exit_and_free(256 + exit_code, lst, env, history);
	exit_and_free(exit_code, lst, env, history);
	return (true);
}
