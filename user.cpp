/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:39:03 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/31 13:27:49 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"

User::User(int &_fd, struct sockaddr_in const &client_addr) : fd(_fd)
{
	this->t_ping = 10000;
	this->ping_on = false;
	this->away_on = false;
	this->address = client_addr;
	this->connection_pswd = 0;
	this->check_user = false;
	this->check_nick = false;
	this->check_regist = false;
	this->op_mode = false;
	this->connection_pswd = 0;
}

User::~User()
{
	std::vector<Channel *>::const_iterator it;
	for (it = this->getChannels().begin(); this->getChannels().size() > 0 && it != this->getChannels().end(); ++it)
	{
		(*it)->disconnectUser(this);
		this->leaveChannel(*it);
		it--;
	}
}

int 	User::getFD() {  return (this->fd); }

const 	std::string User::getUser() const { return (this->user); }
void 	User::setUser(std::string _user) {	this->user = _user; }

const 	std::string User::getRealName() const { return (this->realName); }
void 	User::setRealName(std::string _realName) {	this->realName = _realName; }

const	std::string User::getNick() const { return (this->nick); }
void	User::setNick(std::string _nick) {	this->nick = _nick; }

const 	std::string User::getNickMask() const { return (this->nickMask); }
void 	User::setNickMask(std::string _nickMask) {	this->nickMask = _nickMask; }


bool	User::getOper() const { return (this->op_mode); }
void	User::setOper(bool op) { this->op_mode = op; }

bool	User::getConnectionPswd() const { return (this->connection_pswd); }
void	User::setConnectionPswd(bool cp) { this->connection_pswd = cp; }


const bool	&User::getCheckedUser() const { return (this->check_user); }
void		User::setCheckedUser(bool cu) { this->check_user = cu; }

const bool	&User::getCheckedNick() const { return (this->check_nick); }
void		User::setCheckedNick(bool nu) { this->check_nick = nu; }

bool	&User::getCheckedRegist()
{
	if (getCheckedNick() && getCheckedUser())
		this->check_regist = true;
	return this->check_regist;
}

void 			User::setReply(std::string const &msg) { this->reply.push_back(msg); }
std::string 	User::getReply()
{
	std::string temp;
	if (this->reply.size())
	{
		temp = this->reply[0];
		this->reply.erase(this->reply.begin());
	}
	return temp;
}

std::string User::getClientAdd() const
{
	struct in_addr clientIP;
	clientIP = this->address.sin_addr;
	char ipStr[INET_ADDRSTRLEN];
	return inet_ntop(AF_INET, &clientIP, ipStr, INET_ADDRSTRLEN);
}

std::vector<Channel*>		&User::getChannels() { return this->channels; };

int User::joinChannel(Channel *channel)
{
	std::vector<Channel *>::iterator it;

	if((it = std::find(channels.begin(), channels.end(), channel)) != channels.end())
	{
		return 1;
	}
	this->channels.push_back(channel);
	return 0;
}

void User::leaveChannel(Channel *channel)
{
	for (std::vector<Channel *>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
	{
		if (*it == channel)
		{
			this->channels.erase(it);
			return ;
		}
	}
}

const uint64_t		&User::getTimeZero() const { return this->t_zero; }
void				User::setTimeZero(uint64_t const & time_zero) { this->t_zero = time_zero; }

const uint64_t		&User::getTimePing() const { return this->t_ping; }
void				User::setTimePing(uint64_t const & time_ping) { this->t_ping = time_ping; }

const bool			&User::getPingOn() const { return (this->ping_on); }
void				User::setPingOn(bool po) { this->ping_on = po; }

const std::string 	&User::getPing() const { return this->ping; }
void				User::setPing(std::string p) {this->ping.clear(); this->ping = p; }

const bool			&User::getAwayOn() const { return (this->away_on); }
void				User::setAwayOn(bool po) { this->away_on = po; }

const std::string 	&User::getAway() const { return this->away; }
void				User::setAway(std::string p) { this->away = p; }
