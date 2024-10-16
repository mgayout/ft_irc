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

std::string	Server::join(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::vector<std::string> args = split(arg, ',');
	for (size_t i = 0; i < args.size(); i++)
	{
		if (args[i].at(0) != '#') 
		{
			//sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name\n");
			continue;
		}
		Channel *channel = this->_channels[arg.substr(0, arg.find(" "))];
		if (channel->isFull())
		{
			//sendMessage(clientFd, "ERR_CHANNELISFULL: " + arg.substr(0, arg.find(" ")) + "is full\n");
			continue;
		}
		if (args[i].find(" ") != std::string::npos)
			joinPsswrd(args[i], client);
		else if (channel->isInviteOnly() && channel->isInvited(client))
			joinDefault(args[i], client);
		else
			joinDefault(args[i], client);
	}
	return "";
}

std::string	Server::joinPsswrd(std::string arg, Client *client)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string password = arg.substr(arg.find(" ") + 1);

	if(this->_channels.find(arg) != this->_channels.end())
	{
		if (this->_channels[channelName]->getPassword() != password)
		{
			//sendMessage(clientFd, "ERR_BADCHANNELKEY: Invalid channel key\n");
			return "";
		}
		this->_channels[channelName]->addMember(client, password);
	}
	else
	{
		Channel *newChannel = new Channel(client, arg, password);
		this->_channels.insert(std::make_pair(channelName, newChannel));
	}
	return "";
}

std::string	Server::joinDefault(std::string arg, Client *client)
{
	if(this->_channels.find(arg) != this->_channels.end())
		this->_channels[arg]->addMember(client, "");
	else
	{
		Channel *newChannel = new Channel(client, arg, "");
		this->_channels.insert(std::make_pair(arg, newChannel));
	}
	return "";
}

std::string	Server::part(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::vector<std::string> args = split(arg, ',');
	for (size_t i = 0; i < args.size(); i++)
	{
		if (args[i].at(0) != '#') 
		{
			//sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name\n");
			continue;
		}
		if (args[i].find(" :") != std::string::npos)
			partReason(args[i], client);
		else
			partDefault(args[i], client);
	}
	return "";
}

std::string	Server::partReason(std::string arg, Client *client)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string reason = arg.substr(arg.find(" ") + 1);
	std::string msg = client->getNickname() + " has left " + channelName +"(" + reason + ")";

	if(this->_channels.find(arg) != this->_channels.end())
	{
		this->_channels[channelName]->removeMember(client);
		this->_channels[channelName]->SendMessChan(msg, client);
	}
	else
		sendMessage(client->getSocket(), "ERR_NOSUCHCHANNEL: Invalid channel name\n");
	return "";
}

std::string	Server::partDefault(std::string arg, Client *client)
{
	std::string msg = client->getNickname() + " has left " + arg;
	if(this->_channels.find(arg) != this->_channels.end())
	{
		this->_channels[arg]->removeMember(client);
		_channels[arg]->SendMessChan(msg, client);
	}
	else
		sendMessage(client->getSocket(), "ERR_NOSUCHCHANNEL: Invalid channel name\n");
	return "";
}

std::string	Server::kick(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::vector<std::string> args = split(arg, ',');
	for (size_t i = 0; i < args.size(); i++)
	{
		if (args[i].at(0) != '#') 
		{
			//sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name\n");
			continue;
		}
		if (args[i].find(" :") != std::string::npos)
			kickReason(args[i], client);
		else
			kickDefault(args[i], client);
	}
	return "";
}

