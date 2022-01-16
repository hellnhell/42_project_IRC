/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:13:00 by javrodri          #+#    #+#             */
/*   Updated: 2022/01/11 18:09:29 by javrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "../channel.hpp"
#include <iostream>
#include <array>
#include <vector>

void Server::awayCmmd(std::vector<std::string> const &tokens, User *usr){

    std::string awayText;

    if (tokens.size() > 1){
        for (int i = 1; i != tokens.size() ; i++)
            awayText = awayText + tokens[i] + " ";
        usr->setAwayOn(true);
        usr->setAway(awayText);  
    }
    else{
        usr->setAwayOn(false);
    }
}