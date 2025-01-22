/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_var_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:15:58 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 08:03:50 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_var_list(t_env_var_node **env_var_list)
{
	t_env_var_node	*aux;
	t_env_var_node	*next;

	aux = *env_var_list;
	while (aux)
	{
		free(aux->env_var);
		next = aux->next;
		free(aux);
		aux = next;
	}
	*env_var_list = NULL;
}
