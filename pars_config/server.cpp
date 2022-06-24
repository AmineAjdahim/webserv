/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:20:02 by majdahim          #+#    #+#             */
/*   Updated: 2022/06/20 18:41:21 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(void)
{
}
Server::~Server(void)
{
}

std::string removespaces(std::string str,char c)
{
    str.erase(remove(str.begin(),str.end(), c),str.end());
    return (str);
}

std::vector<Server> Server::get_data(void)
{
    std::vector<Server> servers;
    int i = 0;
     std::ifstream config_file;
    config_file.open("config.conf");
    if(!config_file)
    {
        std::cout << "Error: config file not found" << std::endl;
        exit(1);
    }
    std::string line_config_file;
    while(std::getline(config_file,line_config_file))
    {
    Server server;
        if(line_config_file == "Server {")
        {
            while(std::getline(config_file,line_config_file))
            {
                if(line_config_file.find("port") != std::string::npos)
                {
                    std::string port = line_config_file;
                    port = removespaces(port, ' ');
                    std::string _port = port.substr(port.find(":") +1);
                    _port.pop_back();
                    server.set_port(_port);
                    // _port = port;
                }
                else if(line_config_file.find("host") != std::string::npos)
                {
                    std::string ip = line_config_file;
                    ip = removespaces(ip, ' ');
                    std::string _ip = ip.substr(ip.find(":") +1);
                    _ip.pop_back();
                    server.set_ip(_ip);
                    // _port = port;
                }
                else if(line_config_file.find("client_max_body_size") != std::string::npos)
                {
                    std::string client_max_body_size = line_config_file;
                    client_max_body_size = removespaces(client_max_body_size, ' ');
                    std::string _client_max_body_size = client_max_body_size.substr(client_max_body_size.find(":") +1);
                    _client_max_body_size.pop_back();
                    server.set_client_max_body_size(_client_max_body_size);
                    // _port = port;
                }
                else if (line_config_file.find("location start :") != std::string::npos)
                {
                    _location loc ;
                    while(std::getline(config_file,line_config_file))
                    {
                        if(line_config_file.find("path") != std::string::npos)
                        {
                            std::string path = line_config_file;
                            path = removespaces(path, ' ');
                            loc.set_path(path.substr(path.find(":") +1));
                            
                        }
                        else if(line_config_file.find("root") != std::string::npos)
                        {
                            std::string root = line_config_file;
                            root = removespaces(root, ' ');
                            loc.set_root(root.substr(root.find(":") +1));
                        }
                        else if(line_config_file.find("upload") != std::string::npos)
                        {
                            std::string upload = line_config_file;
                            upload = removespaces(upload, ' ');
                            loc.set_upload(upload.substr(upload.find(":") +1));
                        }
                        else if(line_config_file.find("cgi") != std::string::npos)
                        {
                            std::string cgi = line_config_file;
                            cgi = removespaces(cgi, ' ');
                            loc.set_cgi(cgi.substr(cgi.find(":") +1));
                        }
                        else if(line_config_file.find("auto_index") != std::string::npos)
                        {
                            std::string auto_index = line_config_file;
                            auto_index = removespaces(auto_index, ' ');
                            loc.set_auto_index(auto_index.substr(auto_index.find(":") +1));
                        }
                        else if(line_config_file == "        location end:")
                        {
                            server._locations.push_back(loc);
                            // servers.push_back(server);
                            break;
                        }
                    }
                }
                else if(line_config_file == "}"){
                    servers.push_back(server);
                    break;
                    
                }
            }
        }
    }
    return (servers);
}

// int main()
// {
//     Server server;
//     std::vector<Server> servers = server.get_data();
//     for (size_t i = 0; i < servers.size(); i++)
//     {
//     std::cout << "===============================" << std::endl;
//     std::cout << "           " << "Server : " << i << "            " << std::endl;
//     std::cout << "           " << "-------------"<< "            " << std::endl;
//         std::cout << "host = " << servers[i].get_ip() << std::endl;
//         std::cout << "port = "<<  servers[i].get_port() << std::endl;
//         std::cout << "client_max_body_size = " << servers[i].get_client_max_body_size() << std::endl;
//         // std::cout << server._locations[1]->get_path()<< std::endl;
//         for (size_t j = 0; j < servers[i]._locations.size(); j++)
//         {
//             std::cout << "       _________" << "location : " << j << "_________" << std::endl;
//             std::cout << "path = " << servers[i]._locations[j].get_path()<< std::endl;
//             std::cout << "root = " << servers[i]._locations[j].get_root()<< std::endl;
//             std::cout << "upload = " << servers[i]._locations[j].get_upload()<< std::endl;
//             std::cout << "cgi = " << servers[i]._locations[j].get_cgi()<< std::endl;
//             std::cout << "auto_index = " << servers[i]._locations[j].get_auto_index()<< std::endl;
//         }
//     }
//     return (0);
// }