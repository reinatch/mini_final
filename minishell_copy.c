//
	/* ************************************************************************** */
//
	/*                                                                            */
//
	/*                                                        :::      ::::::::   */
//
	/*   minishell copy.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+        
	+:+     */
// /*   By: rerodrig <rerodrig@student.42porto.com>          +#+  +:+      
	+#+        */
// /*                                                +#+#+#+#+#+  
	+#+           */
//
	/*   Created: 2024/09/01 14:51:36 by joao-oli          #+#    #+#             */
//
	/*   Updated: 2025/01/23 19:19:48 by rerodrig         ###   ########.fr       */
//
	/*                                                                            */
//
	/* ************************************************************************** */

// #include "../includes/minishell.h"

// static char	*find_exit_status_var_pos(char *input)
// {
// 	while (input && *input)
// 	{
// 		if (*input == '\'')
// 			skip_to_closing_quote(&input);
// 		else if (*input == '$' && *(input + 1) == '?')
// 			return (input);
// 		input++;
// 	}
// 	return (NULL);
// }

// static char	*find_env_var_pos(char *input)
// {
// 	while (*input)
// 	{
// 		if (*input == '\'')
// 			skip_to_closing_quote(&input);
// 		if (*input == '\"')
// 		{
// 			input++;
// 			while (*input && *input != '\"')
// 			{
// 				if (*input == '$' && is_valid_env_var_name_char(input[1]))
// 					return (input);
// 				input++;
// 			}
// 		}
// 		if (*input == '$' && is_valid_env_var_name_char(input[1]))
// 			return (input);
// 		input++;
// 	}
// 	return (NULL);
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_env_var_node *env_vars_list = NULL; // Environment variables list
//     int last_exit_status = EXIT_SUCCESS;
	// Track the last command's exit status
//     char *input; // User input from the shell prompt
//     char **commands; // Split commands if pipes exist
//     char *home; // Temp variable to hold custom __HOME variable
//     int i;

//     // Inline: Initialize environment variables list
//     (void)argc;
//     (void)argv;
//     for (i = 0; envp[i]; i++)
//     {
//         t_env_var_node *new_node = ft_calloc(1, sizeof(t_env_var_node));
//         new_node->env_var = ft_strdup(envp[i]);
//         new_node->next = NULL;

//         if (!env_vars_list)
//         {
//             env_vars_list = new_node;
//         }
//         else
//         {
//             t_env_var_node *aux_node = env_vars_list;
//             while (aux_node->next)
//                 aux_node = aux_node->next;
//             aux_node->next = new_node;
//         }
//     }

//     // Add default OLDPWD if not present
//     if (!get_env("OLDPWD", env_vars_list))
//     {
//         t_env_var_node *new_node = ft_calloc(1, sizeof(t_env_var_node));
//         new_node->env_var = ft_strdup("OLDPWD");
//         new_node->next = NULL;

//         if (!env_vars_list)
//             env_vars_list = new_node;
//         else
//         {
//             t_env_var_node *aux_node = env_vars_list;
//             while (aux_node->next)
//                 aux_node = aux_node->next;
//             aux_node->next = new_node;
//         }
//     }

//     // Add custom __HOME variable
//     home = ft_strjoin("__HOME=", get_env_var_value_from_list(env_vars_list,
			"HOME"));
//     t_env_var_node *home_node = ft_calloc(1, sizeof(t_env_var_node));
//     home_node->env_var = ft_strdup(home);
//     home_node->next = NULL;

//     if (!env_vars_list)
//         env_vars_list = home_node;
//     else
//     {
//         t_env_var_node *aux_node = env_vars_list;
//         while (aux_node->next)
//             aux_node = aux_node->next;
//         aux_node->next = home_node;
//     }
//     free(home);

//     // Main shell loop
//     while (TRUE)
//     {
//         // Set up signal handling for an interactive shell
//         setup_interactive_signal_handling();

//         // Inline: Read command
//         input = readline(SHELL_PROMPT);
//         if (!input)
//         {
//             exit_builtin(NULL, &env_vars_list); // Handle EOF or Ctrl-D
//         }
//         if (*input)
//             add_history(input); // Add non-empty input to history

//         // Inline: Input validation
//         short is_valid = TRUE;

//         // 1. Check if input is empty
//         if (!input || is_empty(input))
//         {
//             is_valid = FALSE;
//         }
//         // 2. Check for unclosed quotes
//         else
//         {
//            // Inline: Check for unclosed quotes
// 			char last_opened = 0;
// 			char *str = input;
// 			while (*str)
// 			{
// 				if (!last_opened && (*str == '\'' || *str == '"'))
// 					last_opened = *str; // Open a quote
// 				else if (last_opened && *str == last_opened)
// 					last_opened = 0; // Close the currently open quote
// 				str++;
// 			}
// 			if (last_opened)
// 			{
// 				ft_putstr_fd("You forgot to close some quotes 🌝\n",
					STDERR_FILENO);
