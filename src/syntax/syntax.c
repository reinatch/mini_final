/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:57 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/21 16:24:57 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	starts_with_pipe(char *input)
{
	if (input[0] == '|')
		return (syntax_error("|"));
	return (FALSE);
}

int	has_redirect_without_target(char *input)
{
	char	*redirect_pos;

	redirect_pos = get_next_redirect_pos(input);
	while (redirect_pos)
	{
		if (redirect_pos[0] == '<' && redirect_pos[1] == '<')
			redirect_pos++;
		else if (redirect_pos[0] == '>' && redirect_pos[1] == '>')
			redirect_pos++;
		redirect_pos++;
		while (is_whitespace(*redirect_pos))
			redirect_pos++;
		if (*redirect_pos == '\0')
			return (syntax_error("newline"));
		if (is_invalid_token(*redirect_pos))
			return (unexpected_token(redirect_pos));
		redirect_pos = get_next_redirect_pos(redirect_pos);
	}
	return (FALSE);
}

int	has_empty_pipe(char *input)
{
	char	*next_pipe;

	next_pipe = get_next_pipe(input);
	while (next_pipe)
	{
		next_pipe++;
		while (is_whitespace(*next_pipe))
			next_pipe++;
		if (*next_pipe == '|')
			return (syntax_error("|"));
		next_pipe = get_next_pipe(next_pipe);
	}
	return (FALSE);
}

int	is_invalid_syntax(char *input)
{
	if (starts_with_pipe(input))
		return (TRUE);
	if (has_redirect_without_target(input))
		return (TRUE);
	if (has_empty_pipe(input))
		return (TRUE);
	return (FALSE);
}
