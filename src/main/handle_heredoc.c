/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:46:10 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/22 00:13:25 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_heredoc_position(char *str)
{
	while (*str && str[1])
	{
		if (is_quote(*str))
			skip_to_closing_quote(&str);
		if (*str == '<' && str[1] == '<')
			return (str);
		str++;
	}
	return (NULL);
}

void	read_heredoc(int *exit_status, t_env_var_node *env_var_list,
		char *delimiter, int heredoc_number)
{
	char	*line_read;
	char	*filename;
	int		tmp_file_fd;

	filename = get_tmp_filename(heredoc_number);
	tmp_file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(filename);
	line_read = readline("> ");
	while (line_read && !str_equals(line_read, delimiter))
	{
		expand_exit_status_var(&line_read, *exit_status);
		expand_env_vars(&line_read, env_var_list);
		ft_putstr_fd(line_read, tmp_file_fd);
		ft_putchar_fd('\n', tmp_file_fd);
		free(line_read);
		line_read = readline("> ");
	}
	if (!line_read)
		print_error_msg("warning: heredoc delimited by EOF", delimiter);
	free(line_read);
	close(tmp_file_fd);
	free(delimiter);
	free_env_var_list(&env_var_list);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

int	exec_heredoc(char *delimiter, int heredoc_number, int *exit_status,
		t_env_var_node *env_var_list)
{
	int	child_pid;

	child_pid = fork();
	setup_heredoc_execution_signal_handling(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork - heredoc_prompt", delimiter);
	else if (child_pid == 0)
		read_heredoc(exit_status, env_var_list, delimiter, heredoc_number);
	else
	{
		*exit_status = wait_for_child(child_pid, TRUE);
		setup_interactive_signal_handling();
		if (*exit_status != EXIT_SUCCESS)
			return (FAILED);
	}
	return (SUCCESS);
}

int	process_present_heredocs(char *input, int *exit_status,
		t_env_var_node *env_var_list)
{
	int		heredoc_number;
	char	*heredoc_position;
	char	*delimiter;

	heredoc_number = -1;
	heredoc_position = get_heredoc_position(input);
	while (heredoc_position)
	{
		*heredoc_position = --heredoc_number;
		heredoc_position++;
		delimiter = get_redirect_argument(heredoc_position, 1);
		if (!exec_heredoc(delimiter, heredoc_number, exit_status, env_var_list))
		{
			free(delimiter);
			return (FAILED);
		}
		free(delimiter);
		heredoc_position = get_heredoc_position(input);
	}
	return (SUCCESS);
}
