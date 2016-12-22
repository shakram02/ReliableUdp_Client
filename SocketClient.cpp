//
// Created by ahmed on 12/16/16.
//

#include "SocketClient.h"

#define BUF_LEN 256
#define WELCOME_HEADER "redirect"

/**
 * Creates a new client socket that connects to the specified server address and port
 * @param serverAddr Server Address
 * @param serverPort Port of the server
 */
SocketClient::SocketClient(const string &serverAddr, const unsigned short serverPort)
{

    this->serverAddr = string(serverAddr);
    InitializeSocket(serverPort);
    isInitialized = true;
}


/**
 * Sends an array of bytes (unsigned char) to the server
 * @param bytes Message content to be sent ( reason for char* )
 * @return the number of bytes that were actually sent
 */
long int SocketClient::SendPacket(const char *bytes, unsigned int dataSize)
{
    if (!isInitialized) {
        fprintf(stderr, "An error occurred during initialization, can't call function SendPacket");
        return -1;
    }

    // TODO create a max payload and chunkize the incoming
    // byte array if necessary (an upper class responsibility)

    long int num_bytes;
    if ((num_bytes = sendto(socketFd, bytes, dataSize, 0, (sockaddr *) &endpoint, sizeof(endpoint))) == -1) {
        log_error("send to server");
        exit(1);
    } else {
        cout << "Client:Sent " << num_bytes << " bytes to UDP socket" << endl;
    }
    return num_bytes;
}

long int SocketClient::ReceivePacket(void recvHandler(char *msg))
{
    if (!isInitialized) {
        fprintf(stderr, "An error occurred during initialization, can't call function ReceivePacket");
        exit(-1);
    }
    cout << endl << endl << endl;
    char buf[BUF_LEN] = {0};

    long int num_bytes;
    sockaddr_in remoteEP;
    socklen_t remoteEpLength;

    num_bytes = recvfrom(this->socketFd, buf, sizeof(buf), 0, (sockaddr *) &remoteEP, &remoteEpLength);

    cout << "#DEBUG received:" << num_bytes << " bytes" << endl;

    // TODO Create a logger class, Check the sender is the server?

    // string info[2];
    // info[0] = (inet_ntoa(remoteEP.sin_addr));
    // info[1] = to_string(ntohs(remoteEP.sin_port));
    // cout << "Remote ip:" << info[0] << " Port:" << info[1] << endl;

    if (num_bytes == 0) {
        // TODO client closed connection
        return 0;
    } else if (num_bytes == -1) {
        // TODO Log error
        log_error("timeout");
        return -1;
    } else {
        // DEBUG
        cout << "Received " << num_bytes << " bytes" << endl;
        char redirectMessage[num_bytes + 1] = {0};
        strncpy(redirectMessage, buf, (unsigned int) num_bytes);
        redirectMessage[num_bytes] = '\0';

        close(this->socketFd);  // Close the welcome socket
        SwitchToRedirectedSocket(redirectMessage);
        recvHandler(buf);   // Fire the event
        SendPacket("REDIRECT SUCCESSFUL",
                (unsigned int) (sizeof(char) * (1 + strlen("REDIRECT_SUCCESSFUL"))));   // TEST
    }
    return num_bytes;
}

void SocketClient::SwitchToRedirectedSocket(char *message)
{
    string redirectMessage = string(message);
    redirectMessage.replace(0, strlen(WELCOME_HEADER), "");
    cout << "Redirect port:" << redirectMessage << endl;
    InitializeSocket((unsigned short) stoi(redirectMessage));
}

void SocketClient::InitializeSocket(const unsigned short serverPort)
{
    memset(&endpoint, 0, sizeof(endpoint));

    endpoint.sin_family = AF_INET;
    endpoint.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, this->serverAddr.c_str(), &endpoint.sin_addr) == -1) {
        log_error("Ip to network conversion");
    }
    if ((this->socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        log_error("socket creation");
    }


    timeval timeout;
    // Removing memset causes unidentified behaviour as the values are originally garbage
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = 3;

    if (setsockopt(this->socketFd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeval)) < 0) {
        log_error("set receive timeout");
    }
    if (setsockopt(this->socketFd, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeval)) < 0) {
        // Whatever we're sending might be locked, so a send timeout is set
        log_error("set send timeout");
    }
}

SocketClient::~SocketClient()
{
    if (!isInitialized) {
        return;
    }
    close(this->socketFd);
}