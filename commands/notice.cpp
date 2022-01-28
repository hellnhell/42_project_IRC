/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:44:25 by javier            #+#    #+#             */
/*   Updated: 2022/01/28 10:58:57 by javrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "../user.hpp"

void    Server::noticeCmmd(std::vector<std::string> const& tokens, User* usr){

	User            *destUser;
	std::string     tokenDest;

	it_usr_list     beginUsrList = this->users_on.begin();
	it_usr_list     endUsrList = this->users_on.end();

	destUser = NULL;
	bool  sended = false;
	
	std::string     msg;
	if (tokens.size() > 3)
		replyMsg(ERR_TOOMANYTARGETS, ":Too many targets", usr);
	if (tokens.size() < 2)
		replyMsg(ERR_NORECIPIENT, ":No recipient given(privmsg)", usr);
	else{
		tokenDest = tokens[1];
		if (tokenDest[0] == '#' || tokenDest[0] == '&' || tokenDest[0] == '!' || tokenDest[0] == '+'){
			privmsgCmmdToChannel(tokens, usr);
			sended = true;
			return;
		}
		else{
			for(;beginUsrList != endUsrList; ++beginUsrList){
				std::cout << GREEN << "\n----->> get_nick(): " << (*beginUsrList)->getNick() << WHITE <<std::endl;
				std::cout << GREEN << "\n----->> sended: " << sended << WHITE <<std::endl;
				if (((*beginUsrList)->getNick() == tokenDest) || ((*beginUsrList)->getNickMask() == tokenDest)){
					destUser = *beginUsrList;
					msg += usr->getNickMask() + " NOTICE " + destUser->getNick() + " :" + tokens[2];
					send(destUser->getFD(), msg.c_str(), msg.length(), 0);
					sended = true;
					break;
				}
			}
		}
		std::cout << GREEN << "\n----->> sended: " << sended << WHITE <<std::endl;
		if (sended == false){
			msg = tokens[1] + " : No such nick/channel";
			replyMsg(ERR_NOSUCHNICK, msg, usr);
		}
	}
}
