/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:41:00 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/24 13:57:34 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char ***splited)
{
	int	i;

	i = 0;
	while (*splited && (*splited)[i])
		free((*splited)[i++]);
	if (*splited)
	{
		free(*splited);
		*splited = NULL;
	}
}

//función para limpiar la lista y sus nodos,
//discutir los posibles usos antes de implementar
void	ft_clear_list_and_exit(t_data **list, char *str)
{
	t_data	*aux;
	t_data	*aux2;

	if (str)
		printf("%s", str);
	if (!list || !*list)
		return ;
	aux = *list;
	ft_close_parent_pipes(list);
	while (aux)
	{
		aux2 = aux;
		if (aux -> command)
			ft_free_and_null((void **)(&(aux -> command)));
		if (aux -> arg)
			ft_free_and_null((void **)(&(aux -> arg)));
		if (aux -> oper)
			ft_free_and_null((void **)(&(aux -> oper)));
		if (aux -> fds)
			ft_close_fds(&(aux -> fds), aux -> oper_amount);
		aux = aux -> next;
		free(aux2);
	}
	*list = NULL;
}

void	ft_clear_all(t_mini **mini, char *str, int status)
{
	if (!*mini)
		exit(status);
	if ((*mini)->env_copy)
		ft_free_split(&((*mini)->env_copy));
	if ((*mini)->prompt)
		free((*mini)->prompt);
	if ((*mini)->status)
		free((*mini)->status);
	if ((*mini)->line)
		free((*mini)->line);
	if ((*mini)->list)
	{
		if ((*(*mini)->list))
			ft_clear_list_and_exit((*mini)->list, NULL);
		free((*mini)->list);
	}
	free(*mini);
	rl_clear_history();
	if (str)
		printf("%s\n", str);
	exit(status);
}

void	ft_close_and_free_pipe(int **fd)
{
	int	*aux;

	aux = *fd;
	if (aux)
	{
		close(aux[0]);
		close(aux[1]);
		*fd = NULL;
	}
}

void	ft_close_parent_pipes(t_data **list)
{
	t_data	*aux;

	aux = *list;
	while (aux)
	{
		if (aux -> prev_pipefd)
			ft_close_and_free_pipe(&(aux -> prev_pipefd));
		if (aux -> next_pipefd)
			ft_close_and_free_pipe(&(aux -> next_pipefd));
		aux = aux -> next;
	}
}
