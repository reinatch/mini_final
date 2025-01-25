/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:15:25 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/25 00:39:39 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_arg_size(char *arg_str)
{
	int	arg_end;

	arg_end = 0;
	while (arg_str[arg_end] && !is_name_delimeter(arg_str[arg_end]))
	{
		if (arg_str[arg_end] == '\'')
		{
			remove_char_at(&arg_str[arg_end]);
			while (arg_str[arg_end] && arg_str[arg_end] != '\'')
				arg_end++;
			remove_char_at(&arg_str[arg_end]);
		}
		else if (arg_str[arg_end] == '"')
		{
			remove_char_at(&arg_str[arg_end]);
			while (arg_str[arg_end] && arg_str[arg_end] != '"')
				arg_end++;
			remove_char_at(&arg_str[arg_end]);
		}
		else if (arg_str[arg_end] && !is_name_delimeter(arg_str[arg_end]))
			arg_end++;
	}
	return (arg_end);
}

char	*get_redirect_argument(char *redirect_str, short redirect_token_size)
{
	int		arg_start;
	int		arg_size;
	char	*redirect_arg;
	char	*remaining_cmd;

	arg_start = 0;
	while (redirect_token_size > 0)
	{
		remove_char_at(&redirect_str[arg_start]);
		redirect_token_size--;
	}
	while (is_whitespace(redirect_str[arg_start]))
		arg_start++;
	arg_size = get_arg_size(&redirect_str[arg_start]);
	redirect_arg = ft_substr(redirect_str, arg_start, arg_size);
	remaining_cmd = &redirect_str[arg_start + arg_size];
	ft_memmove(redirect_str, remaining_cmd, ft_strlen(remaining_cmd) + 2);
	return (redirect_arg);
}

char	*get_tmp_filename(int heredoc_number)
{
	char	filename[30];
	char	*number_str;

	ft_bzero(filename, 30);
	number_str = ft_itoa(heredoc_number);
	ft_strlcat(filename, "/tmp/heredoc", 30);
	ft_strlcat(filename, number_str, 30);
	free(number_str);
	return (ft_strdup(filename));
}
