/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:14:40 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/10 17:31:59 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_reset_heredoc_fd(int *fd, char *path)
{
	signal(SIGINT, signal_ctrl_c);
	close(*fd);
	*fd = open(path, O_CREAT | O_RDONLY, 00644);
	if (*fd == -1)
		return (0);
	if (unlink(path) == -1)
		return (0);
	return (1);
}

int	ft_heredoc_open(int **fds, int *actual_op)
{
	if (dup2((*fds)[*actual_op], STDIN_FILENO) == -1)
		return (0);
	(*actual_op)++;
	return (1);
}

int	ft_only_heredoc(char **opers, int **fds, int *actual_op, t_mini **mini)
{
	char	*aux;
	int		i;
	char	*aux3;

	(void)mini;
	aux = NULL;
	aux3 = *opers;
	aux = ft_get_oper(opers);
	i = 0;
	if (!aux)
		return (0);
	i = 1;
	if (*aux3 == '<' && *(aux3 + 1) == '<')
		i = ft_heredoc(aux, fds, actual_op);
	else
		(*actual_op)++;
	return (free(aux), i);
}

int	ft_set_heredoc(t_mini **mini)
{
	t_data	*node;
	int		i;

	i = 1;
	node = (*(*mini)->list);
	while (node && i == 1)
	{
		if (node -> oper)
		{
			if (!(node -> fds))
				node -> fds = malloc(sizeof(int) * node -> oper_amount);
			if (!node -> fds)
				return (0);
			i = 0;
			while (i < node -> oper_amount)
				(node -> fds)[i++] = -1;
			i = ft_do_opers(mini, node -> oper, node -> fds, ft_only_heredoc);
		}
		node = node -> next;
	}
	return (i);
}
