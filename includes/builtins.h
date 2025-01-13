/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:23:07 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/13 09:34:08 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env_var_list.h"

int	is_builtin(char *command);
int	cd_builtin(char **args, t_env_var_node *env_var_list);
int	echo_builtin(char **args);
int	pwd_builtin(void);
int	export_builtin(char **args, t_env_var_node **env_var_list);
int	env_builtin(t_env_var_node *env_var_list);
int	unset_builtin(char **args, t_env_var_node **env_var_list);
int	exit_builtin(char **args, t_env_var_node **env_var_list);

// utils
int	is_valid_env_var_name_char(char c);
int	is_valid_env_var_name(char *name);

#endif
