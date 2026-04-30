/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:51:12 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/24 19:30:52 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	ft_write_heredoc(int fd, char *end)
{
	char	*str;

	rl_on_new_line();
	str = readline("<");
	if (!str)
	{
		if (g_child_work == 2)
			return (0);
		else
			return (1);
	}
	while (!ft_strcmp_custom(end, str))
	{
		if (str)
		{
			ft_putendl_fd(str, fd);
			free(str);
		}
		rl_on_new_line();
		str = readline("<");
		if (!str)
		{
			if (g_child_work == 2)
				return (0);
			else
				return (1);
		}
	}
	return (1);
}
*/

int	ft_write_heredoc(int fd, char *end)
{
	char	*str;
	char	*str2;

	str2 = ft_strtrim_custom(end, "\"");
	while (1)
	{
		str = readline("<");
		if (!str)
		{
			if (g_child_work == 2)
				return (errno = 130, 0);
			printf("warning: here-document delimited by end-of-file");
			printf("wanted `%s')\n", end);
			break ;
		}
		if (ft_strcmp_custom(str2, str) == 1)
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, fd);
		free(str);
	}
	return (free(str2), 1);
}

int	ft_heredoc_create(char	**path)
{
	int		fd;
	char	*str;
	char	*name;
	char	*i;

	str = ft_strdup("/tmp/.temporal_heredoc");
	i = ft_strdup("A");
	fd = -1;
	while (fd == -1 && (*i <= 90 || (*i >= 97 && *i < 123)))
	{
		name = ft_strjoin(str, i);
		if (!name)
			return (free(i), free(str), -1);
		fd = open(name, O_CREAT | O_RDWR | O_EXCL, 00644);
		if (fd != -1)
		{
			*path = name;
			free(str);
			free(i);
			return (fd);
		}
		free(name);
		(*i)++;
	}
	return (free(i), free(str), 0);
}
