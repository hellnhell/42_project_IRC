/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:37:39 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/28 16:22:09 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void	Server::partCmmd(std::vector<std::string>const &tokens, User *usr)
{
	std::vector<std::string>	tok;
	std::string					tmp;
	std::istringstream			ss;
	std::string					leave_msg;
	std::string::size_type		pos;
	Channel						*chan;

	if (tokens.size() == 1 ) //se puede meter el quit
		return this->replyMsg(ERR_NEEDMOREPARAMS,  tokens[0] + " :Not enough parameters", usr);

	std::cout << "\n\n\n token1: " << tokens[1] << std::endl;
	if (tokens.size() > 2)
		leave_msg = tokens[2];
	ss.str(tokens[1]);
	while(getline(ss, tmp, ','))
	{
	 	std::cout << tmp << std::endl;
	 	tok.push_back(tmp);
	}
	//print tok content
	for(int i = 0; i < tok.size(); i++)
		std::cout << "tok[" << i << "]: " << tok[i] << std::endl;
	for(int i = 0; i < tok.size(); i++)
	{
		if(usr->getChannels().size() <= 0)
		{
			std::cout << "User " << usr->getUser() << " is not in any channel" << std::endl;
			return ;
		}
		if ((chan = this->getChannel(tok[i])))
		{
			if(!chan->getNick(usr->getNick()))
				return replyMsg(ERR_NOTONCHANNEL, chan->getName() + " :Not on channel", usr);
			else if (leave_msg.size() > 0)
			{
					this->dataMsg("PART " + (chan)->getName() + " :has left the channel", usr, usr);
					leave_msg += usr->getNickMask() + " PART " + (chan)->getName() + "\n";;
					msgToChannel(leave_msg, usr, chan);
				//send leve_msg to all users in channel
			}
			else
			{
					this->dataMsg("PART " + (chan)->getName() + " :has left the channel", usr, usr);
					leave_msg = usr->getNickMask() + " PART " + (chan)->getName() + "\n";;
					msgToChannel(leave_msg, usr, chan);
				// ???? send generic msg to all users in channel
			}
			(chan)->disconnectUser(usr);
			usr->leaveChannel(chan); // NO se va del canal why?
			
		}
		replyMsg(ERR_NOSUCHCHANNEL, tok[i]  + " :Not such channel", usr);
	}
}
