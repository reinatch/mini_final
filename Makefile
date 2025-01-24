# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 12:05:11 by rerodrig          #+#    #+#              #
#    Updated: 2025/01/23 13:31:27 by rerodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		 =	minishell
CFLAGS		 =	-Wall -Wextra -Werror -g
LDLIBS		 =	-lreadline -lft
LDFLAGS		 += 	-L./libft
OBJ_DIR		 =	build
OBJS		 =	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
SRC_DIR 	 = src/
SRCS		 =	$(MAIN) $(ENV_VAR_LIST) $(BUILTINS) $(EXECUTES) $(REDIRECTS) $(UTILS) \
			 	$(EXPANDS) $(SYNTAX)
MAIN		 =	src/main/minishell.c src/main/prompt.c src/main/split_commands.c src/main/handle_heredoc.c\
			 	src/main/input_error.c
SYNTAX		 =	src/syntax/syntax.c src/syntax/syntax_utils.c
ENV_VAR_LIST =	src/env_var_list/env_var_list.c src/env_var_list/env_var_list_utils.c src/env_var_list/env_var_str_utils.c src/env_var_list/free_env_var_list.c
BUILTINS 	 =	src/builtins/builtins_utils.c src/builtins/echo_builtin.c src/builtins/cd_builtin.c src/builtins/pwd_builtin.c src/builtins/export_builtin.c src/builtins/unset_builtin.c src/builtins/env_builtin.c src/builtins/exit_builtin.c
EXECUTES 	 =	src/executes/run_single_command.c src/executes/run_multiple_commands.c src/executes/wait.c \
				src/executes/run_non_builtin.c src/executes/run_builtin.c src/executes/args_processing_utils.c src/executes/path_handling_utils.c \
				src/executes/redirect_handling_utils.c src/executes/multiple_commands_utils.c src/executes/pipes.c
REDIRECTS 	 =	src/redirects/redirect_utils.c src/redirects/redirect_input.c src/redirects/redirect_output.c \
				src/redirects/redirect_heredoc.c
UTILS		 =	src/utils/error.c src/utils/signals.c src/utils/str_utils.c src/utils/str_checkers.c \
				src/utils/ft_atoll.c src/utils/free_array.c src/utils/arr_len.c src/utils/file_descriptors.c \
				src/utils/heredoc_utils.c src/utils/skip_quotes.c
EXPANDS		 =	src/expansions/expansion_handling.c src/expansions/env_vars_utils.c
LIBFT_A		 =	./libft/libft.a
HEADER		 =	src/includes/minishell.h src/includes/allowed_libs.h src/includes/builtins.h src/includes/errors.h src/includes/executes.h src/includes/env_var_list.h
VPATH		 =	src/builtins src/env_var_list src/utils src/executes src/main src/redirects src/includes src/expansions \
				src/syntax
INCLUDE		 =	-I ./src -I ./src/includes

all: $(NAME)

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "removed $(OBJ_DIR) folder"

fclean: clean
	@rm -rf $(NAME)
	@echo "removed executable"

re: fclean all

$(LIBFT_A):
	make --directory=./libft

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ_DIR):
	mkdir -p $@

leak: all
	valgrind --leak-check=full \
	--show-leak-kinds=all --track-fds=yes --suppressions=ignore_readline.supp ./$(NAME)

test: all
	cd minishell_tester && ./tester