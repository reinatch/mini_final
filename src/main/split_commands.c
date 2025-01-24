/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:29:54 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/24 11:38:23 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_commands(char *input)
{
	char	**commands;

	mark_char_inside_delimiter(input, '|', '"');
	mark_char_inside_delimiter(input, '|', '\'');
	commands = ft_split(input, '|');
	restore_marked_chars(commands, '|');
	return (commands);
}
