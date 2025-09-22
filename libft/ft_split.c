/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:29:14 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/18 12:54:34 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_sizearr(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s != c)
		{
			++len;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (len);
}

static int	ft_splitstring(char **arr, char const *s, char c, size_t *words)
{
	size_t	len;
	char	*aux;

	while (*s != '\0')
	{
		if (*s != c)
		{
			len = 0;
			while (*s != '\0' && *s != c && ++len)
				s++;
			aux = ft_substr(s - len, 0, len);
			if (!aux)
				return (0);
			arr[*words] = aux;
			*words = *words + 1;
		}
		else
			s++;
	}
	return (1);
}

static void	ft_freearr(char **arr, size_t words)
{
	while (words > 0)
		free(arr[--words]);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	size_t			words;
	int				check;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (ft_sizearr(s, c) + 1));
	if (!arr)
		return (NULL);
	words = 0;
	check = ft_splitstring(arr, s, c, &words);
	if (!check)
	{
		ft_freearr(arr, words);
		return (NULL);
	}
	arr[words] = NULL;
	return (arr);
}
