/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:27:12 by sserbin           #+#    #+#             */
/*   Updated: 2022/02/05 16:39:57 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	get_bash_var get a variable as argument (ex: $USER)
	and return the correct value (ex: sserbin)

	0. Check if env is null, in this case return an empty string
	1. Check if it's a var env (should start by $ and the rest only maj + _)
	2. Trim the $ to get the only the var name
	3. Go thought the env, split by = and check if the name is exact
	4. If it's find it, return it, else if just return an empty string
*/

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

char	*get_bash_var(char *var_to_find, char **env)
{
	unsigned int	i;
	char			*var_name;
	char			**env_var;

	if (!env || !var_to_find || var_to_find[1] == '$')
		return (ft_strdup(""));
	if (ft_strcmp(var_to_find, "$?") == 0)
		return (ft_itoa(g_exit_status));
	var_name = ft_strtrim(var_to_find, "$");
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
