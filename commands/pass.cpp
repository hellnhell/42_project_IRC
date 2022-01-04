/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:17:53 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/10 10:35:06 by javrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::passCmmd(std::vector<std::string> const& tokens, User* usr)
{
	std::cout << usr << std::endl; 
	if (!usr->getConnectionPswd())
		return replyMsg(ERR_ALREADYREGISTRED, ": Unauthorized command (already registered)", usr); //?
	if (tokens.empty())
	  	return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + ": Not enough parameters", usr);
	if (tokens[1] != this->getPassword())
		return replyMsg(ERR_PASSWDMISMATCH ,"Password mismatch", usr); //NO se si hace falta
}