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

User::User(int &_fd) : fd(_fd)
{
	std::cout << "User created with fd: " << this->fd << std::endl;
	this->user = "";
	this->nick = "";
	this->password = "";

	user_modes_init(&this->modes);
}

User::~User()
{
	std::cout << "User destroyed with fd: " << this->fd << std::endl;
}


//getters setters
std::string User::get_user() {return (this->user);}

void User::set_user(std::string _user)
{
	this->user = _user;
}

std::string User::get_nick() {return (this->nick);}

void User::set_nick(std::string _nick)
{
	this->nick = _nick;
}

std::string User::get_pass() {return (this->password);}

void User::set_pass(std::string _pass)
{
	this->password = _pass;
}

std::string User::get_modes()
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

void User::set_modes(int modes)
{
	std::bitset<16> modesbit(modes);

//	modesbit = std::BitSet.valueOf(modes);
	if(modesbit.test(3))
		this->modes.i = 1;
	if(modesbit.test(2))
		this->modes.W = 1;
	this->modes.Z = 1;

}
