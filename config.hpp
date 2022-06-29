/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:03:41 by majdahim          #+#    #+#             */
/*   Updated: 2022/06/28 16:18:47 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib>      // For exit() and EXIT_FAILURE
#include <iostream>     // For cout
#include <unistd.h>     // For read
#include <arpa/inet.h>
// #include "pars_config/server.hpp"
#include <sys/select.h>
#include <sys/time.h>

class   _location {
    private:
        std::string _path;
        std::string _root;
        std::string _upload;
        std::string _cgi;
        std::string _auto_index;
    public:
        _location(void){};
        ~_location(){};
        void set_path(std::string path){
            this->_path = path;
        }
        std::string get_path(void)
        {
            return (this->_path);
        }
        void set_root(std::string root){
            this->_root = root;
        }
        std::string get_root(void)
        {
            return (this->_root);
        }
        void set_upload(std::string upload){
            this->_upload = upload;
        }
        std::string get_upload(void)
        {
            return (this->_upload);
        }
        std::string get_cgi(void)
        {
            return (this->_cgi);
        }
        void set_cgi(std::string cgi)
        {
            this->_cgi = cgi;
        }
        void set_auto_index(std::string auto_index)
        {
            this->_auto_index = auto_index;
        }
        std::string get_auto_index(void)
        {
            return (this->_auto_index);
        }  
};


class Config
{
public:
    // typedef struct S_sockaddr_in {
    //     sockaddr_in sockaddr;
    //     sockaddr.sin_family
    // } t_sockaddr_in;
    std::string _port;
    std::string _ip;
    std::vector<_location *> _locations;
    std::string _client_max_body_size;
    sockaddr_in _sockaddr;
    int _sockaddr_len;

    Config(void);
    virtual ~Config(void);
    void add_location(std::string path);
    void set_port(std::string port);
    void set_ip(std::string ip);
    void set_client_max_body_size(std::string client_max_body_size);
    std::string get_client_max_body_size(void);
    std::string get_ip(void);
    std::string get_port(void);
    int _sock_fd;
    void set_sock_fd(int sock_fd);
    int get_sock_fd(void);
    int _client_fd;
    void set_client_fd(int client_fd);
    int get_client_fd(void);
    // t_sockaddr_in _sock_addr;
    
    
    // _location get_location(void);
};