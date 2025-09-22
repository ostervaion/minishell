/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:39 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/18 16:58:55 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	clear_and_return(t_list **node, void *cont, void (*del)(void *))
{
	if (cont)
		(*del)(cont);
	ft_lstclear(node, del);
}

static t_list	*create_node(void *cont, t_list **node, void (*del)(void *))
{
	t_list	*new_node;

	new_node = ft_lstnew(cont);
	if (!new_node)
	{
		clear_and_return(node, cont, del);
		return (NULL);
	}
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*node2;
	void	*cont;

	node = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		cont = (*f)(lst->content);
		if (!cont)
		{
			ft_lstclear(&node, del);
			return (NULL);
		}
		node2 = create_node(cont, &node, del);
		if (!node2)
			return (NULL);
		if (!node)
			node = node2;
		else
			ft_lstadd_back(&node, node2);
		lst = lst->next;
	}
	return (node);
}
