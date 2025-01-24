/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_str_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:39 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/24 11:42:28 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var_name(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	return (ft_substr(env_var, 0, i));
}

char	*get_env_var_value(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=' && env_var[i])
		i++;
	if (!env_var[i])
		return (ft_strdup(""));
	return (&env_var[i + 1]);
}

char	*create_env_var(char *name, char *value)
{
	char	*env_var_definition;
	int		size;
	int		i;

	size = ft_strlen(name) + ft_strlen(value) + 2;
	env_var_definition = ft_calloc(size, sizeof(char));
	i = 0;
	while (*name)
		env_var_definition[i++] = *name++;
	env_var_definition[i++] = '=';
	while (*value)
		env_var_definition[i++] = *value++;
	env_var_definition[i] = '\0';
	return (env_var_definition);
}
