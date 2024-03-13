# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 13:41:14 by janhan            #+#    #+#              #
#    Updated: 2024/03/13 10:26:58 by janhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	minishell

CC						=	cc
CFLAGS					=	-Wall -Wextra -Werror
RM						=	rm -f

INCLUDES				=	includes/

LIBFT_DIR				=	srcs/libft
LIBFT					=	libft.a
LIBFT_C					=	-L$(LIBFT_DIR) -lft

SRCS					=	srcs/

OBJS					=	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -I$(HOMD)/.brew/opt/readline/include \
	-I/usr/local/opt/readline/includes -c $< -o $@

clean :
	$(MAKE) -C $(LIBFT_DIR) clen
	$(RM) $(OBJS)

fclean :
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re
