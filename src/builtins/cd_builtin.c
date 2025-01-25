/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:08:58 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/25 00:41:21 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_error(void)
{
	print_error_msg("cd", "too many arguments");
	return (EXIT_FAILURE);
}

char	*with_tilde_or_none(t_env_var_node *env_var_list, char **args)
{
	char	*path;

	path = NULL;
	if (!args[1] || ft_strlen(args[1]) == 1)
	{
		path = get_env_var_value_from_list(env_var_list, "__HOME");
		return (path);
	}
	chdir(get_env_var_value_from_list(env_var_list, "__HOME"));
	if (args[1] && ft_strlen(args[1]) > 1)
		path = &(args[1][2]);
	return (path);
}

int	cd_builtin(char **args, t_env_var_node *env_var_list)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (args[1] && args[2])
		return (cd_error());
	if (args[1] && !(ft_strncmp(args[1], "~", 1) == 0))
		path = args[1];
	else
		path = with_tilde_or_none(env_var_list, args);
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
