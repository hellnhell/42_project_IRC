/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:41 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/31 14:54:20 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

static bool checkIfChannel(const std::string &str)
{
	if (str[0] == '#' || str[0] == '&' || str[0] == '!' || str[0] == '+')
		return true;
	return false;
}

void Server::joinCmmd(std::vector<std::string> const &tokens, User* usr)
{
	std::string					msg;
	std::stringstream			ss(tokens[1]);
	std::string					tmps;
	std::vector<std::string>	tokens2;
	bool						finded = 0;

	size_t i = 0;
	if (tokens.size() < 2)  
		return (replyMsg(ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters", usr));
	while(getline(ss, tmps, ','))
		tokens2.push_back(tmps);
	while(i < tokens2.size())
	{
		if(checkIfChannel(tokens2[i]))
		{
			std::vector<Channel*>::iterator it;
			for (it = channels.begin(); it != channels.end(); ++it)
			{
				if ((*it)->getName() == tokens2[i])
				{
					if((*it)->getKey().size())
					{
						return replyMsg(ERR_BADCHANNELKEY, ":Cannot join channel (+k)", usr);
					}
					std::vector<User *>::const_iterator it2;
					if ((it2 = std::find((*it)->getBans().begin(), (*it)->getBans().end(), usr)) != (*it)->getBans().end())
						return this->replyMsg(ERR_BANNEDFROMCHAN, (*it)->getName() + " :Cannot join channel (+b)", usr);

					(*it)->joinUser(usr);
					usr->joinChannel(*it);
					dataMsg("JOIN :" + tokens2[i], usr, usr);
					replyMsg(RPL_TOPIC, " TOPIC:" + (*it)->getTopic(), usr);
					msg = usr->getNickMask() + " JOIN " + (*it)->getName() + "\n";
 					msgToChannel(msg, usr, (*it));
					finded = 1;
				}
			}
			try
			{
				if(!finded)
				{
					Channel* chan = new Channel(this, usr, tokens2[i]);
					this->channels.push_back(chan);
					this->channels.back()->joinUser(usr);
					if(usr->joinChannel(chan) ==  1)
						replyMsg(ERR_USERONCHANNEL, usr->getNick() + " " + (*it)->getName() + " :User already on channel", usr);
					dataMsg("JOIN :" + tokens2[i], usr, usr);
					msg = " JOIN " + chan->getName() + "\n";
					msgToChannel(msg, usr, chan);
					replyMsg(RPL_TOPIC, " TOPIC:" + this->channels.back()->getTopic(), usr);
				}
			}
			catch(const std::exception& e)
			{
				replyMsg(ERR_UNAVAILRESOURCE, "Error: " + std::string(e.what()), usr);
				return ;
			}
		}
		else if (checkIfChannel(tokens2[i - 1]))
		{
			std::string key = tokens2[i];
			std::vector<Channel*>::iterator it;
			for(it = channels.begin(); it != channels.end(); ++it)
			{
				if((*it)->getName() == tokens2[i - 1])
				{
					if(key == (*it)->getKey())
					{
						(*it)->joinUser(usr);
						usr->joinChannel(*it);
							 replyMsg(RPL_TOPIC, ":" + (*it)->getTopic(), usr);
					}
					else
						return replyMsg(ERR_BADCHANNELKEY, ":Cannot join channel (+k)", usr);
				}
			}
		}
		else if(tokens[i] == "0" && !this->channels.empty())
		{
			std::vector<Channel*>::iterator it;
			for (it = this->channels.begin(); it != this->channels.end(); ++it)
			{
				(*it)->disconnectUser(usr);
				usr->leaveChannel(*it);
			}
		}
		i++;
	}
}

