/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:58:34 by javrodri          #+#    #+#             */
/*   Updated: 2021/12/10 12:27:12 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../server.hpp"

void    Server::privmsg_cmmd(std::vector<std::string> const& tokens, User* usr){
    
    
    // std::cout << "tokens.size(): " << tokens.size() << "\n" << std::cout;
    // std::cout << "tokens[0]: " << tokens[0] << "\n" << std::cout;
    // std::cout << "tokens[1]: " << tokens[1] << "\n" << std::cout;
    // std::cout << "tokens[2]: " << tokens[2] << "\n" << std::cout;
    // std::cout << "tokens[3]: " << tokens[3] << "\n" << std::cout;
    
    if (tokens.size() > 3)
        reply_msg(ERR_TOOMANYTARGETS, ":Too many targets", usr);
    // else if (tokens.size() < 2)
    //     if //SI NO ENCUENTRA AL USUARIO EN LA LISTA DE USUSARIOS CONECTADOS AL CANAL
    //         error_msg(ERR_NORECIPIENT, ":No recipient given (PRIVMSG)", usr);       
    //     else
    //         error_msg(ERR_NOTEXTOSEND, ":No text to send", usr);       
            
    // if (tokens[1] == ':')

}