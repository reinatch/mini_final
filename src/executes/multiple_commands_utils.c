/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:35:21 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/24 11:41:53 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*init_children_pid(char **commands)
{
	int		*children_pid;
	size_t	size;

	size = count_matrix_lines(commands) + 1;
	children_pid = ft_calloc(size, sizeof(int));
	if (!children_pid)
		return (NULL);
	ft_bzero(children_pid, size);
	return (children_pid);
}

void	clean_after_execute(int *children_pid)
{
	close_extra_fds();
	free(children_pid);
}

void	quit_child(char **commands, t_env_var_node **env_var_list)
{
	rl_clear_history();
	free_env_var_list(env_var_list);
	free_array(commands);
	close_all_fds();
	exit(EXIT_FAILURE);
}
