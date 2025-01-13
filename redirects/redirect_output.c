/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:12:54 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 11:59:56 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_open_flags_and_token_size(char *output_redirect_pos, short *token_size)
{
	int	open_flags;

	open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	*token_size = 1;
	if (output_redirect_pos[1] == '>')
	{
		open_flags = O_WRONLY | O_CREAT | O_APPEND;
		*token_size = 2;
	}
	return (open_flags);
}

int	redirect_output(char *output_redirect_pos)
{
	char	*file_name;
	int		fd;
	short	token_size;
	int		open_flags;

	if (!output_redirect_pos)
		return (SUCCESS);
	open_flags = get_open_flags_and_token_size(output_redirect_pos,
			&token_size);
	file_name = get_redirect_argument(output_redirect_pos, token_size);
	fd = open(file_name, open_flags, 0644);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, STDOUT_FILENO);
	free(file_name);
	return (SUCCESS);
}
