/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:25:40 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/04 12:33:37 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*node2;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		node2 = node->next;
		ft_lstdelone(node, del);
		node = node2;
	}
	*lst = NULL;
}
