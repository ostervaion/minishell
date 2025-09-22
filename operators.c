/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:08:59 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/06 11:13:53 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_oper(char **opers)
{
	char	*aux;

	(*opers)++;
	if (**opers && (**opers == '<' || **opers == '>'))
		(*opers)++;
	while (*opers && **opers && ft_isspace(**opers))
		(*opers)++;
	aux = *opers;
	while (**opers && !ft_isspace(**opers)
		&& **opers != '<' && **opers != '>')
	{
		if (**opers == '\'' || **opers == '"')
			ft_advance_commed_str(opers);
		else
			(*opers)++;
	}
	aux = ft_substr(aux, 0, *opers - aux);
	return (aux);
}

void	ft_init_oper_vars(char **opers, char **aux3, char **aux, int *i)
{
	*aux3 = NULL;
	*aux = NULL;
	*aux3 = *opers;
	*aux = ft_get_oper(opers);
	*i = 0;
}

int	ft_apply_oper(char **opers, int **fds, int *actual_op, t_mini **mini)
{
	char	*aux;
	int		i;
	char	*aux2;
	char	*aux3;

	ft_init_oper_vars(opers, &aux3, &aux, &i);
	if (!aux)
		return (0);
	if (*aux3 == '<' && *(aux3 + 1) == '<')
		i = ft_heredoc_open(fds, actual_op);
	else
	{
		aux2 = ft_before_expand_values(*mini, aux);
		if (!aux2)
			return (free(aux), 0);
		if (*aux3 == '>' && *(aux3 + 1) == '>')
			i = ft_append(aux2, fds, actual_op);
		else if (*aux3 == '<')
			i = ft_input(aux2, fds, actual_op);
		else if (*aux3 == '>')
			i = ft_redirection(aux2, fds, actual_op);
		free(aux2);
	}
	return (free(aux), i);
}

int	ft_do_opers(t_mini **mini, char *opers, int *fds,
	int (*apply_oper_func)(char **, int **, int *, t_mini **))
{
	int	actual_op;
	int	check;

	check = 1;
	actual_op = 0;
	while (*opers && check)
	{
		while (*opers && ft_isspace(*opers))
			opers++;
		if (*opers == '<' || *opers == '>')
			check = apply_oper_func(&opers, &fds, &actual_op, mini);
		else
			check = 0;
	}
	return (check);
}

int	ft_set_opers(t_mini **mini, t_data *node)
{
	int		i;
	char	*opers;

	opers = node -> oper;
	if (!opers)
		return (1);
	if (!(node -> fds))
	{
		node -> fds = malloc(sizeof(int) * node -> oper_amount);
		if (!node -> fds)
			return (0);
		i = 0;
		while (i < node -> oper_amount)
			(node -> fds)[i++] = -1;
	}
	i = ft_do_opers(mini, opers, node -> fds, ft_apply_oper);
	if (i == 0 && g_child_work == 2)
		printf("Operators failed to be set\n");
	return (i);
}
