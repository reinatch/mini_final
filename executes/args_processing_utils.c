/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_processing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:19:32 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 11:59:56 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	contains_quotes(char *str);
static void	remove_quotes(char *str);

char	**split_args(char *command)
{
	char	**exec_args;
	short	has_quotes;

	has_quotes = contains_quotes(command);
	if (has_quotes)
	{
		mark_char_inside_delimiter(command, ' ', '"');
		mark_char_inside_delimiter(command, ' ', '\'');
		remove_quotes(command);
	}
	exec_args = ft_split(command, ' ');
	if (has_quotes)
		restore_marked_chars(exec_args, ' ');
	return (exec_args);
}

static void	remove_quotes(char *str)
{
	char	opening_quote;

	opening_quote = 0;
	while (*str)
	{
		if (is_quote(*str) && !opening_quote)
		{
			opening_quote = *str;
			remove_char_at(str);
		}
		if (*str == opening_quote)
		{
			opening_quote = 0;
			remove_char_at(str);
		}
		str++;
	}
}

static int	contains_quotes(char *str)
{
	if (!str)
		return (FALSE);
	return (ft_strchr(str, '"') != NULL || ft_strchr(str, '\'') != NULL);
}
