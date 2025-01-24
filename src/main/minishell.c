/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:51:36 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/24 11:38:37 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	last_exit_status;

int	run_minishell(t_env_var_node *env_vars_list)
{
	char	*input;
	char	**commands;

	last_exit_status = EXIT_SUCCESS;
	while (TRUE)
	{
		setup_interactive_signal_handling();
		input = read_command(env_vars_list);
		if (is_valid_input(input, &last_exit_status, env_vars_list))
		{
			handle_expansions(&input, env_vars_list, last_exit_status);
			if (has_pipes(input))
			{
				commands = split_commands(input);
				last_exit_status = run_multiple_commands(commands,
						&env_vars_list);
				free_array(commands);
			}
			else
				last_exit_status = run_single_command(input, &env_vars_list);
		}
		free(input);
	}
	return (last_exit_status);
}

int	main(int count, char **args, char **env_vars)
{
	t_env_var_node	*env_vars_list;

	(void)count;
	(void)args;
	env_vars_list = init_env_var_list(env_vars);
	return (run_minishell(env_vars_list));
}
