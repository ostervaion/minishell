/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:01:56 by martimar          #+#    #+#             */
/*   Updated: 2025/06/24 18:41:32 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_numb(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strtrim(str, " 	");
	if (s && s[0] == '-')
		i++;
	while (s && s[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (free(s), 0);
		i++;
	}
	return (free(s), 1);
}

int	ft_exit_invalid(char ***arr, t_mini **mini)
{
	if (ft_check_numb((*arr)[1]))
	{
		printf("exit: too many arguments\n");
		*((*mini)->status) = 1;
		ft_free_split(arr);
		return (-1);
	}
	printf("exit: %s: Numeric argument required\n", (*arr)[1]);
	*((*mini)->status) = 2;
	return (0);
}

void	ft_exit_invalid_2(char **arr, t_mini **mini)
{
	if (!ft_check_numb(arr[1]))
	{
		printf("exit: %s: Numeric argument required\n", arr[1]);
		*((*mini)->status) = 2;
	}
	else
		*((*mini)->status) = ft_atoi(arr[1]);
}

/*It exits the minishell, if arg variable is not NULL, 
it shows an error before freeing everything nd exiting*/
void	ft_exit_command(t_mini **mini, t_data *list)
{
	char	**arr;
	int		len;

	len = 0;
	printf("exit\n");
	if (*((*mini)->list) && list->arg)
	{
		arr = ft_concatenate_args(list);
		if (!arr)
			return ((void)printf("Malloc failed in arr\n"));
		ft_expand_argv_args(mini, arr);
		while (arr[len] != NULL)
			len++;
		if (len > 2)
		{
			if (ft_exit_invalid(&arr, mini) == -1)
				return ;
		}
		else if (len == 2)
			ft_exit_invalid_2(arr, mini);
		else
			*((*mini)->status) = 0;
		ft_free_split(&arr);
	}
	ft_clear_all(mini, NULL, *((*mini)->status));
}
