/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakpipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:07:31 by martimar          #+#    #+#             */
/*   Updated: 2025/06/05 13:40:48 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Return a line of the broken pipe 
section, or error if it finds unclosed 
doble or single quotes*/
char	*return_line(char *str, int *size)
{
	int		i;
	int		sp_quotes;
	int		db_quotes;

	i = 0;
	sp_quotes = 0;
	db_quotes = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '|')
	{
		ft_check_quotes(str[i], &sp_quotes, &db_quotes);
		if (str[i + 1] == '|' && (sp_quotes || db_quotes))
			ft_check_quoted_pipe(str + i + 1, &i, &sp_quotes);
		if (str[i + 1] == '|' || str[i + 1] == '\0')
		{
			if (sp_quotes || db_quotes)
				return (printf("Error: Unclosed quotes\n"), NULL);
			else
				return ((*size) += i + 1, ft_substr(str, 0, i + 1));
		}
		i++;
	}
	return ((*size) += i + 1, str);
}

/*Check if a pipe is inside quotes so we don't break
the pipe when its just a string*/
void	ft_check_quoted_pipe(char *str, int *i, int *sp_quotes)
{
	int		j;
	char	c;

	j = 0;
	if (*sp_quotes)
		c = '\'';
	else
		c = '\"';
	while (str[j] != '\0')
	{
		if (str[j] == c)
		{
			*i += j;
			return ;
		}
		++j;
	}
	j = 0;
	while (str[j] == '|')
		j++;
	*i += j + 1;
}

/*Boolean value that is set based on opened or closed quotes*/
void	ft_check_quotes(char c, int *sp_quotes, int *db_quotes)
{
	if (c == '\'' && !(*db_quotes))
	{
		if (*sp_quotes)
			*sp_quotes = 0;
		else
			*sp_quotes = 1;
	}
	else if (c == '\"' && !(*sp_quotes))
	{
		if (*db_quotes)
			*db_quotes = 0;
		else
			*db_quotes = 1;
	}
}

/* Fills the nodes with the content 
from the previously broken pipes*/
int	ft_fill_nodes(char *str, t_mini *mini)
{
	int		size;
	char	*line;

	if (ft_check_openpipes(str))
		return (ft_clear_list_and_exit(mini->list, NULL), -1);
	while (str && str[0] != '\0')
	{
		size = 0;
		line = return_line(str, &size);
		if (!line)
			return (-1);
		if (ft_new_node(mini->list, line) == 0)
			return (free(line), ft_clear_list_and_exit(mini->list, NULL), -1);
		free(line);
		if (str[size] == '|')
		{
			str += size + 1;
			if (ft_check_openpipes(str))
				return (ft_clear_list_and_exit(mini->list, NULL), -1);
		}
		else
			str += size;
	}
	return (0);
}

/*It check if there is an opened pipe, 
prints a error and returs 1*/
int	ft_check_openpipes(char *str)
{
	while (ft_isspace(*str))
		++str;
	if (*str == '|' || *str == '\0')
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}
