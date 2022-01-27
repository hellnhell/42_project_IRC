/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:56:36 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/27 14:18:53 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void    Server::parseCommands(std::vector<std::string> const &tokens, User *usr, int fd)
{
	if (!usr->getCheckedRegist())
	{
		if(tokens[0] == "USER" || tokens[0] == "user")
		{
			usr = this->list_users[this->_list_connected_user[fd]];
			return this->userCmmd(tokens, usr);
		}
		else if(tokens[0] == "NICK" || tokens[0] == "nick")
		{
			usr = this->list_users[this->_list_connected_user[fd]];
			return this->nickCmmd(tokens, usr);
		}
		else if(tokens[0] == "PASS" || tokens[0] == "pass")
			return this->passCmmd(tokens, usr);
		else if((tokens[0] == "PONG" || tokens[0] == "pong"))
			return this->pongCmmd(tokens, usr);
		else
			return replyMsg(ERR_NOTREGISTERED, ":You should enter <USER> and <NICK> command to register", usr);
	}
	else if (usr->getCheckedRegist())
	{
		if(tokens[0] == "USER" || tokens[0] == "user")
			return this->userCmmd(tokens, usr);
		else if(tokens[0] == "NICK" || tokens[0] == "nick")
			return this->nickCmmd(tokens, usr);
		else if(tokens[0] == "PASS" || tokens[0] == "pass")
			return this->passCmmd(tokens, usr);
		else if(tokens[0] == "PRIVMSG" || tokens[0] == "privmsg")
			return this->privmsgCmmd(tokens, usr);
		else if(tokens[0] == "TIME" || tokens[0] == "time")
			return this->timeCmmd(usr, this->_list_connected_user[fd]);
		else if(tokens[0] == "JOIN" || tokens[0] == "join")
			return this->joinCmmd(tokens, usr);
		else if(tokens[0] == "MOTD" || tokens[0] == "motd")
			return this->motdCmmd(fd);
		else if(tokens[0] == "NAMES" || tokens[0] == "names")
			return this->namesCmmd(tokens, usr, *this);
		else if(tokens[0] == "PONG" || tokens[0] == "pong")
		 	return this->pongCmmd(tokens, usr);
		else if(tokens[0] == "QUIT" || tokens[0] == "quit")
		 	return this->quitCmmd(tokens, usr);
		else if(tokens[0] == "NOTICE" || tokens[0] == "notice")
		 	return this->noticeCmmd(tokens, usr);
		else if(tokens[0] == "AWAY" || tokens[0] == "away")
		 	return this->awayCmmd(tokens, usr);
		else if(tokens[0] == "PART" || tokens[0] == "part")
		 	return this->partCmmd(tokens, usr);
		else if(tokens[0] == "TOPIC" || tokens[0] == "topic")
			return this->topicCmmd(tokens, usr, *this);
		else if(tokens[0] == "MODE" || tokens[0] == "mode")
			return this->modeCmmd(tokens, usr, *this);
        else if(tokens[0] == "WHO" || tokens[0] == "who")
		 	return this->whoCmmd(tokens, usr);
		else if(tokens[0] == "OPER" || tokens[0] == "oper")
		 	return this->operCmmd(tokens, usr);
		else if(tokens[0] == "KILL" || tokens[0] == "kill")
		 	return this->killCmmd(tokens, usr);
		else if(tokens[0] == "KICK" || tokens[0] == "kick")
		 	return this->kickCmmd(tokens, usr);
		return replyMsg(ERR_UNKNOWNCOMMAND, tokens[0] + " :Unkown command", usr);
	}
}
bool 	BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

std::vector<std::string>   Server::parseMessage(std::string buffer)
{
	std::vector<std::string>    tok_tmp;
	std::vector<std::string>    tokens;
	size_t                      pos;
	std::string                 tmps;
	std::stringstream           s(buffer);
	std::istringstream          ss;

	if (buffer[0] == '\n' || buffer[0] == '\r' )
		tokens.push_back("");

	std::string::iterator new_end = std::unique(buffer.begin(), buffer.end(), BothAreSpaces);
	buffer.erase(new_end, buffer.end());
	if (((pos = buffer.find('\n')) != std::string::npos) || ((pos = buffer.find('\r')) != std::string::npos))
		buffer.erase(pos, buffer.size() - pos);
	while(getline(s, tmps, ':'))
		tok_tmp.push_back(tmps);
	if(buffer[0] == ':')
	{
		ss.str(tok_tmp[1]);
		while(ss >> tmps)
		{
			tokens.push_back(tmps);
			std::cout << "*" << tmps << std::endl;
		}

		tokens.erase(tokens.begin());
		if (tok_tmp.size() > 2)
			tokens.push_back(tok_tmp[2]);
	}
	else
	{
		ss.str(tok_tmp[0]);
		while(ss >> tmps)
			tokens.push_back(tmps);
		if (tok_tmp.size() > 1)
			tokens.push_back(tok_tmp[1]);
	}
	if (tokens.size() > 16)
		perror("Too many params\n");
	return tokens;
}
