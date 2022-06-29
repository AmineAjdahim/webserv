#include "pars_config/server.hpp"
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
 #include <fcntl.h>

int checkservers(int c ,std::vector<Server> servers)
{
  for (int i = 0; i < servers.size(); i++)
  {
    if (servers[i].get_sock_fd() == c)
    {
      return c;
    }
  }
  return -1;
}

int main()
{
    Server server;
    std::vector<Server> servers = server.get_data();
    // Create a socket (IPv4, TCP)
    for(size_t i = 0; i < servers.size(); i++)
    {
       int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
         if (sock_fd == -1)
         {
            std::cout << "Error: socket()" << std::endl;
            return -1;
         }
        if(fcntl(sock_fd, F_SETFL, O_NONBLOCK) == -1)
        {
            std::cout << "Error: fcntl()" << std::endl;
            return -1;
        }
            // Bind the socket to a port
        sockaddr_in sockaddr;
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(atoi(servers[i].get_port().c_str()));
        sockaddr.sin_addr.s_addr = inet_addr(servers[i].get_ip().c_str());
        servers[i]._sockaddr = sockaddr;
        servers[i]._sockaddr_len = sizeof(sockaddr);
        int bind_ret = bind(sock_fd, (struct sockaddr *)&servers[i]._sockaddr, servers[i]._sockaddr_len);
        if (bind_ret == -1)
        {
            std::cout << "Error: bind()" << std::endl;
            return -1;
        }
        servers[i].set_sock_fd(sock_fd);
        int listen_ret = listen(sock_fd, 5);
        if (listen_ret == -1)
        {
            std::cout << "Error: listen()" << std::endl;
            return -1;
        }
        std::cout << "created server " << servers[i].get_sock_fd() << std::endl;
    }
    int max_fd = 0;
    fd_set readfds, writefds;
    fd_set tmp_readfds, tmp_writefds;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&tmp_readfds);
    FD_ZERO(&tmp_writefds);
    for(size_t i = 0; i < servers.size(); i++)
    {
        FD_SET(servers[i].get_sock_fd(), &readfds);
        if (servers[i].get_sock_fd() > max_fd)
            max_fd = servers[i].get_sock_fd();
    }
    while(1)
    {
        tmp_readfds = readfds;
        tmp_writefds = writefds;
        int select_ret = select(max_fd + 1, &tmp_readfds, &tmp_writefds, NULL, NULL);
        if (select_ret == -1)
        {
            std::cout << "Error: select()" << std::endl;
            return -1;
        }
        char buffer[1024];
        for(size_t i = 0; i < max_fd + 1; i++)
        {
            if (FD_ISSET(i, &tmp_readfds))
            {
                if(checkservers(i,servers) != -1)
                {
                  // std::cout << "server " << i << " is ready" << std::endl;
                  int client_fd = accept(i, (struct sockaddr *)&servers[i]._sockaddr, (socklen_t *)&servers[i]._sockaddr_len);
                  if (client_fd == -1)
                  {
                      std::cout << "Error: accept()" << std::endl;
                      return -1;
                  }
                  servers[i].set_client_fd(client_fd);
                  std::cout << "accepted client " << i << std::endl;
                  FD_SET(client_fd, &readfds);
                    // FD_SET(client_fd, &writefds);
                  if (client_fd > max_fd)
                      max_fd = client_fd;
                }
                else
                {
                  if(FD_ISSET(i, &readfds))
                  {
                    int recv_ret = recv(i, buffer, 1024, 0);
                    // FD_CLR(i,&readfds);
                    // FD_SET(i,&writefds);
                    if (recv_ret == -1)
                    {
                        std::cout << "Error: recv()" << std::endl;
                        return -1;
                    }
                    if (recv_ret == 0)
                    {
                        std::cout << "Client " << i << " disconnected" << std::endl;
                        FD_CLR(i, &readfds);

                        close(i);
                    }
                    std::cout << buffer << std::endl;
                    memset(buffer,0,1024);
                  }
                  if(FD_ISSET(i,&writefds))
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
                        return -1;
                    }
                    std::cout << "sent to client " << i << std::endl;
                    FD_CLR(i, &writefds);
                  }
                }
            }
        }
    }
}