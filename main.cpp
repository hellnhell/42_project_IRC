/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:11:46 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/10 10:24:53 by javrodri         ###   ########.fr       */
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

Server *parse_params(int argc, char **argv, Server &sv)
{
	int 						port;
	std::string 				psswd;
	std::string 				tmp;
	std::istringstream 			host(argv[1]);
	std::vector<std::string>  	host_info;

	if (argc < 2 || argc > 4)
	{
		std::cout << "Incorrect number of arguments" << std::endl;
		std::cout << "Input can content:" <<std::endl;
		std::cout << "- [host:port_network:password_network] <port> <password>" <<std::endl;
		std::cout << "- [host:port_network:password_network] <port> " <<std::endl;
		std::cout << "- <port> <password>" <<std::endl;
		std::cout << "- <port>" <<std::endl;

	}
	if (argc == 2)
	{
	 	port = getPort(argv[1]);
	 	sv.setHosting(HOST);
	 	sv.setPortNt(PORTNT);
	 	sv.setPassNt(PSSWNT);
	}
	else 
	{
		if (argc == 4)
		{
			while(getline(host, tmp, ':'))
				host_info.push_back(tmp);
			port = getPort(argv[2]);
			psswd = (std::string)argv[3];
			
		}
		else if ( argc == 3)
		{
			if (argv[1][0] == '[')
			{
				while(getline(host, tmp, ':'))
					host_info.push_back(tmp);
				port = getPort(argv[2]);
			}
			else
			{
				port = getPort(argv[1]);
				psswd = (std::string)argv[2];
			}
		}
		if (psswd.size() > 20)
			perror("Password too long");
		sv.setPassword(psswd);
		sv.setHosting(host_info[0]);
		sv.setPortNt(host_info[1]);
		sv.setPassNt(host_info[2]);
	}
	return &sv;
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
	//try de todo??
	try
	{
		Server server;
		gservptr = &server; //??
		int set_read = 0;
		parse_params(argc, argv, server);
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
				server.read_socks();
		}
		return(0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}



