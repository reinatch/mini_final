/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:50:20 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/21 23:50:20 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_equals(const char *str1, const char *str2)
{
	return (ft_strcmp(str1, str2) == 0);
}

void	remove_char_at(char *pos)
{
	ft_memmove(pos, pos + 1, ft_strlen(pos + 1) + 1);
}

void	ft_strjoin_multiple(char **first, char *second, char *third)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(*first, second);
	result = ft_strjoin(temp, third);
	free(temp);
	free(*first);
	*first = result;
}

void	mark_char_inside_delimiter(char *str, char target_char, char delimeter)
{
	short	inside_delimiter;

	inside_delimiter = FALSE;
	while (*str)
	{
		if (*str == delimeter)
			inside_delimiter = !inside_delimiter;
		if (inside_delimiter && *str == target_char)
			*str = -1;
		str++;
	}
}

void	restore_marked_chars(char **matrix, char restore_char)
{
	char	*str;

	while (*matrix)
	{
		str = *matrix;
		while (*str)
		{
			if (*str == -1)
				*str = restore_char;
			str++;
		}
		matrix++;
	}
	return ;
}
