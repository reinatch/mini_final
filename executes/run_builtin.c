/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:26:29 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 11:59:56 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_forked_builtin(char **args, t_env_var_node **env_var_list)
{
	int	exit_status;

	exit_status = run_builtin(args, env_var_list);
	free_array(args);
	free_env_var_list(env_var_list);
	rl_clear_history();
	exit(exit_status);
}

int	run_builtin(char **args, t_env_var_node **env_var_list)
{
	char	*command;

	command = args[0];
	if (str_equals(command, "echo"))
		return (echo_builtin(args));
	if (str_equals(command, "pwd"))
		return (pwd_builtin());
	if (str_equals(command, "env"))
		return (env_builtin(*env_var_list));
	if (str_equals(command, "export"))
		return (export_builtin(args, env_var_list));
	if (str_equals(command, "unset"))
		return (unset_builtin(args, env_var_list));
	if (str_equals(command, "cd"))
		return (cd_builtin(args, *env_var_list));
	if (str_equals(command, "exit"))
		return (exit_builtin(args, env_var_list));
	return (EXIT_FAILURE);
}
