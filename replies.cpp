/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/02 12:04:14 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void	Server::error_msg(std::string err, std::string str, User *usr, int listnum)
{
    std::string error;
    
    error = ":ft_irc.com " + err  + " "  + usr->getNick() + " " + str + "\r\n";
    std::cout << error << std::endl;
    send(this->_list_connected_user[listnum], error.c_str(), error.length(), 0);
}
