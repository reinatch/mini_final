/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:35:24 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/21 16:15:43 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe(int original_fd_out, char *current_command, char **commands)
{
	int			command_count;
	short		is_first_command;
	short		has_next_command;
	static int	pipe_fds[2];

	command_count = count_matrix_lines(commands);
	is_first_command = (current_command == commands[0]);
	has_next_command = (current_command != commands[command_count - 1]);
	if (!is_first_command)
		redirect_fd(pipe_fds[IN], STDIN_FILENO);
	if (has_next_command)
	{
		if (pipe(pipe_fds) == -1)
			print_perror_msg("pipe", current_command);
		redirect_fd(pipe_fds[OUT], STDOUT_FILENO);
	}
	else
		redirect_fd(original_fd_out, STDOUT_FILENO);
}
