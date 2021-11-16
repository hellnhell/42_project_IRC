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

std::vector<std::string>    parse_message(std::string buffer)
{
    std::string                 toks;
    std::vector<std::string>    tokens;
    int                         pos = 0;
    
    if(buffer[0] == ':')
    {
        buffer.erase(buffer.begin());
        std::stringstream           s(buffer);
        while(getline(s, toks, ' '))
        {
            tokens.push_back(toks);
            while()
        }
    }
    std::vector<std::string>::iterator it = tokens.begin();
    while(it != tokens.end())
    {
        std::cout << *it << std::endl;;
        it++;
    }
    return tokens;

}

int main()
{
    std::string buffer = ":prfijoe hfjhf trtru hf : e  blhjggkjh  g";
    parse_message(buffer);
}
