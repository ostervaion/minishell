/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:17:23 by martimar          #+#    #+#             */
/*   Updated: 2025/06/19 17:32:09 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees temp*/
void	ft_check_temp(char **temp)
{
	if (!(*temp))
	{
		if ((*temp))
			free((*temp));
		*temp = NULL;
	}
}

void	ft_status(int status, t_mini *mini)
{
	*(mini->status) = status;
	return ;
}
