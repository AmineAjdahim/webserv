/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:09:41 by majdahim          #+#    #+#             */
/*   Updated: 2022/06/21 22:01:57 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"

Config::Config(void)
{

}
Config::~Config(void)
{
}
void Config::set_port(std::string port)
{
    this->_port = port;
}
void Config::set_ip(std::string ip)
{
    this->_ip = ip;
}
std::string Config::get_ip(void)
{
    return (this->_ip);
}

std::string Config::get_port(void)
{
    return (this->_port);
}

std::string Config::get_client_max_body_size(void)
{
    return (this->_client_max_body_size);
}

void Config::set_client_max_body_size(std::string client_max_body_size)
{
    this->_client_max_body_size = client_max_body_size;
}

void Config::set_sock_fd(int sock_fd)
{
    this->_sock_fd = sock_fd;
}

int Config::get_sock_fd(void)
{
    return (this->_sock_fd);
}

void Config::set_client_fd(int client_fd)
{
    this->_client_fd = client_fd;
}

int Config::get_client_fd(void)
{
    return (this->_client_fd);
}
