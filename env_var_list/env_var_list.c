/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:28:53 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 11:59:56 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_var_node	*init_env_var_list(char **env_vars)
{
	t_env_var_node	*env_var_list;
	char			*home;
	int				i;

	env_var_list = NULL;
	i = 0;
	while (env_vars[i])
	{
		add_to_env_var_list(&env_var_list, env_vars[i]);
		i++;
	}
	if (!get_env_var_node("OLDPWD", env_var_list))
		add_to_env_var_list(&env_var_list, "OLDPWD");
	home = ft_strjoin("__HOME=", get_env_var_value_from_list(env_var_list,
				"HOME"));
	add_to_env_var_list(&env_var_list, home);
	free(home);
	return (env_var_list);
}

void	add_to_env_var_list(t_env_var_node **env_var_list, char *env_var)
{
	t_env_var_node	*new_node;
	t_env_var_node	*aux_node;

	new_node = ft_calloc(1, sizeof(t_env_var_node));
	new_node->env_var = ft_strdup(env_var);
	new_node->next = NULL;
	if (!*env_var_list)
	{
		*env_var_list = new_node;
		return ;
	}
	aux_node = *env_var_list;
	while (aux_node->next)
		aux_node = aux_node->next;
	aux_node->next = new_node;
}
