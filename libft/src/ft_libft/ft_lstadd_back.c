/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:46:15 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 09:26:15 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// ft_lstadd_back
// void ft_lstadd_back(t_list **lst,
// -
// lst: The address of a pointer to
// a list.
// new: The address of a pointer to
// added to the list.
// None
// None
// Adds the node ’new’ at the end of
// t_list *new);
// the first link of
// the node to be
// // the list.

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
