/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:17:53 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/01 12:57:44 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::pass(std::vector<std::string> const& tokens, User* usr)
{
    std::cout << usr << std::endl; 
    if (usr->getConnectionPswd()) //SEG FAULT
        std::cout << ERR_ALREADYREGISTRED << "ALREADY_REGISTER" << std::endl;
    if (tokens.empty())
        perror(ERR_NEEDMOREPARAMS);
    if ( tokens[1] != this->getPassword())
        perror("Incorrect passwd");
}