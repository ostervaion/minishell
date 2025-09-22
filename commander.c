/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:44:20 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/24 11:53:40 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_actual_command2(t_mini **mini, t_data *node)
{
	char	*path;
	char	**argv;

	path = ft_get_env_var((*mini)->env_copy, "PATH");
	if (!path)
		return (ft_clear_all(mini, "Command not found", 127));
	free(path);
	path = ft_check_access((*mini)->env_copy, &(node -> command));
	if (!path)
		return (ft_clear_all(mini, "Command not found", 127));
	argv = ft_concatenate_args(node);
	if (!argv)
		return (free(path),
			ft_clear_all(mini, "Memory reservation failed\n", 1));
	if (ft_do_builtin_forked(mini, node))
		return (free(path), ft_free_split(&argv),
			ft_clear_all(mini, NULL, 1));
	ft_expand_argv_args(mini, argv);
	if (execve(path, argv, (*mini)->env_copy) == -1)
		return (free(path), ft_free_split(&argv),
			ft_clear_all(mini, "Execution failed", 1));
}

void	ft_close_node_pipe_before_current(t_data **list, t_data **node)
{
	t_data	*aux;

	aux = *list;
	while (aux && aux != *node && aux->next != *node)
	{
		if (aux -> prev_pipefd)
			ft_close_and_free_pipe(&(aux -> prev_pipefd));
		if (aux -> next_pipefd)
			ft_close_and_free_pipe(&(aux -> next_pipefd));
		aux = aux -> next;
	}
	if (aux -> next == *node)
	{
		if (aux -> prev_pipefd)
			ft_close_and_free_pipe(&(aux -> prev_pipefd));
	}
}

void	ft_do_actual_command(t_mini **mini, t_data *node)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	ft_close_node_pipe_before_current(((*mini)->list), &node);
	if (!node -> command)
		return (ft_clear_all(mini, NULL, 1));
	ft_check_pipes(node);
	if ((node -> prev_pipefd
			&& dup2(node -> prev_pipefd[0], STDIN_FILENO) == -1)
		|| (node -> next_pipefd
			&& dup2(node -> next_pipefd[1], STDOUT_FILENO) == -1))
		return (ft_clear_all(mini, "Setting the stdout or stdin failed\n", 1));
	if (node -> oper
		&& !ft_set_opers(mini, node))
		return (ft_clear_all(mini, NULL, 1));
	ft_do_actual_command2(mini, node);
}

void	ft_do_list_commands(t_mini **mini, t_data *node)
{
	pid_t	pid;
	int		fd[2];

	if (!node)
		return (ft_wait_for_childs(mini));
	if (node -> next)
	{
		if (pipe(fd) < 0)
			return (ft_clear_all(mini, "Pipe failed", errno));
		node -> next_pipefd = fd;
		node -> next -> prev_pipefd = fd;
	}
	pid = fork();
	if (pid < 0)
		return (ft_clear_all(mini, "Fork failed", errno));
	else if (pid == 0)
	{
		ft_do_actual_command(mini, node);
	}
	else
	{
		g_child_work = 1;
		ft_do_list_commands(mini, node -> next);
	}
}

/*
 * Apply the commands in each node of the list
 * TO DO: flag for the status of the child
 */
void	ft_apply_commands(t_mini **mini)
{
	if (!ft_set_heredoc(mini))
		return ;
	if (!(*((*mini)->list))->next)
	{
		if (!(*((*mini)->list))->command)
			return ((void)ft_set_opers(mini, (*((*mini)->list))));
		else
		{
			if (ft_check_builtin(*((*mini)->list))
				&& ft_do_builtin(mini, *((*mini)->list)))
				return ;
		}
	}
	ft_do_list_commands(mini, *((*mini)->list));
}
