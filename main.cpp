/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:08:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/23 09:26:29 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int		parse(char *arg);
void	init(char **argv);

int	main(int argc, char **argv)
{
	if (argc != 3 || parse(argv[1]) || !argv[2])
	{
		std::cout << "Error" << std::endl;
		return 1;
	}

	init(argv);

	return 0;
}

int	parse(char *arg)
{
	std::string	port = arg;
	long long	nb;

	for (size_t i = 0; i != port.size(); i++)
	{
		if (!isdigit(port[i]))
			return 1;
	}

	nb = std::strtoll(arg, NULL, 10);
	if (nb > 2147483647)
		return 1;
	return 0;
}

void	init(char **argv)
{
	std::string	str;
    int sock = 0;
	int port;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Erreur : Impossible de créer un socket" << std::endl;
        return;
    }

    serv_addr.sin_family = AF_INET;
    port = std::atoi(argv[1]);
	std::cout << port << std::endl;
	serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "Adresse invalide" << std::endl;
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Connexion échouée" << std::endl;
        return;
    }

	while (1)
	{
		std::cout << "ircserv: ";
		std::getline(std::cin, str);
		if (str == "LEAVE")
			break;
		
	}

    close(sock);

    return;
}
