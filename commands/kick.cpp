/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:37:15 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/28 14:00:44 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void	Server::kickCmmd(std::vector<std::string>const &tokens, User *usr)
{
	std::istringstream         		ss;
	std::string                 	tmp;
	std::vector<std::string>		tok_chan;
	std::vector<std::string>		tok_usr;
	std::vector<std::string>		tok_aux;
	Channel							*chan;
	User							*usr2;

	if (tokens.size() < 3)
		return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + " :Not enough parameters", usr);
	ss.str(tokens[1]);
	while(getline(ss, tmp, ','))
		tok_chan.push_back(tmp);
	ss.clear();
	ss.str(tokens[2]);
	while(getline(ss, tmp, ','))
		tok_usr.push_back(tmp);
	for (int i = 0; i < tok_chan.size(); i++)
	{
		if (!(chan = this->getChannel(tok_chan[i])))
		 	return replyMsg(ERR_NOSUCHCHANNEL,  tok_chan[i]  + " :Not such channel", usr);
		if (!(usr2 = chan->getNick(usr->getNick())))
		 	return replyMsg(ERR_NOTONCHANNEL,  tok_chan[i]  + " :You're not on that channel", usr);
		if (!chan->isOperator(usr))
			return replyMsg(ERR_CHANOPRIVSNEEDED,  tok_chan[i] + " :You're not channel operator", usr);
		for (int j = 0; j < tok_usr.size(); j++)
		{
			if (!(usr2 = chan->getNick(tok_usr[j])))
				return replyMsg(ERR_USERNOTINCHANNEL, tok_usr[j] + " " + tok_chan[i] + " :They aren't on that channel", usr);
			tok_aux.push_back("part");
			tok_aux.push_back(tok_chan[i]);
		//	if (!tokens[3].empty())
			if (tokens.size() > 3)
				tok_aux.push_back(tokens[3]);
			this->partCmmd(tok_aux, usr2);
		}
	}
}
