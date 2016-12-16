//
// Created by ahmed on 12/16/16.
//

#include "SocketClient.h"


int SocketClient::SendPacket(unsigned char *bytes)
{

}

void log_error(const char *func_name)
{
    printf("%s:%s\n", func_name, strerror(errno));
}

SocketClient::SocketClient(char *serverAddr, char *serverPort)
{
    struct addrinfo hints;
    struct addrinfo *serverinfo;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM; // UDP socket
    hints.ai_family = AF_INET;    // IPv4 Only
    hints.ai_flags = AI_PASSIVE;

    int sockfd;
    struct addrinfo *res;
    char ipstr[INET_ADDRSTRLEN];

    int err_status;

    // Constructs the sockaddr_in values and save me lots of time
    if ((err_status = getaddrinfo(serverAddr, serverPort, &hints, &serverinfo) != 0))
    {
        printf("getaddrinfo:%s", gai_strerror(err_status));
    }

    for (res = serverinfo; res != NULL; res = res->ai_next)
    {
        if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
        {
            log_error("socket");
            continue;
        }
        break;
    }


    if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    {
        log_error("socket");
        exit(1);
    }

    char *buff = "hey!,you";
    int num_bytes;
    if ((num_bytes = sendto(sockfd, buff, strlen(buff), 0, res->ai_addr, res->ai_addrlen)) == -1)
    {
        log_error("send to server");
        exit(1);
    }
    printf("Client:Sent %d bytes to server", num_bytes);

    freeaddrinfo(serverinfo);
}

addrinfo *CopyAddrInfo(addrinfo *source)
{

}

