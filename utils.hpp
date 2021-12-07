/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:04:23 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/07 14:10:37 by emartin-         ###   ########.fr       */
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

# define GREEN	"\033[1;32m"
# define WHITE	"\033[0;37m"
# define YELLOW	"\033[1;33m"

void						display( void );

#endif