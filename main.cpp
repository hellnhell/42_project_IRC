/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javier <javier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:11:46 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/16 23:08:16 by javier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>
#include "utils.hpp"

Server *gservptr;

void displayDev(Server *serv)
{
	std::cout << "\n\n\t DISPLAY" << "\n";
	std::cout << "Users connected to the server: " << serv->getUsers().size() << "\n";

	std::map<int, User *>::const_iterator it;
	for (it = serv->getUsers().begin(); serv->getUsers().size() >= 0 && it != serv->getUsers().end(); ++it)
	{
		std::cout << "Socket: " << it->first << "\tIP: " << it->second->getClientAdd() << "\tUser: " << it->second->getUser() << "\n";
	}


	std::cout << "Channels: " << serv->getChannels().size() << std::endl;
	std::vector<Channel *>::const_iterator it2;
	std::vector<User *>::const_iterator it3;
	for (it2 = serv->getChannels().begin(); it2 != serv->getChannels().end(); it2++)
	{
		std::cout << "Channel: " << (*it2)->getName() << " Users: " << (*it2)->getUsers().size() << std::endl;
		for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
		{
			std::cout << "User: " << (*it3)->getUser() << " IP: " << (*it3)->getClientAdd() << " Socket: " << (*it3)->getFD() << std::endl;
		}
	}
}


int	getPort(std::string str)
{
	int ret = stoi(str);
	if (str.length() > 10 || (ret < 1 || ret > 65535))
	{
		std::cout << "Not valid port - default 6667 -";
		return 6667;
	}
	return ret;
}


void signal_kill ( int number )
{
	if ( number == SIGINT ) //  number == SIGQUIT || number == SIGTERM???
	{
		std::cout << "----- KILLED -----\n";
		gservptr->~Server();
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	int	port;
	std::string psswd;
	if (argc < 2 || argc > 3)
	{
		std::cout << "Incorrect number of arguments" << std::endl;
		std::cout << "Input must content: <port> or <port> <password>" <<std::endl;
		return 0;
	}
	if (argc == 3)
	{
		psswd = (std::string)argv[2];
		if (psswd.size() > 20)
		{
			std::cout << "Password cannot exceed 20 characters" << std::endl;
			return 0;
		}
	}
	try
	{
		port = getPort(argv[1]);
		Server server;
		gservptr = &server; //??
		int set_read = 0;
		server.setPassword(psswd);
		while(1)
		{
			signal(SIGINT, signal_kill);
			server.build_select_list();
			if((set_read = server.get_read_socks()) < 0)
				throw Server::ServerException();
			if(set_read == 0)
			{
				std::cout << "\r";
				timerDisplay();
				std::cout.flush();
			}
			else
			{
				server.read_socks();
				//displayDev(&server);
			}
		}
		return(0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}




