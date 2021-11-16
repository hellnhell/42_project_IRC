#include "server.hpp"
#include <iostream>

Server *gservptr;

void signal_kill ( int number )
{
	if ( number == SIGINT)
	{
		std::cout << "kill\n";
		gservptr->~Server();
		kill (getpid(), 9);
		exit(EXIT_FAILURE);
	}
}

int main()
{
	Server server;
	gservptr = &server;
	int set_read = 0;
	while(1)
	{
//		sleep(3);
		signal(SIGINT, signal_kill);
		server.build_select_list();
		if((set_read = server.get_read_socks()) < 0)
		{
			perror("select");
			exit(EXIT_FAILURE);
		}
		if(set_read == 0)
		{
			std::cout << ".";
			std::cout.flush();
		} else
			server.read_socks();
	}

	return(0);
}



