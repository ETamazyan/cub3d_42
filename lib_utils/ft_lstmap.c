/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:07:58 by etamazya          #+#    #+#             */
/*   Updated: 2024/02/26 18:40:07 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*llst;

	llst = 0;
	if (!lst || !f || !del)
		return (0);
	while (lst)
	{
		tmp = ft_lstnew(f(lst -> content));
		if (!tmp)
		{
			ft_lstclear(&llst, del);
			return (0);
		}
		ft_lstadd_back(&llst, tmp);
		lst = lst -> next;
	}
	return (llst);
}
