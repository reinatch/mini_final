/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:27 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 00:03:52 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_LIST_H
# define ENV_VAR_LIST_H

typedef struct s_env_var_node
{
	char					*env_var;
	struct s_env_var_node	*next;
}							t_env_var_node;

t_env_var_node				*init_env_var_list(char **envp);
t_env_var_node				*get_env(char *name,
								t_env_var_node *env_var_list);
char						*get_env_var_value_from_list(
								t_env_var_node *env_var_list, char *name);
void						replace_env_var(char *name, char *value,
								t_env_var_node *env_var_list);
void						add_to_env_var_list(t_env_var_node **list,
								char *key_pair);
char						**list_to_envp_format(t_env_var_node *env_var_list);
void						free_env_var_list(t_env_var_node **env_var_list);
char						*create_env_var(char *name, char *value);
char						*get_env_var_name(char *key_pair);
char						*get_env_var_value(char *key_pair);

#endif
