/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:51:24 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 12:28:12 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_exit_status_var_pos(char *input)
{
	while (input && *input)
	{
		if (*input == '\'')
			skip_to_closing_quote(&input);
		else if (*input == '$' && *(input + 1) == '?')
			return (input);
		input++;
	}
	return (NULL);
}

void	expand_exit_status_var(char **input, int last_exit_status)
{
	char	*exit_status_var_pos;
	char	*last_exit_status_str;

	last_exit_status_str = ft_itoa(last_exit_status);
	exit_status_var_pos = find_exit_status_var_pos(*input);
	while (exit_status_var_pos)
	{
		*exit_status_var_pos = '\0';
		ft_strjoin_multiple(input, last_exit_status_str,
			exit_status_var_pos + 2);
		exit_status_var_pos = find_exit_status_var_pos(*input);
	}
	free(last_exit_status_str);
}

static char	*find_env_var_pos(char *input)
{
	while (*input)
	{
		if (*input == '\'')
			skip_to_closing_quote(&input);
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && is_valid_env_var_name_char(input[1]))
					return (input);
				input++;
			}
		}
		if (*input == '$' && is_valid_env_var_name_char(input[1]))
			return (input);
		input++;
	}
	return (NULL);
}

void	expand_env_vars(char **input, t_env_var_node *env_var_list)
{
	char	*env_var_pos;
	char	*var_name;
	char	*var_value;
	int		name_size;

	env_var_pos = find_env_var_pos(*input);
	if (env_var_pos)
	{
		name_size = 0;
		while (is_valid_env_var_name_char(env_var_pos[name_size + 1]))
			name_size++;
		var_name = ft_substr(env_var_pos, 1, name_size);
		*env_var_pos = '\0';
		var_value = get_env_var_value_from_list(env_var_list, var_name);
		if (!var_value)
			var_value = ft_strdup("");
		ft_strjoin_multiple(input, var_value, (env_var_pos + 1 + name_size));
		free(var_name);
		expand_env_vars(input, env_var_list);
	}
}

void	handle_expansions(char **input, t_env_var_node *env_var_list,
		int last_exit_status)
{
	expand_exit_status_var(input, last_exit_status);
	expand_env_vars(input, env_var_list);
}
