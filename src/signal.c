/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 01:39:16 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/04 01:45:22 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signal(void)
{
	signal(SIGINT, exit_handler);
	signal(SIGQUIT, exit_handler);
}

void	exit_handler(int signum)
{
	if (signum == SIGQUIT)
		return ;
	wait(&g_exit_status);
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	if (g_exit_status != SIGINT)
		rl_redisplay();
	g_exit_status = 130;
}
