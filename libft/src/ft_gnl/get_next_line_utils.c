/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:15:20 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/24 11:33:35 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_strchr_gnl(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

size_t	ft_strsize(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_lstlen(t_gnl *stash)
{
	size_t	len;

	len = 0;
	while (stash != NULL)
	{
		len += ft_strsize(stash->buffer);
		stash = stash->next;
	}
	return (len);
}

void	*ft_reset_list(t_gnl *stash)
{
	t_gnl	*temp;

	while (stash != NULL)
	{
		temp = (stash)->next;
		free(stash);
		stash = temp;
	}
	stash = NULL;
	return (NULL);
}
