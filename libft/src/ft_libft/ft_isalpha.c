/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:05:11 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/25 00:36:51 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// isalpha()
// It is used to check if the passed character is alphabetic. or not.
// Its syntax is -: isalpha(int c);
// It takes only one parameter that is the character to be checked.
// Its return value is non-zero value if c is an alphabet, else it returns 0.
// It is defined in header file <ctype.h>

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}
