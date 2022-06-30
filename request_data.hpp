/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_data.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:19:52 by majdahim          #+#    #+#             */
/*   Updated: 2022/06/30 20:20:50 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class response
{
    private:
        std::string  _Request_Url; // path url exemle 127.0.0.1:8080/index.html
        std::string  _Request_Method; // GET POST PUT DELETE etc.
        std::string  _Request_Body; // Path body exemle ./index.html
        std::string  _Request_Header;
        std::string  _Request_qwery; // Data sent in the url exemle ?name=amine&age=20
        std::string  _Request_http_version; // http version exemle 1.1
    public:
        response();
        ~response();
        void set_Request_Url(std::string url);
        void set_Request_Method(std::string method);
        void set_Request_Body(std::string body);
        void set_Request_Header(std::string header);
        void set_Request_qwery(std::string qwery);
        void set_Request_http_version(std::string http_version);
        std::string get_Request_Url();
        std::string get_Request_Method();
        std::string get_Request_Body();
        std::string get_Request_Header();
        std::string get_Request_qwery();
        std::string get_Request_http_version();
        char    *buffer();
};
response::response()
{
    _Request_Url = "";
    _Request_Method = "HTTP/1.1 200 OK\r\n";
    _Request_Body = "\r\n"
                    "<html><body><h1>amine ajdahin</h1></body></html>";
    _Request_Header = "Content-Type: text/html\r\n"
                     "Connection: close\r\n";
    _Request_qwery = "";
}

char*    response::buffer()
{
    char* buffer;
    std::string help;

    buffer = new char[_Request_Method.size() + _Request_Header.size() + _Request_Body.size()];
    help = _Request_Method + _Request_Header + _Request_Body;
    std::strcpy(buffer, help.c_str());

    return (buffer);
}

response::~response()
{
}

void response::set_Request_Url(std::string url)
{
    _Request_Url = url;
}

void response::set_Request_Method(std::string method)
{
    _Request_Method = method;
}
void    response::set_Request_Body(std::string body)
{
    _Request_Body = body;
}
void    response::set_Request_Header(std::string header)
{
    _Request_Header = header;
}
void    response::set_Request_qwery(std::string qwery)
{
    _Request_qwery = qwery;
}
void    response::set_Request_http_version(std::string http_version)
{
    _Request_http_version = http_version;
}
std::string response::get_Request_Url()
{
    return _Request_Url;
}
std::string response::get_Request_Method()
{
    return _Request_Method;
}
std::string response::get_Request_Body()
{
    return _Request_Body;
}
std::string response::get_Request_Header()
{
    return _Request_Header;
}
std::string response::get_Request_qwery()
{
    return _Request_qwery;
}
std::string response::get_Request_http_version()
{
    return _Request_http_version;
}
