/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:22:26 by rokupin           #+#    #+#             */
/*   Updated: 2022/02/05 22:30:26 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*before_and_val(char **s, char **env, int dollar_sign, int old_len)
{
	char	*new_str;
	char	*v_value;
	char	*v_name;
	int		new_len;

	v_name = get_var_name(*s + dollar_sign);
	v_value = get_bash_var(v_name, env);
	new_len = dollar_sign - old_len + ft_strlen(v_value);
	new_str = malloc(sizeof(char) * (new_len + 1));
	new_len = 0;
	while ((*s)[old_len] && !((*s)[old_len] == '$' && to_expand(*s, old_len)))
	{
		new_str[new_len] = (*s)[old_len];
		new_len++;
		old_len++;
	}
	(*s)[dollar_sign] = -1;
	free(v_name);
	dollar_sign = 0;
	while (v_value[dollar_sign])
		new_str[new_len++] = v_value[dollar_sign++];
	new_str[new_len] = '\0';
	free(v_value);
	return (new_str);
}

static void	add_append(char *tmp_str, char **new_str)
{
	char	*old_str;

	if (*new_str == NULL)
		*new_str = ft_strdup(tmp_str);
	else
	{
		old_str = *new_str;
		*new_str = ft_strjoin(old_str, tmp_str);
		free(old_str);
	}
	free(tmp_str);
}

static void	handle_endline(char **tmp_str, char **new_str, char *s)
{
	*tmp_str = ft_strjoin(*new_str, s);
	free(*new_str);
	*new_str = *tmp_str;
}

static char	*process_line(char *s, char **env)
{
	char		*tmp_str;
	char		*new_str;
	int			i;
	static int	prv;

	new_str = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && !(s[i] == '$' && s[i + 1] != '$' && to_expand(s, i)))
			i++;
		if (s[i] == '$' && to_expand(s, i))
		{
			tmp_str = before_and_val(&s, env, i, prv);
			prv = get_varname_len(s + i) + i;
			add_append(tmp_str, &new_str);
		}
		else if (!s[i])
		{
			handle_endline(&tmp_str, &new_str, s + prv);
			prv = 0;
		}
	}
	return (new_str);
}

char	**ft_extend_vars(char **spl, char **env)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (spl[i])
	{
		j = 0;
		handle_tilda(spl, i, env);
		while (spl[i][j] && !(spl[i][j] == '$'
			&& spl[i][j + 1] != '$' && to_expand(spl[i], j)))
			j++;
		if (spl[i][j] == '$' && spl[i][j + 1] != '$' && to_expand(spl[i], j))
		{
			new_line = process_line(spl[i], env);
			free(spl[i]);
			spl[i] = new_line;
		}
		i++;
	}
	return (spl);
}
