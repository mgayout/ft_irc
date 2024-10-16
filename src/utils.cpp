/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:10:11 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 14:10:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string	getCurrentDate()
{
	std::time_t	now = std::time(NULL);
	std::tm*	time = std::localtime(&now);
	char		buffer[1024];

	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time);

	return buffer;
}

void	sendMessage(int clienFd, std::string msg)
{
	/*std::string	newMsg = "[" + currentDateTime() + "] : " + msg;
	if (!this->_clients[clienFd]->getHexchat())
	{
		if (send(clienFd, newMsg.c_str(), newMsg.size(), 0) == -1)
			throw (Server::sendException());
	}
	else
	{
		if (send(clienFd, msg.c_str(), msg.size(), 0) == -1)
			throw (Server::sendException());	
	}*/
	if (send(clienFd, msg.c_str(), msg.size(), 0) == -1)
		throw (Server::sendException());
}

std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length();

    while (start < end && std::isspace(static_cast<unsigned char>(str[start]))) {
        ++start;
    }

    while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1]))) {
        --end;
    }

    return str.substr(start, end - start);
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(str);

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }

    return tokens;
}
