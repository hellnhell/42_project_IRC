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

class Server;
class Channel;

typedef struct s_user_modes //esto copiado de freenode
{
	bool a;			
	bool i;			
	bool w;			
	bool r;			
	bool o;			
	bool co;
}		t_user_modes;

#define i_MODE = 4;

class User
{
	private:
		int					fd;
		bool				connection_pswd;
		bool				check_user;
		bool				check_nick;
		bool				ping_on;
		std::string			user;
		std::string			realName;
		std::string			nick;
		std::string			nickMask;
		std::string			password;
		t_user_modes 		modes;
		struct sockaddr_in	address;

		std::vector<std::string>		reply;
		std::vector<Channel*>			channels;

		uint64_t					t_zero;
		uint64_t					t_ping;
		std::string					ping;


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
		
		const std::string	getNickMask() const;
		void	setNickMask(std::string _nickMask);

		const std::string	getPass() const;
		void	setPass(std::string _nick);

		const std::string	getModes() const;
		void	setModes(int modes);

		bool		getConnectionPswd() const;
		void		setConnectionPswd(bool cp);

		const bool		&getCheckedUser() const;
		void			setCheckedUser(bool cu);

        const bool		&getCheckedNick() const;
		void			setCheckedNick(bool nu);

		const bool		&getPingOn() const;
		void			setPingOn(bool po);

		const std::string 	&getPing() const;
		void				setPing(std::string p);

		std::string	getReply();
		void		setReply(std::string const &msg);

		std::string getClientAdd() const;

		void		joinChannel(Channel *channel);
		void		leaveChannel(Channel *channel);

		std::vector<Channel*> const		&getChannels() { return this->channels; }

		const uint64_t		&getTimeZero() const;
		void				setTimeZero(uint64_t const & time_zero);
		
		const uint64_t		&getTimePing() const;
		void				setTimePing(uint64_t const & time_ping);

};

#endif
