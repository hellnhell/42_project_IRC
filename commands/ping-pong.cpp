#include "../server.hpp"



void    Server::checkPing()
{
    
    std::string ping[] = {"Run mtf run @·5", "Enter the code: 222@++:", "Read more @#/!"};
    std::cout << this->getPingDiff() << std::endl;
    if (this->getPingDiff() == 4)
    {
        std::cout << "Ping command: " << ping[rand() % 3] << std::endl;
        this->flag = 1;
    }
    if (this->getPingDiff() == 10 && this->flag == 1)
            std::cout << "Pong command: "  << std::endl;

}

// void    Server::ping_cmmd(std::vector<std::string> const &tokens, User *usr)
// {

// }