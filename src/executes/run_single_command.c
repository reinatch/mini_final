/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:38:18 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/24 11:40:03 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_forked_external(char **args, t_env_var_node *env_var_list)
{
	int		child_pid;
	char	*command;

	command = args[0];
	child_pid = fork();
	setup_non_interactive_signal_handling(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork", command);
	else if (child_pid == 0)
		run_external(args, env_var_list);
	else
		return (wait_for_child(child_pid, TRUE));
	exit(EXIT_FAILURE);
}

int	run_single_command(char *command, t_env_var_node **env_var_list)
{
	char	**args;
	int		exit_status;
	int		original_fds[2];

	original_fds[IN] = NO_REDIRECT;
	original_fds[OUT] = NO_REDIRECT;
	save_original_fds(original_fds);
	if (!handle_redirects_for_single(command))
	{
		restore_original_fds(original_fds);
		return (EXIT_FAILURE);
	}
	args = split_args(command);
	if (is_builtin(args[0]))
		exit_status = run_builtin(args, env_var_list);
	else
		exit_status = execute_forked_external(args, *env_var_list);
	free_array(args);
	restore_original_fds(original_fds);
	return (exit_status);
}
