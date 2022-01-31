/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:04:23 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/31 12:22:03 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <iostream>
# include <sys/socket.h>
# include <stdlib.h>
# include <unistd.h>
# include <netinet/in.h>
# include <string.h>
# include <arpa/inet.h>
# include "user.hpp"
# include <errno.h>
# include <stdio.h>
# include <sys/time.h>
# include <chrono>
# include <iomanip>
# include <algorithm>
# include <string>
# include <vector>
# include <list>
# include "server.hpp"
# include "user.hpp"

# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define PINK_B	"\033[2;35m"
# define PINK_C	"\033[1;35m"
# define PINK	"\033[0;35m"
# define CIAN   "\033[0;35m"
# define WHITE	"\033[0;37m"


class Server;
class User;


void						timerDisplay( void );
void						actionDisplay(std::string const &action, std::string const &cmd, User *usr);

uint64_t					getTime(void);

std::string					toUpper(std::string str);


#endif
