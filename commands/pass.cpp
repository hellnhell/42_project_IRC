/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:17:53 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/31 13:54:05 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::passCmmd(std::vector<std::string> const& tokens, User* usr)
{
	if (usr->getConnectionPswd())
		return replyMsg(ERR_ALREADYREGISTRED, " :Unauthorized command (already registered)", usr);
	else if (tokens.empty())
		return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + " :Not enough parameters", usr);
	else if (tokens[1] != this->getPassword())
		return replyMsg(ERR_PASSWDMISMATCH ," :Password mismatch", usr); 
	else
		usr->setConnectionPswd(true);
}
