/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:06:45 by juetxeba          #+#    #+#             */
/*   Updated: 2025/05/06 17:27:15 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *pnew)
{
	t_list	*node;

	if (!lst || !pnew)
		return ;
	if (*lst == NULL)
	{
		*lst = pnew;
		return ;
	}
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = pnew;
}
