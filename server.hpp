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

class Server
{
	private:
		int					listening_socket;
		fd_set				reads;
		int 				highsock;
		struct timeval 		timeout;
		// int					readsocks;
		int					_list_connected_user[FD_SETSIZE];

		char 				*ascport;
		int 				port;
		struct sockaddr_in 	server_address;
		// int 				reuse_addr = 1;
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
