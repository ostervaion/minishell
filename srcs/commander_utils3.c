/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:01:36 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/24 13:34:03 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_builtin(t_data *node)
{
	if (ft_strcmp_custom(node->command, "echo"))
		return (1);
	else if (ft_strcmp_custom(node->command, "cd"))
		return (1);
	else if (ft_strcmp_custom(node->command, "pwd"))
		return (1);
	else if (ft_strcmp_custom(node->command, "env"))
		return (1);
	else if (ft_strcmp_custom(node->command, "export"))
		return (1);
	else if (ft_strcmp_custom(node->command, "unset"))
		return (1);
	else if (ft_strcmp_custom(node->command, "exit"))
		return (1);
	return (0);
}

void	ft_expand_argv_args(t_mini **mini, char **argv)
{
	int		i;
	char	*aux;

	i = 1;
	while (argv[i])
	{
		aux = ft_before_expand_values(*mini, argv[i]);
		free(argv[i]);
		argv[i] = aux;
		i++;
	}
}

void	ft_wait_for_childs(t_mini **mini)
{
	int	pid;
	int	pstatus;

	pstatus = 0;
	ft_close_parent_pipes((*mini)->list);
	while (1)
	{
		pid = waitpid(-1, &pstatus, WUNTRACED | WNOHANG);
		if (pid == -1)
		{
			signal(SIGQUIT, SIG_IGN);
			g_child_work = 0;
			if (errno == ECHILD)
				break ;
			perror("waitpid error\n");
			break ;
		}
		if (WIFEXITED(pstatus))
			(*(*mini)->status) = WEXITSTATUS(pstatus);
		if (SIGTTIN == WSTOPSIG((*(*mini)->status)))
			sigttin_handler(SIGTTIN);
		else if (SIGPIPE == WSTOPSIG((*(*mini)->status)))
			sigpipe_handler(SIGPIPE, pid);
	}
}

void	ft_check_pipes(t_data *node)
{
	if (node -> next_pipefd)
		close(node -> next_pipefd[0]);
	if (node -> prev_pipefd)
		close(node -> prev_pipefd[1]);
}

void	ft_count_comm_str(char **str, int *size, int increase)
{
	if (*str && **str == '"')
	{
		(*str)++;
		while (*str && **str != '"')
			(*str)++;
		if (increase)
			(*size)++;
	}
	else if (*str && **str == '\'')
	{
		(*str)++;
		while (*str && **str != '\'')
			(*str)++;
		if (increase)
			(*size)++;
	}
	if (*str && (**str == '\'' || **str == '"'))
		(*str)++;
}
