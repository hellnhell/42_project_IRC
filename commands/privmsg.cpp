/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javier <javier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:58:34 by javrodri          #+#    #+#             */
/*   Updated: 2021/12/10 18:48:51 by javier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../server.hpp"

void    Server::privmsg(std::vector<std::string> const& tokens, User* usr){
    
    User            *destUser;
    Channel         *destChannel;
    std::string     tokenDest;
    
    it_usr_list     beginUsrList = this->users_on.begin();
    it_usr_list     endUsrList = this->users_on.end();
    std::string     msg;
    if (tokens.size() > 3)
        reply_msg(ERR_TOOMANYTARGETS, ":Too many targets", usr);
    if (tokens.size() < 2)
        reply_msg(ERR_NORECIPIENT, ":No recipient given(privmsg)", usr);
    tokenDest = tokens[1];
    for(;beginUsrList != endUsrList; ++beginUsrList){
        //std::cout << "** " << (*beginUsrList)->getNick() << std::endl;
        if ((*beginUsrList)->getNick() == tokenDest){
            destUser = *beginUsrList;
        }
        else{
            msg = tokens[1] + " :No such nick/channel";
            reply_msg(ERR_NOSUCHNICK, msg, usr);
            break;
        }
        return;
    }
    msg.append("PRIVMSG " + tokenDest + " :");
    for(int i = 2; tokens[i] != ""; i++)
        msg.append(tokens[i]);
    send(destUser->getFD(), msg.c_str(), msg.length(), 0);
    // return (msg, destUser, usr);


    
    // std::cout << "tokens.size(): " << tokens.size() << "\n" << std::cout;
    // std::cout << "tokens[0]: " << tokens[0] << "\n" << std::cout;
    // std::cout << "tokens[1]: " << tokens[1] << "\n" << std::cout;
    // std::cout << "tokens[2]: " << tokens[2] << "\n" << std::cout;
    // std::cout << "tokens[3]: " << tokens[3] << "\n" << std::cout;
        // else if (tokens.size() < 2)
    //     if //SI NO ENCUENTRA AL USUARIO EN LA LISTA DE USUSARIOS CONECTADOS AL CANAL
    //         error_msg(ERR_NORECIPIENT, ":No recipient given (PRIVMSG)", usr);       
    //     else
    //         error_msg(ERR_NOTEXTOSEND, ":No text to send", usr);       
            
    // if (tokens[1] == ':')

}