/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:18:35 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/23 17:16:51 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_pwd(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 100);
	buffer = getcwd(buffer, 100);
	printf("%s\n", buffer);
	free(buffer);
}
