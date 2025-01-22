/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:45:56 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 00:13:46 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_input(char *input, int *exit_status, t_env_var_node *env_var_list)
{
	short	result;

	result = TRUE;
	if (is_empty(input))
		result = FALSE;
	else if (is_invalid_syntax(input))
	{
		*exit_status = 2;
		result = FALSE;
	}
	else if (!process_present_heredocs(input, exit_status, env_var_list))
		result = FALSE;
	return (result);
}
