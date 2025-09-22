/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_values2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:19:37 by martimar          #+#    #+#             */
/*   Updated: 2025/06/18 15:30:20 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It moves through the string till it reaches the closing quote*/
int	ft_process_string(t_mini *mini, char **str, char **temp, char c)
{
	int		len;

	len = 1;
	(*str)++;
	while (*str && **str && **str != c)
	{
		(*str)++;
		len++;
	}
	if (**str)
	{
		(*str)++;
		len++;
	}
	return (ft_join_string(mini, *str, temp, len));
}

void	ft_process_tojoin(char **to_join, char **temp2, int check)
{
	if ((*to_join)[0] == '\"' && check == 1)
	{
		*temp2 = ft_strtrim_custom(*to_join, "\"");
		free(*to_join);
		*to_join = *temp2;
	}
}

/*Joint the expanded word/string with the rest of the phrase*/
int	ft_join_string(t_mini *mini, char *str, char **temp, int len)
{
	char	*to_expand;
	char	*to_join;
	char	*temp2;
	int		check;

	check = 1;
	ft_init_values(&to_expand, &to_join);
	to_expand = ft_substr(str - len, 0, len);
	if (!to_expand)
		return (-1);
	if (to_expand[0] == '\'')
		check = 0;
	to_join = ft_expand_values(mini, to_expand);
	if (!to_join)
		return (free(to_expand), -1);
	free(to_expand);
	ft_process_tojoin(&to_join, &temp2, check);
	temp2 = ft_strjoin_custom(*temp, to_join);
	if (!temp2)
		return (free(to_join), -1);
	free(to_join);
	free(*temp);
	*temp = temp2;
	return (0);
}

void	ft_break_command(char *com, int length, t_data *aux, char *auxstr)
{
	com = ft_substr(com, 0, length);
	free(aux -> command);
	aux -> command = com;
	auxstr = ft_strjoin_custom(auxstr, aux -> arg);
	free(aux -> arg);
	aux -> arg = auxstr;
}

/*Expands the value of the command in each of the nodes*/
void	ft_expand_nodes(t_mini **mini)
{
	t_data	*aux;
	char	*str;

	aux = (*(*mini)->list);
	while (aux)
	{
		if (aux -> command)
		{
			str = ft_before_expand_values(*mini, aux -> command);
			if (!str)
				return ;
			ft_change_command(aux, &str);
		}
		aux = aux -> next;
	}
}
