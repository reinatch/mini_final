/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_var_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:15:58 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/24 11:42:34 by rerodrig         ###   ########.fr       */
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
