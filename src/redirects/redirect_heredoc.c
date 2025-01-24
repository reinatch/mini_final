/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:09:56 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/24 11:38:01 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_heredoc(char *heredoc_pos)
{
	char	*filename;
	int		tmp_file_fd;
	int		heredoc_number;

	heredoc_number = (int)(*heredoc_pos);
	filename = get_tmp_filename(heredoc_number);
	tmp_file_fd = open(filename, O_RDONLY);
	if (tmp_file_fd == -1)
	{
		print_perror_msg("open", filename);
		free(filename);
		return ;
	}
	free(filename);
	redirect_fd(tmp_file_fd, STDIN_FILENO);
	remove_char_at(heredoc_pos);
}
