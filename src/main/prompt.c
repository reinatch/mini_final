/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:29:21 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/24 11:38:29 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_command(t_env_var_node *env_vars)
{
	char	*input;

	input = readline(SHELL_PROMPT);
	if (!input)
		exit_builtin(NULL, &env_vars);
	if (*input)
		add_history(input);
	return (input);
}
