/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:13:00 by javrodri          #+#    #+#             */
/*   Updated: 2022/01/27 12:47:26 by javrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "../channel.hpp"
#include <iostream>
#include <array>
#include <vector>

void Server::awayCmmd(std::vector<std::string> const &tokens, User *usr){

    std::string awayText;
    std::string msg;

    if (tokens.size() > 1){
        for (int i = 1; i != tokens.size() ; i++)
            awayText = awayText + tokens[i] + " ";
        usr->setAwayOn(true);
        usr->setAway(awayText);  
        msg.append(RPL_NOWAWAY);
        msg.append(" :You have been marked as being away\n");
        send(usr->getFD(), msg.c_str(), msg.size(), 0);
    }
    else{
        usr->setAwayOn(false);
        msg.append(RPL_UNAWAY);
        msg.append(" :You are no longer marked as being away\n");
        send(usr->getFD(), msg.c_str(), msg.size(), 0);
    }
}