#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string.h>
# include <string>

class User
{
	private:
		int		fd;
		std::string	user;
		std::string	nick;
		std::string	password;
		User();
		User(const User &other);

	public:
		User(int &_fd);
		~User();
		User &operator=(const User &other);

		std::string	get_user();
		void	set_user(std::string _user);

		std::string	get_nick();
		void	set_nick(std::string _nick);

		std::string	get_pass();
		void	set_pass(std::string _nick);

};

#endif
