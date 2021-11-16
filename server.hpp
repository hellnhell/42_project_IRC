#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/select.h>
# include <ctype.h>
# include <netinet/in.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <iostream>
# include <algorithm>
# include <string>
# include <vector>
# include <sstream>

# include "user.hpp"

class Server
{
	private:
		int					listening_socket;
		fd_set				reads;
		fd_set				writes;
		int 				highsock;
		struct timeval 		timeout;
		int					_list_connected_user[FD_SETSIZE];
		User				*list_users[FD_SETSIZE]; //N: cacoso hecho asi



		char 				*ascport;
		int 				port;
		struct sockaddr_in 	server_address;
		Server(const Server &other);

	public:
		Server();
		~Server();
		Server &operator=(const Server &other);

		void	build_select_list();
		int		get_read_socks();
		void	read_socks();
		void	handle_new_connection();
		void	deal_with_data(int listnum);

};

#endif
