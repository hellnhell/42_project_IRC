/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:38:13 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/25 12:53:05 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::whoCmmd(std::vector<std::string>const& tokens, User *usr)
{
	std::string msg;

	std::list<User *>::iterator it;
	for (it = users_on.begin(); it != users_on.end(); ++it)
	{
        if (tokens.size() > 1)
        {
            if ((*it)->getNick() == tokens[1])
            {
                msg = (*it)->getUser() + " " + (*it)->getNick() + " " + (*it)->getRealName() + " " + (*it)->getClientAdd() + "\n";
                replyMsg(RPL_WHOREPLY," :" + msg, usr);
                replyMsg(RPL_ENDOFWHO, (*it)->getUser() + " :End of /WHO list.", usr);
                return ;
            }
            if (tokens[1][0] == '#')
            {
                std::vector<Channel *>::const_iterator it2;
			    std::vector<User *>::const_iterator it3;
			    for (it2 = this->getChannels().begin(); it2 != this->getChannels().end(); it2++)
			    {
                    if (tokens.size() == 3 && tokens[2] == "o")
                    {
                        for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
                        {
                            std::vector<User *>::const_iterator it4;
						    for(it4 = (*it2)->getOps().begin(); it4 != (*it2)->getOps().end(); it4++)
						    {
							    if((*it3)->getNick() == (*it4)->getNick())
							    	msg += "@" + (*it3)->getUser() + " " + (*it3)->getNick()  + " " + (*it3)->getClientAdd();
						    }
                        }
                        replyMsg(RPL_WHOREPLY, msg, usr);
                    }
			    	else if (tokens[1] == (*it2)->getName())
                    {
                        for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
                            msg +=  (*it3)->getUser() + " " + (*it3)->getNick() + " " + (*it3)->getClientAdd() + ", ";
                        replyMsg(RPL_WHOREPLY, " :" + msg, usr);
				    }
                    replyMsg(RPL_ENDOFWHO, usr->getUser() + " :End of /WHO list.", usr); //?
			    }
                return ;
            }
        }
        else
        {
            msg = (*it)->getUser()  + " " + (*it)->getNick() + " " + (*it)->getClientAdd() + "\n";
            replyMsg(RPL_WHOREPLY," :" + msg, usr);
            replyMsg(RPL_ENDOFWHO,  " :End of /WHO list.", usr); //?
        }
	}

}
