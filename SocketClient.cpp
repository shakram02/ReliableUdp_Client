//
// Created by ahmed on 12/16/16.
//

#include "SocketClient.h"

/**
 * Creates a new client socket that connects to the specified server address and port
 * @param serverAddr Server Address
 * @param serverPort Port of the server
 */
SocketClient::SocketClient(char *serverAddr, int serverPort)
{
    struct addrinfo hints;
    struct addrinfo *serverinfo;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM; // UDP socket
    hints.ai_family = AF_INET;    // IPv4 Only
    hints.ai_flags = AI_PASSIVE;


    struct addrinfo *res;

    int err_status;

    // Constructs the sockaddr_in values and save me lots of time
    char *tempString = ToString(serverPort);
    if ((err_status = getaddrinfo(serverAddr, tempString, &hints, &serverinfo) != 0))
    {
        printf("getaddrinfo:%s", gai_strerror(err_status));
    }

    for (res = serverinfo; res != NULL; res = res->ai_next)
    {
        if ((socketFileDescriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
        {
            log_error("socket");
            continue;
        }
        break;
    }

    this->serverAddressInfo = CopyAddressInfo(res);
    freeaddrinfo(serverinfo);

    if ((socketFileDescriptor = socket(serverAddressInfo->ai_family, serverAddressInfo->ai_socktype,
            serverAddressInfo->ai_protocol)) == -1)
    {
        log_error("socket");
        exit(1);
    }
}

SocketClient::~SocketClient()
{
    close(this->socketFileDescriptor);
}

/**
 * Sends an array of bytes (unsigned char) to the server
 * @param bytes Message content to be sent
 * @return the number of bytes that were actually sent
 */
long int SocketClient::SendPacket(const unsigned char *bytes)
{
    // TODO create a max payload and chunkize the incoming byte array if necessary

    long int num_bytes;
    if ((num_bytes = sendto(socketFileDescriptor, bytes, sizeof(bytes), 0, serverAddressInfo->ai_addr,
            serverAddressInfo->ai_addrlen)) == -1)
    {
        log_error("send to server");
        exit(1);
    }
    else
    {
        printf("Client:Sent %ld bytes to server", num_bytes);
    }
    return num_bytes;
}


void log_error(const char *func_name)
{
    printf("%s:%s\n", func_name, strerror(errno));
}


char *ToString(int num)
{
    // Get the exact number of digits in num
    int digits, temp = num;
    do
    {
        digits++;
        temp /= 10;
    } while ((temp % 10) > 0);

    char *stringEquivalent = (char *) malloc(sizeof(char) * digits);
    sprintf(stringEquivalent, "%d", num);
    return stringEquivalent;
}


addrinfo *CopyAddressInfo(addrinfo *src)
{
    addrinfo *cpy = (addrinfo *) malloc(sizeof(addrinfo));
    memset(cpy, 0, sizeof(cpy));

    cpy->ai_addr = (sockaddr *) malloc(sizeof(src->ai_addr));
    cpy->ai_canonname = (char *) malloc(sizeof(src->ai_canonname));

    cpy->ai_addrlen = src->ai_addrlen;
    cpy->ai_family = src->ai_family;
    cpy->ai_flags = src->ai_flags;
    cpy->ai_protocol = src->ai_protocol;
    cpy->ai_socktype = src->ai_socktype;

    if (src->ai_addr != NULL)
    {
        memcpy(cpy->ai_addr, src->ai_addr, sizeof(src->ai_addr));
    }

    if (src->ai_canonname != NULL)
    {
        memcpy(cpy->ai_canonname, src->ai_canonname, sizeof(src->ai_canonname));
    }
    return cpy;
}