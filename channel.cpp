/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:34 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/31 14:56:30 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

static int initType(const std::string &name)
{
	if (name[0] == '#')
		return 0;
	else if (name[0] == '&')
		return 1;
	else if (name[0] == '+')
		return 2;
	else if (name[0] == '!')
		return 3;
	return (4);
}

static void initModes(t_modes *modes)
{
	modes->t = 1;
	modes->k = "";
	modes->b = 0;
	modes->n = 0;
}

Channel::Channel(Server *server, User *creator, const std::string &name)
{
	if(name.empty())
		throw std::invalid_argument("Channel name can't be empty");
	else if (name.size() > 50)
		throw std::invalid_argument("Channel name can't be longer than 50 characters");
	else if (name[0] != '&' && name[0] != '#' && name[0] != '+' && name[0] != '!')
		throw std::invalid_argument("Channel name must start with &, #, + or !");
	else if (((name.find(' ') != std::string::npos) || (name.find(',') != std::string::npos)))
		throw std::invalid_argument("Channel name can't contain spaces or commas");
	else if((name.find(7) != std::string::npos))
		throw std::invalid_argument("Channel name can't contain control characters");
	else
	{
		initModes(&_modes);
		this->_server = server;
		this->_name = name;
		this->_topic = "";
		this->_type = initType(name);
		this->_modes.O = creator->getUser();
		this->_max_users = 1024;
		this->_ops.push_back(creator);
		this->_current_users = 0;
	}
	std::cout << "Channel " << name << " created" << std::endl;
}

Channel::Channel(Server *server, User *creator, const std::string &name, const std::string &topic)
{
	*this = Channel(server, creator, name);
	this->_topic = topic;
}

Channel::Channel(Server *server, User *creator, const std::string &name, unsigned int max_users)
{
	*this = Channel(server, creator, name);
	this->_max_users = max_users;
}

Channel::Channel(Server *server, User *creator, const std::string &name, const std::string &topic, unsigned int max_users)
{
	*this = Channel(server, creator, name, topic);
	this->_max_users = max_users;
}

Channel::~Channel() {}

Channel &Channel::operator=(const Channel &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_topic = rhs._topic;
		this->_type = rhs._type;
		this->_modes = rhs._modes;
		this->_max_users = rhs._max_users;
		this->_ops = rhs._ops;
		this->_current_users = rhs._current_users;
	}
	return (*this);
}

void Channel::setName(const std::string &name)
{
	_name = name;
}

void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

void Channel::setMaxUsers(unsigned int max_users)
{
	_max_users = max_users;
}

void Channel::joinUser(User *user)
{
	std::vector<User *>::iterator it;

	if ((it = std::find(_bans.begin(), _bans.end(), user)) != _bans.end())
		return this->_server->replyMsg(ERR_BANNEDFROMCHAN, this->getName() + " :Cannot join channel (+b)", user);

	if((it = std::find(_users.begin(), _users.end(), user)) != _users.end())
		return;
	_users.push_back(user);
	this->_current_users++;
}

void Channel::disconnectUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_users.begin(), _users.end(), user)) != _users.end())
	{
std::cout << "User " << user->getUser() << " disconnected from channel " << _name << std::endl;
		_users.erase(it);
		this->_current_users--;
	}

	if(this->_current_users <= 0)
	{
		std::cout << "Channel " << this->_name << " deleted" << std::endl;
		this->_server->removeChannel(this);
	}

}

void Channel::kickUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_users.begin(), _users.end(), user)) != _users.end())
	{
		_users.erase(it);
	}
}

int Channel::banUser(User *user, User *banned)
{

	std::vector<User *>::iterator it;

	if((it = std::find(_bans.begin(), _bans.end(), banned)) != _bans.end())
		return -1;
	if((it = std::find(_users.begin(), _users.end(), banned)) == _users.end())
		return -1;
	_bans.push_back(banned);
	std::vector<std::string>		tok_aux;
	tok_aux.push_back("KICK");
	tok_aux.push_back(this->_name);
	tok_aux.push_back(banned->getNick());
	this->_server->kickCmmd(tok_aux, user);
	return 0;
}

void Channel::unbanUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_bans.begin(), _bans.end(), user)) != _bans.end())
	{
		_bans.erase(it);
	}
}

int Channel::opUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_ops.begin(), _ops.end(), user)) != _ops.end())
		return -1;
	if((it = std::find(_users.begin(), _users.end(), user)) == _users.end())
		return -1;
	_ops.push_back(user);
	return 0;
}

void Channel::deopUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_ops.begin(), _ops.end(), user)) != _ops.end())
		_ops.erase(it);

}


std::string Channel::getName() const
{
	return _name;
}

std::string Channel::getTopic() const
{
	return _topic;
}

unsigned int Channel::getMaxUsers() const
{
	return _max_users;
}

unsigned int Channel::getCurrentUsers() const
{
	return _current_users;
}

std::vector<User *> const &Channel::getUsers() const
{
	return _users;
}

std::vector<User *> const &Channel::getOps() const
{
	return _ops;
}

std::vector<User *> const &Channel::getBans() const
{
	return _bans;
}

std::string const Channel::getModes() const
{
	std::string modes;

	if (this->_modes.n)
		modes += "n";
	if (this->_modes.t)
		modes += "t";
	if (this->_modes.k.size())
		modes += "k";
	if (this->_modes.o)
		modes += "o";

	return modes;
}

bool const Channel::getMode(char mode) const
{
	switch (mode)
	{
		case 'n':
			return this->_modes.n;
		case 't':
			return this->_modes.t;
		case 'k':
		{
			if (this->_modes.k.size())
				return true;
			else
				return false;
		}
		case 'o':
			return this->_modes.o;
		default:
			return false;
	}
}

bool const Channel::isOperator(User *usr) const
{
	std::vector<User *>::const_iterator it;

	if((it = std::find(_ops.begin(), _ops.end(), usr)) != _ops.end())
		return true;
	return false;
}

void Channel::setMode(char mode, bool value)
{
	switch (mode)
	{
		case 'n':
			this->_modes.n = value;
			break;
		case 't':
			this->_modes.t = value;
			break;
		case 'k':
			this->_modes.k = value;
			break;
		case 'o':
			this->_modes.o = value;
			break;
		default:
			break;
	}
}

User *Channel::getNick(std::string nickName) const
{
	std::vector<User *>::const_iterator it;

	for (it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if ((*it)->getNick() == nickName)
			return (*it);
	}
	for (it = this->_ops.begin(); it != this->_ops.end(); it++)
	{
		if ((*it)->getNick() == nickName)
			return (*it);
	}
	return (NULL);
}

User *Channel::getBan(std::string nickName) const
{
	std::vector<User *>::const_iterator it;

	for (it = this->_bans.begin(); it != this->_bans.end(); it++)
		if ((*it)->getNick() == nickName)
			return (*it);
	return (NULL);
}

void Channel::setKey(std::string key)
{
	this->_modes.k = key;
}

std::string Channel::getKey() const
{
	return this->_modes.k;
}
