/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ison.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:59:06 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/31 14:01:38 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void	Server::isonCmmd(std::vector<std::string> const &tokens, User *usr)
{
	std::string message = " :";
	
	if ( tokens.size() == 1 )
		return replyMsg(ERR_NEEDMOREPARAMS, "ISON :Not enough parameters", usr);
	for ( size_t i = 1; i < tokens.size() ; i++ )
	{
		std::list<User *>::const_iterator it;
		
		for(it = this->users_on.begin(); it != this->users_on.end(); it++)
		{
			if((*it)->getNick() == tokens[i])
			{
				message.append(tokens[i]);
				break;
			}
			if(i < tokens.size() - 1)
				message.append(" ");
		}
	}
	replyMsg(RPL_ISON , message, usr);
}