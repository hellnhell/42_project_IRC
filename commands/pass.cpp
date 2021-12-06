/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:17:53 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/06 14:19:06 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::pass(std::vector<std::string> const& tokens, User* usr)
{
    std::cout << usr << std::endl; 
    if (usr->getConnectionPswd())
        return error_msg(ERR_ALREADYREGISTRED, "Already register", usr);
    if (tokens.empty())
        return error_msg(ERR_NEEDMOREPARAMS, "Nedd more params", usr);
    if ( tokens[1] != this->getPassword())
        return error_msg(ERR_PASSWDMISMATCH ,"Password mismatch", usr);
}