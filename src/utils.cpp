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

/*std::string	currentDateTime()
{
	time_t		now = time(0);
	struct tm	timestruct;
	char		*buffer[1024];
	timestruct = *localtime(&now);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X", &timestruct);

	return buffer;
}*/

void	sendMessage(int fd, std::string msg)
{
	if (send(fd, msg.c_str(), msg.size(), 0) == -1)
		return ;
}