/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:17:53 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/06 19:02:25 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::pass(std::vector<std::string> const& tokens, User* usr)
{
    std::cout << usr << std::endl;
    if (!usr->getConnectionPswd())
	    return reply_msg(ERR_ALREADYREGISTRED, ": Unauthorized command (already registered)", usr); //?
    if (tokens.empty())
	  	return reply_msg(ERR_NEEDMOREPARAMS, tokens[0] + ": Not enough parameters", usr);
    if (tokens[1] != this->getPassword())
      return reply_msg(ERR_PASSWDMISMATCH ,"Password mismatch", usr); //NO se si hace falta
}
