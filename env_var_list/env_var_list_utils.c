/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:28:45 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 11:59:56 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var_value_from_list(t_env_var_node *env_var_list,
		char *var_name)
{
	t_env_var_node	*aux;

	aux = get_env_var_node(var_name, env_var_list);
	if (!aux)
		return (NULL);
	return (get_env_var_value(aux->env_var));
}

t_env_var_node	*get_env_var_node(char *name, t_env_var_node *env_var_list)
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

	aux = get_env_var_node(name, env_var_list);
	if (aux)
		free(aux->env_var);
	new_keypair = create_env_var(name, value);
	add_to_env_var_list(&env_var_list, new_keypair);
	aux->env_var = new_keypair;
	return ;
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
