//
// Created by ahmed on 12/16/16.
//


#ifndef ENHANCEDUDPCLIENT_SOCKETCLIENT_H
#define ENHANCEDUDPCLIENT_SOCKETCLIENT_H

extern "C"
{
#include "./libs/netutils.h"
};

#include <iostream>
#include <cstdlib>

using namespace std;

class SocketClient
{
public:

    /**
    * Creates a new client socket that connects to the specified server address and port
    * @param serverAddr Server Address
    * @param serverPort Port of the server
    */
    SocketClient(char *serverAddr, unsigned short serverPort);


    /**
    * Sends an array of bytes (unsigned char) to the server
    * @param bytes Message content to be sent
    * @return the number of bytes that were actually sent
    */
    long int SendPacket(const unsigned char *bytes);

    long int ReceivePacket(void recvHandler(char *msg, char *ip));

    ~SocketClient();

private:

    /**
     * File descriptor for the open socket
     */
    int socketFd;
    bool isInitialized = false;
    sockaddr_in endpoint;
};

#endif //ENHANCEDUDPCLIENT_SOCKETCLIENT_H
