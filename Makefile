# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/02/27 14:41:03 by kdhrif           ###   ########.fr        #
=======
#    Updated: 2023/02/27 13:22:46 by yboudoui         ###   ########.fr        #
>>>>>>> 51666af (yboudoui merge)
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

RM					=	rm -f

# **************************************************************************** #

SRCS	=\
./src/utils/string/is_empty.c\
./src/utils/string/str_merge_new_line.c\
./src/utils/string/str_merge_list.c\
./src/utils/string/str_join_list.c\
./src/utils/string/ft_strnstr.c\
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
./src/utils/string/ft_putchar_fd.c\
./src/utils/string/ft_strjoin.c\
./src/utils/string/ft_split.c\
./src/utils/string/string_end_with.c\
./src/utils/string/list_to_str_array.c\
./src/utils/string/string_array_destroy.c\
./src/utils/string/ft_strdup.c\
./src/utils/string/str_slice_charset.c\
./src/utils/string/is_space.c\
./src/utils/string/str_slice_section.c\
./src/utils/list/list_destroy.c\
./src/utils/list/list_create.c\
./src/utils/list/list_last.c\
./src/utils/list/str_array_to_list.c\
./src/utils/list/ft_lstmap.c\
./src/utils/list/list_add.c\
./src/utils/memory/ft_memcpy.c\
./src/utils/memory/ft_calloc.c\
./src/main.c\
./src/parser/prompt/prompt.c\
./src/parser/lexer/lexer.c\
./src/parser/lexer/matching.c\
./src/parser/lexer/token.c\
./src/parser/expander/expander.c\
./src/parser/syntaxer/syntaxer.c\
./src/parser/syntaxer/commande.c\
./src/parser/environment/environment.c\
./src/parser/environment/environment_list.c\
<<<<<<< HEAD
./src/exec/pipex/exit_macro.c\
./src/exec/pipex/dup.c\
./src/exec/pipex/null_str_err.c\
./src/exec/pipex/free_str.c\
./src/exec/pipex/success.c\
./src/exec/pipex/get_next_line_utils.c\
./src/exec/pipex/fork.c\
./src/exec/pipex/get_next_line.c\
./src/exec/pipex/pipe.c\
./src/exec/pipex/error.c\
./src/exec/pipex/pipex.c\
./src/exec/pipex/exception.c\
./src/exec/pipex/path_null.c\
./src/exec/pipex/open.c\
./src/exec/pipex/close.c\
./src/exec/pipex/pipeline_status.c\
./src/exec/pipex/heredoc.c\
=======
./src/execution/heredoc/heredoc.c\
./src/execution/execution.c\
./show/lexer_show.c\
>>>>>>> 51666af (yboudoui merge)

INCS	=\
./show\
./inc/utils/string\
./inc/utils/list\
./inc/utils\
./inc/utils/memory\
./inc/heredoc\
./inc/parser\
./inc/parser/prompt/commande\
./inc/parser/prompt\
./inc/parser/lexer\
./inc/parser/lexer\
./inc/parser/lexer\
./inc/parser/expander\
./inc/parser/environment\
./inc\

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

valgrind:	CFLAGS+= -DCOLORED -g3
valgrind:	re
			@clear
			@valgrind														\
			-q																\
			--suppressions=./.readline.supp									\
			--leak-check=full												\
			--show-leak-kinds=all											\
			--track-origins=yes												\
			--track-fds=yes													\
			./$(NAME)														\

#			--gen-suppressions=yes											\

.PHONY:		all clean fclean re bonus
