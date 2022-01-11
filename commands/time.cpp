/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:46 by javrodri          #+#    #+#             */
/*   Updated: 2021/12/10 10:35:26 by javrodri         ###   ########.fr       */
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
