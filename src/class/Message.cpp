/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:03:24 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 14:03:24 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::msg001(Client *client) {
	std::string	msg = this->getServerPrefix(client, "001") + ":Welcome to the ft_irc " + client->getNickname() + "\r\n";
	return msg;
}

std::string	Server::msg002(Client *client) {
	std::string	msg = this->getServerPrefix(client, "002") + ":Your host is " + this->getHostname() + ", running version " + this->getVersion() + "\r\n";
	return msg;
}

std::string	Server::msg003(Client *client) {
	std::string	msg = this->getServerPrefix(client, "003") + ":This server was created " + this->getDate() + "\r\n";
	return msg;
}

std::string	Server::msg004(Client *client) {
	std::string	msg = this->getServerPrefix(client, "004") + this->getHostname() + " " + this->getVersion() + " 0 itkol\r\n";
	return msg;
}

std::string	Server::msg307(Client *client, std::string target) {
	std::string	msg = this->getServerPrefix(client, "307") + target + " :has identified for this nick\r\n";
	return msg;
}

std::string	Server::msg311(Client *client, Client *target) {
	std::string	msg = this->getServerPrefix(client, "311") + target->getNickname() + " " + target->getUsername() + " * :" + target->getRealname() + "\r\n";
	return msg;
}

std::string	Server::msg312(Client *client, std::string target) {
	std::string	msg = this->getServerPrefix(client, "312") + target + " " + this->getHostname() + " :Some IRC Server\r\n";
	return msg;
}

std::string	Server::msg315(Client *client, std::string target) {
	std::string	msg = this->getServerPrefix(client, "315") + target + " :End of WHO list\r\n";
	return msg;
}

std::string	Server::msg319(Client *client, std::string target) {
	std::string	msg = this->getServerPrefix(client, "319") + " :";
	
	for (unsigned int i = 0; i < this->getClientWithNick(target)->getChannel().size(); i++)
	{
		if (this->getChannel(this->getClientWithNick(target)->getChannel()[i])->isOp(target))
			msg += "@";
		msg += this->getClientWithNick(target)->getChannel()[i] + " ";
	}
	msg += "\r\n";
	return msg;
}

std::string	Server::msg324(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "324") + channel + this->msgmodechannel(channel) + "\r\n";
	return msg;
}

std::string	Server::msg329(Client *client, Channel *channel) {
	std::string	msg = this->getServerPrefix(client, "329") + channel->getName() + " " + channel->getTopic() + " " + channel->getTime() + "\r\n";
	return msg;
}

std::string Server::msg331(Client *client, const std::string &channel) {
    std::string msg = this->getServerPrefix(client, "331") + client->getNickname() + " " + channel + " :No topic is set\r\n";
    return msg;
}

std::string	Server::msg332(Client *client, Channel *channel) {
	std::string	msg = this->getServerPrefix(client, "332") + channel->getName() + " :" + channel->getTopic() + "\r\n";
	return msg;
}

std::string	Server::msg333(Client *client, Channel *channel) {
	std::string	msg = this->getServerPrefix(client, "333") + channel->getName() + " " + channel->getTopicUser() + " " + channel->getTopicTime() + "\r\n";
	return msg;
}

std::string	Server::msg352(Client *client, std::string target)
{
	std::string	msg = "";
	
	if (target[0] == '#') 
	{
		Channel	*channelTarget = this->getChannel(target);
		for (unsigned int i = 0; i < channelTarget->getMembers().size(); i++)
		{
			Client	*clientTarget = this->getClientWithNick(channelTarget->getMembers()[i]);
			if (channelTarget->isOp(channelTarget->getMembers()[i]))
				msg += this->getServerPrefix(client, "352") + channelTarget->getName() + " " + clientTarget->getUsername() + " " + this->getHostname() + " " + this->getHostname() + " " + clientTarget->getNickname() + " H@ :0 " + clientTarget->getRealname() + "\r\n";
			else
				msg += this->getServerPrefix(client, "352") + channelTarget->getName() + " " + clientTarget->getUsername() + " " + this->getHostname() + " " + this->getHostname() + " " + clientTarget->getNickname() + " H :0 " + clientTarget->getRealname() + "\r\n";
		}
	}
	else
	{
		Client	*clientTarget = this->getClientWithNick(target);
		msg = this->getServerPrefix(client, "352") + "* " + clientTarget->getUsername() + " " + this->getHostname() + " " + this->getHostname() + " " + clientTarget->getNickname() + " H :0 " + clientTarget->getRealname() + "\r\n";
	}
	return msg;
}

std::string	Server::msg353(Client *client, std::string channel)
{
	std::string	msg = this->getServerPrefix(client, "353") + "= " + channel + " :" + this->msgclientschannel(channel) + "\r\n";
	return msg;
}

std::string	Server::msg366(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "366") + channel + " :End of /NAMES list\r\n";
	return msg;
}

std::string	Server::msg401(Client *client, std::string target) {
	std::string	msg = this->getServerPrefix(client, "401") + client->getNickname() + " " + target + " :No such nick/channel" + "\r\n";
	return msg;
}

std::string	Server::msg403(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "403") + client->getNickname() + " " + channel + " :No such channel\r\n";
	return msg;
}

std::string Server::msg421(Client *client, std::string command) {
	std::string msg = this->getServerPrefix(client, "421") + " " + command + " :Unknown command\r\n";
	return msg;
}

