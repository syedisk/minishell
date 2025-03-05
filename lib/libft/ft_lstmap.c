/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:37:50 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/06/14 12:44:53 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*cn_node(void *(*f)(void *), void (*del)(void *), void *content)
{
	void	*new_content;
	t_list	*new_node;

	new_content = f(content);
	if (!new_content)
		return (NULL);
	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		del(new_content);
		return (NULL);
	}
	return (new_node);
}

static void	add_node_to_list(t_list **new_lst, t_list **temp, t_list *new_node)
{
	if (!(*new_lst))
		*new_lst = new_node;
	else
		(*temp)->next = new_node;
	*temp = new_node;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*temp;

	new_lst = NULL;
	temp = NULL;
	while (lst)
	{
		new_node = cn_node(f, del, lst->content);
		if (!new_node)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		add_node_to_list(&new_lst, &temp, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
