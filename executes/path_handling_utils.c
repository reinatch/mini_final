/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handling_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:15:41 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 11:59:56 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	build_full_path(char base[], char *part1, char *part2, char *part3)
{
	*base = 0;
	ft_strlcat(base, part1, PATH_MAX);
	ft_strlcat(base, part2, PATH_MAX);
	ft_strlcat(base, part3, PATH_MAX);
}

static int	is_relative_path(char *command)
{
	if (*command == '.')
		command++;
	if (*command == '.')
		command++;
	if (*command == '/')
		return (TRUE);
	return (FALSE);
}

static char	*build_relative_path(char *command, t_env_var_node *env_var_list)
{
	char	absolute_path[PATH_MAX];

	if (*command == '/')
		return (ft_strdup(command));
	absolute_path[0] = 0;
	build_full_path(absolute_path, get_env_var_value_from_list(env_var_list,
			"PWD"), "/", command);
	return (ft_strdup(absolute_path));
}

char	*find_command(char *command, t_env_var_node *env_var_list)
{
	char	*path_env_var_value;
	char	**dirs_in_path;
	char	current_path[PATH_MAX];
	char	**dirs_start;

	if (is_relative_path(command))
		return (build_relative_path(command, env_var_list));
	path_env_var_value = get_env_var_value_from_list(env_var_list, "PATH");
	dirs_in_path = ft_split(path_env_var_value, ':');
	dirs_start = dirs_in_path;
	while (dirs_in_path && *dirs_in_path)
	{
		build_full_path(current_path, *dirs_in_path, "/", command);
		if (access(current_path, F_OK) == 0)
		{
			free_array(dirs_start);
			return (ft_strdup(current_path));
		}
		dirs_in_path++;
	}
	free_array(dirs_start);
	return (NULL);
}
