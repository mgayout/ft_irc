/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:08:33 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 14:08:33 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "Utils.hpp"

std::string	msg001(Client *client);
std::string	msg002(Client *client);
std::string	msg003(Client *client);
std::string	msg004(Client *client);
std::string	msg315(Client *client, std::string target);
std::string	msg324(Client *client, std::string channel);
std::string	msg329(Client *client, Channel *channel);
std::string msg331(Client *client, const std::string &channel);
std::string	msg332(Client *client, Channel *channel);
std::string	msg333(Client *client, Channel *channel);
std::string	msg352(Client *client, std::string target);
std::string	msg353(Client *client, std::string channel);
std::string	msg366(Client *client, std::string channel);
std::string	msg401(Client *client, std::string target);
std::string	msg403(Client *client, std::string channel);
std::string msg421(Client *client, std::string command);
std::string msg432(Client *client, std::string nickname);
std::string	msg433(Client *client, std::string nickname);
std::string msg441(Client* client, std::string nickname, std::string channel);
std::string msg442(Client* client, std::string channel);
std::string	msg443(Client *client, std::string nickname, std::string channel);
std::string	msg451(Client *client, std::string command);
std::string	msg461(Client *client, std::string command);
std::string	msg462(Client *client);
std::string	msg464(Client *client);
std::string	msg471(Client *client, std::string channel);
std::string msg472(Client *client, std::string mode);
std::string	msg473(Client *client, std::string channel);
std::string	msg475(Client *client, std::string channel);
std::string	msg476(Client *client, std::string channel);
std::string	msg482(Client *client, std::string channel);
std::string msginvite(Client *client, std::string channel, std::string nickname);
std::string	msgjoin(Client *client, std::string channel);
std::string	msgjoinop(Client *client, std::string channel);
std::string	msgmode(Client *client, std::vector<std::string> args);
std::string	msgquit(Client *client, std::vector<std::string> arg);
std::string	msgprivmsg(Client *client, std::string target, std::string message);

std::string	getUserPrefix(Client *client);
std::string	getServerPrefix(Client *client, std::string code);

std::string	msgclientschannel(std::string channel);
std::string	msgmodechannel(std::string channel);

#endif