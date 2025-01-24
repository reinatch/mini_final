/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:28:45 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/24 11:42:12 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var_value_from_list(t_env_var_node *env_var_list,
		char *var_name)
{
	t_env_var_node	*aux;

	aux = get_env(var_name, env_var_list);
	if (!aux)
		return (NULL);
	return (get_env_var_value(aux->env_var));
}

t_env_var_node	*get_env(char *name, t_env_var_node *env_var_list)
{
	t_env_var_node	*aux;
	int				size;

	aux = env_var_list;
	size = ft_strlen(name);
	while (aux)
	{
		if (ft_strncmp(name, aux->env_var, size) == 0)
		{
			if (aux->env_var[size] == '=')
				return (aux);
		}
		aux = aux->next;
	}
	return (NULL);
}

void	replace_env_var(char *name, char *value, t_env_var_node *env_var_list)
{
	t_env_var_node	*aux;
	char			*new_keypair;

	new_keypair = create_env_var(name, value);
	if (!new_keypair)
		return ;
	aux = get_env(name, env_var_list);
	if (!aux)
	{
		add_to_env_var_list(&env_var_list, new_keypair);
		free(new_keypair);
		return ;
	}
	free(aux->env_var);
	aux->env_var = new_keypair;
}

size_t	get_env_var_list_size(t_env_var_node *env_var_list)
{
	size_t			size;
	t_env_var_node	*aux;

	size = 0;
	aux = env_var_list;
	while (aux)
	{
		size++;
		aux = aux->next;
	}
	return (size);
}

char	**list_to_envp_format(t_env_var_node *env_var_list)
{
	char			**envp;
	t_env_var_node	*aux;
	int				i;

	envp = calloc(get_env_var_list_size(env_var_list) + 1, sizeof(char *));
	aux = env_var_list;
	i = 0;
	while (aux)
	{
		envp[i] = ft_strdup(aux->env_var);
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}
