/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:55:26 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/24 11:35:44 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_next_redirect_pos(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			skip_to_closing_quote(&str);
		if (*str == '<' || *str == '>' || *str < 0)
			return (str);
		str++;
	}
	return (NULL);
}

void	redirect_fd(int fd_to_redirect, int fd_location)
{
	dup2(fd_to_redirect, fd_location);
	close(fd_to_redirect);
}
