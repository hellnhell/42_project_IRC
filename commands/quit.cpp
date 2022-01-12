#include "../server.hpp"

void	Server::quitCmmd(std::vector<std::string> const &tokens, User *usr)
{
	std::string msg;

	if (tokens.size() > 1)
		msg = "QUIT :" + tokens[1];
	else
		msg = "QUIT : see you soon babe ;)";
	if(usr->getChannels().size() <= 0)
	{
		std::cout << "User " << usr->getUser() << " is not in any channel" << std::endl;
		return replyMsg(ERR_UNKNOWNERROR, msg, usr) ;
	}
	std::vector<Channel *>::const_iterator it;
	for (it = usr->getChannels().begin(); usr->getChannels().size() > 0 && it != usr->getChannels().end(); ++it)
	{
		(*it)->disconnectUser(usr);
		usr->leaveChannel(*it);
		return replyMsg(ERR_UNKNOWNERROR, msg, usr);
		it--;
	}
	actionDisplay("Quited : ", "", usr);
	this->deleteUser(usr);
}
