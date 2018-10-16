#ifndef LISTENER_H
#define LISTENER_H
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

extern int server_fd, new_socket, valread;

class listener
{
public:
    listener();

};

#endif // LISTENER_H
