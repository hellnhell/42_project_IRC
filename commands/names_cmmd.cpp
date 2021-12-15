/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names_cmmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:30:36 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/13 19:31:19 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void    Server::names_cmmd(std::vector<std::string> const& tokens, User *usr)
{
    std::vector<std::string>	tok;
    std::istringstream          ss(tokens[1]);
    std::string                 tmp;
    std::string                 msg;
	Channel						*channel;
    int pos;

    while(getline(ss, tmp, ','))
    {
        std::cout << tmp << std::endl;
        tok.push_back(tmp);
    }
    for (int i = 0; i < tok.size(); i++)
    {
        channel = this->_name_channel[tok[i]];
        if (channel)
        {
            msg = " = " + channel->getName();
            reply_msg(RPL_NAMREPLY, msg, usr);
			reply_msg(RPL_ENDOFNAMES," " + channel->getName() + " :End of /NAMES list.", usr);
        }        
    } 
}