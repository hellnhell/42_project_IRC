#include "../server.hpp"

void    Server::quit_cmmd(std::vector<std::string> const &tokens, User *usr)
{
    std::string msg;
    
    if (tokens.size() > 1)
        msg = "QUIT :" + tokens[1];
    else
        msg = "QUIT : see you soon babe ;)";
    reply_msg(ERR_UNKNOWNERROR, "QUIT command executed", usr);
    actionDisplay("Quited : ", "", usr);
    for (std::list<User *>::iterator it = this->users_on.begin(); it != this->users_on.end(); it++)
	{
        std::cout << *it << std::endl;
		this->users_on.erase(it);
	}

}