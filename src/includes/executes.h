/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:41:13 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 00:03:52 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTES_H
# define EXECUTES_H

# define IN 0
# define OUT 1

// executes
int		run_single_command(char *command, t_env_var_node **env_var_list);
int		run_multiple_commands(char **commands, t_env_var_node **env_var_list);

// one command utils
int		handle_input_redirect(char *command, int original_fds[2]);
int		handle_output_redirect(char *command, int original_fds[2]);

// multiple commands utils
int		*init_children_pid(char **commands);
void	clean_after_execute(int *children_pid);
void	quit_child(char **commands, t_env_var_node **env_var_list);

// execute builtin
int		run_forked_builtin(char **args, t_env_var_node **env_var_list);
int		run_builtin(char **args, t_env_var_node **env_var_list);

// execute external
int		run_external(char **args, t_env_var_node *env_var_list);
char	*find_command(char *command, t_env_var_node *env_var_list);

// wait after fork
int		wait_for_child(int child_pid, int is_last_child);
int		wait_for_children(int children_pid[1024]);

// redirects
void	redirect_fd(int fd_to_redirect, int fd_location);
int		redirect_input(char *command);
int		redirect_output(char *command);
char	*get_next_redirect_pos(char *str);
void	close_all_fds(void);
void	close_extra_fds(void);
char	*get_redirect_argument(char *redirect_str, short redirect_token_size);
char	*get_tmp_filename(int heredoc_number);
void	redirect_heredoc(char *heredoc_pos);
int		handle_redirects_for_single(char *command);
void	restore_original_fds(int original_fds[2]);
void	save_original_fds(int original_fds[2]);

// pipes
void	handle_pipe(int original_out, char *current_command, char **commands);

#endif
