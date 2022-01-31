/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:44:25 by javier            #+#    #+#             */
/*   Updated: 2022/01/31 14:02:17 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "../user.hpp"

void	Server::noticeCmmd(std::vector<std::string> const& tokens, User* usr){

	User			*destUser;
	std::string		tokenDest;

	it_usr_list		beginUsrList = this->users_on.begin();
	it_usr_list		endUsrList = this->users_on.end();

	destUser = NULL;
	bool sended = false;
	
	std::string		msg;
	if (tokens.size() > 3)
		replyMsg(ERR_TOOMANYTARGETS, ":Too many targets", usr);
	if (tokens.size() < 2)
		replyMsg(ERR_NORECIPIENT, ":No recipient given(privmsg)", usr);
	else{
		tokenDest = tokens[1];
		if (tokenDest[0] == '#' || tokenDest[0] == '&' || tokenDest[0] == '!' || tokenDest[0] == '+')
		{
			privmsgCmmdToChannel(tokens, usr);
			sended = true;
			return;
		}
		else{
			for(;beginUsrList != endUsrList; ++beginUsrList)
			{
				if (((*beginUsrList)->getNick() == tokenDest) || ((*beginUsrList)->getNickMask() == tokenDest))
				{
					destUser = *beginUsrList;
					msg += usr->getNickMask() + " NOTICE " + destUser->getNick() + " :" + tokens[2];
					send(destUser->getFD(), msg.c_str(), msg.length(), 0);
					sended = true;
					break;
				}
			}
		}
		if (sended == false)
		{
			msg = tokens[1] + " : No such nick/channel";
			replyMsg(ERR_NOSUCHNICK, msg, usr);
		}
	}
}
