/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:13:31 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/11 15:28:16 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "../utils.hpp"

void    Server::motdCmmd(int const & fd)
{
	User *usr = this->list_users[this->_list_connected_user[fd]];

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

	replyMsg(RPL_WELCOME, " : Welcome to the ft_irc Network " + usr->getNick() + "!" + usr->getUser() + "@"+ this->list_users[this->_list_connected_user[fd]]->getClientAdd() , usr); //
	replyMsg(RPL_YOURHOST, " : Your host is ft_irc.com, running version v:0.01",  this->list_users[this->_list_connected_user[fd]]);
	replyMsg(RPL_CREATE, " : This server is connstantly under construction", this->list_users[this->_list_connected_user[fd]]);
	replyMsg(RPL_MYINFO, " : ft_irc v:0.41 io iobl", this->list_users[this->_list_connected_user[fd]]);
	replyMsg(RPL_MOTDSTART, " : ft_irc.com M O T D enjoy " , this->list_users[this->_list_connected_user[fd]]);
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
	replyMsg(RPL_ENDOFMOTD, " : End of message of the day", this->list_users[this->_list_connected_user[fd]]);
}

