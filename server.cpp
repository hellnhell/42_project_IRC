#include "server.hpp"

# define PORT 6667

static void setnonblocking(int sock)
{
	int opts;

	// std::cout << "set_non_blocking:" << std::endl;
	opts = fcntl(sock, F_GETFL); //Return (as the function result) the file access mode and the file status flags
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

Server::Server()
{
	std::cout << "Server Constructor:" << std::endl;
	//creo socket
	int reuse_addr = 1;
	FD_ZERO(&this->reads);
	this->highsock = 0;
	this->listening_socket = 0;
	this->listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(this->listening_socket < 0)
	{
		perror("Socket");
		exit(EXIT_FAILURE);
	}
	//bzero usuarios


	//establezco opciones de socket
	setnonblocking(this->listening_socket);
	memset(this->_list_connected_user, 0 , sizeof( this->_list_connected_user));

	//aqui pilla el puerto de argv pero test con gon 6667 y lo bindea
	memset((char *)&this->server_address, 0, sizeof(this->server_address));
	this->server_address.sin_family = AF_INET;
	this->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	this->server_address.sin_port = htons(PORT);
	// std::cout << "me bindeo al listening socket:" << std::endl;
	//Permite que te puedas conectar a la red cada vez que ejecutes sin q aparezca q está en uso
	setsockopt(this->listening_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int));
	if(bind(this->listening_socket, (struct sockaddr *) &this->server_address, sizeof(this->server_address)) == -1 )
	{
		perror("bind");
		close(this->listening_socket);
		exit(EXIT_FAILURE);
	}

	//poseso
	if(listen(this->listening_socket, 5) == -1)
	{
		perror("listening");
		close(this->listening_socket);
		exit(EXIT_FAILURE);
	}
	this->highsock = this->listening_socket;
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

	// std::cout << "build_select_list:" << std::endl;
	FD_ZERO(&this->reads);
	FD_SET(this->listening_socket, &this->reads);

	for (listnum = 0; listnum < FD_SETSIZE; listnum++) {
		if (this->_list_connected_user[listnum] != 0) {
			FD_SET(this->_list_connected_user[listnum],&this->reads);
			if (this->_list_connected_user[listnum] > this->highsock)
				this->highsock = this->_list_connected_user[listnum];
		}
	}
}

int Server::get_read_socks()
{
	int readsocks;

	this->timeout.tv_sec = 1;
	this->timeout.tv_usec = 0;
	readsocks = select( (this->highsock + 1 ), &this->reads, (fd_set *) 0, (fd_set *) 0 , &this->timeout);
	return readsocks;
}

void Server::handle_new_connection()
{
	int connection;

	// std::cout << "handle_new_connection:" << std::endl;
	connection = accept(this->listening_socket, NULL, NULL);
	if (connection < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	setnonblocking(connection);
	for (size_t listnum = 0; (listnum < 5) && (connection != -1); listnum++)
	{
		if(this->_list_connected_user[listnum] == 0)
		{
			printf("Connection accepted: fd=%d Slot=%lu\n", connection, listnum);
			this->_list_connected_user[listnum] = connection;
			connection = -1;
		}
	}
	if (connection != -1) {
		printf("\n No room left for new client.\n");
		close(connection);
	}
}

// ES LO MISMO Q EL SEND PERO DEJAMOS LA FX X SI NOS DA X METER MÄS COSAS
// static void sock_puts(int sockfd, char *str)
// {
// 	std::cout << "Sockputs:" << std::endl;
// 	send(sockfd, str, strlen(str), 0);
// }


void Server::deal_with_data(int listnum)
{
	char buffer[80];
	char *cur_char;

	std::cout << "Read_socks:" << std::endl;
	if (recv(this->_list_connected_user[listnum], buffer, 80, 0) == -1)
	{
		std::cout << std::endl << "Connection lost fd -> " << this->_list_connected_user[listnum] << " slot -> " <<  listnum << std::endl;
		close(this->_list_connected_user[listnum]);
		this->_list_connected_user[listnum] = 0;
	}
	else
	{
		//aqui parseo
		std::cout << std::endl << "Received:  " << buffer << std::endl;
		cur_char = buffer;
		while(*cur_char)
		{
			*cur_char = toupper(*cur_char);
			cur_char++;
		}
		send(this->_list_connected_user[listnum], buffer, strlen(buffer), 0);
		send(this->_list_connected_user[listnum], (char *)"\n", strlen((char *)"\n"), 0);
		// sock_puts(this->_list_connected_user[listnum], buffer);
		// sock_puts(this->_list_connected_user[listnum], (char *)"\n");
		std::cout << "Responded: " << buffer << std::endl;
	}
}

void Server::read_socks()
{
	std::cout << "Read_socks:" << std::endl;
	if(FD_ISSET(this->listening_socket, &this->reads))
		this->handle_new_connection();
	for(size_t listnum = 0; listnum < 5; listnum++)
	{
		if(FD_ISSET(this->_list_connected_user[listnum], &this->reads))
			deal_with_data(listnum);
	}
}
