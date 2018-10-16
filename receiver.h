#ifndef RECEIVER_H
#define RECEIVER_H
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

extern int server_fd, new_socket, valread;

class receiver
{
public:
    receiver();
};

#endif // RECEIVER_H
