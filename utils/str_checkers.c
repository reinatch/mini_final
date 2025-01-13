/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:28:39 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 11:59:56 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

short	is_empty(char *str)
{
	if (!str)
		return (TRUE);
	while (*str)
	{
		if (*str != ' ')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

short	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

short	has_pipes(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			skip_to_closing_quote(&str);
		if (*str == '|')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

short	is_name_delimeter(char c)
{
	return (ft_strchr(NAME_DELIMITERS, c) != NULL);
}

short	is_whitespace(char c)
{
	return (ft_strchr(WHITE_SPACES, c) != NULL);
}
