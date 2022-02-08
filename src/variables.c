/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:27:12 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/08 22:15:42 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*env_var_found(char **env_var, char *var_name)
{
	char			*to_return;

	if (count_len_matrice(env_var) == 1)
		to_return = NULL;
	else
		to_return = ft_strdup(env_var[1]);
	free_that_matrice(env_var);
	free(var_name);
	return (to_return);
}

char	*get_value_var(char *var)
{
	if (!var)
		return (ft_strdup(""));
	if (ft_strlen(var) > 3)
		return (ft_strtrim(var, "$"));
	if (ft_strlen(var) == 2 && var[0] == '$')
		return (ft_strdup(&var[1]));
	return (ft_strdup(var));
}

char	*get_bash_var(char *var_to_find, char **env)
{
	unsigned int	i;
	char			*var_name;
	char			**env_var;

	if (!env || !var_to_find || var_to_find[1] == '$')
		return (ft_strdup(""));
	if (ft_strcmp(var_to_find, "$?") == 0)
		return (ft_itoa(g_exit_status));
	var_name = get_value_var(var_to_find);
	i = 0;
	while (env[i])
	{
		env_var = ft_split(env[i], '=');
		if (ft_strcmp(env_var[0], var_name) == 0)
			return (env_var_found(env_var, var_name));
		free_that_matrice(env_var);
		i++;
	}
	free(var_name);
	return (ft_strdup(""));
}
