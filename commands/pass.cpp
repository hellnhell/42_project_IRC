/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:17:53 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/28 11:50:23 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::passCmmd(std::vector<std::string> const& tokens, User* usr)
{
	if (usr->getConnectionPswd())
		return replyMsg(ERR_ALREADYREGISTRED, ": Unauthorized command (already registered)", usr); //?
	else if (tokens.empty())
	  	return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + ": Not enough parameters", usr);
	else if (tokens[1] != this->getPassword())
	{
		std::cout << "111111111" << std::endl;
		return replyMsg(ERR_PASSWDMISMATCH ,"Password mismatch", usr); //NO se si hace falta
	}
    else
        usr->setConnectionPswd(true);
}
