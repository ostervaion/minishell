/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:17:42 by martimar          #+#    #+#             */
/*   Updated: 2026/04/30 13:41:57 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Start of the echo command, it check if the command flags are valid or not*/
void	ft_echo_command(t_mini *mini, t_data *list)
{
	int		flag;
	char	*str;
	char	*temp;

	flag = 0;
	str = NULL;
	if (!(list->arg))
		return ((void)printf("\n"));
	temp = ft_advance_in_str(list->arg, &flag);
	str = ft_before_expand_values(mini, temp);
	free(temp);
	return (ft_status(0, mini), ft_echo_print(str, flag));
}

/*It prints to the terminal the string given to echo,
if the flags == 1, it prints it without line jump*/
void	ft_echo_print(char *s, int flag)
{
	if (!s)
	{
		if (flag)
			return ;
		return ((void)printf("\n"));
	}
	if (!flag)
		return ((void)printf("%s\n", s), free(s));
	return ((void)printf("%s", s), free(s));
}

/*Skips the flags int the list->arg string*/
char	*ft_advance_in_str(char *str, int *flag)
{
	int		i;

	i = 0;
	while (str && str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (ft_adv_return_string(str, i, flag));
		if (!(ft_isspace(str[i])))
			return (ft_return_string(str));
		while (str && ft_isspace(str[i]))
		{
			*flag = 1;
			i++;
		}
		str += i;
		i = 0;
	}
	return (ft_return_string(str));
}

/*Because norminette...*/
char	*ft_adv_return_string(char *str, int i, int *flag)
{
	str += i;
	*flag = 1;
	return (ft_return_string(str));
}

/*Returns a copy of a string from 
the point where there are no more flags*/
char	*ft_return_string(char *str)
{
	char	*s;

	s = ft_strdup(str);
	if (!s)
		return (NULL);
	return (s);
}
