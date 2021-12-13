/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:56:36 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/13 16:24:09 by javrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

bool 						BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

std::vector<std::string>   Server::parse_message(std::string buffer)
{
    std::vector<std::string>    tok_tmp;
    std::vector<std::string>    tokens;
    size_t                      pos;
	std::string                 tmps;    
    std::stringstream           s(buffer);
    std::istringstream          ss;
	
    if (buffer[0] == '\n' || buffer[0] == '\r' )
        tokens.push_back("");
    std::string::iterator new_end = std::unique(buffer.begin(), buffer.end(), BothAreSpaces);
    buffer.erase(new_end, buffer.end()); 
    if (((pos = buffer.find('\n')) != std::string::npos) || ((pos = buffer.find('\r')) != std::string::npos))
        buffer.erase(pos, buffer.size() - pos);
    while(getline(s, tmps, ':'))
        tok_tmp.push_back(tmps);
    if(buffer[0] == ':')
	{
		//gestionar espacio después de :
        ss.str(tok_tmp[1]);
        while(ss >> tmps)
        {
            tokens.push_back(tmps);
            std::cout << "*" << tmps << std::endl;
        }

        tokens.erase(tokens.begin());
		if (tok_tmp.size() > 2)
        	tokens.push_back(tok_tmp[2]); //trailing
    }
    else
    {
        ss.str(tok_tmp[0]);
        while(ss >> tmps)
            tokens.push_back(tmps);
		if (tok_tmp.size() > 1)
        	tokens.push_back(tok_tmp[1]); //triling
    }
    if (tokens.size() > 16)
        perror("Too many params\n");
    // std::cout << "tokens.size(): " << tokens.size() << "\n" << std::cout;
    // std::cout << "tokens[0]: " << tokens[0] << "\n" << std::cout;
    // std::cout << "tokens[1]: " << tokens[1] << "\n" << std::cout;
    // std::cout << "tokens[2]: " << tokens[2] << "\n" << std::cout;
    // std::cout << "tokens[3]: " << tokens[3] << "\n" << std::cout;
    return tokens;
}

