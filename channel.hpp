#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include "user.hpp"

//types: 0 -> # disponible en el IRC network
//       1 -> & local server
//       2 -> + modeless channel
//       3 -> ! timestamped channel en no timestamped network

typedef struct s_modes
{
		std::string					O; // give "channel creator" status;
		std::vector<std::string>	o; // give/take channel operator privilege;
		std::vector<std::string>	v; // give/take the voice privilege;

		bool a; // toggle the anonymous channel flag; &puede ser toggleado por op. !puede settearse pero no unset por el channel creator, no disponible en #+.
		bool i; // toggle the invite-only channel flag; mask matches invite list o invited by op
		bool m; // toggle the moderated channel; solo mv
		bool n; // toggle the no messages to channel from clients on theoutside;
		bool q; // toggle the quiet channel flag;
		bool p; // toggle the private channel flag;
		bool s; // toggle the secret channel flag;
		bool r; // toggle the server reop channel flag;
		bool t; // toggle the topic settable by channel operator only flag;

		bool k; // set/remove the channel key (password);
		bool l; // set/remove the user limit to channel;

		bool b; // set/remove ban mask to keep users out;
		bool e; // set/remove an exception mask to override a ban mask;
		bool I; // set/remove an invitation mask to automatically override the invite-only flag;
} t_modes;

class Channel
{
	private:
		std::vector<User *>	_users;
		std::vector<User *>	_ops;
		std::vector<User *>	_bans;
		std::string			_name;
		std::string			_topic;
		std::string			_password;
		int					_type;
		t_modes				_modes;
		unsigned int 		_max_users;
		unsigned int 		_current_users;

		//std::string			_password; // TODO

		Channel(Channel const &src);
		Channel &operator=(Channel const &rhs);
	public:
		Channel(User *creator, const std::string &name);
		Channel(User *creator, const std::string &name, unsigned int max_users);
		Channel(User *creator, const std::string &name, const std::string &topic);
		Channel(User *creator, const std::string &name, const std::string &topic, unsigned int max_users);
		~Channel();

		void					setName(const std::string &name);
		void					setTopic(const std::string &topic);
		void					setMaxUsers(unsigned int max_users);

		void					joinUser(User *user);
		void					disconnectUser(User *user);
		void					kickUser(User *user);
		void					banUser(User *user);
		void					unbanUser(User *user);
		void					opUser(User *user);
		void					deopUser(User *user);

		std::string				getName() const;
		std::string				getTopic() const;
		unsigned int			getMaxUsers() const;
		unsigned int			getCurrentUsers() const;
		std::vector<User *>		getUsers() const;
		std::vector<User *>		getOps() const;
		std::vector<User *>		getBans() const;




};

#endif // CHANNEL_HPP