#include "server.hpp"
#include <iostream>

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
		Server server(port);
		gservptr = &server;
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
				std::cout << ".";
				std::cout.flush();
			} else
				server.read_socks();
		}
		return(0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}