std::string	Server::kickReason(std::string arg, Client *client)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string nickname = arg.substr(arg.find(" ") + 1, arg.find(" :") - (arg.find(" ") + 1));
	std::string reason = arg.substr(arg.find(" :") + 2);

	if (this->_channels.find(channelName) != this->_channels.end())
	{
		Channel* channel = this->_channels[channelName];

		if (channel->isOP(client))
		{
			Client* targetClient = findClient(nickname);
			if (targetClient && this->_channels[channelName]->isMember(targetClient))
			{
				channel->removeMember(targetClient);
				channel->SendMessChan(nickname + " has been kicked by " + client->getNickname() + " (" + reason + ")\n", client);
				sendMessage(targetClient->getSocket(), "You have been kicked from " + channelName + " by " + client->getNickname() + "\n");
			}
			else
			{
				sendMessage(client->getSocket(), "ERR_USERNOTINCHANNEL: User is not in the channel\n");
			}
		}
		else
			sendMessage(client->getSocket(), "ERR_CHANOPRIVSNEEDED: You're not channel operator\n");
	}
	else
		sendMessage(client->getSocket(), "ERR_NOSUCHCHANNEL: Invalid channel name\n");
	return "";
}

std::string	Server::kickDefault(std::string arg, Client *client)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string nickname = arg.substr(arg.find(" ") + 1);

	if (this->_channels.find(channelName) != this->_channels.end())
	{
		Channel* channel = this->_channels[channelName];

		if (channel->isOP(client))
		{
			Client* targetClient = findClient(nickname);
			if (targetClient && channel->isMember(targetClient))
			{
				channel->removeMember(targetClient);
				//channel->SendMessChan(nickname + " has been kicked by " + this->_clients[clientFd]->getNickname(), this->_clients[clientFd] + "\n");
				sendMessage(targetClient->getSocket(), "You have been kicked from " + channelName + " by " + client->getNickname() + "\n");
			}
			else
			{
				sendMessage(client->getSocket(), "ERR_USERNOTINCHANNEL: User is not in the channel\n");
			}
		}
		else
			sendMessage(client->getSocket(), "ERR_CHANOPRIVSNEEDED: You're not channel operator\n");
	}
	else
		sendMessage(client->getSocket(), "ERR_NOSUCHCHANNEL: Invalid channel name\n");
	return "";
}

std::string	Server::invite(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::vector<std::string> args = split(arg, ' ');
	Client *targetClient = findClient(args[1]);

	if (args[0] != "INVITE")
	{
		//sendMessage(clientFd, "ERR_UNKNOWNCOMMAND: Unknown command\n");
		return "";
	}
	if (args.size() < 3)
    {
       // sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for INVITE\n");
        return "";
    }
	if (!this->isClient(targetClient))
	{
		//sendMessage(clientFd, "ERR_NOSUCHNICK: No such nick/channel\n");
		return "";
	}
	if (args[2].at(0) != '#') 
	{
		//sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name\n");
		return "";
	}
	if (this->_channels.find(args[2]) == this->_channels.end())
	{
		//sendMessage(clientFd, "ERR_NOSUCHCHANNEL: No such channel\n");
		return "";
	}
	if (!this->_channels[args[2]]->isOP(client))
	{
       // sendMessage(clientFd, "ERR_CHANOPRIVSNEEDED: You're not a channel operator\n");
        return "";
	}

	if (this->_channels[args[2]]->isMember(targetClient))
	{
		//sendMessage(clientFd, "ERR_USERONCHANNEL: " + args[1] + " is already on " + args[2] + "\n");
		return "";
	}
	this->_channels[args[2]]->ADDInvited(targetClient);
	sendMessage(targetClient->getSocket(), ":" + client->getNickname() + " INVITE " + args[1] + " " + args[2] + "\n");
	return "";
}

std::string	Server::topic(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::vector<std::string> args = split(arg, ' ');

	if (args.size() < 2) 
	{
		//sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for TOPIC\n");
		return "";
	}

	std::string channelName = args[1];
	if (channelName.at(0) != '#') 
	{
		//sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name\n");
		return "";
	}
	if (this->_channels.find(channelName) == this->_channels.end())
	{
		//sendMessage(clientFd, "ERR_NOSUCHCHANNEL: No such channel\n");
		return "";
	}

	Channel *channel = this->_channels[channelName];
	if (args.size() == 2) 
	{
		//sendMessage(clientFd, "RPL_TOPIC: " + channel->getName() + " :" + channel->getTopic() + "\n");
		return "";
	}

	if (args.size() >= 3) 
	{
		std::string newTopic = arg.substr(arg.find(' ', arg.find(' ') + 1) + 1);

		if (channel->isTopicProtected() && !channel->isOP(client)) 
		{
			//sendMessage(clientFd, "ERR_CHANOPRIVSNEEDED: You're not a channel operator\n");
			return "";
		}
		channel->setTopic(newTopic);
		channel->SendMessChanAll("TOPIC " + channel->getName() + " :" + newTopic + "\n");
	}
	return "";
}

