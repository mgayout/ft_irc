/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:40:28 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 13:40:28 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Channel.hpp"

const std::string			&Channel::getName() {return this->_name;}
const std::string			&Channel::getPassword() {return this->_password;}
const std::string			&Channel::getTopic() {return this->_topic;}
const std::string			&Channel::getTopicUser() {return this->_topicUser;}
const std::string			&Channel::getTopicTime() {return this->_topicTime;}
const std::string			&Channel::getDate() {return this->_date;}
const bool					&Channel::getI() {return this->_i;}
const bool					&Channel::getT() {return this->_t;}
const unsigned int			&Channel::getMaxClient() {return this->_maxClient;}
std::vector<std::string>	&Channel::getInvited() {return this->_invited;}
std::vector<std::string>	&Channel::getMembers() {return this->_members;}
std::vector<std::string>	&Channel::getOp() {return this->_op;}
int							Channel::getNbClient() {return this->_members.size();}
