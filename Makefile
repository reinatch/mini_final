# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 12:05:11 by rerodrig          #+#    #+#              #
#    Updated: 2025/01/13 12:05:14 by rerodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 =	minishell
CFLAGS		 =	-Wall -Wextra -Werror -g
LDLIBS		 =	-lreadline -lft
LDFLAGS		 += 	-L./libft
OBJ_DIR		 =	obj
OBJS		 =	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS		 =	$(MAIN) $(ENV_VAR_LIST) $(BUILTINS) $(EXECUTES) $(REDIRECTS) $(UTILS) \
			 	$(EXPANDS) $(SYNTAX)
MAIN		 =	minishell.c prompt.c split_commands.c handle_heredoc.c\
			 	input_error.c
SYNTAX		 =	syntax.c syntax_utils.c
ENV_VAR_LIST =	env_var_list.c env_var_list_utils.c env_var_str_utils.c free_env_var_list.c
BUILTINS 	 =	builtins_utils.c echo_builtin.c cd_builtin.c pwd_builtin.c export_builtin.c unset_builtin.c env_builtin.c exit_builtin.c
EXECUTES 	 =	run_single_command.c run_multiple_commands.c wait.c \
				run_non_builtin.c run_builtin.c args_processing_utils.c path_handling_utils.c \
				redirect_handling_utils.c multiple_commands_utils.c pipes.c
REDIRECTS 	 =	redirect_utils.c redirect_input.c redirect_output.c \
				redirect_heredoc.c
UTILS		 =	error.c signals.c str_utils.c str_checkers.c \
				ft_atoll.c free_array.c arr_len.c file_descriptors.c \
				heredoc_utils.c skip_quotes.c
EXPANDS		 =	expansion_handling.c env_vars_utils.c
LIBFT_A		 =	./libft/libft.a
HEADER		 =	minishell.h allowed_libs.h builtins.h errors.h executes.h env_var_list.h
VPATH		 =	builtins env_var_list utils executes main redirects includes expansions \
				syntax
INCLUDE		 =	-I ./ -I ./includes

all: $(NAME)

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf obj
	@echo "removed obj folder"

fclean: clean
	@rm -rf $(NAME)
	@echo "removed executable"

re: fclean all

$(LIBFT_A):
	make --directory=./libft

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ_DIR):
	mkdir -p $@

leak: all
	valgrind --leak-check=full \
	--show-leak-kinds=all --track-fds=yes --trace-children=yes ./$(NAME)

test: all
	cd minishell_tester && ./tester
