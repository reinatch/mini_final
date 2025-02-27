/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:28:18 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/24 11:37:45 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_input(char *input_redirect_pos)
{
	char	*file_name;
	int		fd;

	if (!input_redirect_pos)
		return (SUCCESS);
	file_name = get_redirect_argument(input_redirect_pos, 1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, STDIN_FILENO);
	free(file_name);
	return (SUCCESS);
}
