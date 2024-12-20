/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:54:08 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 10:54:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <algorithm>
# include <sys/socket.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include <map>
# include <stdlib.h>
# include <set>
# include <sstream>
# include <ctime>
# include <signal.h>
# include <cstring>

extern volatile sig_atomic_t ctrl;

template <typename T>
std::string					itoa(T value);

std::string					getCurrentTime();
void						handleSignal(int signal);
std::string					getCurrentDate();
std::string					trim(const std::string& str);
std::vector<std::string>	split(const std::string& str, char delimiter, bool hexchat);
bool						nicknameCharacter(const char c);

#endif