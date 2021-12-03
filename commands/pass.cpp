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
    if (usr->getConnectionPswd())
        error_msg(ERR_ALREADYREGISTRED, "ALREADY_REGISTER", usr);
    if (tokens.empty())
        error_msg(ERR_NEEDMOREPARAMS, "NEED MORE PARAMS", usr);
    if ( tokens[1] != this->getPassword())
        error_msg(ERR_PASSWDMISMATCH ,"Incorrect passwd", usr);
}