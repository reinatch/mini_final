/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:13:45 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 09:34:08 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define NOT_EXECUTABLE 126
# define OUT_OF_RANGE 255
# define BUILTIN_MISUSE 2
# define FORK_ERROR -1
# define CMD_NOT_FOUND_MSG "command not found"
# define NOT_EXECUTABLE_MSG "Is a directory"

void	print_error_msg(char *command, char *msg);
void	exit_with_error(char *command, char *msg, int error);
void	print_perror_msg(char *command, char *perror_msg);
void	exit_with_perror(char *command, char *perror_msg, int error);
void	print_var_name_error_msg(char *command, char *varname);

#endif
