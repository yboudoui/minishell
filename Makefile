# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
#    Updated: 2022/12/29 17:16:59 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

RM					=	rm -f

# **************************************************************************** #

SRCS	=\
./utils/string/ft_strnstr.c\
./utils/string/str_slice_prefix.c\
./utils/string/ft_strncmp.c\
./utils/string/ft_strlen.c\
./utils/string/ft_substr.c\
./utils/string/ft_str_find_prefix.c\
./utils/string/ft_strdup.c\
./utils/string/str_slice_charset.c\
./utils/string/is_space.c\
./utils/string/str_slice_section.c\
./utils/list/list_add_front.c\
./utils/list/list_clear.c\
./utils/list/list_destroy.c\
./utils/list/list_create.c\
./utils/list/list_last.c\
./utils/list/ft_lstsize.c\
./utils/list/list_remove_one.c\
./utils/list/ft_lstiter.c\
./utils/list/list_add_back.c\
./utils/list/ft_lstmap.c\
./utils/list/list_create_back.c\
./utils/memory/ft_memcpy.c\
./utils/memory/ft_calloc.c\
./main.c\
./parser/parser.c\
./show/lexer_show.c\
./lexer/src/token_match.c\
./lexer/src/lexer.c\
./lexer/src/token.c\

INCS	=\
./utils/string\
./utils/list\
./utils\
./utils/memory\
./parser\
./show\
./lexer/inc\

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
