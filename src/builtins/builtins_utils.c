/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:08:14 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/24 11:42:42 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *command)
{
	short	return_code;

	return_code = FALSE;
	if (!command)
		return_code = FALSE;
	else if (str_equals(command, "echo"))
		return_code = TRUE;
	else if (str_equals(command, "cd"))
		return_code = TRUE;
	else if (str_equals(command, "pwd"))
		return_code = TRUE;
	else if (str_equals(command, "export"))
		return_code = TRUE;
	else if (str_equals(command, "unset"))
		return_code = TRUE;
	else if (str_equals(command, "env"))
		return_code = TRUE;
	else if (str_equals(command, "exit"))
		return_code = TRUE;
	return (return_code);
}
