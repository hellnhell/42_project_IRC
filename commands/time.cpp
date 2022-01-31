/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:46 by javrodri          #+#    #+#             */
/*   Updated: 2022/01/31 13:50:50 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../server.hpp"

void Server::timeCmmd(User *usr, int fd_user)
{
	std::string 	dt;

	time_t ttime = time(0);
	std::string message;
	dt = ctime(&ttime);
	message = usr->getUser() + " " + dt + " " + "\r\n";
	replyMsg(RPL_TIME, message, usr);
}
