/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:22:26 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/17 19:22:28 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *get_var_name(char *str)
{
	char	*v_name;
	int		v_len;

	v_len = 1;
	if (ft_isdigit(str[v_len]) || str[v_len] == '$' || str[v_len] == '?')
	{
		v_name = ft_strdup("$$");
		if (ft_isdigit(str[v_len]))
			v_name[1] = str[v_len];
		if (str[v_len] == '?')
			v_name[1] = '?';
		return (v_name);
	}
	while (ft_isalnum(str[v_len]) || str[v_len] == '_')
		v_len++;
	v_name = malloc(sizeof(char) * (v_len + 1));
	v_name[0] = '$';
	v_len = 1;
	while (ft_isalnum(str[v_len]) || str[v_len] == '_')
	{
		v_name[v_len] = str[v_len];
		v_len++;
	}
	v_name[v_len] = '\0';
	return (v_name);
}

static char	*before_and_val(char **s, char **env, int dollar_sign)
{
	char	*new_str;
	char	*v_value;
	char	*v_name;
	int		new_len;

	v_name = get_var_name(*s + dollar_sign);
	v_value = get_bash_var(v_name, env);
	new_len = dollar_sign + ft_strlen(v_value);
	new_str = malloc(sizeof(char) * (new_len + 1));
	new_len = 0;
	while (new_len < dollar_sign)
	{
		new_str[new_len] = (*s)[new_len];
		new_len++;
	}
	*s += new_len + ft_strlen(v_name);
	free(v_name);
	dollar_sign = 0;
	while (v_value[dollar_sign])
		new_str[new_len++] = v_value[dollar_sign++];
	new_str[new_len] = '\0';
	free(v_value);
	return (new_str);
}

static void		add_append(char *tmp_str, char **new_str)
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

static char		*process_line(char *s, char **env)
{
	char	*tmp_str;
	char	*new_str;
	int		i;

	new_str = NULL;
	while (1)
	{
		i = 0;
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] == '$')
		{
			tmp_str = before_and_val(&s, env, i);
			add_append(tmp_str, &new_str);
		}
		else if (!s[i])
		{
			tmp_str = ft_strjoin(new_str, s);
			free(new_str);
			new_str = tmp_str;
			break;
		}
	}
	return (new_str);
}

char		**ft_extend_vars(char **splitted, char **env)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (splitted[i])
	{
		j = 0;
		while (splitted[i][j] && splitted[i][0] != '\'' && splitted[i][j] != '$')
			j++;
		if (splitted[i][0] != '\'' && splitted[i][j] == '$')
		{
			new_line = process_line(splitted[i], env);
			free(splitted[i]);
			splitted[i] = new_line;
		}
		i++;
	}
	return (splitted);
}
