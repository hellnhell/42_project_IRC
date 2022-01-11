#include "../server.hpp"

void    Server::quitCmmd(std::vector<std::string> const &tokens, User *usr)
{
	std::string msg;
	
	if (tokens.size() > 1)
		msg = "QUIT :" + tokens[1];
	else
		msg = "QUIT : see you soon babe ;)";
	replyMsg(ERR_UNKNOWNERROR, "QUIT command executed", usr);
	actionDisplay("Quited : ", "", usr);
    this->deleteUser(usr); //Recorrer channels... Nestor help
}