/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:12:00 by joao-oli          #+#    #+#             */
/*   Updated: 2025/01/24 11:43:08 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fits_in_long_long(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (FALSE);
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (TRUE);
	out = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (FALSE);
		out = out * 10 + c;
		str++;
	}
	return (TRUE);
}

void	prepare_for_exit(char **args, t_env_var_node **env_var_list)
{
	free_array(args);
	free_env_var_list(env_var_list);
	rl_clear_history();
}

int	exit_builtin(char **args, t_env_var_node **env_var_list)
{
	int		exit_status;
	char	*exit_status_str;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_status = EXIT_SUCCESS;
	if (args && args[1] != NULL)
	{
		exit_status_str = args[1];
		if (!fits_in_long_long(exit_status_str))
		{
			prepare_for_exit(args, env_var_list);
			exit_with_error("exit", "numeric argument required",
				BUILTIN_MISUSE);
		}
		else
			exit_status = ft_atoll(exit_status_str);
	}
	if (args && args[1] != NULL && args[2] != NULL)
	{
		print_error_msg("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	prepare_for_exit(args, env_var_list);
	close_all_fds();
	exit(exit_status);
}
