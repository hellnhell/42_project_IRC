/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:35:45 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/15 12:50:01 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::userCmmd(std::vector<std::string> const &tokens, User *usr)
{
	//Salen todos los mensajes de error??
	
	if (!usr->getConnectionPswd())
		 return replyMsg(ERR_PASSWDMISMATCH, "Password mismatch", usr); //NO se si es necesario 
	if(tokens.size() < 5)
		 return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + ": Not enough parameters", usr);
	if(usr->getUser()[0])
		 return replyMsg(ERR_ALREADYREGISTRED, ": Unauthorized command (already registered)", usr);
	if(!isalnum(tokens[1][0]))
		 return replyMsg(ERR_USERSDONTMATCH, "Username do not match", usr);//Va en el mode command creo
	if(!std::isdigit(tokens[2][0]) && tokens[2][0] != '*') //E:si es asterisco tiene q ir??
		 return replyMsg(ERR_UNKNOWNMODE, "Uknown mode", usr);//Va en el mode command

	usr->setUser(tokens[1]);
	if (tokens[2] != "*")
	{
		usr->setModes(std::stoi(tokens[2]));
		usr->setRealName(tokens[4]);
	}
	actionDisplay("User created", "", usr);
	usr->setCheckedUser(true);
	usr->setTimePing(0);
	this->users_on.push_back(usr);
	// std::cout << std::endl << "User:  " << usr->getUser() << "\nmodes:" << usr->getModes() << "\nReal name: " << usr->getRealName() << std::endl;
}