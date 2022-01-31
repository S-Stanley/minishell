/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 00:32:02 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/01 00:33:23 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_outfile(t_token *lst)
{
	int	outfile;

	if (lst->append)
		outfile = open(lst->outfile,
				O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		outfile = open(lst->outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
	return (outfile);
}

char	*get_fd(char *filename)
{
	if (!filename)
		return (ft_strdup(""));
	return (ft_strdup(filename));
}
