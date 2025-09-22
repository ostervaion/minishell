/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:59:36 by juetxeba          #+#    #+#             */
/*   Updated: 2025/02/18 15:18:24 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_last_line(char **saved_l)
{
	char	*line;

	line = NULL;
	if (saved_l && *saved_l && (*saved_l)[0] != '\0')
	{
		line = ft_strdupgnl(*saved_l);
		if (!line)
			return (NULL);
		free(*saved_l);
		*saved_l = NULL;
	}
	return (line);
}

void	*ft_calloc(size_t type, size_t length)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc(type * length);
	if (!ptr)
		return (NULL);
	else
	{
		while (i < (type * length))
			ptr[i++] = '\0';
	}
	return (ptr);
}

char	*ft_strdupgnl(char *s)
{
	size_t	i;
	size_t	n;
	char	*str;

	i = 0;
	n = 0;
	while (s[i] != '\0')
		i++;
	str = (char *)malloc(i + 1);
	if (str == NULL)
		return (NULL);
	while (n < i)
	{
		str[n] = s[n];
		n++;
	}
	str[n] = '\0';
	return (str);
}

void	ft_printable(char **saved_l, char **line)
{
	int		i;
	char	*aux;

	if (!(*saved_l))
		return ;
	i = 0;
	while ((*saved_l)[i] != '\n' && (*saved_l)[i] != '\0')
		i++;
	if ((*saved_l)[i] == '\n')
	{
		*line = (char *) ft_calloc (sizeof(char), i + 2);
		if (!*line)
			return ;
		aux = ft_strdupgnl(*saved_l + i + 1);
		if (!aux)
			return (free(*line));
		while (i >= 0)
		{
			(*line)[i] = (*saved_l)[i];
			i--;
		}
		free(*saved_l);
		*saved_l = aux;
	}
}

void	ft_strjoingnl(char **saved_l, char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!(*saved_l))
		*saved_l = ft_strdupgnl(buffer);
	else
	{
		while ((*saved_l)[i] != '\0')
			i++;
		while (buffer[j] != '\0')
			j++;
		str = (char *)ft_calloc(sizeof(char), i + j + 1);
		if (!str)
			return ;
		while (--j >= 0)
			str[i + j] = buffer[j];
		while (--i >= 0)
			str[i] = (*saved_l)[i];
		free(*saved_l);
		*saved_l = str;
	}
}
