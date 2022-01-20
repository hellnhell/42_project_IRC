/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:11:46 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/20 12:33:08 by javrodri         ###   ########.fr       */
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

		//print ops on channel
		std::cout << "Channel: " << (*it2)->getName() << "\tOps: ";
		for (it3 = (*it2)->getOps().begin(); it3 != (*it2)->getOps().end(); it3++)
		{
			std::cout << (*it3)->getNick() << " ";
		}
		std::cout << std::endl;


		std::cout << "Channel: " << (*it2)->getName() << " Users: " << (*it2)->getUsers().size() << std::endl;
		for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
		{
			std::cout << "nick: ";

			std::vector<User *>::const_iterator it4;
			for (it4 = (*it2)->getOps().begin(); it4 != (*it2)->getOps().end(); it4++)
			{
				if ((*it3)->getNick() == (*it4)->getNick())
				{
					std::cout << "*";
					it4 = (*it2)->getOps().end();
					it4--;
				}
			}

			std::cout << (*it3)->getNick() << " ";
			std::cout << (*it3)->getFD() << std::endl;
			//std::cout << (*it3)->getUser() << " IP: " << (*it3)->getClientAdd() << " Socket: " << (*it3)->getFD() << std::endl;
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
	if ( number == SIGINT) //  number == SIGQUIT || number == SIGTERM???
	{
		std::cout << RED "\n💀  KILLED 💀 \n" << WHITE;
		gservptr->~Server();
		std::cout << "----- KILLED -----\n";
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
	int i = 1;
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
			server.buildSelectList();
			if((set_read = server.getReadSocks()) < 0)
			{
				// std::cout << RED "mal" WHITE << std::endl;
				throw Server::ServerException();
			}
			// std::cout << RED << set_read << WHITE << std::endl;

			if(set_read == 0)
			{
				std::cout << "\r";
				timerDisplay();
				server.checkPing();
				std::cout <<  "  Connections : " << YELLOW << server.getUsers().size() << WHITE << "\tChannels: " << YELLOW << server.getChannels().size() << WHITE " ";
				if ( i == 4)
					i = 1;
				 switch (i)
				 {
				 	case 1:
				 		std::cout << "\t☁️\t" ; // "** O" << " O **" 🌎 POSIBILIDADES VARIAS
				 		break;
				 	case 2:
				 		std::cout << "\t🌧️\t"; // "** ^" << " ^ **" 🌏
				 		break;
					case 3:
				 		std::cout << "\t🌨️\t" ; // "** -" << " - **" 🌍
				 		break;
				 	default:
				 		break;
				}
				i++;
				// server.checkPing();
				std::cout.flush();
			}
			else
			{
				std::cout << "\n";
				server.readSocks();
				displayDev(&server);
			}
		}
		return(0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}




