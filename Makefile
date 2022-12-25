# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
#    Updated: 2022/12/25 18:03:03 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

RM					=	rm -f

# **************************************************************************** #

SRCS	=\
./utils/string/ft_strnstr.c\
./utils/string/ft_strncmp.c\
./utils/string/ft_strlen.c\
./utils/string/ft_substr.c\
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
./parser/lexer/token/token.c\
./parser/lexer/lexer.c\
./parser/lexer/modules/is_and.c\
./parser/lexer/modules/is_redirect_err.c\
./parser/lexer/modules/is_redirect_err_append.c\
./parser/lexer/modules/is_redirect_out.c\
./parser/lexer/modules/is_subshell.c\
./parser/lexer/modules/is_redirect_out_append.c\
./parser/lexer/modules/is_double_quote.c\
./parser/lexer/modules/is_simple_quote.c\
./parser/lexer/modules/is_redirect_in.c\
./parser/lexer/modules/is_semicolon.c\
./parser/lexer/modules/is_or.c\
./parser/lexer/modules/is_background.c\
./parser/lexer/modules/is_pipe.c\

INCS	=\
./utils/string\
./utils/list\
./utils\
./utils/memory\
./parser/lexer/token\
./parser/lexer/modules\
./parser/lexer\

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
			--suppressions=./readline.supp									\
			--leak-check=full												\
			--show-leak-kinds=all											\
			--track-origins=yes												\
			--track-fds=yes													\
			./$(NAME)														\

#			--gen-suppressions=yes											\

.PHONY:		all clean fclean re bonus