std::string	Server::mode(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::vector<std::string> args = split(arg, ' ');
	if (args.size() < 2)
	{
		//sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for MODE\n");
		return "";
	}
	if (args[0] != "MODE")
	{
		//sendMessage(clientFd, "ERR_UNKNOWNCOMMAND: Unknown command\n");
		return "";
	}
	if (args[1].at(0) != '#') 
	{
		//sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name\n");
		return "";
	}
	if (args[2].at(0) != '+' && args[2].at(0) != '-')
	{
		//sendMessage(clientFd, "ERR_UNKNOWNMODE: Unknown mode\n");
		return "";
	}
	Channel *channel = this->_channels[args[1]];
	std::string mode = args[2].substr(1);
	modeOp(client, channel, mode, args);
	return "";
}

std::string	Server::modeOp(Client *client, Channel *channel, std::string mode, std::vector<std::string> args)
{
	if (!channel->isOP(client))
	{
		//sendMessage(clientFd, "ERR_CHANOPRIVSNEEDED: You're not channel operator\n");
		return "";
	}

	if (mode == "+i" || mode == "-i")
	{
		if (mode == "+i")
			channel->setPrivate(true);
		else
			channel->setPrivate(false);

		channel->SendMessChanAll("MODE " + channel->getName() + " " + mode + "\n");
	}

	else if (mode == "+k" || mode == "-k")
	{
		if (mode == "+k")
		{
			if (args.size() < 4)
			{
				//sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for MODE\n");
				return "";
			}
			channel->setPassword(args[3]);
			channel->SendMessChanAll("MODE " + channel->getName() + " +k " + args[3] + "\n");
		}
		else
		{
			channel->setPassword("");
			channel->SendMessChanAll("MODE " + channel->getName() + " -k\n");
		}
	}

	else if (mode == "+l" || mode == "-l")
	{
		if (mode == "+l")
		{
			if (args.size() < 4)
			{
				//sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for MODE\n");
				return "";
			}
			channel->setMaxClients(std::atoi(args[3].c_str()));
			channel->SendMessChanAll("MODE " + channel->getName() + " +l " + args[3] + "\n");
		}
		else
		{
			channel->setMaxClients(-1);
			channel->SendMessChanAll("MODE " + channel->getName() + " -l\n");
		}
	}


	else if (mode == "+o" || mode == "-o")
	{
		if (args.size() < 4)
		{
			//sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for MODE\n");
			return "";
		}
		Client *targetClient = findClient(args[3]);
		if (channel->isMember(targetClient))
		{
			if (mode == "+o")
				channel->OP(targetClient);
			else
				channel->DEOP(targetClient);

			channel->SendMessChanAll("MODE " + channel->getName() + " " + mode + " " + args[3] + "\n");
		}
		else
		{
			sendMessage(client->getSocket(), "ERR_USERNOTINCHANNEL: User is not in the channel\n");
		}
	}

	else if (mode == "+t" || mode == "-t")
	{
		if (mode == "+t")
			channel->setTopicChange(false);  
		else
			channel->setTopicChange(true);

		channel->SendMessChanAll("MODE " + channel->getName() + " " + mode + "\n");
	}
	else
	{
		//sendMessage(clientFd, "ERR_UNKNOWNMODE: Unknown mode\n");
		return "";
	}
	return "";
}

std::string	Server::cap(Client *client)
{
	client->setHexchat(true);
	return "";
}

std::string	Server::pass(std::string arg, Client *client)
{
	std::string	msg;

	if (arg.size())
	{
		if (client->getPwd())
			return this->msg462(client);
		if (arg == this->getPassword())
			client->setPwd(true);
		else
			return this->msg464(client);
	}
	else
		return this->msg461(client, "PASS");
	return "";
}

