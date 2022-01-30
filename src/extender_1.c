/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:33:03 by rokupin           #+#    #+#             */
/*   Updated: 2022/01/29 16:33:05 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int to_expand(char *line, int index)
{
	int	i;

	i = 0;
	while (i <= index)
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"' && i < index)
				i++;
			if (i >= index)
				return (1);
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'' && i < index)
				i++;
			if (i >= index)
				return (0);
		}
		else
		{
			if (i >= index)
				return (1);
		}
		i++;
	}
	return 0;
}

char *get_var_name(char *str)
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

int	get_varname_len(char *str)
{
	char	*varname;
	int		len;

	varname = get_var_name(str);
	len = ft_strlen(varname);
	free(varname);
	return (len);
}
/*
echo "$USER"123'$USER'
echo "$USER"123"$HOME"
echo $USER'$USER'"$USER"
echo "$USER"
echo $USER
echo ""$USER""
echo "'"$USER"'"
echo "'$USER'"
echo '"$USER"'
echo '"$USER"$USER'
echo "'"$USER"$USER"
echo '"'$USER'"'
echo '''$USER'''
echo '"'"'$USER'"'"'
echo '"''$USER''"'
echo '"''$USER''"$USER'
echo '"''$USER''$USER'
echo '"''$USER'"'"$USER'
echo '"''$USER'"'"$USER"'"
*/