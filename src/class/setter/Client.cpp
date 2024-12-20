/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:12:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 15:12:06 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Client.hpp"

void	Client::setNickname(const std::string nick) {this->_nickname = nick;}
void	Client::setUsername(const std::string user) {this->_username = user;}
void	Client::setRealname(const std::string real) {this->_realname = real;}
void	Client::setPwd(bool b) {this->_pwd = b;}
void	Client::setNick(bool b) {this->_nick = b;}
void	Client::setUser(bool b) {this->_user = b;}
void	Client::setReal(bool b) {this->_real = b;}
void	Client::setHexchat(bool b) {this->_hexchat = b;}
void	Client::setPing(bool b) {this->_ping = b;}
void	Client::setLastPing(std::time_t t) {this->_lastping = t;}