/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:51:26 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/23 11:23:14 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_if_alphanum(t_token *lst)
{
	int		i;
	char	*value_err;
	char	*value_err2;

	if (count_len_matrice(lst->cmd) > 2)
	{
		print_error(1, lst->exec_name);
		return (false);
	}
	i = 0;
	while (lst->cmd[1][i])
	{
		if (lst->cmd[1][i] < '0' || lst->cmd[1][i] > '9')
		{
			value_err = ft_strjoin(lst->exec_name, ":");
			value_err2 = ft_strjoin(value_err, lst->cmd[1]);
			print_error(2, lst->exec_name);
			free(value_err2);
			free(value_err);
			exit(255);
		}
		i++;
	}
	return (true);
}

bool	builtin_exit(t_token *lst)
{
	int	exit_code;

	if (count_len_matrice(lst->cmd) == 1)
		exit(0);
	if (!check_if_alphanum(lst))
		return (false);
	exit_code = ft_atoi(lst->cmd[1]);
	if (exit_code > 255 || exit_code < 0)
		exit(2);
	exit(exit_code);
}
