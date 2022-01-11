/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:52 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/11 15:29:17 by nazurmen         ###   ########.fr       */
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
	this->flag = 0;
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
	this->op_password = "duck123";
}

Server::~Server()
{
	close(this->listening_socket);
	std::map<int, User *>::iterator it = this-> list_users.begin();
	while (it != this->list_users.end() )
	{
		std::cout << "\r";
		actionDisplay("Connection closed", "", this->list_users[it->first] );
        delete it->second;
		close(it->first);
		FD_CLR(it->first, &this->reads);
		it++;
	}
	this->list_users.clear();
	close(this->listening_socket);
	FD_ZERO(&this->reads);
	memset(this->_list_connected_user, 0 , sizeof( this->_list_connected_user));
	memset((char *) &this->server_address, 0 , sizeof( this->server_address));
	std::cout << "Destructor Server\n";
}

void Server::buildSelectList()
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

int Server::getReadSocks()
{
	this->timeout.tv_sec = 1;
	this->timeout.tv_usec = 0;
	return select((this->highsock + 1 ), &this->reads, (fd_set *) 0, (fd_set *) 0 , &this->timeout);
}

void Server::handleNewConnection()
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
			std::cout << "New connection: " << connection << "\nclient address: " << this->list_users[connection]->getClientAdd() << std::endl;
			if (this->getPassword().empty())
				this->list_users[connection]->setConnectionPswd(1);
			else
				this->list_users[connection]->setConnectionPswd(0);
			this->list_users[this->_list_connected_user[listnum]]->setTimeZero(getTime());
			std::cout << "\r";
			// printf("Connection accepted: fd=%d Slot=%lu\n", connection, listnum);
			actionDisplay("Connection accepted", "", list_users[connection]);
			connection = -1;
		}
	}
	if (connection != -1) {
		printf("\n No room left for new client.\n");
		close(connection);
	}
}

void Server::dealWithData(int listnum)
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
		deleteUser(this->list_users[this->_list_connected_user[listnum]]);
		// delete (this->list_users[this->_list_connected_user[listnum]]);
		// // std::cout << std::endl << "Connection lost fd -> " << this->_list_connected_user[listnum] << " slot -> " <<  listnum << std::endl;
		// close(this->_list_connected_user[listnum]);
		// this->_list_connected_user[listnum] = 0;
	}
	else
	{
		User *tmpuser = this->list_users[this->_list_connected_user[listnum]];
		tokens = parseMessage(recived);
		if (tokens[0].empty())
			return;
		actionDisplay("Attend client", " CMD:" + tokens[0], tmpuser);
		parseCommands(tokens, tmpuser, listnum);
		std::cout << std::endl << "Received:  " << recived << std::endl;
		send(this->_list_connected_user[listnum], recived.c_str(), recived.length(), 0);
		send(this->_list_connected_user[listnum], (char *)"\n", strlen((char *)"\n"), 0);
	}
}

void Server::readSocks()
{
	if(FD_ISSET(this->listening_socket, &this->reads))
		this->handleNewConnection();
	for(size_t listnum = 0; listnum < FD_SETSIZE; listnum++)
	{
		if(FD_ISSET(this->_list_connected_user[listnum], &this->reads))
		{
			this->list_users[this->_list_connected_user[listnum]]->setTimeZero(getTime());
			std::cout << "\r";
			dealWithData(listnum);
		}
	}
}


//SETTERs-GETTERs

void Server::setPassword(std::string psswd) { this->password = psswd; }
std::string	Server::getPassword() const { return this->password; };

std::map<int, User *> const& Server::getUsers() const { return this->list_users; }
std::vector<Channel *> const& Server::getChannels() const { return this->channels; }


void Server::removeChannel(Channel *channel)
{
	std::vector<Channel *>::iterator it;
	it = std::find(this->channels.begin(), this->channels.end(), channel);
	if (it != this->channels.end())
		this->channels.erase(it);
}

void	Server::deleteUser(User *usr) // REVISAR
{
	this->users_on.remove(usr);
	for (int i = 0; i < FD_SETSIZE; i++)
		if( this->_list_connected_user[i] == usr->getFD())
			this->_list_connected_user[i] = 0;
	close (usr->getFD());
	this->list_users.erase(usr->getFD());
	actionDisplay("Removed user", usr->getNick(), usr);
	//Remove el resto de cosas q no se q son
	delete usr;
}

//Channel *Server::getChannel(std::string name) const
Channel			*Server::getChannel(std::string name) const
{
	if (this->channels.size() == 0)
		return NULL;
	std::vector<Channel *>::const_iterator it;
	it = std::find_if(this->channels.begin(), this->channels.end(), [&name](Channel *c) { return c->getName() == name; });
	return *it;
}
