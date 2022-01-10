#include "../server.hpp"
 
void Server::whoCmmd(std::vector<std::string>const& tokens, User *usr)
{
	std::string msg;

 
	std::list<User *>::iterator it;
	for (it = users_on.begin(); it != users_on.end(); ++it)
	{
        if (tokens.size() > 1)
        {
            if ((*it)->getNick() == tokens[1])
            {
                msg = (*it)->getUser() + " " + (*it)->getClientAdd() + " " + (*it)->getNick() + " H+ :0 " + (*it)->getRealName();
                replyMsg(RPL_WHOREPLY, msg, usr);
                replyMsg(RPL_ENDOFWHO, (*it)->getUser() + " :End of WHO list.", usr);
                return ;
            }
            if (tokens[1][0] == '#')
            {
                std::vector<Channel *>::const_iterator it2;
			    std::vector<User *>::const_iterator it3;
			    for (it2 = this->getChannels().begin(); it2 != this->getChannels().end(); it2++)
			    {
			    	if (tokens[1] == (*it2)->getName())
                    {
                        for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
                            msg += "\n" + (*it3)->getUser() + " " + (*it3)->getClientAdd() + " " + (*it3)->getNick();
                        replyMsg(RPL_WHOREPLY, msg, usr);
				    }
                    //Wait for OPS
                    // if (tokens.size() == 3 && tokens[2] == "o")
                    // {
                    //     for(it3 = (*it2)->getOps().begin(); it3 != (*it2)->getOps().end(); ++it3)
                    //         msg += "\n" + (*it3)->getUser() + " " + (*it3)->getClientAdd() + " " + (*it3)->getNick();
                    //     replyMsg(RPL_WHOREPLY, msg, usr);
                    // }
                    replyMsg(RPL_ENDOFWHO, (*it3--)->getUser() + " :End of WHO list.", usr); //?
			    }
                return ;
            }
        }
        else
        {
            msg = (*it)->getUser() + " " + (*it)->getClientAdd() + " " + (*it)->getNick() + "  " + (*it)->getRealName();
            replyMsg(RPL_WHOREPLY, msg, usr);
            replyMsg(RPL_ENDOFWHO, (*it)->getUser() + " :End of WHO list.", usr); //?
        }
	}
	
}
