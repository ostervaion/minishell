/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:42:11 by martimar          #+#    #+#             */
/*   Updated: 2025/06/18 14:11:51 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Takes care of variable expansion and manages quotes*/
char	*ft_before_expand_values(t_mini *mini, char *str)
{
	int		len;
	int		check;
	char	*temp;

	temp = NULL;
	check = 0;
	while (str && *str)
	{
		len = 0;
		while (*str && *str != '\'' && *str != '\"')
		{
			len++;
			str++;
		}
		if (len > 0)
			check = ft_join_string(mini, str, &temp, len);
		else if (*str == '\"')
			check = ft_process_string(mini, &str, &temp, '\"');
		else if (*str == '\'')
			check = ft_process_string(mini, &str, &temp, '\'');
		if (check == -1)
			return (ft_check_temp(&temp), NULL);
	}
	return (temp);
}

/*Expand enviroment variable, it will use an fd to write on it
and the return the line using gnl.*/
char	*ft_expand_values(t_mini *mini, char *str)
{
	int		i;
	int		fd;

	ft_createpath_openfile(&fd);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[0] == '\'')
			return (close(fd),
				ft_check_if_env_var(mini->env_copy, str));
		else if (str[i] == '$' && str[i + 1] == '?')
			ft_put_number_fd(mini, fd, &i);
		else if (str[i] == '$' && !ft_isalnum(str[i + 1]) && str[i + 1] != '_')
			ft_putchar_fd(str[i], fd);
		else if (str[i] == '$')
		{
			if (ft_expand_variable(mini->env_copy, str + i + 1, fd, &i) == -1)
				return (close(fd), NULL);
		}
		else
			ft_putchar_fd(str[i], fd);
		i++;
	}
	return (ft_close_fd_return_line(fd));
}

/*Checks if the string inside single quotes has a enviroment 
variable to expand, if it does, it will return the quoted line
withu delete the single quotes. Otherwise it trims the quotes.*/
char	*ft_check_if_env_var(char **env_copy, char *str)
{
	int		j;
	int		len;
	char	*env_var;
	char	*key;

	len = 0;
	j = 1;
	while (str[j] != '\0' && str[j] != '\"' && str[j] != '\'' && str[j] != '$')
		j++;
	if (str[j] == '$')
	{
		j++;
		while (ft_isprint(str[j + len]) && str[j + len] != '\0'
			&& str[j + len] != '\"' && str[j + len] != '\'')
			len++;
	}
	key = ft_substr(str, j, len);
	if (!key)
		return ((void)printf("Malloc failed\n"), NULL);
	env_var = ft_get_env_var(env_copy, key);
	if (env_var)
		return (free(key), free(env_var), ft_strdup(str));
	return (free(key), ft_strtrim(str, "\'"));
}

/*If the variable to expand exist, it writes to the fd its value.
Other wise it jumps the non-existing key on the string.*/
int	ft_expand_variable(char **env_copy, char *str, int fd, int *i)
{
	int		j;
	char	*env_var;
	char	*key;

	j = 0;
	while (!(ft_isspace(str[j])) && str[j] != '\0'
		&& str[j] != '\"' && str[j] != '\'' && str[j] != '$' )
		j++;
	key = ft_substr(str, 0, j);
	if (!key)
		return ((void)printf("Malloc failed\n"), -1);
	env_var = ft_get_env_var(env_copy, key);
	free(key);
	if (env_var)
	{
		ft_putstr_fd(env_var, fd);
		free(env_var);
	}
	*i += j;
	return (0);
}

/*Closes the fd and returns the line using gnll*/
char	*ft_close_fd_return_line(int fd)
{
	char	*str;

	ft_putchar_fd('\0', fd);
	close(fd);
	fd = open("/tmp/.temporary_file", O_RDONLY);
	if (fd == -1)
		return (printf("Error opening file: %s\n", strerror(errno)), NULL);
	str = get_next_line(fd);
	unlink("/tmp/.temporary_file");
	close(fd);
	return (str);
}
