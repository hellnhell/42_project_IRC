# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 11:59:14 by emartin-          #+#    #+#              #
#    Updated: 2022/01/09 18:50:13 by javrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#No me va en linux para variar
NAME			= irc-server

SRCS_DIR= ./

NAME			= irc-server

SRCS_DIR= ./

SRCS			= main.cpp \
					server.cpp \
					user.cpp \
					parse.cpp \
					replies.cpp \
					channel.cpp \
					commands/user_cmmd.cpp \
					commands/nick.cpp \
					commands/pass.cpp	\
					commands/time.cpp	\
					commands/privmsg.cpp \
					commands/join.cpp \
					commands/names.cpp \
					commands/motd.cpp	\
					commands/quit.cpp	\
					commands/part.cpp	\
					commands/ping-pong.cpp \
					utils.cpp

OBJS_DIR = objects/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJ))

CC				= clang++
RM				= rm -rf
CFLAGS			= -g3 -std=c++98 -Wall -Wextra -Werror -I.

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)commands/
	@echo "\033[0;33mCompiling: $<\033[0m"
	@${CC} $(FLAGS) -c $< -o $@
$(NAME):		$(OBJS)
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

all: $(NAME)

all: $(NAME)

clean:
	@echo "Cleaning: $(OBJS_DIR)"
	@$(RM) $(OBJS_DIR)

fclean: clean
	@echo "Cleaning: $(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY:			all clean fclean re