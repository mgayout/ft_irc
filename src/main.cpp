/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:08:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/12/10 09:59:29 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

volatile sig_atomic_t ctrl = 0;

int	main(int argc, char **argv)
{
	char	hostname[1024];
	std::string	pwd;
	int			port;

	if (argc != 3)
	{
		std::cout << "Error: ./ircserv <port> <password>" << std::endl;
		std::exit(1);
	}

	port = atoi(argv[1]);
	
	if (port < 0 || port > 65535)
	{
		std::cout << "Error: invalid port" << std::endl;
		std::exit(1);
	}
	
	pwd = argv[2];
	
	if (gethostname(hostname, sizeof(hostname)))
	{
		std::cout << "Error: invalide hostname" << std::endl;
		std::exit(1);
	}
	
	try
	{
		signal(SIGINT, handleSignal);
	
		Server	server(hostname, port, pwd);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}

void	handleSignal(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
		ctrl++;
}