/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:19:08 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/21 16:24:57 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_env_var_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_env_var_name(char *name)
{
	if (!ft_isalpha(*name))
		return (FALSE);
	while (*name)
	{
		if (!is_valid_env_var_name_char(*name))
			return (FALSE);
		name++;
	}
	return (TRUE);
}
