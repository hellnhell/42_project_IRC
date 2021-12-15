/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:58:34 by javrodri          #+#    #+#             */
/*   Updated: 2021/12/15 13:06:22 by javrodri         ###   ########.fr       */
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
    // std::cout << "tokens.size(): " << tokens.size() << "\n" << std::cout;
    if (tokens.size() > 3)
        reply_msg(ERR_TOOMANYTARGETS, ":Too many targets", usr);
    if (tokens.size() < 2)
        reply_msg(ERR_NORECIPIENT, ":No recipient given(privmsg)", usr);
    else{
        tokenDest = tokens[1];
        for(;beginUsrList != endUsrList; ++beginUsrList){
            if ((*beginUsrList)->getNick() == tokenDest){
                destUser = *beginUsrList;
                break;
            }
            else if ((*beginUsrList)->getNickMask() == tokenDest){
                destUser = *beginUsrList;
                break;
            }
            else{
                msg = tokens[1] + " :No such nick/channel";
                reply_msg(ERR_NOSUCHNICK, msg, usr);
            }
        }
        msg.append("PRIVMSG " + usr->getNickMask() + " :" + tokens[2]);
        send(destUser->getFD(), msg.c_str(), msg.length(), 0);
    }
}