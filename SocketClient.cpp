//
// Created by ahmed on 12/16/16.
//

#include "SocketClient.h"

#define BUF_LEN 50

/**
 * Creates a new client socket that connects to the specified server address and port
 * @param serverAddr Server Address
 * @param serverPort Port of the server
 */
SocketClient::SocketClient(char *serverAddr, unsigned short serverPort)
{
    memset(&endpoint, 0, sizeof(endpoint));

    endpoint.sin_family = AF_INET;
    endpoint.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverAddr, &endpoint.sin_addr) == -1)
    {
        log_error("Ip to network conversion");
    }
    if ((this->socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        log_error("socket creation");
    }


    timeval timeout;
    // Removing memset causes unidentified behaviour as the values are originally garbage
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = 3;

    if (!setsockopt(this->socketFd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeval)))
    {
        log_error("set receive timeout");
    }
    if (!setsockopt(this->socketFd, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeval)))
    {
        // Whatever we're sending might be locked, so a send timeout is set
        log_error("set send timeout");
    }
    isInitialized = true;
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
        cout << "Client:Sent " << num_bytes << " to UDP socket" << endl;
    }
    return num_bytes;
}

long int SocketClient::ReceivePacket(void recvHandler(char *msg, char *ip))
{

    if (!isInitialized)
    {
        fprintf(stderr, "An error occurred during initialization, can't call function ReceivePacket");
        exit(-1);
    }

    char buf[BUF_LEN] = {0};
    char host[NI_MAXHOST] = {0};

    long int num_bytes;
    sockaddr_storage remoteEP;
    socklen_t remoteEpLength;

    num_bytes = recvfrom(this->socketFd, buf, sizeof(buf), 0, (sockaddr *) &remoteEP, &remoteEpLength);

    // TODO Create a logger class
    //getnameinfo((struct sockaddr *) remoteEP, remoteEpLength, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
    getnameinfo((struct sockaddr *) &remoteEP, remoteEpLength, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
    //inet_ntop(((struct sockaddr *) &remoteEP)->sa_family, &(((struct sockaddr_in *) &remoteEP)->sin_addr), host,INET_ADDRSTRLEN);

    cout << "Remote ip:" << host << endl;

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
        // DEBUG
        cout << "Received " << num_bytes << " bytes" << endl;
        recvHandler(buf, host);
    }
    return num_bytes;
}

SocketClient::~SocketClient()
{
    if (!isInitialized)
    {
        return;
    }
    close(this->socketFd);
}