// 				is_valid = FALSE;
// 			}
//         }

//         // 3. Check for invalid syntax
//         if (is_valid && is_invalid_syntax(input))
//         {
//             last_exit_status = 2;
//             is_valid = FALSE;
//         }

// // 4. Process heredocs
// if (is_valid)
// {
//     int heredoc_number = -1;
//     char *heredoc_position = input;

//     while (heredoc_position)
//     {
//         // Inline heredoc position detection
//         while (*heredoc_position && *(heredoc_position + 1))
//         {
//             if (is_quote(*heredoc_position))
//                 skip_to_closing_quote(&heredoc_position);
//             if (*heredoc_position == '<' && *(heredoc_position + 1) == '<')
//                 break ;  // Found heredoc start
//             heredoc_position++;
//         }

//         // If heredoc position found
//         if (*(heredoc_position) == '<' && *(heredoc_position + 1) == '<')
//         {
//             *heredoc_position = --heredoc_number;
//             heredoc_position++;  // Move past the "<" characters

//             char *delimiter = get_redirect_argument(heredoc_position, 1);

//             // Fork for heredoc processing
//             int child_pid = fork();
//             setup_heredoc_execution_signal_handling(child_pid);

//             if (child_pid == -1)
//                 print_perror_msg("fork - heredoc_prompt", delimiter);
//             else if (child_pid == 0)  // Child process for heredoc reading
//             {
//                 char *line_read;
//                 char *filename = get_tmp_filename(heredoc_number);
//                 int tmp_file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC,
		0644);
//                 free(filename);

//                 line_read = readline("> ");
//                 while (line_read && !str_equals(line_read, delimiter))
//                 {
//                     expand_exit_status_var(&line_read, last_exit_status);
//                     expand_env_vars(&line_read, env_vars_list);
//                     ft_putstr_fd(line_read, tmp_file_fd);
//                     ft_putchar_fd('\n', tmp_file_fd);
//                     free(line_read);
//                     line_read = readline("> ");
//                 }
//                 if (!line_read)
//                     print_error_msg("warning: heredoc delimited by EOF",
	delimiter);

//                 free(line_read);
//                 close(tmp_file_fd);
//                 free(delimiter);
//                 free_env_var_list(&env_vars_list);
//                 rl_clear_history();
//                 exit(EXIT_SUCCESS);
//             }
//             else  // Parent process
//             {
//                 last_exit_status = wait_for_child(child_pid, TRUE);
//                 setup_interactive_signal_handling();
//                 if (last_exit_status != EXIT_SUCCESS)
//                 {
//                     free(delimiter);
//                     is_valid = FALSE;
//                     break ;
//                 }
//             }

//             free(delimiter);
//         }
//         else
//         {
//             break ;  // No more heredoc positions found
//         }
//     }
// }

//         // Execute if input is valid
//         if (is_valid)
//         {
//             // Inline: Handle expansions
//             // Expand exit status variable ($?)
//             char *exit_status_var_pos = find_exit_status_var_pos(input);
//             char *last_exit_status_str = ft_itoa(last_exit_status);
//             while (exit_status_var_pos)
//             {
//                 *exit_status_var_pos = '\0';
//                 ft_strjoin_multiple(&input, last_exit_status_str,
	exit_status_var_pos + 2);
//                 exit_status_var_pos = find_exit_status_var_pos(input);
//             }
//             free(last_exit_status_str);

//             // Expand environment variables ($VAR_NAME)
//             char *env_var_pos = find_env_var_pos(input);
//             while (env_var_pos)
//             {
//                 int name_size = 0;
//                 while (is_valid_env_var_name_char(env_var_pos[name_size
		+ 1]))
//                     name_size++;
//                 char *var_name = ft_substr(env_var_pos, 1, name_size);
//                 *env_var_pos = '\0';
//                 char *var_value = get_env_var_value_from_list(env_vars_list,
		var_name);
//                 if (!var_value)
//                     var_value = ft_strdup("");
//                 ft_strjoin_multiple(&input, var_value, (env_var_pos + 1
		+ name_size));
//                 free(var_name);
//                 env_var_pos = find_env_var_pos(input);
//             }

//             // Check if the input contains pipes
//             if (has_pipes(input))
//             {
//                 // Split the input into separate commands
//                 commands = split_commands(input);

//                 // Execute multiple commands (with pipes)
//                 last_exit_status = run_multiple_commands(commands,
		&env_vars_list);

//                 // Free the allocated memory for commands
//                 free_array(commands);
//             }
//             else
//             {
//                 // Execute a single command (no pipes)
//                 last_exit_status = run_single_command(input, &env_vars_list);
//             }
//         }

//         // Free the input string after processing
//         free(input);
//     }

//     // Cleanup environment variables and exit
//     free_env_var_list(&env_vars_list);
//     return (last_exit_status);
// }
