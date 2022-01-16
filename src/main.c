/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:25:37 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/16 01:26:19 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <minishell.h>
#include "include/minishell.h"

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	t_prompt prompt;

	// prompt init
	prompt.cmds = NULL;
	prompt.envs = env;
	prompt.cmds_l = 0;



	return (0);
}
