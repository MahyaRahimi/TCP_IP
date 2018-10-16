#ifndef LISTENER2_H
#define LISTENER2_H
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

extern int server_fd, new_socket, valread;

class listener2
{
public:
    listener2();
};

#endif // LISTENER2_H
