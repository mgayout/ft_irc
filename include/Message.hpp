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
std::string	msg433(Client *client, std::string nickname);
std::string	msg461(Client *client, std::string command);
std::string	msg462(Client *client);
std::string	msg464(Client *client);

#endif