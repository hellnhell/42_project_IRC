/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 20:11:02 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/10 19:55:36 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../server.hpp"

bool is_channel(std::string const &str)
{
	if (str[0] == '#' || str[0] == '&' || str[0] == '+' || str[0] == '!')
		return true;
	return false;
}

void	Server::mode_cmmd(std::vector<std::string> const &tokens, User *usr, Server &serv)
{
	if(tokens.size() < 2)
		return reply_msg(ERR_NEEDMOREPARAMS, "MODE", usr);
	if(is_channel(tokens[1]))
	{
		Channel *channel = serv.getChannel(tokens[1]);
		if(!channel)
			return reply_msg(ERR_NOSUCHCHANNEL, tokens[1], usr);
		if(tokens.size() == 2)
			return reply_msg(RPL_CHANNELMODEIS, channel->getModes(), usr);
		if(!channel->isOperator(usr))
			return reply_msg(ERR_CHANOPRIVSNEEDED, ":You're not channel operator", usr);
		if(tokens[2].size() > 4)
			return reply_msg(ERR_NEEDMOREPARAMS, "MODE", usr);

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
					if(tokens.size() == 3)
						return reply_msg(ERR_NEEDMOREPARAMS, "MODE", usr);
					if(mode_set)
						channel->setKey(tokens[3]);
					else
						channel->setKey("");
				}
				else if(tokens[2][i] == 'o')
				{
					User *user = channel->getNick(tokens[3]);
					if(!user)
						return reply_msg(ERR_USERNOTINCHANNEL, tokens[3], usr);
					if(mode_set)
					{
						if(channel->opUser(user) == -1)
							return reply_msg(ERR_USERSDONTMATCH, ":Cannot change mode for other users", usr);
					}
					else
						channel->deopUser(user);
				}
				else
					return reply_msg(ERR_UNKNOWNMODE, &tokens[2][i], usr);
			}
		}
	}
	else
	{
		//user
	}


}
