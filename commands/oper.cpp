#include "../server.hpp"

//gestionar el -o en modes??
void	Server::operCmmd(std::vector<std::string> const &tokens, User *usr)
{
	if (tokens.size() < 3)
		return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + ":Not enough parameters", usr);
	else if (toUpper(tokens[1]).compare(toUpper(usr->getUser())) != 0)
		return replyMsg(ERR_NOOPERHOST, ":Incorrect user connected", usr);
	else if (tokens[2] == this->op_password)
	{
		if (usr->getOper() == true)
			return;
		else
			usr->setOper(true);
		return replyMsg(RPL_YOUREOPER, ":IRC Operator mode activated", usr);
	}
	else
		return replyMsg(ERR_PASSWDMISMATCH, " :Password mismatch", usr);
}
