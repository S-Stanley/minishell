/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:11:58 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/07 21:12:40 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_prompt(void)
{
	char	*prompt;
	char	*cwd;

	cwd = malloc(sizeof(char) * 100);
	if (!cwd)
		return ;
	cwd = getcwd(cwd, 100);
	prompt = ft_strjoin(cwd, "> ");
	free(cwd);
	if (!prompt)
		return ;
	write(1, prompt, ft_strlen(prompt));
	free(prompt);
}
