/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:12:00 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 08:03:50 by rerodrig         ###   ########.fr       */
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

static void	check_args_error(char **args)
{
	char	*exit_status;

	if (!args || !args[1])
	{
		if (args)
			free_array(args);
		close_all_fds();
		exit(EXIT_SUCCESS);
	}
	exit_status = args[1];
	if (!fits_in_long_long(exit_status))
	{
		free_array(args);
		exit_with_error("exit", "numeric argument required", BUILTIN_MISUSE);
	}
	if (args[2] != NULL)
	{
		free_array(args);
		exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
}

int	exit_builtin(char **args, t_env_var_node **env_var_list)
{
	int	exit_status;

	rl_clear_history();
	free_env_var_list(env_var_list);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	check_args_error(args);
	close_all_fds();
	exit_status = ft_atoll(args[1]);
	free_array(args);
	exit(exit_status);
}
