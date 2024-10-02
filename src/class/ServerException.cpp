/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:59:39 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/30 17:59:39 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

const char	*Server::sendException::what(void) const throw()
{
	return ("send() error");
}

const char	*Server::pollException::what(void) const throw()
{
	return ("poll() error");
}