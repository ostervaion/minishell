/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:55:13 by martimar          #+#    #+#             */
/*   Updated: 2025/06/19 17:29:16 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It searches for PWD key in env_copy and 
prints it*/
void	ft_pwd_command(t_mini *mini, t_data *list)
{
	char	*path;
	char	**arr;

	arr = ft_concatenate_args(list);
	if (!arr)
		return ((void)printf("Malloc failed in arr\n"));
	if (arr[1] && arr[1][0] == '-' && ft_isalpha(arr[1][1]))
		return (ft_free_split(&arr), (void)printf("No flags allowed\n"));
	path = ft_get_env_var(mini->env_copy, "PWD");
	if (!path)
		return (ft_free_split(&arr), (void)printf("Error getting path\n"));
	printf("%s\n", path);
	free(path);
	ft_free_split(&arr);
	ft_status(0, mini);
}
