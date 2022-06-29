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


int checkservers(int c ,std::vector<Server> servers)
{
  // Server server;
  // std::vector<Server> servers = server.get_data();
  for (int i = 0; i < servers.size(); i++)
  {
    if ((servers)[i].get_sock_fd() == c)
    {
      return i;
    }
  } 
  // for (int i = 0; i < servers.; i++)
  // {
  //   if (servers[i].get_sock_fd() == i)
  //   {
  //     return i;
  //   }
  // }
  return -1;
}


int main()
{
  Server server;
  std::vector<Server> servers = server.get_data();
  // Create a socket (IPv4, TCP)

  //  for (size_t i = 0; i < servers.size(); i++)
  //   {
  //   std::cout << "===============================" << std::endl;
  //   std::cout << "           " << "Server : " << i << "            " << std::endl;
  //   std::cout << "           " << "-------------"<< "            " << std::endl;
  //       std::cout << "host = " << servers[i].get_ip() << std::endl;
  //       std::cout << "port = "<<  servers[i].get_port() << std::endl;
  //       std::cout << "client_max_body_size = " << servers[i].get_client_max_body_size() << std::endl;
  //       // std::cout << server._locations[1]->get_path()<< std::endl;
  //       for (size_t j = 0; j < servers[i]._locations.size(); j++)
  //       {
  //           std::cout << "       _________" << "location : " << j << "_________" << std::endl;
  //           std::cout << "path = " << servers[i]._locations[j].get_path()<< std::endl;
  //           std::cout << "root = " << servers[i]._locations[j].get_root()<< std::endl;
  //           std::cout << "upload = " << servers[i]._locations[j].get_upload()<< std::endl;
  //           std::cout << "cgi = " << servers[i]._locations[j].get_cgi()<< std::endl;
  //           std::cout << "auto_index = " << servers[i]._locations[j].get_auto_index()<< std::endl;
  //       }
  //   }

  std::cout << "===============================" << std::endl;
  fd_set current_socket, read_socket;

  for (size_t i = 0; i < servers.size(); i++)
  {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
      perror("socket");
      exit(EXIT_FAILURE);
    }
    servers[i].set_sock_fd(sockfd);
    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(servers[i].get_port().c_str()));
    sockaddr.sin_addr.s_addr = inet_addr(servers[i].get_ip().c_str());
    servers[i]._sockaddr = sockaddr;
    servers[i]._sockaddr_len = sizeof(sockaddr);
    if (bind(sockfd, (struct sockaddr *)&servers[i]._sockaddr, servers[i]._sockaddr_len) == -1)
    {
      perror("bind");
      exit(EXIT_FAILURE);
    }
    {
      std::cout << "Failed to bind " << errno << std::endl;
      exit(EXIT_FAILURE);
    }
    // std::cout << servers[i].get_ip() << ":" << servers[i].get_port() << std::endl;
    if (listen(sockfd, 50) < 0)
    {
      std::cout << "Failed to listen " << errno << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  fd_set copyread_socket, copycurrent_socket;
  // std::cout << servers.back().get_sock_fd() << std::endl;
  int max_fd = -1;

    FD_ZERO(&copyread_socket);
    FD_ZERO(&copycurrent_socket);
    FD_ZERO(&current_socket);
    FD_ZERO(&read_socket);
    for (size_t i = 0; i < servers.size(); i++)
    {
      FD_SET(servers[i].get_sock_fd(), &copyread_socket);
      if(servers[i].get_sock_fd() > max_fd)
      {
        max_fd = servers[i].get_sock_fd();
      }
    }

  while (1)
  {
    read_socket = copyread_socket;
    current_socket = copycurrent_socket;
    int ret = select(max_fd + 1, &read_socket, &current_socket, NULL, NULL);
    if(ret == -1)
    {
      std::cout << "select error" << std::endl;
      exit(EXIT_FAILURE);
    }
    char buffer[1024];
    for (size_t i = 0; i < max_fd +1; i++)
    {
      if(FD_ISSET(i, &read_socket) || FD_ISSET(i, &current_socket))
      {
       
          if(checkservers(i,servers) != -1)
          {
            int client_sockfd = accept(i, NULL, NULL);
            // 
            if (client_sockfd == -1)
            {
              perror("accept");
              exit(EXIT_FAILURE);
            }
            // servers[].set_client_fd(client_sockfd);
            FD_SET(client_sockfd, &copycurrent_socket);
            if(client_sockfd > max_fd)
            {
              max_fd = client_sockfd;
            }
            std::cout << "New client connected" << std::endl;
          }
          else
          {
            if(FD_ISSET(i, &copycurrent_socket))
            {
              int rc = read(i, buffer,1024);
              if (rc == -1)
              {
                perror("recv");
                exit(EXIT_FAILURE);
              }
              if (rc == 0)
              {
                std::cout << "Client disconnected" << std::endl;
                FD_CLR(i, &copycurrent_socket);
                // FD_CLR(i, &copycurrent_socket);
                close(i);
              }
              else
              {
                std::cout << "Received " << rc << " bytes" << std::endl;
                std::cout << "Received : " << buffer << std::endl;
                // std::cout << "Received : " << buffer << std::endl;
              }
              

            }
          
        }
      }
    }
     
  }



}
    // for (size_t i = 0; i < servers.size(); i++)
    // {
    //   if (FD_ISSET(servers[i].get_sock_fd(), &current_socket))
    //   {
    //     char buffer[1024];
    //     int n = read(servers[i].get_sock_fd(), buffer, 1024);
    //     if (n == 0)
    //     {
    //       std::cout << "Client disconnected" << std::endl;
    //       close(servers[i].get_sock_fd());
    //     }
    //     else if (n < 0)
    //     {
    //       perror("read");
    //       exit(EXIT_FAILURE);
    //     }
    //     else
    //     {
    //       std::cout << "Received " << n << " bytes" << std::endl;
    //       std::cout << "Data: " << buffer << std::endl;
    //     }
    //   }
    // }



  //   for(size_t i = 0; i < servers.size(); i++)
  //   {
  //     FD_SET(servers[i].get_sock_fd(), &copyread_socket);
  //     FD_SET(servers[i].get_sock_fd(), &copycurrent_socket);
  //   }
  //   read_socket = copyread_socket;
  //   current_socket = copycurrent_socket;
  //   // for (size_t i = 0; i < servers.size(); i++)
  //   // {
  //   //   FD_SET(servers[i].get_sock_fd(), &read_socket);
  //   // }
  //   int max_fd = FD_SETSIZE;
  //    if(int rt = select(FD_SETSIZE , &read_socket, &current_socket, NULL, NULL) < 0)
  //   {
  //     std::cout << "Failed to select " << errno << std::endl;
  //     exit(EXIT_FAILURE);
  //   }
  //   std::cout << "servers        :" << servers.size() << std::endl;
    // for (size_t i = 0; i < servers.size(); i++)
    // {
    //   if (FD_ISSET(servers[i].get_sock_fd(), &read_socket))
    //   {

    //       // std::cout << "===============================" << std::endl;
    //     std::cout << "           " << "Server : " << i << "            "<< servers[i].get_sock_fd() <<  << std::endl;
        
    //     // int client_sockfd = accept(servers[i].get_sock_fd(), NULL, NULL);
    //     // if (client_sockfd == -1)
    //     // {
    //     //   perror("accept");
    //     //   exit(EXIT_FAILURE);
    //     // }
    //     // FD_SET(client_sockfd, &current_socket);
    //     // if (client_sockfd > max_fd)
    //     // {
    //     //   max_fd = client_sockfd;
    //     // }
    //     // std::cout << "Client connected" << std::endl;
    //     // std::cout << " " << std::endl;
    //     // char buffer[1024];
    //     // int n = read(client_sockfd, buffer, 1024);
    //     // if (n == -1)
    //     // {
    //     //   perror("read");
    //     //   exit(EXIT_FAILURE);
    //     // }
    //     // // std::cout << " " << buffer << std::endl;
    //     // // std::cout << " " << buffer << std::endl;
    //     // std::cout << "Client request : " << buffer << std::endl;
    //     // std::cout << " " << std::endl;
    //     // std::cout << " " << std::endl;
        char buffer1[] = "HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/html\r\n"
                         "Connection: close\r\n"
                         "\r\n"
                         "<html><body><h1>amine ajdahin</h1></body></html>";
        // send(client_sockfd, buffer1, strlen(buffer1), 0);
    //   }
    // }
  // }
// }