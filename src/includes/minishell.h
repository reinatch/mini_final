/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:36:50 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 08:03:50 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# define SHELL_ERROR_SIGNATURE "Mini(S)Hell$: "
# define SHELL_PROMPT "Mini(S)Hell$ > "
# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define PATH_MAX 4096
# define LLONG_MAX 9223372036854775807
# define WHITE_SPACES " \t\n\r\v\f"
# define NAME_DELIMITERS " \t\n\r\v\f><|"

# define NO_REDIRECT -1

# include "allowed_libs.h"
# include "builtins.h"
# include "env_var_list.h"
# include "errors.h"
# include "executes.h"

// minishell
int			run_minishell(t_env_var_node *env_var_list);

// prompt
char		*read_command(t_env_var_node *env_var_list);

// syntax
int			is_valid_input(char *input, int *exit_status,
				t_env_var_node *env_var_list);
int			is_invalid_syntax(char *input);
int			is_invalid_token(char c);
int			unexpected_token(char *input);
int			syntax_error(char *token);
char		*get_next_pipe(char *str);

// heredoc_prompt
int			process_present_heredocs(char *input, int *exit_status,
				t_env_var_node *env_var_list);

// tratativas
void		handle_expansions(char **input, t_env_var_node *env_var_list,
				int exit_status);
void		expand_env_vars(char **input, t_env_var_node *env_var_list);
void		expand_exit_status_var(char **input, int exit_status);

// command table
char		**split_commands(char *input);

// tokenizer
char		**split_args(char *command);

// signals
void		setup_interactive_signal_handling(void);
void		setup_non_interactive_signal_handling(int child_pid);
void		setup_heredoc_execution_signal_handling(int child_pid);

// utils
int			str_equals(const char *str1, const char *str2);
short		is_quote(char c);
short		is_empty(char *str);
short		is_name_delimeter(char c);
short		is_whitespace(char c);
short		has_pipes(char *str);
void		free_array(char **arr);
int			count_matrix_lines(char **arr);
long long	ft_atoll(const char *str);
void		remove_char_at(char *str);
char		*get_token_position(char *str, char *token);
void		skip_to_closing_quote(char **str);
void		ft_strjoin_multiple(char **first, char *second, char *third);
void		mark_char_inside_delimiter(char *str, char target_char,
				char delimeter);
void		restore_marked_chars(char **matrix, char restore_char);

#endif
