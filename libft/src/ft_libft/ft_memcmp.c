/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:01:30 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/25 02:05:48 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

//     The memcmp() function compares the first n bytes (each
//    interpreted as unsigned char) of the memory areas s1 and s2.
//    The memcmp() function returns an integer less than, equal to, or
//    greater than zero if the first n bytes of s1 is found,
//    respectively, to be less than, to match, or be greater than the
//    first n bytes of s2.
//    For a nonzero return value, the sign is determined by the sign of
//    the difference between the first pair of bytes (interpreted as
//    unsigned char) that differ in s1 and s2.
//    If n is zero, the return value is zero.

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*d;
	const unsigned char	*s;

	d = s1;
	s = s2;
	while (n-- > 0)
	{
		if (*d != *s)
			return (*d - *s);
		d++;
		s++;
	}
	return (0);
}
