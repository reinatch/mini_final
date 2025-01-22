/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:08:58 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 00:13:46 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_error(void)
{
	print_error_msg("cd", "too many arguments");
	return (EXIT_FAILURE);
}

int	cd_builtin(char **args, t_env_var_node *env_var_list)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (args[1] && args[2])
		return (cd_error());
	if (args[1] && !str_equals(args[1], "~"))
		path = args[1];
	else
		path = get_env_var_value_from_list(env_var_list, "__HOME");
	if (chdir(path) != 0)
	{
		print_perror_msg("cd", args[1]);
		return (EXIT_FAILURE);
	}
	pwd = get_env_var_value_from_list(env_var_list, "PWD");
	oldpwd = get_env_var_value_from_list(env_var_list, "OLDPWD");
	if (oldpwd && pwd && *pwd)
		replace_env_var("OLDPWD", pwd, env_var_list);
	if (pwd && *pwd)
		replace_env_var("PWD", getcwd(cwd, PATH_MAX), env_var_list);
	return (EXIT_SUCCESS);
}
