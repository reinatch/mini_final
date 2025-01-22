/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:01:57 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 08:03:51 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putnstr_fd(char *s, int fd, int n)
{
	if (s)
		return ((int)write(fd, s, n));
	return (0);
}
