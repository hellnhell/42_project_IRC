/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:35:45 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/11 17:40:16 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::userCmmd(std::vector<std::string> const &tokens, User *usr)
{
	//Salen todos los mensajes de error??

	if (!usr->getConnectionPswd())
		return replyMsg(ERR_PASSWDMISMATCH, " :Password mismatch", usr);
	if (tokens.size() < 4)
		return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + " :Not enough parameters", usr);
	if (usr->getUser()[0])
		return replyMsg(ERR_ALREADYREGISTRED, " :Unauthorized command (already registered)", usr);
	if (!isalnum(tokens[1][0]))
		return replyMsg(ERR_USERSDONTMATCH, " :Username do not match", usr);//Va en el mode command creo
	// for(int i = 2; i < 5; i++)
	// {
	// 	if(!std::isdigit(tokens[i][0]) && tokens[i][0] != '*')
	// 		return replyMsg(ERR_UNKNOWNMODE, " :Uknown mode", usr);//Va en el mode command
	// }
	usr->setUser(tokens[1]);
	if (tokens[2] != "*")
	{
		usr->setModes(std::stoi(tokens[2]));
		usr->setRealName(tokens[3]);
	}
	actionDisplay("User created", "", usr);
	usr->setCheckedUser(true);
	usr->setTimePing(0);
	this->users_on.push_back(usr);
	// std::cout << std::endl << "User:  " << usr->getUser() << "\nmodes:" << usr->getModes() << "\nReal name: " << usr->getRealName() << std::endl;
}
