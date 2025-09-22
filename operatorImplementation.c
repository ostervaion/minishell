/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operatorImplementation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:18:52 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/24 19:58:11 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_sigint(int fd, char *path)
{
	if (g_child_work == 2)
		dup2(fd, STDIN_FILENO);
	else if (fd != -1)
		close(fd);
	unlink(path);
}

int	ft_heredoc(char *opers, int **fds, int *actual_op)
{
	int		fd;
	int		fdin;
	char	*path;
	int		global;

	global = g_child_work;
	g_child_work = 3;
	if (!opers)
		return (0);
	fd = ft_heredoc_create(&path);
	if (fd == -1)
		return (0);
	fdin = dup(STDIN_FILENO);
	if (fdin == -1)
		return (ft_check_sigint(fdin, path), 0);
	if (!ft_write_heredoc(fd, opers))
		return (ft_check_sigint(fdin, path), free(path),
			close(fd), printf("\n"), 0);
	if (!ft_reset_heredoc_fd(&fd, path))
		return (ft_check_sigint(fdin, path),
			free(path), close(fd), 0);
	(*fds)[(*actual_op)++] = fd;
	return (g_child_work = global, free(path), 1);
}

int	ft_append(char *opers, int **fds, int *actual_op)
{
	char	*file;
	char	*aux;
	int		fd;

	file = NULL;
	while (*opers && ft_isspace(*opers))
		opers++;
	aux = opers;
	while (*opers && !ft_isspace(*opers)
		&& *opers != '<' && *opers != '>')
		opers++;
	file = ft_substr(aux, 0, opers - aux);
	if (!file)
		return (0);
	fd = open(file, O_APPEND | O_WRONLY | O_CREAT, 00644);
	if (fd == -1)
		return (perror("Failed to open file"), free(file), 0);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (free(file), close(fd), 0);
	(*fds)[(*actual_op)++] = fd;
	return (free(file), 1);
}

int	ft_input(char *opers, int **fds, int *actual_op)
{
	char	*file;
	char	*aux;
	int		fd;

	file = NULL;
	while (*opers && ft_isspace(*opers))
		opers++;
	aux = opers;
	while (*opers && !ft_isspace(*opers)
		&& *opers != '<' && *opers != '>')
		opers++;
	file = ft_substr(aux, 0, opers - aux);
	if (!file)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Failed to open file"), free(file), 0);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (free(file), close(fd), 0);
	(*fds)[(*actual_op)++] = fd;
	return (free(file), 1);
}

int	ft_redirection(char *opers, int **fds, int *actual_op)
{
	char	*file;
	char	*aux;
	int		fd;

	file = NULL;
	while (*opers && ft_isspace(*opers))
		opers++;
	aux = opers;
	while (*opers && !ft_isspace(*opers)
		&& *opers != '<' && *opers != '>')
		opers++;
	file = ft_substr(aux, 0, opers - aux);
	if (!file)
		return (0);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
		return (perror("Failed to open file"), free(file), 0);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (free(file), close(fd), 0);
	(*fds)[(*actual_op)++] = fd;
	return (free(file), 1);
}
