/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:35:45 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/31 13:49:46 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::userCmmd(std::vector<std::string> const &tokens, User *usr)
{
	if (!usr->getConnectionPswd())
		return ;
	if (tokens.size() < 4)
		return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + " :Not enough parameters", usr);
	if (usr->getUser()[0])
		return replyMsg(ERR_ALREADYREGISTRED, " :Unauthorized command (already registered)", usr);
	if (!isalnum(tokens[1][0]))
		return replyMsg(ERR_USERSDONTMATCH, " :Username do not match", usr);
	usr->setUser(tokens[1]);
	if (tokens[2] != "*")
		usr->setRealName(tokens[3]);
	actionDisplay("User created", "", usr);
	usr->setCheckedUser(true);
	if (usr->getCheckedRegist())
		usr->setTimePing(0);
	usr->setNickMask(":" + usr->getNick() + "!" + usr->getUser() + "@" + usr->getClientAdd());
	this->users_on.push_back(usr);
}
