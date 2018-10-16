#ifndef SENDER_H
#define SENDER_H
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

extern int server_fd, new_socket, valread;

class sender
{
public:
    sender();
};

#endif // SENDER_H
