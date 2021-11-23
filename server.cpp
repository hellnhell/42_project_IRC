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

Server::Server(int port)
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
	this->cmd_list.push_back("USER");
	this->cmd_list.push_back("NICK");
	this->cmd_list.push_back("EXIT");

}

Server::~Server()
{
	close( this->listening_socket );
	FD_ZERO( &this->reads );
	memset( this->_list_connected_user, 0 , sizeof( this->_list_connected_user ) );
	memset( (char *) &this->server_address, 0 , sizeof( this->server_address ) );
	std::cout << "Destructor Server\n";
}

void Server::setPassword(std::string psswd) { this->password = psswd; }
std::string	Server::getPassword() const { return this->password; };


//SERVER CONST

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
	struct sockaddr_in client_address;

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
			this->list_users[connection] = new User(connection, client_address);
			if (this->getPassword().empty())
				std::cout << "Password needed or not" << std::endl; // gestionar cositas
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

std::vector<std::string>   Server::parse_message(std::string buffer)
{
    std::vector<std::string>    tok_tmp;
    std::vector<std::string>    tokens;
    size_t                      pos;
	std::string                 tmps;    
    std::stringstream           s(buffer);
    std::istringstream          ss;
	
    if (buffer.empty())
        tokens.push_back("");
	//Puede que haya que gestionar q haya más de un espacio entre cmds
    if (((pos = buffer.find('\n')) != std::string::npos) || ((pos = buffer.find('\r')) != std::string::npos))
        buffer.erase(pos, buffer.size() - pos);
    while(getline(s, tmps, ':'))
        tok_tmp.push_back(tmps);
    if(buffer[0] == ':')
	{
        ss.str(tok_tmp[1]);
        while(ss >> tmps)
            tokens.push_back(tmps);
        tokens.erase(tokens.begin());
		if (tokens.size() > 1)
        	tokens.push_back(tok_tmp[2]);
    }
    else
    {
        ss.str(tok_tmp[0]);
        while(ss >> tmps)
            tokens.push_back(tmps);
		if (tokens.size() > 0)
        	tokens.push_back(tok_tmp[1]);
    }
	//El número de parámetros t
	return tokens;
}

void Server::deal_with_data(int listnum)
{
	char buffer[512]; //N: 512 y sin lios -> IIRC at least znc crashes, other clients like xchat start having rendering issues and some (I think irssi) completely disregard content after the 512th byte

	std::string		buff_input;
	ssize_t			verify;
	std::string 	recived;
	std::vector<std::string> tokens;

	std::cout << "read_socks:" << std::endl;
	while ((verify = recv(this->_list_connected_user[listnum], buffer, 512, 0)) > 0)
	{
		buffer[verify] = 0;
		recived += buffer;
	}
	if(recived.length() <= 0)	//N: si es menor pierde conexion, si no hace cosas
	{
		//delete user?
		delete (this->list_users[this->_list_connected_user[listnum]]);
		std::cout << std::endl << "Connection lost fd -> " << this->_list_connected_user[listnum] << " slot -> " <<  listnum << std::endl;
		close(this->_list_connected_user[listnum]);
		this->_list_connected_user[listnum] = 0;
	}
	else
	{
		//USER <user> <mode> <unused> <realname>
		//USER guest 0 * :Ronnie Reagan
			//el modo debe ser numerico una bitmask, con dos dos bits, bit 2 modo 'w' bit 3 modo 'i'
			//el realname puede contener espacios
			//Hacer pruebas con los tokens y gestión errores;
		tokens = parse_message(recived);
		if (tokens[0].empty())
			return;
		std::transform(tokens[0].begin(), tokens[0].end(),tokens[0].begin(), ::toupper);
		if ((std::find(cmd_list.begin(), cmd_list.end(), tokens[0]) == cmd_list.end()))
		{
			perror("Unknow command error!"); //Hay q hacer gestion de errores
			exit(EXIT_FAILURE);
		} 
		if(tokens[0] == "USER" || tokens[0] == "user")
		{
			User *tmpuser;
			std::cout << "hacecosas" << std::endl;
			tmpuser = this->list_users[this->_list_connected_user[listnum]];
			this->user_cmd(tokens, tmpuser);
			// tmpuser->setNick(tokens[1]);
			//tmpuser->set_modes(std::stoi(tokens[2])); //gestionar si no es int
			// tmpuser->setUser(tokens[4]);
			// std::cout << std::endl << "Nick:  " << tmpuser->getNick() << "\nmodes:" << tmpuser->get_modes() << "\nUser: " << tmpuser->get_user() << std::endl;
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
	std::cout << "Read_socks:" << std::endl;
	if(FD_ISSET(this->listening_socket, &this->reads))
		this->handle_new_connection();
	for(size_t listnum = 0; listnum < 5; listnum++)
	{
		if(FD_ISSET(this->_list_connected_user[listnum], &this->reads))
			deal_with_data(listnum);
	}
}

