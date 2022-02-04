/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 01:39:16 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/04 01:39:40 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signal(void)
{
	struct sigaction	sa_signal;

	sa_signal.sa_sigaction = exit_handler;
	sigaction(SIGINT, &sa_signal, NULL);
	sigaction(SIGQUIT, &sa_signal, NULL);
}

void	exit_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == 3)
		return ;
	g_exit_status = 130;
	rl_redisplay();
	printf("\n");
	if (info->si_pid == 0)
		printf("minishell2> ");
}
