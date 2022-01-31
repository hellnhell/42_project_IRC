/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:47 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/31 13:48:21 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include <list>
# include "user.hpp"
# include "server.hpp"

class User;
class Server;

typedef std::vector<std::string>::iterator	it_str_list_chnl;
typedef std::vector<User *>::iterator			it_usr_list_chnl;

typedef struct s_modes
{
		std::string		k;
		std::string		O; 
		bool 			o; 
		bool 			t; 
		bool 			b; 
		bool 			n;
} t_modes;

class Channel
{
	private:
		Server *			_server;
		std::vector<User *>	_users;
		std::vector<User *>	_ops;
		std::vector<User *>	_bans;
		std::string			_name;
		std::string			_topic;

		int					_type;
		t_modes				_modes;
		unsigned int 		_max_users;
		unsigned int 		_current_users;

		Channel(Channel const &src);
	public:
		Channel(Server *server, User *creator, const std::string &name);
		Channel(Server *server, User *creator, const std::string &name, unsigned int max_users);
		Channel(Server *server, User *creator, const std::string &name, const std::string &topic);
		Channel(Server *server, User *creator, const std::string &name, const std::string &topic, unsigned int max_users);
		~Channel();

		Channel &operator=(Channel const &rhs);

		void					setName(const std::string &name);
		void					setTopic(const std::string &topic);
		void					setMaxUsers(unsigned int max_users);
		void					setMode(char mode, bool value);
		void					setKey(std::string key);

		void					joinUser(User *user);
		void					disconnectUser(User *user);
		void					kickUser(User *user);
		int						banUser(User *user, User *banned);
		void					unbanUser(User *user);
		int						opUser(User *user);
		void					deopUser(User *user);

		std::string				getName() const;
		std::string				getTopic() const;
		unsigned int			getMaxUsers() const;
		unsigned int			getCurrentUsers() const;
		std::string 			getKey() const;
		std::vector<User *>		const &getUsers() const;
		std::vector<User *>		const &getOps() const;
		std::vector<User *>		const &getBans() const;
		User *					getNick(std::string userName) const;
		User *					getBan(std::string userName) const;

		std::string				const getModes() const;
		bool					const getMode(char mode) const;
		bool					const isOperator(User *usr) const;
};

#endif
