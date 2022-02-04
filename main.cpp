/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:11:46 by emartin-          #+#    #+#             */
/*   Updated: 2022/02/04 11:37:45 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>
#include "utils.hpp"

Server *gservptr;

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
	if ( number == SIGINT)
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
		Server server(port);
		gservptr = &server;
		int set_read = 0;
		server.setPassword(psswd);
		while(1)
		{
			signal(SIGINT, signal_kill);
			server.buildSelectList();
			if((set_read = server.getReadSocks()) < 0)
				throw Server::ServerException();
			if(set_read == 0)
			{
				std::cout << "\r";
				timerDisplay();
				std::cout <<  "  Connections : " << YELLOW << server.getUsers().size() << WHITE << "\tChannels: " << YELLOW << server.getChannels().size() << WHITE " ";
				if ( i == 4)
					i = 1;
				 switch (i)
				 {
				 	case 1:
				 		std::cout << "\t☁️\t" ; // "** O" << " O **" 🌎 
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
				server.checkPing();
				std::cout.flush();
			}
			else
			{
				std::cout << "\n";
				server.readSocks();
			}
		}
		return(0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}




