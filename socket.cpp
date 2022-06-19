#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#include <arpa/inet.h>

int main() {
  // Create a socket (IPv4, TCP)

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Listen to port 9999 on any address
  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  sockaddr.sin_port = htons(5056); // htons is necessary to convert a number to
                                   // network byte order
  if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cout << "Failed to bind to port 5050. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

        // Start listening. Hold at most 10 connections in the queue
        if (listen(sockfd, 10) < 0) {
            std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
            exit(EXIT_FAILURE);
        }
        // Grab a connection from the queue
          printf("\n+++++++ Waiting for new connection ++++++++\n\n");
          int addrlen = sizeof(sockaddr);
          int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
          if (connection < 0) {
              std::cout << "Accept fail. errno: " << errno << std::endl;
              exit(EXIT_FAILURE);
          }

          // Read from the connection
          char buffer[1024];
          int bytesRead = read(connection, buffer, 1024);
          printf("%s\n",buffer);
          // std::cout << "Read fail. errno: " << errno << std::endl;
          if (bytesRead < 0) {
              std::cout << "Read fail. errno: " << errno << std::endl;
              exit(EXIT_FAILURE);
          }
          // send(connection, hello.c_str(), hello.length(), 0);


          // Close the connections
          close(connection);
          close(sockfd);
}