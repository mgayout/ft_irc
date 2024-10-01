/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:42:54 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 17:42:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void	Server::join(std::string arg, int clientFd)
{
	std::string	msg = "New channel has been created : " + arg + "\n";
	
	std::cout << "New channel has been created : " << arg << "\n";
	sendMessage(clientFd, msg);
}

void	Server::part(std::string arg, int clientFd)
{
	std::string	msg = "A client left channel \"" + arg + "\"\n";
	
	std::cout << "A client left channel \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::kick(std::string arg, int clientFd)
{
	std::string	msg = "A client was kicked out from channel \"" + arg + "\"\n";
	
	std::cout << "A client was kicked out from channel \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::invite(std::string arg, int clientFd)
{
	std::string	msg = "A client invited someone on channel \"" + arg + "\"\n";
	
	std::cout << "A client invited someone on channel \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::topic(std::string arg, int clientFd)
{
	std::string	msg = "topic \"" + arg + "\"\n";
	
	std::cout << "topic \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::mode(std::string arg, int clientFd)
{
	std::string	msg = "mode \"" + arg + "\"\n";
	
	std::cout << "mode \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::cap(int clientFd)
{
	this->_clients[clientFd]->setHexchat(true);
	std::cout << "hexchat" << std::endl;
}

void	Server::pass(std::string arg, int clientFd)
{
	std::string	msg;

	if (arg.size())
	{
		if (arg == this->_password)
		{
			this->_clients[clientFd]->setPassword(true);
			msg = "Password is correct\n";
			sendMessage(clientFd, msg);
		}
		else
		{
			msg = "Password is incorrect\n";
			sendMessage(clientFd, msg);
		}
	}
	else
	{
		msg = "Error : PASS <password>\n";
		sendMessage(clientFd, msg);
	}
}

void	Server::nick(std::string arg, int clientFd)
{
	std::string	msg;

	if (arg.size())
	{
		if (!this->nicknameUsed(arg))
		{
			if (this->_clients[clientFd]->getNickname().size())
			{
				msg = "Nickname has been change\n";
				sendMessage(clientFd, msg);
			}
			else
			{
				msg = "Nickname has been add\n";
				sendMessage(clientFd, msg);
			}
			this->_clients[clientFd]->setNickname(arg);
		}
		else
		{
			msg = "New nickname is already used\n";
			sendMessage(clientFd, msg);
		}
	}
	else
	{
		msg = "Error : NICK <nickname>\n";
		sendMessage(clientFd, msg);
	}
}

void	Server::user(std::string arg, int clientFd)
{
	std::string	msg;

	if (arg.size())
	{
		if (!this->usernameUsed(arg))
		{
			if (this->_clients[clientFd]->getUsername().size())
			{
				msg = "Username has been change\n";
				sendMessage(clientFd, msg);
			}
			else
			{
				msg = "Username has been add\n";
				sendMessage(clientFd, msg);
			}
			this->_clients[clientFd]->setUsername(arg);
		}
		else
		{
			msg = "New username is already used\n";
			sendMessage(clientFd, msg);
		}
	}
	else
	{
		msg = "Error : USER <username>\n";
		sendMessage(clientFd, msg);
	}
}

void	Server::op(std::string arg, int clientFd)
{
	std::string	msg = "op \"" + arg + "\"\n";
	
	std::cout << "op \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::deop(std::string arg, int clientFd)
{
	std::string	msg = "deop \"" + arg + "\"\n";
	
	std::cout << "deop \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::msg(std::string arg, int clientFd)
{
	std::string	msg, nick;
	int			space;

	if (this->_clients[clientFd]->getAuthenticated())
	{
		if (arg.size() && (space = arg.find(' ')) > 0 && arg[space + 1] != '\0')
		{
			nick = arg.substr(0, space);
			msg = arg.substr(space + 1, arg.size() - space);
			if (this->nicknameUsed(nick))
			{
				if (this->nicknameUsed(nick) != this->_clients[clientFd]->getSocket())
				{
					msg = this->_clients[clientFd]->getNickname() + " -> " + msg + "\n";
					sendMessage(this->nicknameUsed(nick), msg);
					sendMessage(clientFd, "Message send\n");
				}
				else
				{
					msg = "You can't send a private message to yourself\n";
					sendMessage(clientFd, msg);
				}
			}
			else
			{
				msg = "Error : MSG <nick> <message>\n";
				sendMessage(clientFd, msg);
			}
		}
		else
		{
			msg = "Error : MSG <nick> <message>\n";
			sendMessage(clientFd, msg);
		}
	}
	else
	{
		msg = "You have to be authenticated before using this command.\n";
		sendMessage(clientFd, msg);
	}
}

void	Server::quit(std::string arg, int clientFd)
{
	std::string	msg = "quit \"" + arg + "\"\n";
	
	std::cout << "quit \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::sendfile(std::string arg, int clientFd)
{
	std::string	msg = "sendfile \"" + arg + "\"\n";
	
	std::cout << "sendfile \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::getfile(std::string arg, int clientFd)
{
	std::string	msg = "getfile \"" + arg + "\"\n";
	
	std::cout << "getfile \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::bot(std::string arg, int clientFd)
{
	std::string	msg = "bot  \"" + arg + "\"\n";
	
	std::cout << "bot \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}
