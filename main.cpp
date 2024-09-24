/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:08:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/24 13:34:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

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

/*void	init(char **argv)
{
	std::string	str;
	int sock = 0, clientsock = 0, msgrec = 0;
	struct sockaddr_in serv, client;
	socklen_t	clientsock_len = sizeof(client);
	char	buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return;

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(std::atoi(argv[1]));

	if (inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

	if (bind(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0)
	{
		std::cout << "Error: port " << argv[1] << " is occuped." << std::endl;
		close (sock);
		return ;
	}

	if (listen(sock, 1) < 0)
	{
		std::cout << "Error" << std::endl;
		close(sock);
		return ;
	}

	while (1)
	{
		clientsock = accept(sock, (struct sockaddr *)&client, &clientsock_len);
		if (clientsock < 0)
		{
			std::cout << "Error 2" << std::endl;
			close(sock);
			return ;
		}
		std::cout << "Connecte";
		if (recv(sock, buffer, sizeof(buffer) - 1, 0))
			std::cout << buffer << std::endl;

	}

	clientsock = accept(sock, (struct sockaddr *)&client, &clientsock_len);
	if (clientsock < 0)
	{
		std::cout << "Error 2" << std::endl;
		close(sock);
		return ;
	}
	if (connect(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
    	perror("connect failed");
    	exit(EXIT_FAILURE);
	}
	std::cout << "Connecte" << std::endl;

	close (sock);

	
	//send(clientsock, "Salut", 5, 0);
	//std::cout << "Message envoye au client." << std::endl;

	while (1)
	{
		msgrec = recv(sock, buffer, sizeof(buffer) - 1, 0);
		//std::cout << msgrec << std::endl;
		if (msgrec > 0)
		{
			buffer[msgrec] = '\0';
			std::cout << buffer << std::endl;
			break ;
		}
		//error("recv");
	}
	std::cout << "before while" << std::endl;

	while (1)
		//std::cout << "" << std::endl;

    close(sock);
	clos setsockopt,e(clientsock);
    return;
}*/

void	init(char **argv)
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // Création du socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Échec de la création du socket." << std::endl;
        return ;
    }
    
    // Attacher le socket au port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        std::cerr << "Erreur lors de l'attachement du socket." << std::endl;
        return ;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(std::atoi(argv[1]));
    
    // Lier le socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Erreur lors de la liaison." << std::endl;
        return ;
    }
    
    // Écoute des connexions
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Erreur lors de l'écoute." << std::endl;
        return ;
    }
    
    std::cout << "Serveur en attente de connexions sur le port " << argv[1] << "..." << std::endl;
    
	 if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
        }

    while (true) {
        // Accepter une nouvelle connexion
        
        //std::cout << "Nouveau client connecté." << std::endl;

        // Message à envoyer au client
        std::string	msg = "Bonjour !";
        send(new_socket, msg.c_str(), msg.size(), 0);
		char buffer[1024] = {0};
    	int bytes_received = recv(new_socket, buffer, 1024, 0);
		buffer[bytes_received] = '\0';
		if (bytes_received > 0)
		{
    	    std::cout << "Message reçu du client: " << std::string(buffer, bytes_received) << std::endl;
			if (buffer[0] == 's')
				break ;
    	}
		else if (bytes_received == 0)
			std::cout << "Le client s'est déconnecté." << std::endl;
		else
			std::cerr << "Erreur lors de la réception du message." << std::endl;
	}	
	
	close(new_socket);
	
    return ;
}


