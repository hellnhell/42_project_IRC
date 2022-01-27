/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:52 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/27 17:39:15 by emartin-         ###   ########.fr       */
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

Server::Server(int port)
{
	std::cout << "Server Constructor:" << std::endl;
	int reuse_addr = 1;
	FD_ZERO(&this->reads);
	FD_ZERO(&this->writes);
	this->highsock = 0;
	// this->flag = 0;
	this->buffCommand = "";
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
	this->server_address.sin_port = htons(port);
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
			FD_SET(this->_list_connected_user[listnum], &this->reads);
			if (this->_list_connected_user[listnum] > this->highsock)
				this->highsock = this->_list_connected_user[listnum];
		}
	}
	if(buff_users.empty())
		return ;
	std::vector<User *>::iterator it;
	for(it = this->buff_users.begin(); it != buff_users.end(); ++it)
	{
		FD_SET((*it)->getFD(), &this->writes);//cambiar fd
	}
}

int Server::getReadSocks()
{
// std::cout << "getReadSocks " << std::endl;
// int temp;

	this->timeout.tv_sec = 1;
	this->timeout.tv_usec = 0;

	// temp = select((this->highsock + 1 ), &this->reads, &this->writes, (fd_set *) 0 , &this->timeout);
	// if(temp)
	// 	std::cout << ""
// std::cout << "fd read: " << *(int *)&this->reads << " fd write: " << *(int *)&this->writes << std::endl;
	return select((this->highsock + 1 ), &this->reads, &this->writes, (fd_set *) 0 , &this->timeout);
}

void Server::handleNewConnection()
{
	int connection;
	struct sockaddr_in client_address;

	//mio
	memset( (char *) &client_address, 0, sizeof(client_address));
	socklen_t sock_len = sizeof(client_address);
	connection = accept(this->listening_socket, (struct sockaddr *)&client_address, &sock_len);
	
	//endmio
//	connection = accept(this->listening_socket, NULL, NULL);
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
			this->list_users[connection] = new User(connection, client_address); // no pillamos sockaddress en ningun momento
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
	char 			buffer[513];
	std::string		buff_input;
	ssize_t			verify;
	std::string 	recived;
	std::string 	recived2;
	size_t			pos;
	std::vector<std::string> tokens;

	recived = this->buffCommand;

	while ((verify = recv(this->_list_connected_user[listnum], buffer, 512, 0)) > 0)
	{
		buffer[verify] = 0;
		recived += buffer;
	}
	std::cout << std::endl << "recived:  " << recived << std::endl;
	if(recived.length() <= 0)
	{
		actionDisplay("Connection lost", "", this->list_users[this->_list_connected_user[listnum]]);
		deleteUser(this->list_users[this->_list_connected_user[listnum]]);
	}
	else
	{
		while(recived.length())
		{
			if((pos = recived.find('\n')) != std::string::npos)
			{
				recived2 = recived.substr(0, pos + 1);
				recived.erase(0, pos + 1);

				
				if(recived2.length() > 510)
				{
				 	recived2 = recived2.substr(0, 510);
				}
				if(recived2[0] != '\r' && recived2[0] != '\n')
				{
					User *tmpuser = this->list_users[this->_list_connected_user[listnum]];
					tokens = parseMessage(recived2);
					if (tokens[0].empty())
						return;
					actionDisplay("Attend client", " CMD:" + tokens[0], tmpuser);
					parseCommands(tokens, tmpuser, listnum);
					std::cout << std::endl << "Received:  " << recived2 << std::endl;
				}
				this->buffCommand.clear();
			}
			else
			{
				this->buffCommand += recived;
				recived.clear();
			}
		}

	}
}



void Server::sendBuffMsg(User *usr)
{
	int			diff;
	size_t		len;
	std::string	messages;
	std::vector<User *>::iterator it;

	diff = 0;
	len = 0;


	while ( ( messages = usr->getReply() ).size() != 0)
	{
		if ( messages.length() > 512 )
		{
			messages = messages.substr(0, 512);
			messages[510] = '\r';
			messages[511] = '\n';
		}
		len = send(usr->getFD(), messages.c_str(), messages.length(), 0);
		std::cout << BLUE << messages << WHITE << std::endl;
		diff = messages.length() - len;
		if ( diff > 0 )
		{
			usr->setReply(messages.substr(diff, messages.length()) );
			break ;
		}
	}
	if ( diff == 0 )
	{
		if ((it = std::find(buff_users.begin(), buff_users.end(), usr)) != buff_users.end())
			this->buff_users.erase(it);
	}
}

void Server::readSocks()
{
	std::vector<User *>::iterator it;
	for(it = this->buff_users.begin(); it != buff_users.end(); it++)
	{
		if(FD_ISSET((*it)->getFD(), &this->writes))
		{
			this->sendBuffMsg((*it));
			it--;
		}
	}
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

Channel *Server::getChannel(std::string name) const
{
	if (this->channels.size() == 0)
		return NULL;
	std::vector<Channel *>::const_iterator it;
	for(it = this->channels.begin(); it != this->channels.end(); it++)
	{
		if((*it)->getName() == name)
			return (*it);
	}
	return(NULL);
}

void Server::removeChannel(Channel *channel)
{
	std::vector<Channel *>::iterator it;
	it = std::find(this->channels.begin(), this->channels.end(), channel);
	if (it != this->channels.end())
		this->channels.erase(it);
}

void	Server::deleteUser(User *usr)
{
	actionDisplay("Removed user", usr->getNick(), usr);
	this->users_on.remove(usr);
	for (int i = 0; i < FD_SETSIZE; i++)
		if( this->_list_connected_user[i] == usr->getFD())
			this->_list_connected_user[i] = 0;
	this->list_users.erase(usr->getFD());
	close (usr->getFD());
	delete usr;
}
