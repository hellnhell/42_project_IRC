/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:58:34 by javrodri          #+#    #+#             */
/*   Updated: 2022/01/27 18:50:45 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void    Server::privmsgCmmd(std::vector<std::string> const& tokens, User* usr){

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
					msg += usr->getNickMask() + " PRIVMSG " + destUser->getNick() + " :" + tokens[2] + "\n";
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
	if (destUser && destUser->getAwayOn()){
		std::cout << GREEN << "\n----->> away: " << destUser->getAwayOn() << WHITE <<std::endl;
		std::string msgAwayReply;
		msgAwayReply = " :" + destUser->getAway();
		replyMsg(RPL_AWAY, msgAwayReply, usr);
	}
}

void    Server::privmsgCmmdToChannel(std::vector<std::string> const& tokens, User* usr){

	User            *destUser;
	Channel         *destChannel;
	std::string     tokenDest;

	it_usr_list     beginUsrList = this->users_on.begin();
	it_usr_list     endUsrList = this->users_on.end();

	std::vector<Channel *>::const_iterator it2;
	std::vector<Channel *>::const_iterator it3;

	destUser = NULL;
	it2 = this->getChannels().begin();
	it3 = this->getChannels().end();
	std::string     msg;
	tokenDest = tokens[1];
	if (tokenDest[0] == '#' || tokenDest[0] == '&' || tokenDest[0] == '!' || tokenDest[0] == '+'){
		for (;it2 != it3; ++it2){
			if ((*it2)->getName() == tokenDest){
				destChannel = *it2;
				msg = usr->getNickMask() + " PRIVMSG " + destChannel->getName() + " :" + tokens[2];
				msgToChannel(msg, usr, destChannel);
				return;
			}
		}
		msg = " " + tokenDest + " : No such nick/channel";
		replyMsg(ERR_NOSUCHNICK, msg, usr);
	}
}


