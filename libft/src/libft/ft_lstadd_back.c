/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:43:21 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 17:05:24 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p_lst;

	if (!lst)
		return ;
	else if (!*lst)
		*lst = new;
	else
	{
		p_lst = *lst;
		while (p_lst->next)
			p_lst = p_lst->next;
		p_lst->next = new;
	}
}
