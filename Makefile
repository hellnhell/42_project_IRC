# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 11:59:14 by emartin-          #+#    #+#              #
#    Updated: 2021/11/30 13:17:20 by emartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#No me va en linux para variar
NAME			= irc-server

SRCS			= 	main.cpp 		\
				 	server.cpp		\
				 	user.cpp		\
					replies.cpp		\
				 	commands/user_cmmd.cpp	\
					commands/pass.cpp		\
					commands/nick.cpp	
					
OBJS			= $(SRCS:.cpp=.o)
CC				= clang++ 
RM				= rm -f
CFLAGS			= -g -Wall -Wextra -Werror -I.

all:			$(NAME)

$(NAME):		$(OBJS)
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re