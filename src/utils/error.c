/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:41:59 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/25 00:42:06 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_msg(char *command, char *msg)
{
	ft_putstr_fd(SHELL_ERROR_SIGNATURE, STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	exit_with_error(char *command, char *msg, int error)
{
	print_error_msg(command, msg);
	close_all_fds();
	exit(error);
}

void	print_perror_msg(char *command, char *perror_msg)
{
	ft_putstr_fd(SHELL_ERROR_SIGNATURE, STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(perror_msg);
}

void	exit_with_perror(char *command, char *perror_msg, int error)
{
	print_perror_msg(command, perror_msg);
	close_all_fds();
	rl_clear_history();
	exit(error);
}

void	print_var_name_error_msg(char *command, char *varname)
{
	ft_putstr_fd(SHELL_ERROR_SIGNATURE, STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(varname, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
