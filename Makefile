# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
#    Updated: 2023/01/04 18:24:12 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

RM					=	rm -f

# **************************************************************************** #

#./src/parser/syntaxer/syntaxer.c\

SRCS	=\
./src/utils/string/ft_strnstr.c\
./src/utils/string/str_slice_prefix.c\
./src/utils/string/ft_strncmp.c\
./src/utils/string/ft_strlen.c\
./src/utils/string/ft_substr.c\
./src/utils/string/ft_str_find_prefix.c\
./src/utils/string/ft_strdup.c\
./src/utils/string/str_slice_charset.c\
./src/utils/string/is_space.c\
./src/utils/string/str_slice_section.c\
./src/utils/list/list_add.c\
./src/utils/list/list_clear.c\
./src/utils/list/list_destroy.c\
./src/utils/list/list_create.c\
./src/utils/list/list_last.c\
./src/utils/list/ft_lstsize.c\
./src/utils/list/ft_lstiter.c\
./src/utils/list/ft_lstmap.c\
./src/utils/memory/ft_memcpy.c\
./src/utils/memory/ft_calloc.c\
./src/main.c\
./src/parser/lexer/token/cleaner.c\
./src/parser/lexer/token/matching.c\
./src/parser/lexer/token/token.c\
./src/parser/lexer/lexer.c\
./src/read_line/read_line_handler.c\
./show/lexer_show.c\

INCS	=\
./show\
./inc/utils/string\
./inc/utils/list\
./inc/utils\
./inc/utils/memory\
./inc/parser\
./inc/read_line\
./inc/lexer\

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

valgrind:	fclean
			@$(MAKE) all -C . CFLAGS="-Wall -Wextra -Werror -g3"
			@valgrind														\
			-s																\
			--suppressions=./.readline.supp									\
			--leak-check=full												\
			--show-leak-kinds=all											\
			--track-origins=yes												\
			--track-fds=yes													\
			./$(NAME)														\

#			--gen-suppressions=yes											\

.PHONY:		all clean fclean re bonus
