/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/10 12:23:49 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void	Server::reply_msg(std::string rep, std::string str, User *usr)
{
    std::string msg;
    
    if (rep[0] > 3)
        msg = RED SERVER_MASK + rep  + " "  + usr->getNick() + " " + str + WHITE "\r\n";
    else        
        msg = GREEN SERVER_MASK + rep  + " "  + usr->getNick() + " " + str + WHITE "\r\n";
	send(usr->getFD(), msg.c_str(), msg.length(), 0);
    // usr->setReply(error);
}

// void	Server::msg_to_user(std::string msg, User *sender_usr, User *recipe_usr)
// {
//     std::string format_message;
    
//     format_message = ":ft_irc.com " + format_message + " "  + recipe_usr->getNick() + "\r\n";
//     send(recipe_usr->getFD(), format_message.c_str(), format_message.length(), 0);
//     // std::cout << error << std::endl;
//     // usr->setReply(error);
// }

//FUTURO MENSAJE DE UN USUARIO A UN CANAL, ITERA POR LOS USUARIOS DENTRO DEL CANAL Y LO ENVIA
//O RECIBE UN VECTOR DE FD Y ENVIA EL MENSAJE A ESOS FDs

// void	Server::msg_to_channel(std::string msg, std::string str, User *usr)
// {
//     std::string error;
    
//     error = ":ft_irc.com " + err + " "  + usr->getNick() + str + "\r\n";
//     send(usr->getFD(), error.c_str(), error.length(), 0);
//     std::cout << error << std::endl;
//     usr->setReply(error);
// }

