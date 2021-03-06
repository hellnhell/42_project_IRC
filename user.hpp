/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:39:06 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/31 13:27:16 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

class User
{
	private:
		int					fd;
		bool				connection_pswd;
		bool				check_user;
		bool				check_nick;
		bool				check_regist;
		bool				ping_on;
		bool				away_on;
		bool				op_mode;
		std::string			user;
		std::string			realName;
		std::string			nick;
		std::string			nickMask;
		std::string			password;
		std::string			away;
		struct sockaddr_in	address;

		std::vector<std::string>	reply;
		std::vector<Channel*>		channels;

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
		void				setUser(std::string _user);

		const std::string	getRealName() const;
		void				setRealName(std::string _nick);

		const std::string	getNick() const;
		void				setNick(std::string _nick);

		const std::string	getNickMask() const;
		void				setNickMask(std::string _nickMask);

		const std::string	getPass() const;
		void				setPass(std::string _nick);
		bool				getConnectionPswd() const;
		void				setConnectionPswd(bool cp);

		bool				getOper() const;
		void				setOper(bool op);

		const bool			&getCheckedUser() const;
		void				setCheckedUser(bool cu);
		const bool			&getCheckedNick() const;
		void				setCheckedNick(bool nu);
		bool				&getCheckedRegist();

		const bool			&getPingOn() const;
		void				setPingOn(bool po);
		const std::string	&getPing() const;
		void				setPing(std::string p);
		const uint64_t		&getTimeZero() const;
		void				setTimeZero(uint64_t const & time_zero);
		const uint64_t		&getTimePing() const;
		void				setTimePing(uint64_t const & time_ping);

		const bool			&getAwayOn() const;
		void				setAwayOn(bool po);

		const std::string 	&getAway() const;
		void				setAway(std::string p);

		std::string			getReply();
		void				setReply(std::string const &msg);

		std::string			getClientAdd() const;

		int						joinChannel(Channel *channel);
		void					leaveChannel(Channel *channel);
		std::vector<Channel*>	&getChannels();

};

#endif
