/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:10:47 by majdahim          #+#    #+#             */
/*   Updated: 2022/06/25 19:40:27 by majdahim         ###   ########.fr       */
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


#include <sys/types.h>


#include <unistd.h>

class socket_server : public Server
{
private:
public:

    socket_server(/* args */);
    ~socket_server();
    int create_socket();
    void bind_socket(int sockfd, sockaddr_in sockaddr);
    void listen_socket(int sockfd);
    void setup_server();
    int accept_new_client(int sockfd);
    void handle_client(int sockfd);
    
};