std::string	Server::nick(std::string arg, Client *client)
{
	std::string	msg;

	if (!client->getPwd())
		return "";
	if (arg.size())
	{
		if (client->getNick())
			return this->msg462(client);
		if (!this->nicknameUsed(arg))
		{
			client->setNickname(arg);
			client->setNick(true);
			if (client->getAuthenticated())
				return (this->msg001(client) +\
						this->msg002(client) + \
						this->msg003(client) + \
						this->msg004(client));
		}
		else
			return this->msg433(client, arg);
	}
	else
		return this->msg461(client, "NICK");
	return "";
}

std::string	Server::user(std::string arg, Client *client)
{
	std::string	msg;

	if (!client->getPwd())
		return "";
	if (arg.size())
	{
		if (client->getUser())
			return this->msg462(client);
		if (!this->usernameUsed(arg))
		{
			client->setUsername(arg);
			client->setUser(true);
			if (client->getAuthenticated())
				return (this->msg001(client) +\
						this->msg002(client) + \
						this->msg003(client) + \
						this->msg004(client));
		}
	}
	else
		return this->msg461(client, "USER");
	return "";
}

std::string	Server::op(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::string	msg = "op \"" + arg + "\"\n";
	
	std::cout << "op \"" << arg << "\"\n";
	sendMessage(client->getSocket(), msg);
	return "";
}

std::string	Server::deop(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::string	msg = "deop \"" + arg + "\"\n";
	
	std::cout << "deop \"" << arg << "\"\n";
	sendMessage(client->getSocket(), msg);
	return "";
}

std::string	Server::msg(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::string	msg, nick;
	int			space;

	if (client->getAuthenticated())
	{
		if (arg.size() && (space = arg.find(' ')) > 0 && arg[space + 1] != '\0')
		{
			nick = arg.substr(0, space);
			msg = arg.substr(space + 1, arg.size() - space);
			if (this->nicknameUsed(nick))
			{
				if (this->nicknameUsed(nick) != client->getSocket())
				{
					msg = client->getNickname() + " -> " + msg + "\n";
					sendMessage(this->nicknameUsed(nick), msg);
					sendMessage(client->getSocket(), "Message send\n");
				}
				else
				{
					msg = "You can't send a private message to yourself\n";
					sendMessage(client->getSocket(), msg);
				}
			}
			else
			{
				msg = "Error : MSG <nick> <message>\n";
				sendMessage(client->getSocket(), msg);
			}
		}
		else
		{
			msg = "Error : MSG <nick> <message>\n";
			sendMessage(client->getSocket(), msg);
		}
	}
	else
	{
		msg = "You have to be authenticated before using this command.\n";
		sendMessage(client->getSocket(), msg);
	}
	return "";
}

std::string	Server::quit(Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::string	msg = "Disconnected\n";
	sendMessage(client->getSocket(), msg);

	for (unsigned int i = 0; i < this->_pfds.size(); i++)
	{
		if (this->_pfds[i].fd == client->getSocket())
		{
			std::cout << "Client n°" << i << " has been disconnected\n";
			close (this->_pfds[i].fd);
			close(client->getSocket());
			this->_pfds.erase(this->_pfds.begin() + i);
			this->_clients.erase(client->getSocket());
			this->_nbClient--;
			break;
		}
	}
	return "";
}

std::string	Server::sendfile(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::string	msg = "sendfile \"" + arg + "\"\n";
	
	std::cout << "sendfile \"" << arg << "\"\n";
	sendMessage(client->getSocket(), msg);
	return "";
}

std::string	Server::getfile(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::string	msg = "getfile \"" + arg + "\"\n";
	
	std::cout << "getfile \"" << arg << "\"\n";
	sendMessage(client->getSocket(), msg);
	return "";
}

std::string	Server::bot(std::string arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	std::string	msg = "bot  \"" + arg + "\"\n";
	
	std::cout << "bot \"" << arg << "\"\n";
	sendMessage(client->getSocket(), msg);
	return "";
}
