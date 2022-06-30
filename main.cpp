#include "socket.hpp"

int main()
{
    socket_server server;
    server.create_socket();
	  server.select_socket();
    return 0;
}