std::string Server::msg432(Client *client, std::string nickname) {
	std::string msg = this->getServerPrefix(client, "432") + " " + nickname + " :Erroneus nickname\r\n";
	return msg;
}

std::string	Server::msg433(Client *client, std::string nickname) {
	std::string	msg = this->getServerPrefix(client, "433") + " " + nickname + " :Nickname is already in use\r\n";
	return msg;
}

std::string Server::msg441(Client* client, std::string nickname, std::string channel) {
	std::string msg = this->getServerPrefix(client, "441") + channel + " " + nickname + " " + " :They are not on that channel\r\n";
	return msg;
}

std::string Server::msg442(Client* client, std::string channel) {
    std::string msg = this->getServerPrefix(client, "442") + client->getNickname() + " " + channel + " :You are not on that channel\r\n";
	return msg;
}

std::string	Server::msg443(Client *client, std::string nickname, std::string channel) {
    std::string msg = this->getServerPrefix(client, "443") + " " + nickname + " " + channel + " :is already on channel\r\n";
    return msg;
}

std::string	Server::msg451(Client *client, std::string command) {
	std::string	msg = this->getServerPrefix(client, "451") + command + " :You have not registered\r\n";
	return msg;
}

std::string	Server::msg461(Client *client, std::string command) {
	std::string	msg = this->getServerPrefix(client, "461") + command + " :Not enough parameters\r\n";
	return msg;
}

std::string	Server::msg462(Client *client) {
	std::string	msg = this->getServerPrefix(client, "462") + " :You may not reregister\r\n";
	return msg;
}

std::string	Server::msg464(Client *client) {
	std::string	msg = this->getServerPrefix(client, "464") + " :Password incorrect\r\n";
	return msg;
}

std::string	Server::msg471(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "471") + channel + " :Cannot join channel (+l)\r\n";
	return msg;
}

std::string Server::msg472(Client *client, std::string mode) {
    std::string msg = this->getServerPrefix(client, "472") + " " + mode + " :is unknown mode char\r\n";
    return msg;
}

std::string	Server::msg473(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "473") + channel + " :Cannot join channel (+i)\r\n";
	return msg;
}

std::string	Server::msg475(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "475") + channel + " :Cannot join channel (+k)\r\n";
	return msg;
}

std::string	Server::msg476(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "476") + channel + " :Bad Channel Mask\r\n";
	return msg;
}

std::string	Server::msg482(Client *client, std::string channel) {
    std::string msg = this->getServerPrefix(client, "482") + " " + channel + " :You're not channel operator\r\n";
    return msg;
}

std::string Server::msginvite(Client *client, std::string nickname, std::string channel) {
	std::string msg = ":" + client->getNickname() + " INVITE " + nickname + " " + channel + "\r\n";
	return msg;
}

std::string Server::msgjoin(Client *client, std::string channel) {
	std::string msg = this->getUserPrefix(client) + "JOIN " + channel + "\r\n";
	return msg;
}

std::string Server::msgjoinop(Client *client, std::string channel) {
	std::string msg = ":" + this->getHostname() + " MODE " + channel + " +o " + client->getNickname() + "\r\n";
	return msg;
}

std::string	Server::msgmode(Client *client, std::vector<std::string> args)
{
	std::string msg = this->getUserPrefix(client) + " " + args[0] + " " + args[1] + " " + args[2];
	if (args.size() == 4)
		msg += " " + args[3];
	msg += "\r\n";
	return msg;
}

std::string	Server::msgpart(Client *client, std::string channel, std::string message) {
	std::string msg = this->getUserPrefix(client) + "PART " + channel + " " + message + "\r\n";
	return msg;
}

std::string Server::msgprivmsg(Client *client, std::string target, std::string message) {
	std::string	msg = this->getUserPrefix(client) + "PRIVMSG " + target + " " + message + "\n\r";
	return msg;
}

std::string	Server::msgquit(Client *client, std::vector<std::string> arg) {
	std::string msg;
	
	for (unsigned int i = 1; i < arg.size(); i++)
		msg += arg[i] + " ";
	msg.erase(msg.size() - 1, 1);
	msg = this->getUserPrefix(client) + "QUIT :Quit: " + msg + "\r\n";
	return msg;
}

std::string	Server::msgkick(Client *client, std::vector<std::string> arg) {
	std::string msg = "";
	
	for (unsigned int i = 3; i < arg.size(); i++)
		msg += arg[i] + " ";
	if (msg.size())
		msg.erase(msg.size() - 1, 1);
	if (msg.size())
		msg = this->getUserPrefix(client) + "KICK " + arg[1] + " " + arg[2] + " " + msg + "\r\n";
	else
		msg = this->getUserPrefix(client) + "KICK " + arg[1] + " " + arg[2] + " " + client->getNickname() + "\r\n";
	return msg;
}

std::string	Server::msgtopic(Client *client, std::string channel, std::string message) {
	std::string msg;
	msg = this->getUserPrefix(client) + "TOPIC " + channel + " " + message + "\r\n";
	return msg;
}

std::string	Server::msgping(Client *client) {
	std::string msg;

	client->setPing(true);
	msg = ":" + this->getHostname() + " PING :" + client->getNickname() + "\r\n";
	return msg;
}

std::string	Server::msgpong(Client *client, std::string message) {
	std::string msg;
	msg = this->getUserPrefix(client) + "PONG :" + message + "\r\n";
	return msg;
}