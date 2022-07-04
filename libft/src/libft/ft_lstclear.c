/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:24:00 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 17:05:48 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p_lst;

	if (!lst)
		return ;
	while (*lst)
	{
		p_lst = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = p_lst;
	}
}
