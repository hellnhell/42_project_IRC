#include "../server.hpp"

 // ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER       RPL_NAMREPLY                    RPL_ENDOFNAMES
void Server::names_cmmd( std::vector<std::string> const &tokens, User *usr )
{
	std::vector<std::string>	tok;
    std::istringstream          ss;
    std::string                 tmp;
	std::string					message;
	Channel						*channel;
	bool						flags;
    std::vector<Channel *>::iterator it2;
    std::vector<User *>::iterator it3;

    if (tokens.size() == 1)
    {
        for (it2 = this->getChannels().begin(); it2 != this->getChannels().end(); it2++)
        {
            std::cout << "Channel: " << (*it2)->getName() << " Users: " << (*it2)->getUsers().size() << std::endl;
            for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
            {
                std::cout << "User: " << (*it3)->getUser() << " IP: " << (*it3)->getClientAdd() << " Socket: " << (*it3)->getFD() << std::endl;
            }
        }
    }
    else
    {
        ss.str(tokens[1]);
        while(getline(ss, tmp, ','))
            tok.push_back(tmp);
    }
}