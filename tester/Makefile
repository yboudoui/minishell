# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
#    Updated: 2023/03/11 14:45:47 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell_tester

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

RM					=	rm -f

# **************************************************************************** #

SRCS	=\
./src/utils/string/is_empty.c\
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
./src/utils/string/ft_substr.c\
./src/utils/string/ft_str_find_prefix.c\
./src/utils/string/ft_strchr.c\
./src/utils/string/ft_atoi.c\
./src/utils/string/ft_itoa.c\
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
./src/multiplexer.c\
./src/main.c\
./src/shell.c\

INCS	=\
./inc/utils\
./inc/utils\
./inc/utils\
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

fsanitize:	CFLAGS+= -fsanitize=address -g
fsanitize:	re

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

re_valgrind:	CFLAGS+= -g3
re_valgrind:	re valgrind

.PHONY:		all clean fclean re bonus
