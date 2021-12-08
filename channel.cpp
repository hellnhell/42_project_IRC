/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:34 by nazurmen          #+#    #+#             */
/*   Updated: 2021/12/08 20:43:37 by nazurmen         ###   ########.fr       */
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

Channel::Channel(User *creator, const std::string &name)
{
	if(name.empty())
		perror("Channel name cannot be empty");
	else if (name.size() > 50)
		perror("Channel name is too long");
	else if (name[0] != '&' || name[0] != '#' || name[0] != '+' || name[0] != '!')
		perror("Channel name must start with &, #, +, or !");
	else if (name.find_first_of(" ,"))
		perror("Channel name cannot contain spaces or commas");
	else if(name.find_first_of(7))
		perror("Channel name cannot contain control characters");
	else
	{
		initModes(&_modes);
		this->_name = name;
		this->_topic = "";
		this->_password = "";
		this->_type = initType(name);
		this->_modes.O = creator->getUser();
		this->_max_users = 1024;
		this->_ops.push_back(creator);
		this->_current_users = 1;
	}

	std::cout << "Channel " << name << " created" << std::endl;
}

Channel::Channel(User *creator, const std::string &name, const std::string &topic) : Channel(creator, name) {
	this->_topic = topic;
}

Channel::Channel(User *creator, const std::string &name, unsigned int max_users) : Channel(creator, name)
{
	this->_max_users = max_users;
}

Channel::Channel(User *creator, const std::string &name, const std::string &topic, unsigned int max_users) : Channel(creator, name, topic)
{
	this->_max_users = max_users;
}

Channel::~Channel() {}

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
		_users.push_back(*it);
}

void Channel::disconnectUser(User *user)
{
	std::vector<User *>::iterator it;

	if((it = std::find(_users.begin(), _users.end(), user)) != _users.end())
		_users.erase(it);
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

std::vector<User *> Channel::getUsers() const
{
	return _users;
}

std::vector<User *> Channel::getOps() const
{
	return _ops;
}

std::vector<User *> Channel::getBans() const
{
	return _bans;
}
