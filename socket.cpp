/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:15:53 by majdahim          #+#    #+#             */
/*   Updated: 2022/06/30 21:07:02 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"
#include <sstream>
#include "request_data.hpp"

socket_server::~socket_server(){}
socket_server::socket_server(/* args */){}

int socket_server::checkservers(int c ,std::vector<Server> servers)
{
  for (int i = 0; i < servers.size(); i++)
  {
    if (servers[i].get_sock_fd() == c)
    	return c;
  }
  return -1;
}

std::string socket_server::removespaces(std::string str,char c)
{
	str.erase(remove(str.begin(),str.end(), c),str.end());
	return (str);
}

void socket_server::set_max_fd(int max_fd)
{
  this->max_fd = max_fd;
}

int socket_server::get_max_fd()
{
  return this->max_fd;
}

void request(char *buffer)
{
  std::cout << buffer << std::endl;
  memset(buffer,0,1024);
}

int socket_server::socketserver(int i)
{
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		std::cout << "Error: socket()" << std::endl;
		return -1;
	}
	if (fcntl(sock_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "Error: fcntl()" << std::endl;
		return -1;
	}
	this->Servers[i].set_sock_fd(sock_fd);
	return sock_fd;
}

int socket_server::bindserver(int i)
{
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(atoi(this->Servers[i].get_port().c_str()));
	sockaddr.sin_addr.s_addr = inet_addr(this->Servers[i].get_ip().c_str());
	this->Servers[i]._sockaddr = sockaddr;
	this->Servers[i]._sockaddr_len = sizeof(sockaddr);
	int bind_ret = bind(this->Servers[i].get_sock_fd(), (struct sockaddr *)&this->Servers[i]._sockaddr, this->Servers[i]._sockaddr_len);
	if (bind_ret == -1)
	{
		std::cout << "Error: bind()" << std::endl;
		exit(1);
	}
	return 0;
}

int socket_server::listenserver(int i)
{
	int listen_ret = listen(this->Servers[i].get_sock_fd(), 5);
	if (listen_ret == -1)
	{
		std::cout << "Error: listen()" << std::endl;
		return -1;
	}
	return 0;
}

int socket_server::create_socket(void)
{
	this->Servers = this->get_data();
	for (size_t i = 0; i < this->Servers.size(); i++)
	{
		int sock_fd = this->socketserver(i); // create socket
    	this->bindserver(i); // bind socket
		this->listenserver(i); // listen socket
		std::cout << "========== created server ==========" << std::endl;
	}
	return 0;
}

void socket_server::inisialize_for_select()
{
	this->max_fd = 0;

    FD_ZERO(&this->readfds);
    FD_ZERO(&this->writefds);
	for(size_t i = 0; i < this->Servers.size(); i++)
    {
		// std::cout << "select_socket: " << this->Servers[i].get_sock_fd() << std::endl;
        FD_SET(this->Servers[i].get_sock_fd(), &this->readfds);
        if (this->Servers[i].get_sock_fd() > this->max_fd)
            this->max_fd = this->Servers[i].get_sock_fd();
    }
}

