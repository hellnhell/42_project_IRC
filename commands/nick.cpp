/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javier <javier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:15:28 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/10 12:31:46 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../server.hpp"
#include "../user.hpp"

// OK 	ERR_NONICKNAMEGIVEN	"431"       ":No nickname given" - Returned when a nickname parameter expected for a command and isn't found. 
// OK 		ERR_ERRONEUSNICKNAME	"432"       "<nick> :Erroneous nickname"- Returned after receiving a NICK message which contains characters which do not fall in the defined set.  See section 2.3.1 for details on valid nicknames.
// ????? 	ERR_UNAVAILRESOURCE	"437"       "<nick/channel> :Nick/channel is temporarily unavailable" - Returned by a server to a user trying to join a channel currently blocked by the channel delay mechanism.- Returned by a server to a user trying to change nickname when the desired nickname is blocked by the nick delay mechanism.
// ok     	ERR_NICKNAMEINUSE	       "433"   "<nick> :Nickname is already in use" - Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.
// ?????  	ERR_RESTRICTED            "484"      ":Your connection is restricted!"- Sent by the server to a user upon connection to indicate the restricted nature of the connection (user mode "+r").


void Server::nick_cmmd(std::vector<std::string> const &tokens, User *usr)
{

	std::map<int, User*>::iterator it;

	if (!usr->getConnectionPswd()) //No se si es necesario
        return reply_msg(ERR_PASSWDMISMATCH ,"Password mismatch", usr);
	if(tokens.size() != 2)
		return reply_msg(ERR_NONICKNAMEGIVEN, ": No nickname given", usr);
	if(tokens[1] == usr->getNick())
		return reply_msg(ERR_NICKNAMEINUSE, tokens[1] + "Unauthorized command (already registered)", usr);
	if(tokens[1].size() > 9)
		return reply_msg(ERR_ERRONEUSNICKNAME, tokens[1] + " Erroneus nickname", usr);
	if(tokens[1][0] == '-' ||
		tokens[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`|^_-{}[]\\") != std::string::npos)
		return reply_msg(ERR_ERRONEUSNICKNAME, tokens[1] + " Erroneus nickname", usr);

	for(it = this->list_users.begin(); it != this->list_users.end(); it++)
	{
		std::cout << it->first << " fds chekeados" << std::endl;
		if(it->first >= 4) //N: esto es una chapuza por que no se usar mapas y hay mapas con fds < 4 que peta por no inicializarse maybe
		{
			if((*it).second->getNick() == tokens[1])
			{
				std::cout << "Error nickname " << tokens[1] << " is invalid" << std::endl;
				send(usr->getFD(), "Not a valid nickname\n", 21, 0); //esto no cumple nada pero por ver algo en el cliente
				std::cout << std::endl << "Nick: " << usr->getNick();
				return ;
			}
		}
	}
	usr->setNick(tokens[1]);
	usr->setNickMask(usr->getNick() + "!" + usr->getUser() + "@ft_irc.com");
	usr->setCheckedNick(true);
    actionDisplay( "Nick created", "", usr);

}