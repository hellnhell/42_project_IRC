/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:16:16 by emartin-          #+#    #+#             */
/*   Updated: 2021/11/16 15:57:07 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void   parse_message(std::string buffer)
{
    std::vector<std::string>    tokens;
    size_t                      i;
	std::string                  tmps;    
   
    if (buffer.empty())
        tokens.push_back("");
    if (((i = buffer.find('\n')) != std::string::npos) || ((i = buffer.find('\r')) != std::string::npos)){
        buffer.erase(i, buffer.size() - i);
        // buffer.push_back('\0');
    }
    std::istringstream ss(buffer);
	while(ss >> tmps)
    {
        if (tmps.find(":") != std::string::npos)
        {
            tokens.insert(pos, end)
        }
        else
		    tokens.push_back(tmps);
    }
    if(buffer[0] == ':') // tokens[0] = prfx tokens[1] = comando
    {
        if(buffer[1] == ' ')
            perror("Message : ");
        std::string command = tokens[1];
    }
    else  // tokens[0] = cmmand tokens[1]
    {
        std::string command = tokens[0];
        std::cout << tokens[1];
    }
    return ;
}

int main()
{
    std::string buffer = ":prefix cmmd param1 param2 :todo junto aaa\n";
    parse_message(buffer);
    return 0;
}
