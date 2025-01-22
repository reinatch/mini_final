/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:10:17 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/21 16:22:46 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_invalid_token(char c)
{
	if (c == '|')
		return (TRUE);
	if (c == '>')
		return (TRUE);
	if (c == '<')
		return (TRUE);
	return (FALSE);
}

int	unexpected_token(char *input)
{
	if (input[0] == '<' && input[1] == '<')
		return (syntax_error("<<"));
	else if (input[0] == '>' && input[1] == '>')
		return (syntax_error(">>"));
	input[1] = '\0';
	return (syntax_error(input));
}

int	syntax_error(char *token)
{
	ft_putstr_fd(SHELL_ERROR_SIGNATURE, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (TRUE);
}

char	*get_next_pipe(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			skip_to_closing_quote(&str);
		if (*str == '|')
			return (str);
		str++;
	}
	return (NULL);
}
