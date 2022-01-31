/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping-pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:37:45 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/31 11:13:43 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void    Server::checkPing()
{
	User* usr
	;
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
				std::string aux =  ":ft_irc.com  409 :[Connection aborted]";
				send(usr->getFD(),  aux.c_str(), aux.length(), 0);
		  		actionDisplay("Connection lost", "", usr);
				this->deleteUser(usr);
				return ;
			}
			else if ((usr->getPingOn() == false))
			{
				usr->setPingOn(true);
				usr->setPing(pingpass);
				pingpass = usr->getPing() + "\n";
				send(usr->getFD(),"PING :", strlen("PING "), 0);
				send(usr->getFD(),pingpass.c_str(), pingpass.length(), 0);
				actionDisplay("Pinged", "", usr);
			}
		}
		it++;
	}
}

void    Server::pongCmmd(std::vector<std::string> const &tokens, User *usr)
{
	if (tokens.size() <= 1 || tokens[1] != usr->getPing())
	{
		std::string aux =  ":ft_irc.com  409 :[Connection aborted]";
		send(usr->getFD(),  aux.c_str(), aux.length(), 0);
		this->deleteUser(usr);
		return;
	}
	if (usr->getTimePing() == 0)
		this->initMsg(usr->getFD());
	usr->setPingOn(false);
	usr->setTimePing(120000);
	actionDisplay("Ping introduced", "", usr);
	return ;
}


void    Server::initMsg(int const & fd)
{
	User *usr = this->list_users[fd];

	std::string s1 = " .-./`)  .-------.           _______            _______   .-./`) ,---------.     _______     .---.  .---.  ";
	std::string s2 = " \\ .-.') |  _ _   \\        /   __  \\           \\  ____ \\  \\ .-.')\\          \\  /   __   \\    |   |  |_ _|  ";
	std::string s3 = " / `-' \\ | ( ' )  |       | ,_/  \\__)          | |   \\  | / `-' \\ `--.  ,---' | ,_/  \\ __)   |   |  ( ' )  ";
	std::string s4 = "  `-'`   |(_ o _) /       ,-./  )              | |____/ /  `-'`\"`    |   \\  ,-./   )         |   '-(_{;}_) ";
	std::string s5 = "  .---.  | (_,_).'   __  \\   '_ '`)            |   _ _ '.  .---.     :_ _: \\   '_  '`)       |      (_,_)  ";
	std::string s6 = "  |   |  |  |\\  \\  |    | > (_)  )  __         |  ( ' )  \\ |   |     (_I_)  >  (_)   )  __   | _ _--.   |  ";
	std::string s7 = "  |   |  |  | \\  `'    / (  .  .-'_/  )        | (_{;}_) | |   |    (_(=)_) (  .   .-'/   )  |( ' ) |   |  ";
	std::string s8 = "  |   |  |  |  \\     /     `-'`-'     /        |  (_,_)  / |   |     (_I_)   `-'`-'      /   (_{;}_)|   |  ";
	std::string s9 = "  '---'  ''-'   `'-'       `._____.'           /_______.'  '---'     '---'      `._____.'     (_,_) '---'  ";


	std::string s10 = "         Welcome: " + usr->getNick();

	replyMsg(RPL_WELCOME, " :Welcome to the ft_irc Network " + usr->getNick() + "!" + usr->getUser() + "@"+ this->list_users[fd]->getClientAdd() , usr); //
	replyMsg(RPL_YOURHOST, " :Your host is ft_irc.com, running version v:0.01",  this->list_users[fd]);
	replyMsg(RPL_CREATE, " :This server is connstantly under construction", this->list_users[fd]);
	replyMsg(RPL_MYINFO, " :ft_irc v:0.01 io iobl", this->list_users[fd]);
	replyMsg(RPL_MOTDSTART, " :ft_irc.com W E L C O M E enjoy " , this->list_users[fd]);
	replyMsg(RPL_MOTD, " :" , usr);
	replyMsg(RPL_MOTD, " :" GREEN + s1 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s2 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s3 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s4 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s5 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s6 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s7 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s8 + WHITE, usr);
	replyMsg(RPL_MOTD, " :" GREEN + s9 + WHITE, usr);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_MOTD, " :"  , usr);
	replyMsg(RPL_ENDOFMOTD, " :End of welcome message", this->list_users[fd]);

}

