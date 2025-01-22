/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:04:17 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 00:13:46 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	remove_from_env_var_list(char *varname,
				t_env_var_node **env_var_list);
static void	del_next_node(t_env_var_node **node);

int	unset_builtin(char **args, t_env_var_node **env_var_list)
{
	char	*varname;
	int		exit_status;

	args++;
	exit_status = EXIT_SUCCESS;
	if (!*args)
		return (FAILED);
	while (*args)
	{
		varname = *args;
		if (!is_valid_env_var_name(varname))
		{
			print_var_name_error_msg("unset", varname);
			exit_status = EXIT_FAILURE;
		}
		else
			remove_from_env_var_list(varname, env_var_list);
		args++;
	}
	return (exit_status);
}

static void	remove_from_env_var_list(char *varname,
		t_env_var_node **env_var_list)
{
	t_env_var_node	*aux;

	aux = *env_var_list;
	while (aux && aux->next)
	{
		if (ft_strncmp((aux->next)->env_var, varname, ft_strlen(varname)) == 0)
		{
			if ((aux->next)->env_var[ft_strlen(varname)] == '=')
				return (del_next_node(&aux));
		}
		aux = aux->next;
	}
}

static void	del_next_node(t_env_var_node **node)
{
	t_env_var_node	*temp;

	temp = (*node)->next;
	(*node)->next = ((*node)->next)->next;
	free(temp->env_var);
	free(temp);
}