void socket_server::parse_request(char *buffer,int recv_ret)
{
	response res;
	std::string request = "";
	request = buffer;
	std::vector<std::string> tokens;

	int i = request.find("\r\n");
	while (i != std::string::npos)
	{
		tokens.push_back(request.substr(0, i));
		request.erase(0, i + 2);
		i = request.find("\r\n");
	}
	if(tokens.size() > 0)
	{
		std::string content_type = "";
		std::string content_length = "";
		std::string method = "";
		std::string request_type = "";
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i].find("Content-Type:") != std::string::npos)
			{
				std::string content_type_tmp = tokens[i];
				content_type_tmp = removespaces(content_type_tmp,' ');
				content_type = content_type_tmp.substr(tokens[i].find(":") + 1);
			}
			if(tokens[i].find("Content-Length:") != std::string::npos)
			{
				std::string content_length_tmp = tokens[i];
				content_length_tmp = removespaces(content_length_tmp,' ');
				content_length = content_length_tmp.substr(tokens[i].find(":") + 1);
			}
			if(tokens[i].find("HTTP/1.1") != std::string::npos)
			{
				std::stringstream ss(tokens[i]);
				std::string token;
				//========get method==========
				std::getline(ss, token, ' ');
				res.set_Request_Method(token);
				//========get path==========
				std::getline(ss, token, ' ');
				res.set_Request_Url(token);
				//========get request type==========
				std::getline(ss, token, ' ');
				res.set_Request_http_version(token);		
				// request_type = tokens[i];
			}
		}
		std::cout << "==========line one=============" << std::endl;
		std::cout << "    method    : " << res.get_Request_Method() << std::endl;
		std::cout << "     path     : " << res.get_Request_Url() << std::endl;
		std::cout << " http version : " << res.get_Request_http_version() << std::endl;
		std::cout << "==========line two=============" << std::endl;
		std::cout << " content_type : " << content_type << std::endl;
		std::cout << " content_length : " << content_length << std::endl;
	}
	std::cout << "==========line three=============" << std::endl;
	std::cout << " read_ret : " << recv_ret << std::endl;


	
	// find 
	
}

void socket_server::read_request(int i)
{
	char buffer[1024];
  	memset(buffer,'\0',1024);
	int recv_ret = recv(i, buffer, 1024, 0);
	// FD_CLR(i,&this->readfds);
	// FD_SET(i,&this->writefds);
	if (recv_ret == -1)
	{
		std::cout << "Error: recv()" << std::endl;
		return ;
	}
	if (recv_ret == 0)
	{
		std::cout << "Client " << i << " disconnected" << std::endl;
		FD_CLR(i, &this->readfds);
		close(i);
	}
	this->parse_request(buffer,recv_ret);
	// std::cout << buffer << std::endl;
}

void	socket_server::send_response(int i)
{
	char buffer1[] = "HTTP/1.1 200 OK\r\n"
					 "Content-Type: text/html\r\n"
					 "Connection: close\r\n"
					 "\r\n"
					 "<html><body><h1>amine ajdahin</h1></body></html>";
	int send_ret = send(i, buffer1, strlen(buffer1), 0);
	close(i);
	if (send_ret == -1)
	{
		std::cout << "Error: send()" << std::endl;
		return ;
	}
	std::cout << "sent to client " << i << std::endl;
	FD_CLR(i, &this->writefds);
}

void socket_server::accept_client(int i)
{
	int client_fd = accept(i, (struct sockaddr *)&this->Servers[i]._sockaddr, (socklen_t *)&this->Servers[i]._sockaddr_len);
	if (client_fd == -1)
	{
		std::cout << "Error: accept()" << std::endl;
		return ;
	}
	this->Servers[i].set_client_fd(client_fd);
	// std::cout << "accepted client " << i << std::endl;
	FD_SET(client_fd, &this->readfds);
	// FD_SET(client_fd, &writefds);
	if (client_fd > this->max_fd)
		this->max_fd = client_fd;
}

int socket_server::select_socket()
{
	this->inisialize_for_select();
    fd_set tmp_readfds, tmp_writefds;
	while(1)
    {
        tmp_readfds = this->readfds;
        tmp_writefds = this->writefds;
        int select_ret = select(this->max_fd + 1, &tmp_readfds, &tmp_writefds, NULL, NULL);
        if (select_ret == -1)
        {
            std::cout << "Error: select()" << std::endl;
            return -1;
        }
		for(size_t i = 0; i < this->max_fd + 1; i++)
        {
            if (FD_ISSET(i, &tmp_readfds))
            {
                if(this->checkservers(i,this->Servers) != -1)
					this->accept_client(i);
                else
                {
                  if(FD_ISSET(i, &this->readfds))
					this->read_request(i);
                  if(FD_ISSET(i,&this->writefds))
					this->send_response(i);
                }
            }
        }
	}
	return 0;
}