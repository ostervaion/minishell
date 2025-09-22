/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:40:12 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/17 15:30:58 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_to_oper(t_data *node, char **str, int *check_error)
{
	char	*aux;

	aux = *str;
	ft_check_error_oper(str, check_error);
	while (*check_error && **str && ft_isspace(**str))
		(*str)++;
	if (**str == '>' || **str == '<' || !**str)
		*check_error = 0;
	if (**str == '\'' || **str == '"')
		return (ft_add_to_oper_with_comms(node, aux, str, check_error));
	while (*check_error && **str && !ft_isspace(**str)
		&& (**str != '\'' && **str != '"' && **str != '>' && **str != '<'))
		(*str)++;
	if (!*check_error)
		return ;
	*check_error = ft_substr_join_to_str(aux, *str - aux, &(node -> oper));
	if (*check_error)
		node -> oper_amount++;
}

char	*ft_add_commed_data(char **str, int *coms, int *coms2, int *check_error)
{
	char	*aux;

	aux = *str;
	while (**str && !ft_check_coms(*coms, *coms2))
	{
		(*str)++;
		ft_add_to_coms(coms, coms2, **str);
	}
	if (*str - aux > 1)
		aux = ft_substr(aux, 0, *str - aux);
	else
		aux = NULL;
	if (!aux)
		*check_error = 0;
	return (aux);
}

char	*ft_add_noncommed_data(t_data *node, char **str, int *check_error)
{
	char	*aux;
	char	*aux2;
	int		export;

	export = ft_strcmp_custom(node -> command, "export");
	aux = *str;
	aux2 = 0;
	while (**str && !ft_isspace(**str) && (**str != '\'' || **str != '"'))
	{
		if (!export && (**str == '<' || **str == '>'))
			*check_error = ft_oper_found(node, str, &aux, check_error);
		else
			(*str)++;
	}
	return (ft_substr(aux, 0, *str - aux));
}

//conjunto de funciones para añadir información al nodo
int	ft_insert_data_to_node(t_data *node, char *str)
{
	int		check_error;
	char	*aux;

	check_error = 1;
	aux = NULL;
	while (*str && check_error)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str)
			ft_loop_data_insertion(node, &str, &check_error);
	}
	return (check_error);
}

//Función para crear un nuevo nodo de la lista,
//a la vez que la llena de información y la añade a la lista como nuevo
//primer elemento
int	ft_new_node(t_data **list, char *str)
{
	t_data	*node;

	node = (t_data *) malloc (sizeof(t_data));
	if (!node)
		return (ft_clear_list_and_exit(list, str), 0);
	node -> prev_pipefd = NULL;
	node -> next_pipefd = NULL;
	node -> next = NULL;
	node -> oper_amount = 0;
	node -> arg = NULL;
	node -> oper = NULL;
	node -> fds = NULL;
	node -> command = NULL;
	if (!ft_insert_data_to_node(node, str))
		return (ft_clear_list_and_exit(list, "Syntax error\n"), 0);
	if (!*list)
		*list = node;
	else
		ft_add_node_back(list, node);
	return (1);
}
