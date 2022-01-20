/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:47:48 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/20 01:16:30 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	builtin_cd(const char *path)
{
	if (chdir(path) == 0)
		return (true);
	return (false);
}

int	main(int ac, char **av)
{
	char	*buffer;

	buffer = NULL;
	if (ac != 2)
		return (0);
	printf("Current directory: %s\n", getcwd(buffer, 0));
	free(buffer);
	printf("%d\n", builtin_cd(av[1]));
	printf("Current directory: %s\n", getcwd(buffer, 0));
	free(buffer);
	return (0);
}
