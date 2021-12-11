/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:52 by nazurmen          #+#    #+#             */
/*   Updated: 2021/12/10 16:59:23 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

static void setnonblocking(int sock)
{
	int opts;

	opts = fcntl(sock, F_GETFL);
	if (opts < 0) {
		perror("fcntl(F_GETFL)");
		exit(EXIT_FAILURE);
	}
	opts = (opts | O_NONBLOCK);
	if (fcntl(sock,F_SETFL,opts) < 0) {
		perror("fcntl(F_SETFL)");
		exit(EXIT_FAILURE);
	}
	return;
}

const char* Server::ServerException::what() const throw ()
{
	return "Server Exception: Something went wrong\n";
}

Server::Server()
{
	std::cout << "Server Constructor:" << std::endl;
	int reuse_addr = 1;
	FD_ZERO(&this->reads);
	this->highsock = 0;
	this->listening_socket = 0;
	this->listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(this->listening_socket < 0)
	{
		perror("Socket");
		throw Server::ServerException();
	}
	setnonblocking(this->listening_socket);
	memset(this->_list_connected_user, 0 , sizeof( this->_list_connected_user));
	memset((char *)&this->server_address, 0, sizeof(this->server_address));
	this->server_address.sin_family = AF_INET;
	this->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	this->server_address.sin_port = htons(PORT);
	setsockopt(this->listening_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int));
	if(bind(this->listening_socket, (struct sockaddr *) &this->server_address, sizeof(this->server_address)) == -1 )
	{
		perror("bind");
		close(this->listening_socket);
		throw Server::ServerException();
	}
	if(listen(this->listening_socket, FD_SETSIZE) == -1)
	{
		perror("listening");
		close(this->listening_socket);
		throw Server::ServerException();
	}
	this->highsock = this->listening_socket;
	this->cmd_list.push_back("PASS");
	this->cmd_list.push_back("USER");
	this->cmd_list.push_back("NICK");
	this->cmd_list.push_back("EXIT");
	this->cmd_list.push_back("TIME");
	this->cmd_list.push_back("JOIN");
	this->cmd_list.push_back("PRIVMSG");
	this->cmd_list.push_back("MOTD");

}

Server::~Server()
{
	close( this->listening_socket );
	FD_ZERO( &this->reads );
	memset( this->_list_connected_user, 0 , sizeof( this->_list_connected_user ) );
	memset( (char *) &this->server_address, 0 , sizeof( this->server_address ) );
	std::cout << "Destructor Server\n";
}

void Server::build_select_list()
{
	int listnum;

	FD_ZERO(&this->reads);
	FD_ZERO(&this->writes);
	FD_SET(this->listening_socket, &this->reads);
	for (listnum = 0; listnum < FD_SETSIZE; listnum++) {
		if (this->_list_connected_user[listnum] != 0) {
			FD_SET(this->_list_connected_user[listnum],&this->reads);
			FD_SET(this->_list_connected_user[listnum],&this->writes);
			if (this->_list_connected_user[listnum] > this->highsock)
				this->highsock = this->_list_connected_user[listnum];
		}
	}
}

int Server::get_read_socks()
{
	this->timeout.tv_sec = 1;
	this->timeout.tv_usec = 0;
	return select((this->highsock + 1 ), &this->reads, (fd_set *) 0, (fd_set *) 0 , &this->timeout);
}

void Server::handle_new_connection()
{
	int connection;
	struct sockaddr_in client_address;

	connection = accept(this->listening_socket, NULL, NULL);
	if (connection < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	setnonblocking(connection);
	for (size_t listnum = 0; (listnum < FD_SETSIZE) && (connection != -1); listnum++)
	{
		if(this->_list_connected_user[listnum] == 0)
		{
			this->_list_connected_user[listnum] = connection;
			this->list_users[connection] = new User(connection, client_address);
			if (this->getPassword().empty())
				this->list_users[connection]->setConnectionPswd(1);
			else
				this->list_users[connection]->setConnectionPswd(0);
			// printf("Connection accepted: fd=%d Slot=%lu\n", connection, listnum);
			actionDisplay("Connection accepted", "", list_users[connection]);

			connection = -1;
		}
	}
	if (connection != -1) {
		printf("\n No room left for new client.\n");
		close(connection);
	}

std::map<int, User*>::iterator it;

for(it = this->list_users.begin(); it != this->list_users.end(); it++)
{
	std::cout << it->first << " fds chekeados en handle" << std::endl;
}

}

void Server::deal_with_data(int listnum)
{
	char 			buffer[512];
	std::string		buff_input;
	ssize_t			verify;
	std::string 	recived;
	std::vector<std::string> tokens;

	while ((verify = recv(this->_list_connected_user[listnum], buffer, 512, 0)) > 0)
	{
		buffer[verify] = 0;
		recived += buffer;
	}
	if(recived.length() <= 0)
	{
		//delete user?
		actionDisplay("Connection lost", "", this->list_users[this->_list_connected_user[listnum]]);
		delete (this->list_users[this->_list_connected_user[listnum]]);
		// std::cout << std::endl << "Connection lost fd -> " << this->_list_connected_user[listnum] << " slot -> " <<  listnum << std::endl;
		close(this->_list_connected_user[listnum]);
		this->_list_connected_user[listnum] = 0;
	}
	else
	{
		User *tmpuser = this->list_users[this->_list_connected_user[listnum]];
		tokens = parse_message(recived);
		if (tokens[0].empty())
			return;
		std::transform(tokens[0].begin(), tokens[0].end(),tokens[0].begin(), ::toupper);
		actionDisplay("Attend client", " CMD:" + tokens[0], tmpuser);
		if ((std::find(cmd_list.begin(), cmd_list.end(), tokens[0]) == cmd_list.end()))
			return reply_msg(ERR_UNKNOWNCOMMAND, tokens[0] + " :Unkown command", tmpuser);
		if(tokens[0] == "USER" || tokens[0] == "user")
		{
			tmpuser = this->list_users[this->_list_connected_user[listnum]];
			this->user_cmd(tokens, tmpuser);
		}
		else if(tokens[0] == "NICK" || tokens[0] == "nick")
		{
			tmpuser = this->list_users[this->_list_connected_user[listnum]];
			this->nick_cmd(tokens, tmpuser);
		}
		else if(tokens[0] == "PASS" || tokens[0] == "pass")
		{
			this->pass(tokens, tmpuser); //N: esto no está definido
		}
		else if(tokens[0] == "PRIVMSG" || tokens[0] == "PRIVMSG")
		{
			this->privmsg(tokens, tmpuser);
		}
		else if(tokens[0] == "TIME" || tokens[0] == "time")
		{
			if (this->list_users[this->_list_connected_user[listnum]] == NULL)
				this->time_cmd(tmpuser, this->_list_connected_user[listnum]);
			else
			 	return reply_msg(ERR_NOTREGISTERED, "TIME :You have not registered.", tmpuser);
		}
		else if(tokens[0] == "NICK" || tokens[0] == "nick")
		{
			tmpuser = this->list_users[this->_list_connected_user[listnum]];
			this->nick_cmd(tokens, tmpuser);
		}
		else if(tokens[0] == "JOIN" || tokens[0] == "join")
		{
			this->join_cmd(tokens, tmpuser);
		}
		else if(tokens[0] == "MOTD" || tokens[0] == "motd")
		{
			this->motd_cmmd(listnum);
		}


		std::cout << std::endl << "Received:  " << recived << std::endl;
		send(this->_list_connected_user[listnum], recived.c_str(), recived.length(), 0);
		send(this->_list_connected_user[listnum], (char *)"\n", strlen((char *)"\n"), 0);
		// sock_puts(this->_list_connected_user[listnum], buffer);
		// sock_puts(this->_list_connected_user[listnum], (char *)"\n");
		std::cout << "Responded: " << recived << std::endl;
	}
}

void Server::read_socks()
{
	if(FD_ISSET(this->listening_socket, &this->reads))
		this->handle_new_connection();
	for(size_t listnum = 0; listnum < FD_SETSIZE; listnum++)
	{
		if(FD_ISSET(this->_list_connected_user[listnum], &this->reads))
			deal_with_data(listnum);
	}
}

void Server::setPassword(std::string psswd) { this->password = psswd; }
std::string	Server::getPassword() const { return this->password; };

