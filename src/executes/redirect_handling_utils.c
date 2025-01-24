/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handling_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:58:26 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/24 11:41:30 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_original_fds(int original_fds[2])
{
	if (original_fds[IN] == NO_REDIRECT)
		original_fds[IN] = dup(STDIN_FILENO);
	if (original_fds[OUT] == NO_REDIRECT)
		original_fds[OUT] = dup(STDOUT_FILENO);
}

void	restore_original_fds(int original_fds[2])
{
	if (original_fds[IN] != NO_REDIRECT)
		redirect_fd(original_fds[IN], STDIN_FILENO);
	if (original_fds[OUT] != NO_REDIRECT)
		redirect_fd(original_fds[OUT], STDOUT_FILENO);
}

int	handle_redirects_for_single(char *command)
{
	char	*redirect;

	redirect = get_next_redirect_pos(command);
	while (redirect)
	{
		if (*redirect == '<' && redirect_input(redirect) == FAILED)
			return (FAILED);
		else if (*redirect == '>' && redirect_output(redirect) == FAILED)
			return (FAILED);
		else if (*redirect < 0)
			redirect_heredoc(redirect);
		redirect = get_next_redirect_pos(command);
	}
	return (SUCCESS);
}
