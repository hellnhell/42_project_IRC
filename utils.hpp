/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:04:23 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/10 14:18:48 by emartin-         ###   ########.fr       */
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

# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define PINK_B	"\033[2;35m"
# define PINK_C	"\033[1;35m"
# define PINK	"\033[0;35m"
# define CIAN   "\033[0;35m"
# define WHITE	"\033[0;37m"


// green=$'\e[0;92;40m'
// green_b=$'\e[0;30;102m'
// green_d=$'\e[0;2;92;40m'
// red=$'\e[0;92;31m'
// green_b=$'\e[0;92;102m'
// blue=$'\e[0;34;40m'
// cyan=$'\e[0;1;36;40m'
// magenta=$'\e[0;1;95;40m'
// yellow=$'\e[0;92;33m'
// nc=$'\e[0m'


void						timerDisplay( void );
void	                    actionDisplay(std::string const &action, std::string const &cmd, User *usr);


#endif