/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javier <javier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:34 by nazurmen          #+#    #+#             */
/*   Updated: 2021/12/16 23:15:20 by javier           ###   ########.fr       */
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
	modes->a = 0;
	modes->i = 0;
	modes->m = 0;
	modes->n = 0;
	modes->p = 0;
	modes->s = 0;
	modes->t = 0;
	modes->r = 0;
	modes->k = 0;
	modes->l = 0;
	modes->b = 0;
	modes->e = 0;
	modes->I = 0;
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
		this->_password = "";
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
		this->_password = rhs._password;
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
	{
		perror("User is banned from this channel");
		return ;
	}

	if((it = std::find(_users.begin(), _users.end(), user)) != _users.end())
	{
		perror("User is already in this channel");
		return ;
	}
	_users.push_back(user);
	this->_current_users++;
}

void Channel::disconnectUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_users.begin(), _users.end(), user)) != _users.end())
	{
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

void Channel::banUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_users.begin(), _users.end(), user)) != _users.end())
	{
		_bans.push_back(*it);
		_users.erase(it);
	}
}

void Channel::unbanUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_bans.begin(), _bans.end(), user)) != _bans.end())
	{
		_bans.erase(it);
	}
}

void Channel::opUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_ops.begin(), _ops.end(), user)) != _ops.end())
	{
		_ops.push_back(*it);
		_users.erase(it);
	}
}

void Channel::deopUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_ops.begin(), _ops.end(), user)) != _ops.end())
	{
		_ops.erase(it);
		_users.push_back(*it);
	}
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
