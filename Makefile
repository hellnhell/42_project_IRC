# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 11:59:14 by emartin-          #+#    #+#              #
#    Updated: 2021/11/22 12:02:44 by emartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= irc-server
SRCS 		= main.cpp 	server.cpp user.cpp
OBJS 		= $(SRCS:.cpp=.o)
C++			= clang++ 
C++FLAGS	= -Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address


all:		$(NAME)
$(NAME):	$(OBJS)
			$(C++) $(C++FLAGS) -o $(NAME) $(OBJS)
clean:
			-@rm -f $(OBJS)

fclean: 	clean
			-@rm -f $(NAME)

re:			fclean all

.PHONY: all clea fclean re test