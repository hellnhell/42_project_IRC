/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:58:34 by javrodri          #+#    #+#             */
/*   Updated: 2022/01/27 12:00:43 by javrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void    Server::privmsgCmmd(std::vector<std::string> const& tokens, User* usr){

	User            *destUser;
	std::string     tokenDest;

	it_usr_list     beginUsrList = this->users_on.begin();
	it_usr_list     endUsrList = this->users_on.end();

	destUser = NULL;
	
	std::string     msg;
	if (tokens.size() > 3)
		replyMsg(ERR_TOOMANYTARGETS, ":Too many targets", usr);
	if (tokens.size() < 2)
		replyMsg(ERR_NORECIPIENT, ":No recipient given(privmsg)", usr);
	else{
		tokenDest = tokens[1];
		if (tokenDest[0] == '#' || tokenDest[0] == '&' || tokenDest[0] == '!' || tokenDest[0] == '+'){
			privmsgCmmdToChannel(tokens, usr);
			return;
		}
		else{
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
					std::cout << GREEN <<tokenDest << " aaaaaaaaaaaaaa2 " << std::endl;
					msg = tokens[1] + " :No such nick/channel";
					replyMsg(ERR_NOSUCHNICK, msg, usr);
				}
			}
		}
		msg.append("PRIVMSG " + usr->getNickMask() + " :" + tokens[2]);
		send(usr->getFD(), msg.c_str(), msg.length(), 0);
	}
	if (destUser && destUser->getAwayOn()){
		std::string msgAwayReply;
		msgAwayReply.append("AWAY " + destUser->getNickMask() + " :" + destUser->getAway()) + "\n";
		send(usr->getFD(), msgAwayReply.c_str(), msgAwayReply.length(), 0);
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
				std::cout << RED << "enviamensajeachannel" << WHITE << std::endl;
				msgToChannel(msg, usr, destChannel);
				break;
			}
			msg = " " + tokenDest + " :No such nick/channel";
			replyMsg(ERR_NOSUCHNICK, msg, usr);
		}
	}
	if (destUser && destUser->getAwayOn()){
		std::string msgAwayReply;
		msgAwayReply.append("AWAY " + destUser->getNickMask() + " :" + destUser->getAway()) + "\n";
		send(usr->getFD(), msgAwayReply.c_str(), msgAwayReply.length(), 0);
	}
}


