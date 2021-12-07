/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:10:03 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/07 13:10:04 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../server.hpp"

void Server::time_cmd(User *usr, int fd_user){
	std::string 	dt;

    time_t ttime = time(0);
	std::string message;
	dt = ctime(&ttime);
	message.append(RPL_TIME);
	message = ":ft_irc.com " + usr->getUser() + SERVER_MASK + dt + " " + "\r\n";
	send(fd_user, message.c_str(), message.length(), 0); //Funciona, falta comprobar si un cliente lo gestiona correctamente.
}