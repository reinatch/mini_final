/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:03:57 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/24 11:43:02 by rerodrig         ###   ########.fr       */
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
