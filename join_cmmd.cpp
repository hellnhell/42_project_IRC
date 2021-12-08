#include "server.hpp"


void Server::join_cmd(std::vector<std::string> const &tokens, User* usr)
{
	if (tokens.size() < 2)
	{
		std::cout << "Usage: /join <channel>" << std::endl;
		return;
	}

	//enviar informacion al usuario joineado sobre el canal y sus comandos disponibles
	std::vector<Channel*>::iterator it;
	for (it = channels.begin(); it != channels.end(); ++it)
	{
		if ((*it)->getName() == tokens[1])
		{
			(*it)->joinUser(usr);
			std::cout << "Joined channel " << (*it)->getName() << std::endl;
			std::cout << "Available commands: /msg <user> <message>, /leave, /list, /users, /help" << std::endl;
			return;
		}
	}
	this->channels.push_back(new Channel(usr, tokens[1]));
	this->channels.back()->joinUser(usr);
	std::cout << "Joined channel " << this->channels.back()->getName() << std::endl;
	std::cout << "Available commands: /msg <user> <message>, /leave, /list, /users, /help" << std::endl;
}
