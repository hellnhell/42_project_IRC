/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping-pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:37:45 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/20 13:15:56 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"


void    Server::checkPing()
{
	User* usr;
	std::string ping[] = {"5@·Run/mtf/run/@·5", "222@++222@++", "5#55Read/more5#55", "5.-You/would/have/studied.-5"};
	std::string pingpass = ping[rand() % 4];
	std::map<int, User*>::iterator it = this->list_users.begin();

	while (it != this->list_users.end())
	{
		usr = this->list_users[it->first];
		if ((getTime() - usr->getTimeZero()) > usr->getTimePing())
		{
			if ((usr->getCheckedRegist() == false || usr->getPingOn() == true)
			 && (getTime() - usr->getTimeZero() > usr->getTimePing() + 100000))
			{
				if (usr->getPingOn() && !usr->getCheckedRegist())
					replyMsg("ERROR :Registration timeout ", " [Connection aborted]", usr);
				else
					replyMsg("ERROR :Ping timeout ", " [Connection aborted]", usr);
		  		actionDisplay("Connection lost", "", usr);
				this->deleteUser(usr);
				return ;
			}
			else if ((usr->getPingOn() == false))
			{
				usr->setPingOn(true);
				usr->setPing(pingpass);
				pingpass = usr->getPing() + "\n";
				send(usr->getFD(),"PING ", strlen("PING "), 0);
				send(usr->getFD(),pingpass.c_str(), pingpass.length(), 0);
				actionDisplay("Pinged", "", usr);
			}
		}
		it++;
	}
}

void    Server::pongCmmd(std::vector<std::string> const &tokens, User *usr)
{
	if (tokens.size() > 1 && tokens[1] == usr->getPing())
	{
		if (usr->getTimePing() == 0)
			this->initMsg( usr->getFD() );
		usr->setPingOn(false);
		usr->setTimePing(120000);
		actionDisplay("Ping introduced", "", usr);
		std::string msg = "396 " + usr->getNick() + " 127.0.0.1 :is now your displayed host\n";
		send(usr->getFD(), msg.c_str(), msg.size(), 0);
		send(usr->getFD(), "396 ---WELCOME---\n", 18, 0);
	}
	else
	{
		replyMsg("ERROR :Wrong reply, sorry! ", " [Connection aborted]", usr);
		deleteUser(usr);
	}
}


void    Server::initMsg(int const & fd)
{
	User *usr = this->list_users[fd];

	std::string s1 = "  .'(     /`-.     )-.       /(,-.  .'(  .-,.-.,-.    )).-.       .'(  ";
	std::string s2 = "  (  )  ,' _  )  ,' ,-,_)    ,' _   ) (  ) ) ,, ,. (  ,' ,-,_)  ,') (  ) ";
	std::string s3 = "  ) (  (  '-' ( (  .   _    (  '-' (  ) (  )( |(  )/ (  .   _  (  '-' (  ";
	std::string s4 = "  (  )  ) ,_ .'  ) '..' )    )  _   ) (  )    ( )     ) '..' )  ) .-.  ) ";
	std::string s5 = "   ) ) (  ' ) ) (  ,   (    (  '-' /   ) )    ( (    (  ,   (  (  ,  ) ) ";
	std::string s6 = "    )/  )/   )/  )/'._.'     )/._.'     )/     )/     )/'._.'   )/    )/ ";
	std::string s7 = "                                                                          ";


	std::string challenge[] = {RED " Welcome: And, when you want something, all the universe conspires in helping you to achieve it",
								YELLOW " Welcome: It's the possibility of having a dream come true that makes life interesting",
								BLUE " Welcome: One is loved because one is loved. No reason is needed for loving.",
								PINK " Welcome: When we love, we always strive to become better than we are. When we strive to become better than we are, everything around us becomes better too",
								CIAN " Welcome: So, I love you because the entire universe conspired to help me find you"};
	std::string wlc = challenge[rand() % 5] +  WHITE;

	replyMsg(RPL_WELCOME, " : Welcome to the ft_irc Network " + usr->getNick() + "!" + usr->getUser() + "@"+ this->list_users[fd]->getClientAdd() , usr); //
	replyMsg(RPL_YOURHOST, " : Your host is ft_irc.com, running version v:0.01",  this->list_users[fd]);
	replyMsg(RPL_CREATE, " : This server is connstantly under construction", this->list_users[fd]);
	replyMsg(RPL_MYINFO, " : ft_irc v:0.41 io iobl", this->list_users[fd]);
	replyMsg(RPL_MOTDSTART, " : ft_irc.com M O T D enjoy " , this->list_users[fd]);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_MOTD, " :" GREEN  + s1 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s2 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s3 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s4 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s5 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s6 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s7 + WHITE, usr);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_MOTD, " :" + wlc, usr);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_ENDOFMOTD, " : End of message of the day", this->list_users[fd]);
}

