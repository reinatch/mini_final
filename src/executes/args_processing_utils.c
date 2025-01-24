/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_processing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:19:32 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/24 11:42:03 by rerodrig         ###   ########.fr       */
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
	int		quote_found;

	quote_found = 1;
	while (quote_found)
	{
		opening_quote = 0;
		quote_found = 0;
		while (*str)
		{
			if (is_quote(*str))
			{
				if (!opening_quote)
					opening_quote = *str;
				else
					opening_quote = 0;
				remove_char_at(str);
				quote_found = 1;
			}
			else
				str++;
		}
	}
}

static int	contains_quotes(char *str)
{
	if (!str)
		return (FALSE);
	return (ft_strchr(str, '"') != NULL || ft_strchr(str, '\'') != NULL);
}
