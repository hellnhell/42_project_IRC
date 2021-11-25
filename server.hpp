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
# include <deque>
# include <map>
# include <list>
# include <sstream>
# include "user.hpp"


//ERRORS
# define ERR_NOPASSWD				"002"
# define ERR_ALREADYREGISTRED		"462"
# define ERR_NEEDMOREPARAMS			"461"



class Server
{
	private:
		int						listening_socket;
		fd_set					reads;
		fd_set					writes;
		int 					highsock;
		struct timeval 			timeout;
		int						_list_connected_user[FD_SETSIZE];
		std::map<int, User*> 	list_users;
		char 					*ascport;
		int 					port;
		struct sockaddr_in 		server_address;

		std::deque<std::string> cmd_list;
		Server(const Server &other);

		std::list<User *>		users_on;
		std::string				password;

	public:
		Server(int port);
		~Server();
		Server &operator=(const Server &other);

		void						build_select_list();
		int							get_read_socks();
		void						read_socks();
		void						handle_new_connection();
		void						deal_with_data(int listnum);
		std::vector<std::string>	parse_message(std::string buffer);

		void						setPassword(std::string psswd);
		std::string					getPassword() const;

		void						user_cmd(std::vector<std::string> const &tokens, User *usr);
		void 						pass(std::vector<std::string> const& tokens, User* usr);



};

#endif
