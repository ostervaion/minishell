/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:25:43 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/17 15:31:01 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_end_data_insertion(char *aux, char *str, char **aux2,
		t_data *node)
{
	int	check_error;

	check_error = 1;
	check_error = ft_substr_join_to_str(aux, str - aux, aux2);
	if (!check_error && *aux2)
		free(*aux2);
	else if (check_error)
		ft_add_new_data(node, aux2);
	return (check_error);
}

void	ft_loop_data_insertion(t_data *node, char **str, int *check_error)
{
	char	*aux;
	char	*aux2;

	aux2 = NULL;
	aux = *str;
	while (**str && !ft_isspace(**str) && *check_error)
	{
		while (**str && !ft_isspace(**str) && !(**str == '<' || **str == '>')
			&& !(**str == '\'' || **str == '"'))
			(*str)++;
		if (**str && (**str == '<' || **str == '>'))
		{
			*check_error = ft_substr_join_to_str(aux, *str - aux, &aux2);
			if (!*check_error)
				return ;
			ft_add_to_oper(node, str, check_error);
			if (!*check_error)
				continue ;
			aux = *str;
		}
		if (**str && (**str == '\'' || **str == '"'))
			ft_advance_commed_str(str);
	}
	if (*check_error)
		*check_error = ft_end_data_insertion(aux, *str, &aux2, node);
}

void	ft_check_error_oper(char **str, int *check_error)
{
	char	c;
	int		oper_amount;

	oper_amount = 0;
	c = **str;
	while (**str && !ft_isspace(**str) && c == **str)
	{
		oper_amount++;
		(*str)++;
	}
	*check_error = !(oper_amount > 2 || !**str);
}

int	ft_add_new_data(t_data *node, char **str)
{
	char	*aux;

	if (node -> command)
	{
		if (node -> arg)
		{
			aux = ft_strjoin(node -> arg, " ");
			if (!aux)
				return (0);
			free(node -> arg);
			node -> arg = aux;
			aux = ft_strjoin(aux, *str);
			if (!aux)
				return (0);
			free(node -> arg);
			node -> arg = aux;
			free(*str);
		}
		else
			node -> arg = *str;
	}
	else
		node -> command = *str;
	return (1);
}

int	ft_oper_found(t_data *node, char **str, char **aux, int *check_error)
{
	char	*aux2;

	aux2 = *str;
	ft_add_to_oper(node, str, check_error);
	if (!*check_error)
		return (0);
	*aux = ft_substr(*aux, 0, aux2 - *aux);
	if (!aux)
		return (0);
	*check_error = ft_add_new_data(node, aux);
	if (!*check_error)
		return (free(*aux), 0);
	*aux = *str;
	if (*check_error)
		return (1);
	else
		return (0);
}
