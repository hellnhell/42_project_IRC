#include "user.hpp"


static void user_modes_init(t_user_modes *modes)
{
	modes->a = 0;
	modes->i = 0;
	modes->w = 0;
	modes->r = 0;
	modes->o = 0;
	modes->co = 0;
}

User::User(int &_fd, struct sockaddr_in const &client_addr) : fd(_fd)
{
	// this->user = "";
	// this->nick = "";
	// this->password = "";
	// this->realName = "";
	this->t_ping = 20000;
	this->ping_on = false;
	this->address = client_addr;
	this->connection_pswd = 0;
	this->check_user = false;
	this->check_nick = false;
	std::cout << "User created with fd: " << this->fd  <<std::endl;
	user_modes_init(&this->modes);
	this->address = client_addr;
}

User::~User() {} //Puedes meter aquí el actionDispl


//getters setters

int User::getFD() {  return (this->fd); }

const std::string User::getUser() const { return (this->user); }
void User::setUser(std::string _user) {	this->user = _user; }

const std::string User::getRealName() const { return (this->realName); }
void User::setRealName(std::string _realName) {	this->realName = _realName; }

const std::string User::getNick() const { return (this->nick); }
void User::setNick(std::string _nick) {	this->nick = _nick; }

const std::string User::getNickMask() const { return (this->nickMask); }
void User::setNickMask(std::string _nickMask) {	this->nickMask = _nickMask; }

const std::string User::getModes() const
{
	std::string ret;

	if(this->modes.a)
		ret.append("a");
	if(this->modes.i)
		ret.append("i");
	if(this->modes.w)
		ret.append("w");
	if(this->modes.r)
		ret.append("r");
	if(this->modes.o)
		ret.append("o");
	if(this->modes.co)
		ret.append("co");
	return (ret);
}

void User::setModes(int modes)
{
	std::bitset<16> modesbit(modes);

//	modesbit = std::BitSet.valueOf(modes);
	if(modesbit.test(3))
		this->modes.i = 1;
	if(modesbit.test(2))
		this->modes.w = 1;
}

bool	User::getConnectionPswd() const { return (this->connection_pswd); }
void	User::setConnectionPswd(bool cp) { this->connection_pswd = cp; }


const bool	&User::getCheckedUser() const { return (this->check_user); }
void		User::setCheckedUser(bool cu) { this->check_user = cu; }

const bool	&User::getCheckedNick() const { return (this->check_nick); }
void		User::setCheckedNick(bool nu) { this->check_nick = nu; }

void 			User::setReply(std::string const &msg) { this->reply.push_back(msg); }
std::string 	User::getReply()
{
	std::string temp;
	if (this->reply.size())
	{
		temp = this->reply[0];
		this->reply.erase(this->reply.begin());
	}
	return temp;
}

std::string User::getClientAdd(  ) const 
{
	struct in_addr clientIP;
	clientIP = this->address.sin_addr;
	char ipStr[INET_ADDRSTRLEN];
	return inet_ntop(AF_INET, &clientIP, ipStr, INET_ADDRSTRLEN);
}

void User::joinChannel(Channel *channel)
{
	this->channels.push_back(channel);
}

void User::leaveChannel(Channel *channel)
{
	for (std::vector<Channel *>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
	{
		if (*it == channel)
		{
			this->channels.erase(it);
			return ;
		}
	}
}

const uint64_t		&User::getTimeZero() const { return this->t_zero; }
void				User::setTimeZero(uint64_t const & time_zero) { this->t_zero = time_zero; }

const uint64_t		&User::getTimePing() const { return this->t_ping; }
void				User::setTimePing(uint64_t const & time_ping) { this->t_ping = time_ping; }

const bool			&User::getPingOn() const { return (this->ping_on); }
void				User::setPingOn(bool po) { this->ping_on = po; }

const std::string 	&User::getPing() const { return this->ping; }
void				User::setPing(std::string p) { this->ping = p; };