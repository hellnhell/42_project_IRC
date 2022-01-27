/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 20:11:02 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/27 18:18:12 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../server.hpp"

bool is_channel(std::string const &str)
{
	if (str[0] == '#' || str[0] == '&' || str[0] == '+' || str[0] == '!')
		return true;
	return false;
}

void	Server::modeCmmd(std::vector<std::string> const &tokens, User *usr, Server &serv)
{
	if(tokens.size() < 2)
		return replyMsg(ERR_NEEDMOREPARAMS, " MODE :Not enough parameters", usr);
	if(is_channel(tokens[1]))
	{
		Channel *channel = serv.getChannel(tokens[1]);
		if(!channel)
			return replyMsg(ERR_NOSUCHCHANNEL, tokens[1], usr);
		if(tokens.size() == 2)
			return replyMsg(RPL_CHANNELMODEIS, channel->getModes(), usr);
		if(!channel->isOperator(usr))
			return replyMsg(ERR_CHANOPRIVSNEEDED, ":You're not channel operator", usr);
		if(tokens[2].size() > 4)
			return replyMsg(ERR_NEEDMOREPARAMS, " MODE :Not enough parameters", usr);

		if((tokens[2][0] == '-' || tokens[2][0] == '+') && tokens[2].size() > 1)
		{
			for(int i = 1; i < tokens[2].size(); i++)
			{
				bool mode_set = 0;
				if(tokens[2][0] == '+')
					mode_set = 1;
				if(tokens[2][i] == 'n')
					channel->setMode('n', mode_set);
				else if(tokens[2][i] == 't')
					channel->setMode('t', mode_set);
				else if(tokens[2][i] == 'k')
				{
					//channel->setMode('k', mode_set);
					if(tokens.size() != 4)
						return replyMsg(ERR_NEEDMOREPARAMS, " MODE :Not enough parameters", usr);
					if(mode_set)
						channel->setKey(tokens[3]);
					else
						channel->setKey("");
				}
				else if(tokens[2][i] == 'o')
				{
					if(tokens.size() != 4)
						return replyMsg(ERR_NEEDMOREPARAMS, " MODE :Not enough parameters", usr);
					User *user = channel->getNick(tokens[3]);
					if(!user)
						return replyMsg(ERR_USERNOTINCHANNEL, tokens[3], usr);
					if(mode_set)
					{
						if(channel->opUser(user) == -1)
							return replyMsg(ERR_USERSDONTMATCH, ":Cannot change mode for other users", usr);
					}
					else
						channel->deopUser(user);
				}
				else if(tokens[2][i] == 'b')
				{
					if(tokens.size() != 4)
						return replyMsg(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters", usr);
					std::cout << "b" << std::endl;
					User *banned = channel->getNick(tokens[3]);
					if(!banned)
						return replyMsg(ERR_USERNOTINCHANNEL, tokens[3], usr);
					if(mode_set)
					{
						std::cout << "baneame esta" << std::endl;
						if(channel->banUser(usr, banned) == -1)
							return replyMsg(ERR_USERSDONTMATCH, ":Cannot change mode for other users", usr);
					}
					else
						channel->unbanUser(banned);
				}
				else
					return replyMsg(ERR_UNKNOWNMODE, &tokens[2][i], usr);
			}
		}
	}
	else
	{
		//user
	}


}
