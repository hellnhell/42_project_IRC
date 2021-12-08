# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 11:59:14 by emartin-          #+#    #+#              #
#    Updated: 2021/12/08 20:40:08 by nazurmen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#No me va en linux para variar
NAME			= irc-server

SRCS			= main.cpp server.cpp user.cpp user_cmmd.cpp nick_cmmd.cpp pass.cpp channel.cpp join_cmmd.cpp
OBJS			= $(SRCS:.cpp=.o)
CC				= clang++
RM				= rm -f
CFLAGS			= -fsanitize=address -g3 -Wall -Wextra -Werror -I.

all:			$(NAME)

$(NAME):		$(OBJS)
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
