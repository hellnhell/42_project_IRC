#include "user.hpp"


static void user_modes_init(t_user_modes *modes)
{
	modes->c = 0;
	modes->d = 0;
	modes->g = 0;
	modes->i = 0;
	modes->x = 0;
	modes->z = 0;
	modes->B = 0;
	modes->D = 0;
	modes->I = 0;
	modes->L = 0;
	modes->R = 0;
	modes->S = 0;
	modes->W = 0;
	modes->Z = 0;
}

User::User(int &_fd, struct sockaddr_in const &client_addr) : fd(_fd)
{
	this->user = "";
	this->nick = "";
	this->password = "";
	this->address = client_addr;
	std::cout << "User created with fd: " << this->fd  <<std::endl;
	user_modes_init(&this->modes);
}

User::~User()
{
	std::cout << "User destroyed with fd: " << this->fd << std::endl;
}


//getters setters
std::string User::getUser() { return (this->user); }

void User::setUser(std::string _user)
{
	this->user = _user;
}

std::string User::getNick() { return (this->nick); }

void User::setNick(std::string _nick)
{
	this->nick = _nick;
}

std::string User::getModes()
{
	std::string ret;

	if(this->modes.c)
		ret.append("c");
	if(this->modes.d)
		ret.append("d");
	if(this->modes.g)
		ret.append("g");
	if(this->modes.i)
		ret.append("i");
	if(this->modes.x)
		ret.append("x");
	if(this->modes.z)
		ret.append("z");
	if(this->modes.B)
		ret.append("B");
	if(this->modes.D)
		ret.append("D");
	if(this->modes.I)
		ret.append("I");
	if(this->modes.L)
		ret.append("L");
	if(this->modes.R)
		ret.append("R");
	if(this->modes.S)
		ret.append("S");
	if(this->modes.W)
		ret.append("W");
	if(this->modes.Z)
		ret.append("Z");
	return (ret);
}

void User::setModes(int modes)
{
	std::bitset<16> modesbit(modes);

//	modesbit = std::BitSet.valueOf(modes);
	if(modesbit.test(3))
		this->modes.i = 1;
	if(modesbit.test(2))
		this->modes.W = 1;
	this->modes.Z = 1;

}

bool	User::getConnectionPswd() const { return (this->connection_pswd); }
void	User::setConnectionPswd(bool cp) { this->connection_pswd = cp; }
