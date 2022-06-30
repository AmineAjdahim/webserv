/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:10:47 by majdahim          #+#    #+#             */
/*   Updated: 2022/06/30 21:00:16 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib>      // For exit() and EXIT_FAILURE
#include <iostream>     // For cout
#include <unistd.h>     // For read
#include <arpa/inet.h>
#include "pars_config/server.hpp"
#include <sys/select.h>
#include <sys/time.h>

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

#include <sys/types.h>

#include <fcntl.h>
#include <unistd.h>
#include <iostream>

class socket_server : public Server
{
private:

public:
    int max_fd;
    void set_max_fd(int max_fd);
    int get_max_fd();
    fd_set readfds, writefds;

    socket_server(/* args */);
    ~socket_server();
    std::vector<Server> Servers;
    int socketserver(int i); // create socket server
    int bindserver(int i); // bind socket server 
    int listenserver(int i); // listen socket server
    void inisialize_for_select(); // inisialize socket server
    void read_request(int i); // read request from socket server
    void send_response(int i); // response to socket server
    void accept_client(int i); // accept client from socket server
    void parse_request(char *buffer,int recv_ret); // parse request from socket server
    
    int create_socket(void);
    int select_socket(void);
    int checkservers(int c,std::vector<Server> servers);
    std::string removespaces(std::string str,char c);
    
};
