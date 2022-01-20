/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:24:51 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/20 01:50:22 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_lst {
	int		fd_in;
	int		fd_out;
	char	**full_cmd;
}	t_lst;

t_lst	*create_lst(char **cmd, int *redirections)
{
	t_lst	*new;

	new = malloc(sizeof(lst));
	if (!new)
		return (NULL);
	new->fd_in = redirections[0];
	new->fd_out = redirections[1];
	new->full_cmd = cmd;
	new->next = NULL;
	return (new);
}

t_lst	*add_lst(t_lst *lst, char **cmd, int *redirections)
{
	t_lst	*new;
	t_lst	*tmp;

	new = create_lst(redirections, args);
	if (!lst)
		return (new);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (tmp);
}

t_lst	*build_lst(const char **cmd_line)
{
	unsigned int	i;
	t_lst			*lst;
	char			*ptr;

	lst = NULL;
	i = -1;
	while (cmd_line[++i])
	{
		lst = add_lst(lst, full_cmd(&cmd[i]), get_redirection(&cmd_line[i]));
		while (cmd_line[i] && ft_strcmp(cmd_line[i], "|") != 0)
			i++;
	}
	return (lst);
}

void	exec_cmd(void)
{
	return ;
}

void	exec(char **cmd_line)
{
	t_lst	*lst;

	lst = NULL;
	lst = build_lst(lst, cmd_line);
	exec_cmd(lst);
	free(cmd_line);
	free_that_matrice(lst);
}
