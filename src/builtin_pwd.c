/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:18:35 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/22 18:30:13 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(buffer, -1);
	printf("%s\n", buffer);
	free(buffer);
}
