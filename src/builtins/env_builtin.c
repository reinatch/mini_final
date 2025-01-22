/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:03:57 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 00:13:46 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_builtin(t_env_var_node *env_var_list)
{
	t_env_var_node	*aux;

	aux = env_var_list;
	while (aux)
	{
		if (ft_strchr(aux->env_var, '='))
			ft_putendl_fd(aux->env_var, STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}
