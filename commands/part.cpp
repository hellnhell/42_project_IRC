#include "../server.hpp"

void	Server::partCmmd(std::vector<std::string> const& tokens, User *usr)
{
	std::vector<std::string>	tok;
	std::istringstream			ss(tokens[1]);
	std::string					tmp;
	std::string					leave_msg;
	std::string::size_type		pos;

	std::cout << "\n\n\n token1: " << tokens[1] << std::endl;

	 while(getline(ss, tmp, ','))
	{
	 	std::cout << tmp << std::endl;
	 	tok.push_back(tmp);
	}
	//print tok content
	for(int i = 0; i < tok.size(); i++)
		std::cout << "tok[" << i << "]: " << tok[i] << std::endl;
	for(int i = 0; i < tok.size(); i++)
	{
		if(usr->getChannels().size() <= 0)
		{
			std::cout << "User " << usr->getUser() << " is not in any channel" << std::endl;
			return ;
		}
		std::vector<Channel *>::const_iterator it;
		for (it = usr->getChannels().begin(); usr->getChannels().size() > 0 && it != usr->getChannels().end(); ++it)
		{
			if ((*it)->getName() == tok[i])
			{
				if (leave_msg.size() > 0)
				{
					//send leve_msg to all users in channel
				}
				else
				{
					//send generic msg to all users in channel
				}
				(*it)->disconnectUser(usr);
				usr->leaveChannel(*it);
				it--;
			}
		}
	}
}