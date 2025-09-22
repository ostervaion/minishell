/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:20:25 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/24 19:27:05 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_coms(int coms, int coms2)
{
	if (coms % 2 == 0 || coms2 % 2 == 0)
		return (0);
	return (1);
}

void	ft_add_to_coms(int *coms, int *coms2, char c)
{
	if (c == '\'' && *coms2 % 2 == 0)
		*coms += 1;
	else if (c == '"' && *coms % 2 == 0)
		*coms2 += 1;
}

int	ft_substr_join_to_str(char	*initialstr, int endofstr, char **strtojoin)
{
	char	*aux;
	char	*aux2;

	aux = NULL;
	aux2 = NULL;
	if (endofstr == 0)
		return (1);
	aux = ft_substr(initialstr, 0, endofstr);
	if (!aux)
		return (0);
	if (*strtojoin)
		aux2 = ft_strjoin(*strtojoin, aux);
	else
		aux2 = ft_strdup(aux);
	if (!aux2)
		return (free(aux), 0);
	if (*strtojoin)
		free(*strtojoin);
	free(aux);
	*strtojoin = aux2;
	return (1);
}

void	ft_add_node_back(t_data **list, t_data *node)
{
	t_data	*aux;

	aux = *list;
	while (aux -> next != NULL)
		aux = aux -> next;
	aux -> next = node;
}

void	ft_add_to_oper_with_comms(t_data *node, char *aux,
		char **str, int *check_error)
{
	char	c;

	c = **str;
	(*str)++;
	while (**str && **str != c)
		(*str)++;
	*check_error = ft_substr_join_to_str(aux, *str - aux + 1, &(node -> oper));
	if (*check_error)
		node -> oper_amount++;
	(*str)++;
}
