#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string.h>
# include <string>
# include <bitset>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <vector>

# include "channel.hpp"

class Channel;

typedef struct s_user_modes //esto copiado de freenode
{
	bool c;			//		blocks private messages from users who dont sare a common channel
	bool d;			//		deaf, makes you not recieve any notice or message
	bool g;			//		caller-id, ignores priveate messages from unkown users, pero notifica que alguien intenta mensajearte, pudiendo aceptarlos con "/accept"
	bool i;			//bit 3, 8	invisible, hides you from global WHO by regular users
	bool x;			//		host-cloacking, reemplaza tu hostname con una hash
	bool z;			//		secure messages only, solo acepta mensajes de usuarios conectandose a traves de TLS
	bool B;			//		bot mode, Marks you as a bot
	bool D;			//		privdeaf, no puedes recibir mensajes privados
	bool I;			//		hidden whois, hides WHOIS channel list from non-staff
	bool L;			//		disable forwarding, previene channel forwards from affecting you, si te han baneao te jodes y no te lo saltas
	bool R;			//		block unidentified, ignores private messages from users not identified with services
	bool S;			//		strip color, strips color/formating messages de mensajes privados
	bool W;			//bit 2, 2	see wallops, te suscribe a wallosps messages cosa de frenode
	bool Z;			//		connected securely, cuando te contectas por SSL/TLS
}		t_user_modes;

#define i_MODE = 4;

class User
{
	private:
		int					fd;
		bool				connection_pswd;
		std::string			user;
		std::string			realName;
		std::string			nick;
		std::string			password;
		t_user_modes 		modes;
		struct sockaddr_in	address;

		std::vector<std::string>		reply;

		std::vector<Channel*>		channels;

		User();
		User(const User &other);

	public:
		User(int &_fd, struct sockaddr_in const &client_addrs);
		~User();
		User &operator=(const User &other);

		int getFD();

		const std::string	getUser() const;
		void	setUser(std::string _user);

		const std::string	getRealName() const;
		void	setRealName(std::string _nick);

		const std::string	getNick() const;
		void	setNick(std::string _nick);

		const std::string	getPass() const;
		void	setPass(std::string _nick);

		const std::string	getModes() const;
		void	setModes(int modes);

		bool		getConnectionPswd() const;
		void		setConnectionPswd(bool cp);

		std::string	getReply();
		void		setReply(std::string const &msg);

		std::string getClientAdd() const;

		void		joinChannel(Channel *channel);
		void		leaveChannel(Channel *channel);

		std::vector<Channel*> const		&getChannels() { return this->channels; }

};

#endif
