/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:17:52 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/10 17:32:43 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_getpath(char **env)
{
	int		num;
	int		check;
	char	*str;
	char	**splited;

	num = 0;
	check = 0;
	while (!check && env[num])
	{
		str = ft_strnstr(env[num], "PATH=", 5);
		if (str)
			check = 1;
		else
			num++;
	}
	str = ft_substr(str, 5, ft_strlen(str));
	if (!str)
		return (NULL);
	splited = ft_split(str, ':');
	free(str);
	return (splited);
}

char	*ft_check_access(char **env, char **coms)
{
	char	*str;
	char	*str2;
	char	**path;
	int		num;

	if (!access(*coms, X_OK))
		return (ft_strdup(*coms));
	num = 0;
	str2 = ft_strjoin("/", coms[0]);
	if (!str2)
		return (NULL);
	path = ft_getpath(env);
	if (!path)
		return (free(str2), NULL);
	while (path[num])
	{
		str = ft_strjoin(path[num++], str2);
		if (!access(str, X_OK))
			break ;
		free(str);
		str = NULL;
	}
	ft_free_split(&path);
	free(str2);
	return (str);
}

int	ft_get_argv_size(t_data *node)
{
	int		size;
	char	*str;
	char	*str2;

	size = 1;
	str = node -> arg;
	while (str && *str)
	{
		while (*str && ft_isspace(*str))
			str++;
		ft_count_comm_str(&str, &size, 1);
		if (*str && !ft_isspace(*str))
		{
			str2 = str;
			while (*str && !ft_isspace(*str) && *str != '\'' && *str != '"')
				str++;
			if (str2 != str)
				size++;
		}
	}
	return (size);
}

void	ft_add_to_argv(char **argv, char *str1, char *str2, int *size)
{
	char	*aux;

	aux = NULL;
	aux = ft_substr(str1, 0, str2 - str1);
	if (aux)
	{
		argv[*size] = aux;
		(*size)++;
	}
}

int	ft_split_args(char *str, char **argv)
{
	int		size;
	char	*aux;

	size = 1;
	while (str && *str)
	{
		while (*str && ft_isspace(*str))
			str++;
		aux = str;
		ft_count_comm_str(&str, &size, 0);
		if (aux != str)
			ft_add_to_argv(argv, aux, str, &size);
		if (!*str)
			break ;
		aux = str;
		while (*str && !ft_isspace(*str) && *str != '\'' && *str != '"')
			str++;
		if (aux != str)
			ft_add_to_argv(argv, aux, str, &size);
	}
	argv[size] = NULL;
	return (size);
}
