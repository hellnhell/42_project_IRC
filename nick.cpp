#include "server.hpp"

void    Server::nick(std::vector<string> const& tokens, User* usr)
{
    if (usr->getNick().empty())
    {
        usr->setNick(tokens[1]);
        //lo añades a una lista de nicks para ver si está.
        //plantear meterlo en mapa y buscar x key??
    }
    else
        //if find nick en la lista de nicks borras y seteas
}