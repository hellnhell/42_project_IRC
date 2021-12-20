#include "../server.hpp"


void    Server::checkPing()
{
    User* usr;
    std::string ping[] = {"5@·Run/mtf/run/@·5", "222@++222@++", "5#55Read/more5#55", "5.-You/would/have/studied.-5"};
    std::string pingpass = ping[rand() % 4];
    std::map<int, User*>::iterator it = this->list_users.begin();

    while (it != this->list_users.end())
    {
        usr = this->list_users[it->first];
        if ((getTime() - usr->getTimeZero()) > usr->getTimePing())
        {
            if ((usr->getCheckedUser() == false || usr->getPingOn() == true) && ((getTime() - usr->getTimeZero()) > (usr->getTimePing() + 10000)))
            {
                if (usr->getPingOn())
                    reply_msg("ERROR :Ping timeout ", " [Connection aborted]", usr);
                else
                    reply_msg("ERROR :Registration timeout ", " [Connection aborted]", usr);
          		actionDisplay("Connection lost", "", usr);
                this->deleteUser(usr);
                return ;
            }
            else if (usr->getCheckedUser() == true || usr->getPingOn() == false)
            {
                usr->setPingOn(true);
                usr->setPing(pingpass);
                pingpass = usr->getPing() + "\n";
                send(usr->getFD(),"PING ", strlen("PING "), 0);
                send(usr->getFD(),pingpass.c_str(), pingpass.length(), 0);
                std::cout << "\r";
                actionDisplay("Pinged", "", usr);
            }
        }
        it++;
    }
}

//UNo como comando y uno como control??
void    Server::pong_cmmd(std::vector<std::string> const &tokens, User *usr)
{
    if (tokens.size() > 1 && tokens[1] == usr->getPing())
    {
        usr->setPingOn(false);
        usr->setTimePing(40000);
        actionDisplay("Ping introduced", "", usr);
    }
    else
    {
        std::cout << tokens[1]  << "yyyyyy" << usr->getPing() << "yyyyyy " << tokens.size()<< std::endl;
        reply_msg("ERROR :Wrong reply, sorry! ", " [Connection aborted]", usr);
        // deleteUser(usr);
    }
}
