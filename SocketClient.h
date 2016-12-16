//
// Created by ahmed on 12/16/16.
//

#include<stdio.h>
#include <sys/socket.h>
#include <unistd.h>
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
    /**
    * Sends an array of bytes (unsigned char) to the server
    * @param bytes Message content to be sent
    * @return the number of bytes that were actually sent
    */
    long int SendPacket(const unsigned char *bytes);

    /**
    * Creates a new client socket that connects to the specified server address and port
    * @param serverAddr Server Address
    * @param serverPort Port of the server
    */
    SocketClient(char *serverAddr, int serverPort);

    ~SocketClient();

private:

    /**
     * File descriptor for the open socket
     */
    int socketFileDescriptor;

    addrinfo *serverAddressInfo;
};

/**
 * Logs the errorno to output stream
 * @param func_name name of the function that caused the error
 */
void log_error(const char *);

/**
 * Converts the given integer number to a string
 * @param num number to be converted
 * @return String equivalent
 */
char *ToString(int);

/**
 * Copies Address info object to another one
 * @param src Source Address info object
 * @return Copy of src
 */
addrinfo *CopyAddressInfo(addrinfo *src);


#endif //ENHANCEDUDPCLIENT_SOCKETCLIENT_H
