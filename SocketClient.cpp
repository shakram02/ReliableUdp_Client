//
// Created by ahmed on 12/16/16.
//

#include "SocketClient.h"


/**
 * Creates a new client socket that connects to the specified server address and port
 * @param serverAddr Server Address
 * @param serverPort Port of the server
 */
SocketClient::SocketClient(char *serverAddr, unsigned short serverPort)
{

    int s, i, slen = sizeof(endpoint);
    memset(&endpoint, 0, sizeof(endpoint));

    endpoint.sin_family = AF_INET;
    endpoint.sin_port = htons(serverPort);

    // Fill the sin_addr using pton
    if (inet_pton(AF_INET, serverAddr, &endpoint.sin_addr) == -1)
    {
        log_error("Ip to network conversion");
    }
    if ((this->socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        log_error("socket creation");
    }


    timeval timeout;
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = 3;

    if (!setsockopt(this->socketFd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeval)))
    {
        log_error("set receive timeout");
    }
    if (!setsockopt(this->socketFd, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeval)))
    {
        log_error("set send timeout");
    }
    isInitialized = true;
}

SocketClient::~SocketClient()
{
    if (!isInitialized)
    {
        return;
    }
    close(this->socketFd);
}

/**
 * Sends an array of bytes (unsigned char) to the server
 * @param bytes Message content to be sent
 * @return the number of bytes that were actually sent
 */
long int SocketClient::SendPacket(const unsigned char *bytes)
{
    if (!isInitialized)
    {
        fprintf(stderr, "An error occurred during initialization, can't call function SendPacket");
        return -1;
    }

    // TODO create a max payload and chunkize the incoming byte array if necessary

    long int num_bytes;
    if ((num_bytes = sendto(socketFd, bytes, sizeof(bytes), 0, (sockaddr *) &endpoint, sizeof(endpoint))) == -1)
    {
        log_error("send to server");
        exit(1);
    }
    else
    {
        printf("Client:Sent %ld bytes to UDP socket\n", num_bytes);
    }
    return num_bytes;
}

long int SocketClient::ReceivePacket(unsigned char buff[])
{
    if (!isInitialized)
    {
        fprintf(stderr, "An error occurred during initialization, can't call function ReceivePacket");
        exit(-1);
    }
    const int buffLen = 512;
    char buf[buffLen];
    // TODO receive with timeout
    long int num_bytes;
    sockaddr remoteEP;
    socklen_t remoteEpLength;

    num_bytes = recvfrom(this->socketFd, buf, sizeof(buf), 0, &remoteEP, &remoteEpLength);
    // TODO Create a logger class

    if (num_bytes == 0)
    {
        // TODO client closed connection

        return 0;
    }
    else if (num_bytes == -1)
    {
        // TODO Log error
        log_error("timeout");
        return -1;
    }
    else
    {
        printf("Received %d bytes\n", num_bytes);
    }

}

