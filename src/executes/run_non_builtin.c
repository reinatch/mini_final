/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-oli <joao-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:39:20 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/07 18:41:42 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_folder(char *command)
{
	struct stat	statbuf;

	if (stat(command, &statbuf) != 0)
		return (0);
	if (S_ISDIR(statbuf.st_mode))
	{
		if (*command == '.')
			command++;
		if (*command == '.')
			command++;
		if (*command == '/')
			return (TRUE);
	}
	return (FALSE);
}

static void	handle_execve_errors(char **args, char *path, char **envp)
{
	int	error;

	error = EXIT_FAILURE;
	print_perror_msg("execve", args[0]);
	if (access(path, F_OK) != 0)
		error = CMD_NOT_FOUND;
	else if (access(path, X_OK) != 0)
		error = NOT_EXECUTABLE;
	free_array(args);
	free_array(envp);
	free(path);
	exit(error);
}

void	external_exit(char **args, t_env_var_node *env_var_list,
		int exit_status)
{
	if (exit_status == NOT_EXECUTABLE)
		print_error_msg(args[0], NOT_EXECUTABLE_MSG);
	if (exit_status == CMD_NOT_FOUND)
		print_error_msg(args[0], CMD_NOT_FOUND_MSG);
	rl_clear_history();
	close_all_fds();
	free_env_var_list(&env_var_list);
	free_array(args);
	exit(exit_status);
}

static int	env_var_list_has_path(t_env_var_node *env_var_list)
{
	return (get_env_var_value_from_list(env_var_list, "PATH") != NULL);
}

int	run_external(char **args, t_env_var_node *env_var_list)
{
	char	*path;
	char	*command;
	char	**envp;

	command = args[0];
	if (is_empty(command))
		external_exit(args, env_var_list, EXIT_SUCCESS);
	if (is_folder(command))
		external_exit(args, env_var_list, NOT_EXECUTABLE);
	path = find_command(command, env_var_list);
	if (path == NULL && env_var_list_has_path(env_var_list))
		external_exit(args, env_var_list, CMD_NOT_FOUND);
	else if (path == NULL)
		path = ft_strdup(command);
	rl_clear_history();
	close_extra_fds();
	envp = list_to_envp_format(env_var_list);
	free_env_var_list(&env_var_list);
	if (execve(path, args, envp) == -1)
		handle_execve_errors(args, path, envp);
	exit(EXIT_SUCCESS);
}
