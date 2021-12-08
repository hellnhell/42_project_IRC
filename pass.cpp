#include "server.hpp"

void Server::pass(std::vector<std::string> const &tokens, User* usr)
{
	std::cout << usr << std::endl;
	if (usr->getConnectionPswd()) //SEG FAULT
		std::cout << ERR_ALREADYREGISTRED << "ALREADY_REGISTER" << std::endl;
	if (tokens.empty())
		perror(ERR_NEEDMOREPARAMS);
	if ( tokens[1] != this->getPassword())
		perror("Incorrect passwd");
}
