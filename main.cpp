#include <sys/socket.h>

int server_fd = socket(AF_INET, SOCK_STREAM, 0);
if(server_fd < 0)
{
    perror("socket");
    exit(1);
}

#include <sys/socket.h> 

struct sockaddr_in address;
const int PORT = 8080;
memset((char *)&address, 0, sizeof(address)); 
address.sin_family = AF_INET; 
address.sin_addr.s_addr = htonl(INADDR_ANY); 
address.sin_port = htons(PORT); 
if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0) 
{ 
    perror("bind failed"); 
    return 0; 
}