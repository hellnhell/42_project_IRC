/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:17:53 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/11 17:40:15 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::passCmmd(std::vector<std::string> const& tokens, User* usr)
{
	std::cout << YELLOW <<  usr->getConnectionPswd() << std::endl;
	if (usr->getConnectionPswd())
		return replyMsg(ERR_ALREADYREGISTRED, ": Unauthorized command (already registered)", usr); //?
	else if (tokens.empty())
	  	return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + ": Not enough parameters", usr);
	else if (tokens[1] != this->getPassword())
		return replyMsg(ERR_PASSWDMISMATCH ,"Password mismatch", usr); //NO se si hace falta
    else
        usr->setConnectionPswd(true);
}
