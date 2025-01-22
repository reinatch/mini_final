/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_multiple_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:29:31 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 08:03:50 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_redirects_for_multiple(char *command, char **commands,
		t_env_var_node **env_var_list)
{
	char	*redirect;

	redirect = get_next_redirect_pos(command);
	while (redirect)
	{
		if (*redirect == '<')
			if (redirect_input(redirect) == FAILED)
				quit_child(commands, env_var_list);
		if (*redirect == '>')
			if (redirect_output(redirect) == FAILED)
				quit_child(commands, env_var_list);
		if (*redirect < 0)
			redirect_heredoc(redirect);
		redirect = get_next_redirect_pos(command);
	}
}

static void	run_forked_command(char *command, char **commands,
		t_env_var_node **env_var_list)
{
	char	**args;

	close_extra_fds();
	args = split_args(command);
	free_array(commands);
	if (is_builtin(args[0]))
		run_forked_builtin(args, env_var_list);
	else
		run_external(args, *env_var_list);
}

int	run_multiple_commands(char **commands, t_env_var_node **env_var_list)
{
	int	original_fds[2];
	int	*children_pid;
	int	i;

	original_fds[IN] = NO_REDIRECT;
	original_fds[OUT] = NO_REDIRECT;
	save_original_fds(original_fds);
	children_pid = init_children_pid(commands);
	i = -1;
	while (commands[++i])
	{
		handle_pipe(original_fds[OUT], commands[i], commands);
		children_pid[i] = fork();
		setup_non_interactive_signal_handling(children_pid[i]);
		if (children_pid[i] == -1)
			print_perror_msg("fork", commands[i]);
		else if (children_pid[i] == 0)
		{
			free(children_pid);
			handle_redirects_for_multiple(commands[i], commands, env_var_list);
			run_forked_command(commands[i], commands, env_var_list);
		}
	}
	restore_original_fds(original_fds);
	return (wait_for_children(children_pid));
}
