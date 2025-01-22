/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-oli <joao-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:04:06 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/22 08:03:50 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_env_vars(t_env_var_node *env_var_list)
{
	t_env_var_node	*aux;

	aux = env_var_list;
	while (aux)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(get_env_var_name(aux->env_var), STDOUT_FILENO);
		if (ft_strchr(aux->env_var, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(get_env_var_value(aux->env_var), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}

static int	add_env_vars(char **args, t_env_var_node **env_var_list)
{
	char	*key_pair;
	char	*var_name;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	while (*args)
	{
		key_pair = *args;
		var_name = get_env_var_name(key_pair);
		if (!is_valid_env_var_name(var_name) || str_equals(key_pair, "="))
		{
			print_var_name_error_msg("export", key_pair);
			exit_status = EXIT_FAILURE;
		}
		else if (get_env(var_name, *env_var_list))
			replace_env_var(var_name, get_env_var_value(key_pair),
				*env_var_list);
		else
			add_to_env_var_list(env_var_list, key_pair);
		free(var_name);
		args++;
	}
	return (exit_status);
}

int	export_builtin(char **args, t_env_var_node **env_var_list)
{
	args++;
	if (!*args)
		return (print_env_vars(*env_var_list));
	else
		return (add_env_vars(args, env_var_list));
}
