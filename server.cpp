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

	// std::cout << "handle_new_connection:" << std::endl;
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
			printf("Connection accepted: fd=%d Slot=%lu\n", connection, listnum);
			this->_list_connected_user[listnum] = connection;
			this->list_users[connection] = new User(connection);
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
	char buffer[512]; //N: 512 y sin lios -> IIRC at least znc crashes, other clients like xchat start having rendering issues and some (I think irssi) completely disregard content after the 512th byte

//	char *cur_char;
	std::string buff_input;
	ssize_t verify;
	std::string received;
	std::vector<std::string> tokens;


	std::cout << "read_socks:" << std::endl;
	while ((verify = recv(this->_list_connected_user[listnum], buffer, 512, 0)) > 0)
	{
		buffer[verify] = 0;
		received += buffer;
	}
	if(received.length() <= 0)	//N: si es menor pierde conexion, si no hace cosas
	{


		//delete user?
		delete (this->list_users[this->_list_connected_user[listnum]]);
		//end delete user?


		std::cout << std::endl << "Connection lost fd -> " << this->_list_connected_user[listnum] << " slot -> " <<  listnum << std::endl;
		close(this->_list_connected_user[listnum]);
		this->_list_connected_user[listnum] = 0;

	}
//	if (verify <= 0) // Puede q sea solo menor pero hay q hacer pruebecitas //N: testado que <= XD
//		perror("buffer: ");
	else
	{
		//aqui parseo
		std::istringstream ss(received);
		std::string tmps;
		while(ss >> tmps)
			tokens.push_back(tmps);

		std::cout << std::endl << "token0:  " << tokens[0] << std::endl;

		if(tokens[0] == "USER")
		{
			std::cout << std::endl << "User:  " << tokens[1] << std::endl;
		}

		//USER <user> <mode> <unused> <realname>










		std::cout << std::endl << "Received:  " << received << std::endl;

		//old toupper
		/*//N: lo he pasao a string porque si
		cur_char = received;
		while(*cur_char)
		{
			*cur_char = toupper(*cur_char);
			cur_char++;
		}
		*/
		std::transform(received.begin(), received.end(), received.begin(), ::toupper);

		send(this->_list_connected_user[listnum], received.c_str(), received.length(), 0);
		send(this->_list_connected_user[listnum], (char *)"\n", strlen((char *)"\n"), 0);

		// sock_puts(this->_list_connected_user[listnum], buffer);
		// sock_puts(this->_list_connected_user[listnum], (char *)"\n");

		std::cout << "Responded: " << received << std::endl;
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
