/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:45:56 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 13:24:07 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_error(void)
{
	ft_putstr_fd("You forgot to close some quotes 🌝\n", STDERR_FILENO);
	return (1);
}

static int	has_unclosed_quotes(char *str)
{
	char	last_opened;

	last_opened = 0;
	while (*str && !last_opened)
	{
		if (*str == '\'' || *str == '"')
			last_opened = *str;
		str++;
	}
	while (*str && last_opened)
	{
		if (*str && *str == last_opened)
			last_opened = 0;
		str++;
	}
	if (*str)
		return (has_unclosed_quotes(str));
	else if (!last_opened)
		return (0);
	else
		return (print_error());
}

int	is_valid_input(char *input, int *exit_status, t_env_var_node *env_var_list)
{
	short	result;

	result = TRUE;
	if (is_empty(input))
		result = FALSE;
	else if (has_unclosed_quotes(input))
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
