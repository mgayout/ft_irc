/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:39:02 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 11:39:02 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Client.hpp"

const int					&Client::getSocket() {return this->_socket;}
const std::string			&Client::getNickname() {return this->_nickname;}
const std::string			&Client::getUsername() {return this->_username;}
const std::string			&Client::getRealname() {return this->_realname;}
const bool					&Client::getPwd() {return this->_pwd;}
const bool					&Client::getNick() {return this->_nick;}
const bool					&Client::getUser() {return this->_user;}
const bool					&Client::getReal() {return this->_real;}
const bool					&Client::getHexchat() {return this->_hexchat;}
const bool					&Client::getPing() {return this->_ping;}
const std::time_t			&Client::getLastPing() {return this->_lastping;}
std::vector<std::string>	Client::getChannel() {return this->_channels;}
