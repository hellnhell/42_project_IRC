/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping-pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:37:45 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/20 12:35:02 by javrodri         ###   ########.fr       */
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
		usr->setPingOn(false);
		usr->setTimePing(120000);
		actionDisplay("Ping introduced", "", usr);
		std::string msg = "396 " + usr->getNick() + " 127.0.0.1 :is now your displayed host\n";
		send(usr->getFD(), msg.c_str(), msg.size(), 0);
		//motdCmmd(usr->getFD());
		send(usr->getFD(), "396 ---WELCOME---\n", 18, 0);
	}
	else
	{
		replyMsg("ERROR :Wrong reply, sorry! ", " [Connection aborted]", usr);
		deleteUser(usr);
	}
}
