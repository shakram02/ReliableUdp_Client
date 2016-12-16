//
// Created by ahmed on 12/16/16.
//

#include<stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <memory.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstdlib>


#ifndef ENHANCEDUDPCLIENT_SOCKETCLIENT_H
#define ENHANCEDUDPCLIENT_SOCKETCLIENT_H


class SocketClient
{
public:
    int SendPacket(unsigned char *bytes);

    SocketClient(char *serverAddr, char *serverPort);


};


#endif //ENHANCEDUDPCLIENT_SOCKETCLIENT_H
