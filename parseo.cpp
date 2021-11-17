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
    std::string                 toks;
    std::vector<std::string>    tokens;
    size_t                      i;
   
    if (buffer.empty())
        tokens.push_back("");
    if (((i = buffer.find('\n')) != std::string::npos) || ((i = buffer.find('\r')) != std::string::npos)){
        buffer.erase(i, buffer.size() - i);
        // buffer.push_back('\0');
    }
    std::stringstream           s(buffer);
    if(buffer[0] == ':') // tokens[0] = prfx tokens[1] = comando
    {
        while(getline(s, toks, ' '))
            tokens.push_back(toks);
        std::string command = tokens[1];
        std::vector<std::string>::iterator it = tokens.begin();
        while (it != tokens.end())
        {
            std::cout << *it << "/";
            it++;                    
        }
        std::cout << std::endl;
    }
    else  // tokens[0] = cmmand tokens[1]
    {
        while(getline(s, toks, ' '))
            tokens.push_back(toks);
        std::string command = tokens[0];
        //       std::vector<std::string>::iterator it = tokens.begin();
        // while (it != tokens.end())
        // {
        //     std::cout << *it << "/" << std::endl;
        //     it++;                    
        // }
    
    }
    return ;
}

int main()
{
    std::string buffer = ":prefix cmmd param1 param2 :todo junto aaa\r\n";
    parse_message(buffer);
    return 0;
}
