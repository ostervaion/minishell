/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:39:25 by martimar          #+#    #+#             */
/*   Updated: 2025/06/19 17:28:17 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_string_export(t_mini *mini, char *str)
{
	int		i;
	char	*keytemp;
	char	*key;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		if (ft_process_key(mini, str, &keytemp, i) == -1)
			return ;
		if (ft_process_value(mini, str, &value, i) == -1)
			return ((void)free(keytemp));
		if (ft_check_valid(keytemp, value, mini) == -1)
			return (free(keytemp), free(value));
		key = ft_strjoin_custom(keytemp, "=");
		free(keytemp);
		if (!key)
			return (free(value), (void)printf("Malloc failed in key\n"));
		ft_export_command_search(mini, &key, &value);
		ft_status(0, mini);
	}
}

void	ft_break_string(char *aux, int *i)
{
	int		db_quotes;
	int		sp_quotes;

	db_quotes = 0;
	sp_quotes = 0;
	while (aux[*i])
	{
		if (ft_isspace(aux[*i]) && sp_quotes == 0 && db_quotes == 0)
			break ;
		ft_check_quotes(aux[*i], &sp_quotes, &db_quotes);
		(*i)++;
	}
}

void	ft_export_comand_start(t_mini *mini, t_data *list)
{
	int		i;
	char	*aux;
	char	*temp;

	i = 0;
	aux = list->arg;
	while (aux && aux[i] != '\0')
	{
		while (ft_isspace(*aux))
			++aux;
		ft_break_string(aux, &i);
		temp = ft_substr(aux, 0, i);
		if (!temp)
			return ((void)printf("Malloc failed in temp\n"));
		ft_process_string_export(mini, temp);
		free(temp);
		aux += i;
		i = 0;
	}
}

void	ft_export_command(t_mini *mini, t_data *list)
{
	char	*str;

	if (!list->arg)
		return ;
	str = ft_before_expand_values(mini, list->arg);
	if (str && str[0] == '-' && ft_isprint(str[1]))
		return (free(str), (void)printf("No flags allowed\n"));
	free(str);
	ft_export_comand_start(mini, list);
}
