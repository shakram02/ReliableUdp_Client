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
#include <vector>

using namespace std;
typedef long int FileSize;

class SocketClient
{
public:

    /**
    * Creates a new client socket that connects to the specified server address and port
    * @param server_addr Server Address
    * @param server_port Port of the server
    */
    SocketClient(const string &server_addr, const unsigned short server_port,
            void recv_callback(char *chunk, long chunk_size));


    /**
    * Sends an array of bytes (unsigned char) to the server
    * @param data Message content to be sent
    * @return the number of bytes that were actually sent
    */
    void SendPacket(vector<char> &data);

/**
 * This function receives only 1 packet, when an attempt is made to connect to the server
 * a handshake message is sent, then the server redirects the client to another port
 * if a receive operation times out, this function will report to the caller
 * @param recvHandler
 * @return
 */
    long int ReceivePacket();

    ~SocketClient();

    int HandshakeServer(string &handshake);

private:

    void InitializeSocket(const unsigned short server_port);

    /**
     * File descriptor for the open socket
     */
    int socket_fd = 0;
    unsigned long int totalReceivedBytes = 0;
    bool is_initialized = false;
    sockaddr_in endpoint;
    string server_addr;

    void (*recv_handler)(char *chunk, long chunk_size);

    void SwitchToRedirectedSocket(char *message);


};

#endif //ENHANCEDUDPCLIENT_SOCKETCLIENT_H
