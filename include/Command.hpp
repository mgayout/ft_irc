/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:05:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 14:05:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Utils.hpp"

std::string		join(std::vector<std::string> arg, Client *client);
std::string		createChannel(std::string channel, std::string password, Client *client);
std::string		joinChannel(std::string channelname, std::string password, Client *client);

std::string		part(std::vector<std::string> arg, Client *client);

std::string		kick(std::vector<std::string> arg, Client *client);

std::string		invite(std::vector<std::string> arg, Client *client);

std::string		topic(std::vector<std::string> arg, Client *client);

std::string		mode(std::vector<std::string> arg, Client *client);

std::string		cap(Client *client);

std::string		pass(std::vector<std::string> arg, Client *client);
std::string		nick(std::vector<std::string> arg, Client *client);
std::string		user(std::vector<std::string> arg, Client *client);

std::string		msgpart(Client *client, std::string channel, std::string message);

std::string		privmsg(std::vector<std::string> arg, Client *client, bool sendme);
std::string		privmsgChannel(std::string channel, std::string msg, Client *client, bool sendme);
std::string		privmsgClient(std::string target, std::string msg, Client *client);

std::string		quit(std::vector<std::string> arg, Client *client);

std::string		sendfile(std::vector<std::string> arg, Client *client);
std::string		getfile(std::vector<std::string> arg, Client *client);

Client*			botInit();
std::string		bot(std::vector<std::string> arg, Client *client);

std::string		who(std::vector<std::string> arg, Client *client);
std::string		whois(std::vector<std::string> arg, Client *client);

std::string		ping(std::vector<std::string> arg, Client* client);
std::string		pong(std::vector<std::string> arg, Client* client);

#endif