//
// Created by ahmed on 12/16/16.
//


#ifndef ENHANCEDUDPCLIENT_SOCKETCLIENT_H
#define ENHANCEDUDPCLIENT_SOCKETCLIENT_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <Packet.h>
#include <netinet/in.h>
#include <AddressInfo.h>
#include <RawUdpSocket.h>

using namespace std;

class ClientSocket
{
public:

    /**
    * Creates a new client socket that connects to the specified server address and port
    * @param server_addr Server Address
    * @param server_port Port of the server
    */
    ClientSocket(const string &server_addr, const unsigned short server_port);


    bool ReceiveDataPacket(unique_ptr<Packet> &data_pckt);

    ~ClientSocket();

    int InitFileRequest(string &handshake);

    void SendAckPacket(unsigned int seqno);

private:
    /**
    * Sends an array of bytes (unsigned char) to the server
    * @param data Message content to be sent
    * @return the number of bytes that were actually sent
    */
    void SendPacket(byte *data, unsigned int data_len);

    /**
     * This function receives only 1 packet, when an attempt is made to connect to the server
     * a handshake message is sent, then the server redirects the client to another port
     * if a receive operation times out, this function will report to the caller
     * @param recvHandler
     * @return
     */
    long ReceiveRaw(void **buf);

    bool is_disposed = false;

    void InitializeSocket(const unsigned short server_port);

    bool LogSockError(long num_bytes, string function_name);

    /**
     * File descriptor for the open socket
     */
    int socket_fd = 0;
    unsigned long int totalReceivedBytes = 0;
    bool is_initialized = false;
    sockaddr_in endpoint;
    string server_addr;
    unique_ptr<RawUdpSocket> socket;
    unique_ptr<AddressInfo> server_info;

    void log_error(const char *func_name);
};

#endif //ENHANCEDUDPCLIENT_SOCKETCLIENT_H
