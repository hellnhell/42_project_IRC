#include "../server.hpp"

void	Server::partCmmd(std::vector<std::string>const &tokens, User *usr)
{
	std::vector<std::string>	tok;
	std::string					tmp;
	std::istringstream			ss;
	std::string					leave_msg;
	std::string::size_type		pos;

    if (tokens.size() == 1 ) //se puede meter el quit
        return this->replyMsg(ERR_NOSUCHCHANNEL, "<empty> :No such channel", usr);
	std::cout << "\n\n\n token1: " << tokens[1] << std::endl;
    ss.str(tokens[1]);
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
		std::vector<Channel *>::iterator it;
		for (it = usr->getChannels().begin(); usr->getChannels().size() > 0 && it != usr->getChannels().end(); ++it)
		{
			if ((*it)->getName() == tok[i])
			{
				if (leave_msg.size() > 0)
				{
                    msgToChannel(leave_msg, usr, *it);
					//send leve_msg to all users in channel
				}
				else
				{
                    leave_msg = usr->getNickMask() + "  " + (*it)->getName() + "\n";;
                    msgToChannel(leave_msg, usr, *it);
					// ???? send generic msg to all users in channel
				}
				(*it)->disconnectUser(usr);
				usr->leaveChannel(*it);
				it--;
			}
		}
	}
}