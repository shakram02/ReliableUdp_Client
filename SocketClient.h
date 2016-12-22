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
    SocketClient(const string &serverAddr, const unsigned short serverPort);


    /**
    * Sends an array of bytes (unsigned char) to the server
    * @param bytes Message content to be sent
    * @return the number of bytes that were actually sent
    */
    void SendPacket(const char *bytes, unsigned int dataSize);

/**
 * This function receives only 1 packet, when an attempt is made to connect to the server
 * a handshake message is sent, then the server redirects the client to another port
 * if a receive operation times out, this function will report to the caller
 * @param recvHandler
 * @return
 */
    long int ReceivePacket(void recvHandler(char *msg));

    ~SocketClient();

    int HandshakeServer(string &handshake);

private:

    void InitializeSocket(const unsigned short serverPort);

    /**
     * File descriptor for the open socket
     */
    int socketFd;
    bool isInitialized = false;
    sockaddr_in endpoint;
    string serverAddr;

    void SwitchToRedirectedSocket(char *message);


};

#endif //ENHANCEDUDPCLIENT_SOCKETCLIENT_H
