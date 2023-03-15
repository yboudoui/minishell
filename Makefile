# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
#    Updated: 2023/03/15 17:34:22 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

RM					=	rm -f

# **************************************************************************** #

SRCS	=\
./src/utils/string/is_empty.c\
./src/utils/string/ft_atoi.c\
./src/utils/string/str_merge_new_line.c\
./src/utils/string/is_alpha.c\
./src/utils/string/str_merge_list.c\
./src/utils/string/str_join_list.c\
./src/utils/string/str_find_pattern.c\
./src/utils/string/ft_strnstr.c\
./src/utils/string/is_alnum.c\
./src/utils/string/ft_strtrim.c\
./src/utils/string/string_cmp.c\
./src/utils/string/str_merge.c\
./src/utils/string/str_new_empty.c\
./src/utils/string/str_slice_prefix.c\
./src/utils/string/ft_strncmp.c\
./src/utils/string/ft_strlen.c\
./src/utils/string/ft_putstr_fd.c\
./src/utils/string/ft_substr.c\
./src/utils/string/ft_str_find_prefix.c\
./src/utils/string/ft_strchr.c\
./src/utils/string/ft_itoa.c\
./src/utils/string/ft_putchar_fd.c\
./src/utils/string/ft_strjoin.c\
./src/utils/string/ft_split.c\
./src/utils/string/string_end_with.c\
./src/utils/string/list_to_str_array.c\
./src/utils/string/string_array_destroy.c\
./src/utils/string/ft_strrchr.c\
./src/utils/string/ft_strdup.c\
./src/utils/string/str_slice_charset.c\
./src/utils/string/is_space.c\
./src/utils/string/str_slice_section.c\
./src/utils/string/is_digit.c\
./src/utils/list/list_destroy.c\
./src/utils/list/list_create.c\
./src/utils/list/list_last.c\
./src/utils/list/str_array_to_list.c\
./src/utils/list/list_insert.c\
./src/utils/list/ft_lstmap.c\
./src/utils/list/list_add.c\
./src/utils/memory/ft_memcmp.c\
./src/utils/memory/ft_memcpy.c\
./src/utils/memory/ft_calloc.c\
./src/utils/memory/sizeof_array.c\
./src/main.c\
./src/parser/prompt/prompt.c\
./src/parser/lexer/lexer.c\
./src/parser/lexer/matching.c\
./src/parser/lexer/token.c\
./src/parser/syntaxer/commande.c\
./src/parser/environment/insert.c\
./src/parser/environment/environment.c\
./src/parser/environment/definition.c\
./src/parser/environment/environment_list.c\
./src/parser/environment/utils.c\
./src/execution/heredoc/heredoc.c\
./src/execution/cmd.c\
./src/execution/execution.c\
./src/execution/pipex/success.c\
./src/execution/pipex/execute.c\
./src/execution/pipex/cmd.c\
./src/execution/pipex/stat.c\
./src/execution/pipex/get_paths.c\
./src/execution/pipex/pipe.c\
./src/execution/pipex/parse_env.c\
./src/execution/pipex/pipex.c\
./src/execution/pipex/path_null.c\
./src/execution/pipex/error/dup.c\
./src/execution/pipex/error/null_str_err.c\
./src/execution/pipex/error/fork.c\
./src/execution/pipex/error/error.c\
./src/execution/pipex/signal.c\
./src/execution/pipex/free.c\
./src/execution/pipex/wait.c\
./src/execution/pipex/get_cmd_path.c\
./src/execution/pipex/exit.c\
./src/execution/pipex/exec_builtins.c\
./src/execution/pipex/open.c\
./src/execution/pipex/pipeline_status.c\
./src/execution/pipex/redir.c\
./src/execution/builtin/unset.c\
./src/execution/builtin/is_builtin.c\
./src/execution/builtin/exit.c\
./src/execution/builtin/cd.c\
./src/execution/builtin/env.c\
./src/execution/builtin/echo.c\
./src/execution/builtin/export.c\
./src/execution/builtin/pwd.c\
./show/lexer_show.c\

INCS	=\
./show\
./inc/utils\
./inc/utils\
./inc/utils\
./inc/parser\
./inc/parser/prompt/commande\
./inc/parser/prompt\
./inc/parser/environment\
./inc\
./inc/execution/heredoc\
./inc/execution/pipex\
./inc/execution\
./inc/execution/builtin\

OBJS				=	$(SRCS:.c=.o)

# **************************************************************************** #


all:		$(NAME)

$(OBJS): %.o : %.c
		@$(CC) $(CFLAGS) $(addprefix -I , $(INCS)) -c $< -o $@
		@echo $(CC) $(CFLAGS) $@


$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
			@echo $(CC) $(CFLAGS) $(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

fsanitize:	CFLAGS+= -DCOLORED -fsanitize=address -g
fsanitize:	re

#			ASAN_OPTIONS=suppressions=.readline.fsanitize.supp"

valgrind:
			@clear
			@valgrind														\
			-q																\
			--suppressions=./.readline.supp									\
			--leak-check=full												\
			--show-leak-kinds=all											\
			--track-origins=yes												\
			--track-fds=yes													\
			./$(NAME)														\

re_valgrind:	CFLAGS+= -DCOLORED -g3
re_valgrind:	all valgrind

#			--gen-suppressions=yes											\

.PHONY:		all clean fclean re bonus
