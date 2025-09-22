/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:59:02 by juetxeba          #+#    #+#             */
/*   Updated: 2025/02/18 15:19:06 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_line(int fd, char *buffer, char **saved_l)
{
	ssize_t	bytes_read;
	char	*line;
	int		i;

	line = NULL;
	bytes_read = 0;
	ft_printable(saved_l, &line);
	while (!line)
	{
		i = 0;
		while (buffer[i] != '\0')
			buffer[i++] = '\0';
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		else if (bytes_read == 0)
			return (ft_last_line(saved_l));
		ft_strjoingnl(saved_l, buffer);
		ft_printable(saved_l, &line);
	}
	return (line);
}

void	*free_and_return(char ***saved_l)
{
	if (*saved_l && **saved_l)
	{
		free(**saved_l);
		**saved_l = NULL;
	}
	if (*saved_l)
	{
		free(*saved_l);
		*saved_l = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		**saved_l[1024];
	char			*line;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!saved_l[fd])
	{
		saved_l[fd] = (char **) malloc (sizeof(char *));
		if (!saved_l[fd])
			return (NULL);
		*saved_l[fd] = NULL;
	}
	buffer = (char *)ft_calloc(sizeof(char *), BUFFER_SIZE + 1);
	if (!buffer)
		return (free_and_return(&saved_l[fd]));
	line = ft_read_line(fd, buffer, saved_l[fd]);
	free(buffer);
	if (!line)
		free_and_return(&saved_l[fd]);
	return (line);
}
