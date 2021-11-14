#include "user.hpp"

User::User(int &_fd) : fd(_fd)
{
	std::cout << "User created with fd: " << this->fd << std::endl;
	this->user = "";
	this->nick = "";
	this->password = "";
}

User::~User()
{
	std::cout << "User destroyed with fd: " << this->fd << std::endl;
}


//getters setters
std::string User::get_user() {return (this->user);}

void User::set_user(std::string _user)
{
	this->user = _user;
}

std::string User::get_nick() {return (this->nick);}

void User::set_nick(std::string _nick)
{
	this->nick = _nick;
}

std::string User::get_pass() {return (this->password);}

void User::set_pass(std::string _pass)
{
	this->password = _pass;
}
