/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:47:43 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/12 15:45:35 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_advance_commed_str(char **str)
{
	char	c;

	c = **str;
	if (!(**str))
		return ;
	(*str)++;
	while (**str && **str != c)
		(*str)++;
	if (**str)
		(*str)++;
}
