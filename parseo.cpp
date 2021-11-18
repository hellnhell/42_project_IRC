/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:16:16 by emartin-          #+#    #+#             */
/*   Updated: 2021/11/18 18:14:29 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void parse_message(std::string buffer)
{
    std::vector<std::string>    tok_tmp;
    std::vector<std::string>    tokens;
    size_t                      pos;
	std::string                 tmps;
    std::stringstream           s(buffer);
    std::istringstream          ss;

    if (buffer.empty())
        tokens.push_back("");
    if (((pos = buffer.find('\n')) != std::string::npos) || ((pos = buffer.find('\r')) != std::string::npos))
        buffer.erase(pos, buffer.size() - pos);
    while(getline(s, tmps, ':'))
        tok_tmp.push_back(tmps);
    if(buffer[0] == ':'){
        ss.str(tok_tmp[1]);
        while(ss >> tmps)
            tokens.push_back(tmps);
//          tokens.erase(tokens.begin()); //N: creo que asin
        tokens.push_back(tok_tmp[2]);
    }
    else
    {
        ss.str(tok_tmp[0]);
        while(ss >> tmps)
            tokens.push_back(tmps);
        tokens.push_back(tok_tmp[1]);
    }


    //N: esto es cutrez para verlo, pero deberia returnear vector string(?)
   for(auto i: tokens)
    std::cout << i << std::endl;



    return;
}

int main()
{
    std::string buffer =":prefijo cmmd param param : hola que tal";
    // std::string buffer2 =":prf cmmd param param : asd";
    parse_message(buffer);
    // parse_message(buffer2);

    return 0;
}
