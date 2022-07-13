/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:59:56 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 17:06:44 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*copy_lst;
	t_list	*tem;
	t_list	*tem_f;

	if (!lst)
		return (NULL);
	copy_lst = NULL;
	while (lst)
	{
		tem_f = f(lst->content);
		tem = ft_lstnew(tem_f);
		if (!tem)
		{
			ft_lstclear(&copy_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&copy_lst, tem);
		lst = lst->next;
	}
	return (copy_lst);
}
